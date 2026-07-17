#include "mirpch.h"
#include "WindowsWindow.h"

#include "../../Miriya/Core/Log.h"
#include "Miriya/Events/ApplicationEvent.h"
#include "Miriya/Events/MouseEvent.h"
#include "Miriya/Events/KeyEvent.h"

#include "Platform/OpenGL/OpenGLContext.h"

// #include "glad/gl.h"
#include <GLFW/glfw3.h>

namespace Miriya {

static bool    s_GLFWInitialized = false;
static uint8_t s_GLFWWindowCount = 0;

static void GLFWErrorCallback(int error, const char* description)
{
    MIR_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
}

WindowsWindow::WindowsWindow(const WindowProps& props)
{
    MIR_PROFILE_FUNCTION();

    Init(props);
}

WindowsWindow::~WindowsWindow()
{
    MIR_PROFILE_FUNCTION();

    WindowsWindow::Shutdown();
}

void WindowsWindow::Init(const WindowProps& props)
{
    MIR_PROFILE_FUNCTION();

    m_Data.Title  = props.Title;
    m_Data.Width  = props.Width;
    m_Data.Height = props.Height;

    MIR_CORE_INFO("Creating window {0}, ({1}, {2})", props.Title, props.Width, props.Height);

    if (s_GLFWWindowCount == 0) {
        // TODO: glfwTerminate on system shutdown
        MIR_PROFILE_SCOPE("glfwInit");

        int success = glfwInit();   // want glfw to initialize

        MIR_CORE_ASSERT(success, "Could not initialize GLFW!");
        glfwSetErrorCallback([](int error, const char* description) {
            MIR_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
        });
        // glfwSetErrorCallback(GLFWErrorCallback);
    }

    {
        MIR_PROFILE_SCOPE("glfwCreateWindow");
        m_Window = glfwCreateWindow(static_cast<int>(props.Width),
                                    static_cast<int>(props.Height),
                                    m_Data.Title.c_str(),
                                    nullptr,
                                    nullptr);
        ++s_GLFWWindowCount;
    }

    m_Context = CreateScope<OpenGLContext>(m_Window);
    m_Context->Init();

    glfwSetWindowUserPointer(m_Window, &m_Data);
    SetVSync(true);

    // set glfw callback
    glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) {
        WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
        data.Width       = width;
        data.Height      = height;

        WindowResizeEvent event(width, height);
        data.EventCallback(event);
    });

    glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) {
        WindowData&      data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
        WindowCloseEvent event;
        data.EventCallback(event);
    });

    glfwSetKeyCallback(
        m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
            WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

            switch (action) {
            case GLFW_PRESS:
            {
                KeyPressedEvent event(key, 0);
                data.EventCallback(event);
                break;
            }
            case GLFW_RELEASE:
            {
                KeyReleasedEvent event(key);
                data.EventCallback(event);
                break;
            }
            case GLFW_REPEAT:
            {
                KeyPressedEvent event(key, 1);
                data.EventCallback(event);
                break;
            }
            }
        });

    glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int keycode) {
        WindowData&   data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
        KeyTypedEvent event(keycode);
        data.EventCallback(event);
    });

    glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods) {
        WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

        switch (action) {
        case GLFW_PRESS:
        {
            MouseButtonPressedEvent event(button);
            data.EventCallback(event);
            break;
        }
        case GLFW_RELEASE:
        {
            MouseButtonReleasedEvent event(button);
            data.EventCallback(event);
            break;
        }
        }
    });

    glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset) {
        WindowData&        data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
        MouseScrolledEvent event(static_cast<float>(xOffset), static_cast<float>(yOffset));
        data.EventCallback(event);
    });

    glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos) {
        WindowData&     data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
        MouseMovedEvent event(static_cast<float>(xPos), static_cast<float>(yPos));
        data.EventCallback(event);
    });
}


void WindowsWindow::Shutdown()
{
    MIR_PROFILE_FUNCTION();

    glfwDestroyWindow(m_Window);
    --s_GLFWWindowCount;

    if (s_GLFWWindowCount == 0) {
        glfwTerminate();
    }
}

void WindowsWindow::OnUpdate()
{
    MIR_PROFILE_FUNCTION();

    glfwPollEvents();
    m_Context->SwapBuffers();
}

void WindowsWindow::SetVSync(bool enabled)
{
    MIR_PROFILE_FUNCTION();

    if (enabled) {
        glfwSwapInterval(1);
    }
    else {
        glfwSwapInterval(0);
    }

    m_Data.VSync = enabled;
}

bool WindowsWindow::IsVSync() const
{
    return m_Data.VSync;
}
}   // namespace Miriya
