#pragma once

#include "Miriya/Core/Base.h"

namespace Miriya {
class Input
{
public:
    static bool                    IsKeyPressed(int keycode);
    static bool                    IsMouseButtonPressed(int button);
    static std::pair<float, float> GetMousePosition();
    static float                   GetMouseX();
    static float                   GetMouseY();

    // protected:
    //     // Interface depends on platform
    //     virtual bool                    IsKeyPressedImpl(int keycode)        = 0;
    //     virtual bool                    IsMouseButtonPressedImpl(int button) = 0;
    //     virtual std::pair<float, float> GetMousePositionImpl()               = 0;
    //     virtual float                   GetMouseXImpl()                      = 0;
    //     virtual float                   GetMouseYImpl()                      = 0;

    // private:
    //     // singleton
    //     // global, not belong to this class
    //     static Scope<Input> s_Instance;
};

}   // namespace Miriya
