#include "mirpch.h"
#include "Miriya/Core/Application.h"

#include "Miriya/Core/Log.h"

#include "Miriya/Renderer/Renderer.h"

#include "Miriya/Core/Input.h"

#include <GLFW/glfw3.h>

namespace Miriya {

Application* Application::s_Instance = nullptr;

Application::Application(const std::string& name)
{
    MIR_PROFILE_FUNCTION();

    MIR_CORE_ASSERT(!s_Instance, "Application already exists!");
    s_Instance = this;

    // b/c it's an explicit constructor, we need to type unique ptr
    // unique_ptr means no need to delete the window manually when terminate
    // window since application is obviously a singleton
    m_Window = Window::Create(WindowProps(name));
    m_Window->SetEventCallback(MIR_BIND_EVENT_FN(Application::OnEvent));

    Renderer::Init();

    m_ImGuiLayer = new ImGuiLayer();
    PushOverlay(m_ImGuiLayer);
}

Application::~Application() = default;

void Application::PushLayer(Layer* layer)
{
    MIR_PROFILE_FUNCTION();

    m_LayerStack.PushLayer(layer);
    layer->OnAttach();
}

void Application::PushOverlay(Layer* layer)
{
    MIR_PROFILE_FUNCTION();

    m_LayerStack.PushOverlay(layer);
    layer->OnAttach();
}

void Application::Close()
{
    m_Running = false;
}

void Application::OnEvent(Event& e)
{
    MIR_PROFILE_FUNCTION();

    EventDispatcher dispatcher(e);
    dispatcher.Dispatch<WindowCloseEvent>(MIR_BIND_EVENT_FN(Application::OnWindowClose));
    dispatcher.Dispatch<WindowResizeEvent>(MIR_BIND_EVENT_FN(Application::OnWindowResize));

    // reverse iterator
    for (auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); ++it) {
        // go backwards stack
        (*it)->OnEvent(e);
        if (e.Handled) break;
    }
}

void Application::Run()
{
    MIR_PROFILE_FUNCTION();

    while (m_Running) {
        // main application loop
        MIR_PROFILE_SCOPE("RunLoop");

        float    time     = static_cast<float>(glfwGetTime());   // TODO: Platform::GetTime()
        Timestep timestep = time - m_LastFrameTime;
        m_LastFrameTime   = time;

        if (!m_Minimized) {
            {
                MIR_PROFILE_SCOPE("LayerStack OnUpdate");

                for (Layer* layer : m_LayerStack) {
                    layer->OnUpdate(timestep);
                }
            }

            // TODO: do on render thread
            m_ImGuiLayer->Begin();
            {
                MIR_PROFILE_SCOPE("LayerStack OnImGuiRender");

                for (Layer* layer : m_LayerStack) {
                    layer->OnImGuiRender();
                }
            }
            m_ImGuiLayer->End();
        }

        m_Window->OnUpdate();
    }
}

bool Application::OnWindowResize(WindowResizeEvent& e)
{
    MIR_PROFILE_FUNCTION();

    if (e.GetWidth() == 0 || e.GetHeight() == 0) {
        m_Minimized = true;
        return false;
    }

    m_Minimized = false;
    Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());

    return false;
}

bool Application::OnWindowClose(WindowCloseEvent& e)
{
    m_Running = false;
    return true;
}
}   // namespace Miriya
