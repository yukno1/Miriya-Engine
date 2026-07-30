#pragma once

#include "Miriya/Core/Keycode.h"
#include "Miriya/Core/MouseCode.h"

#include <glm/glm.hpp>

namespace Miriya {
class Input
{
public:
    static bool      IsKeyPressed(KeyCode key);
    static bool      IsMouseButtonPressed(MouseCode button);
    static glm::vec2 GetMousePosition();
    static float     GetMouseX();
    static float     GetMouseY();
};

}   // namespace Miriya
