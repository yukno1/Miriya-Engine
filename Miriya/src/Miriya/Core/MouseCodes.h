#pragma once

namespace Miriya {
typedef enum class MouseCode : uint16_t
{
    // From glfw3.h
    Button0 = 0,
    Button1 = 1,
    Button2 = 2,
    Button3 = 3,
    Button4 = 4,
    Button5 = 5,
    Button6 = 6,
    Button7 = 7,

    ButtonLast   = Button7,
    ButtonLeft   = Button0,
    ButtonRight  = Button1,
    ButtonMiddle = Button2
} Mouse;

inline std::ostream& operator<<(std::ostream& os, MouseCode mouseCode)
{
    os << static_cast<int32_t>(mouseCode);
    return os;
}
}   // namespace Miriya

// FROM glfw3.h
#define MIR_MOUSE_BUTTON_0 ::Miriya::Mouse::Button0
#define MIR_MOUSE_BUTTON_1 ::Miriya::Mouse::Button1
#define MIR_MOUSE_BUTTON_2 ::Miriya::Mouse::Button2
#define MIR_MOUSE_BUTTON_3 ::Miriya::Mouse::Button3
#define MIR_MOUSE_BUTTON_4 ::Miriya::Mouse::Button4
#define MIR_MOUSE_BUTTON_5 ::Miriya::Mouse::Button5
#define MIR_MOUSE_BUTTON_6 ::Miriya::Mouse::Button6
#define MIR_MOUSE_BUTTON_7 ::Miriya::Mouse::Button7
#define MIR_MOUSE_BUTTON_LAST ::Miriya::Mouse::ButtonLast
#define MIR_MOUSE_BUTTON_LEFT ::Miriya::Mouse::ButtonLeft
#define MIR_MOUSE_BUTTON_RIGHT ::Miriya::Mouse::ButtonRight
#define MIR_MOUSE_BUTTON_MIDDLE ::Miriya::Mouse::ButtonMiddle