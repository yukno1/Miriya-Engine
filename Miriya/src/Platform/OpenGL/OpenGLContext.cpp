#include "mirpch.h"
#include "OpenGLContext.h"

#include "glad/gl.h"
#include <GLFW/glfw3.h>

namespace Miriya {

OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
    : m_WindowHandle(windowHandle)
{
    MIR_CORE_ASSERT(windowHandle, "windowHandle is null!");
}

void OpenGLContext::Init()
{
    MIR_PROFILE_FUNCTION();

    glfwMakeContextCurrent(m_WindowHandle);
    int status = gladLoadGL(glfwGetProcAddress);
    MIR_CORE_ASSERT(status, "Failed to initialize GLAD!");


    MIR_CORE_INFO("OpenGL Info:");
    MIR_CORE_INFO("  Vendor: {0}", (const char*)glGetString(GL_VENDOR));
    MIR_CORE_INFO("  Renderer: {0}", (const char*)glGetString(GL_RENDERER));
    MIR_CORE_INFO("  Version: {0}", (const char*)glGetString(GL_VERSION));

    int versionMajor = 0;
    int versionMinor = 0;
    glGetIntegerv(GL_MAJOR_VERSION, &versionMajor);
    glGetIntegerv(GL_MINOR_VERSION, &versionMinor);

    MIR_CORE_ASSERT(versionMajor > 4 || (versionMajor == 4 && versionMinor >= 5),
                    "Hazel requires at least OpenGL version 4.5!");
}

void OpenGLContext::SwapBuffers()
{
    MIR_PROFILE_FUNCTION();

    glfwSwapBuffers(m_WindowHandle);
}
}   // namespace Miriya
