#include "Application.h"
#include "mirpch.h"

#include "Log.h"

#include "Miriya/Renderer/Renderer.h"

#include "Input.h"

#include <GLFW/glfw3.h>

namespace Miriya {
#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

Application* Application::s_Instance = nullptr;

Application::Application()
{
    MIR_PROFILE_FUNCTION();

    MIR_CORE_ASSERT(!s_Instance, "Application already exists!");
    s_Instance = this;

    // b/c it's an explicit constructor, we need to type unique ptr
    // unique_ptr means no need to delete the window manually when terminate
    // window since application is obviously a singleton
    m_Window = std::unique_ptr<Window>(Window::Create());
    m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));

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

void Application::OnEvent(Event& e)
{
    MIR_PROFILE_FUNCTION();

    EventDispatcher dispatcher(e);
    dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));
    dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(OnWindowResize));

    for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();) {
        // go backwards stack
        (*--it)->OnEvent(e);
        if (e.Handled) break;
    }
}

void Application::Run()
{
    MIR_PROFILE_FUNCTION();

    while (m_Running) {
        // main application loop
        MIR_PROFILE_SCOPE("RunLoop");

        auto     time     = static_cast<float>(glfwGetTime());   // TODO: Platform::GetTime()
        Timestep timestep = time - m_LastFrameTime;
        m_LastFrameTime   = time;

        if (!m_Minimized) {
            {
                MIR_PROFILE_SCOPE("LayerStack OnUpdate");

                for (Layer* layer : m_LayerStack) layer->OnUpdate(timestep);
            }

            // TODO: do on render thread
            m_ImGuiLayer->Begin();
            {
                MIR_PROFILE_SCOPE("LayerStack OnImGuiRender");

                for (Layer* layer : m_LayerStack) layer->OnImGuiRender();
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
