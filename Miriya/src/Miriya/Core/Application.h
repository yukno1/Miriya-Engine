#pragma once

#include "Base.h"

#include "Window.h"
#include "LayerStack.h"
#include "Miriya/Events/Event.h"
#include "Miriya/Events/ApplicationEvent.h"

// #include "Miriya/Core/Timestep.h"

#include "Miriya/ImGui/ImGuiLayer.h"

namespace Miriya {

struct ApplicationCommandLineArgs
{
    int    Count = 0;
    char** Args  = nullptr;

    const char* operator[](int index) const
    {
        MIR_CORE_ASSERT(index < Count);
        return Args[index];
    }
};

class Application
{
public:
    Application(const std::string&         name = "Miriya App",
                ApplicationCommandLineArgs args = ApplicationCommandLineArgs());
    virtual ~Application();

    void Run();

    void OnEvent(Event& e);

    void PushLayer(Layer* layer);
    void PushOverlay(Layer* overlay);

    inline Window& GetWindow() { return *m_Window; }

    void Close();

    ImGuiLayer* GetImGuiLayer() { return m_ImGuiLayer; }

    static Application& Get() { return *s_Instance; }

    ApplicationCommandLineArgs GetCommandLineArgs() const { return m_CommandLineArgs; }

private:
    bool OnWindowClose(WindowCloseEvent& e);
    bool OnWindowResize(WindowResizeEvent& e);

private:
    ApplicationCommandLineArgs m_CommandLineArgs;
    std::unique_ptr<Window>    m_Window;
    // imgui layer automatically added by Miriya runtime
    ImGuiLayer* m_ImGuiLayer;

    bool       m_Running   = true;
    bool       m_Minimized = false;
    LayerStack m_LayerStack;

    // Timestep m_Timestep;
    float m_LastFrameTime = 0.0f;

    static Application* s_Instance;
};

// To be defined in client
Application* CreateApplication(ApplicationCommandLineArgs args);
}   // namespace Miriya
