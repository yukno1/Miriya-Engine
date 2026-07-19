#include "mirpch.h"
#include "Miriya/Core/Input.h"

#include <GLFW/glfw3.h>
#include "Miriya/Core/Application.h"

namespace Miriya {

// Scope<Input> Input::s_Instance = CreateScope<WindowsInput>();

bool Input::IsKeyPressed(int keycode)
{
    auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
    auto state  = glfwGetKey(window, keycode);
    return state == GLFW_PRESS || state == GLFW_REPEAT;
}

bool Input::IsMouseButtonPressed(int button)
{
    auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
    auto state  = glfwGetMouseButton(window, button);
    return state == GLFW_PRESS;
}

std::pair<float, float> Input::GetMousePosition()
{
    auto   window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    return {static_cast<float>(xpos), static_cast<float>(ypos)};
}

float Input::GetMouseX()
{
    auto [xpos, ypos] = GetMousePosition();
    return xpos;
}

float Input::GetMouseY()
{
    auto [xpos, ypos] = GetMousePosition();
    return ypos;
}
}   // namespace Miriya
