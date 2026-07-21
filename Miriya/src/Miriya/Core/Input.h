#pragma once

#include "Miriya/Core/Base.h"
#include "Miriya/Core/Keycodes.h"
#include "Miriya/Core/MouseCodes.h"

namespace Miriya {
class Input
{
public:
    static bool                    IsKeyPressed(KeyCode key);
    static bool                    IsMouseButtonPressed(MouseCode button);
    static std::pair<float, float> GetMousePosition();
    static float                   GetMouseX();
    static float                   GetMouseY();
};

}   // namespace Miriya
