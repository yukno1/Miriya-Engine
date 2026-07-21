#pragma once

namespace Miriya {
typedef enum class KeyCode : uint16_t
{
    // From glfw3.h
    Space      = 32,
    Apostrophe = 39, /* ' */
    Comma      = 44, /* , */
    Minus      = 45, /* - */
    Period     = 46, /* . */
    Slash      = 47, /* / */

    D0 = 48, /* 0 */
    D1 = 49, /* 1 */
    D2 = 50, /* 2 */
    D3 = 51, /* 3 */
    D4 = 52, /* 4 */
    D5 = 53, /* 5 */
    D6 = 54, /* 6 */
    D7 = 55, /* 7 */
    D8 = 56, /* 8 */
    D9 = 57, /* 9 */

    Semicolon = 59, /* ; */
    Equal     = 61, /* = */

    A = 65,
    B = 66,
    C = 67,
    D = 68,
    E = 69,
    F = 70,
    G = 71,
    H = 72,
    I = 73,
    J = 74,
    K = 75,
    L = 76,
    M = 77,
    N = 78,
    O = 79,
    P = 80,
    Q = 81,
    R = 82,
    S = 83,
    T = 84,
    U = 85,
    V = 86,
    W = 87,
    X = 88,
    Y = 89,
    Z = 90,

    LeftBracket  = 91, /* [ */
    Backslash    = 92, /* \ */
    RightBracket = 93, /* ] */
    GraveAccent  = 96, /* ` */

    World1 = 161, /* non-US #1 */
    World2 = 162, /* non-US #2 */

    /* Function keys */
    Escape      = 256,
    Enter       = 257,
    Tab         = 258,
    Backspace   = 259,
    Insert      = 260,
    Delete      = 261,
    Right       = 262,
    Left        = 263,
    Down        = 264,
    Up          = 265,
    PageUp      = 266,
    PageDown    = 267,
    Home        = 268,
    End         = 269,
    CapsLock    = 280,
    ScrollLock  = 281,
    NumLock     = 282,
    PrintScreen = 283,
    Pause       = 284,
    F1          = 290,
    F2          = 291,
    F3          = 292,
    F4          = 293,
    F5          = 294,
    F6          = 295,
    F7          = 296,
    F8          = 297,
    F9          = 298,
    F10         = 299,
    F11         = 300,
    F12         = 301,
    F13         = 302,
    F14         = 303,
    F15         = 304,
    F16         = 305,
    F17         = 306,
    F18         = 307,
    F19         = 308,
    F20         = 309,
    F21         = 310,
    F22         = 311,
    F23         = 312,
    F24         = 313,
    F25         = 314,

    /* Keypad */
    KP0        = 320,
    KP1        = 321,
    KP2        = 322,
    KP3        = 323,
    KP4        = 324,
    KP5        = 325,
    KP6        = 326,
    KP7        = 327,
    KP8        = 328,
    KP9        = 329,
    KPDecimal  = 330,
    KPDivide   = 331,
    KPMultiply = 332,
    KPSubtract = 333,
    KPAdd      = 334,
    KPEnter    = 335,
    KPEqual    = 336,

    LeftShift    = 340,
    LeftControl  = 341,
    LeftAlt      = 342,
    LeftSuper    = 343,
    RightShift   = 344,
    RightControl = 345,
    RightAlt     = 346,
    RightSuper   = 347,
    Menu         = 348
} Key;

inline std::ostream& operator<<(std::ostream& os, KeyCode keyCode)
{
    os << static_cast<int32_t>(keyCode);
    return os;
}

}   // namespace Miriya


// From glfw3.h
#define MIR_KEY_SPACE ::Miriya::Key::Space
#define MIR_KEY_APOSTROPHE ::Miriya::Key::Apostrophe /* ' */
#define MIR_KEY_COMMA ::Miriya::Key::Comma           /* , */
#define MIR_KEY_MINUS ::Miriya::Key::Minus           /* - */
#define MIR_KEY_PERIOD ::Miriya::Key::Period         /* . */
#define MIR_KEY_SLASH ::Miriya::Key::Slash           /* / */
#define MIR_KEY_0 ::Miriya::Key::D0
#define MIR_KEY_1 ::Miriya::Key::D1
#define MIR_KEY_2 ::Miriya::Key::D2
#define MIR_KEY_3 ::Miriya::Key::D3
#define MIR_KEY_4 ::Miriya::Key::D4
#define MIR_KEY_5 ::Miriya::Key::D5
#define MIR_KEY_6 ::Miriya::Key::D6
#define MIR_KEY_7 ::Miriya::Key::D7
#define MIR_KEY_8 ::Miriya::Key::D8
#define MIR_KEY_9 ::Miriya::Key::D9
#define MIR_KEY_SEMICOLON ::Miriya::Key::Semicolon /* ; */
#define MIR_KEY_EQUAL ::Miriya::Key::Equal         /* = */
#define MIR_KEY_A ::Miriya::Key::A
#define MIR_KEY_B ::Miriya::Key::B
#define MIR_KEY_C ::Miriya::Key::C
#define MIR_KEY_D ::Miriya::Key::D
#define MIR_KEY_E ::Miriya::Key::E
#define MIR_KEY_F ::Miriya::Key::F
#define MIR_KEY_G ::Miriya::Key::G
#define MIR_KEY_H ::Miriya::Key::H
#define MIR_KEY_I ::Miriya::Key::I
#define MIR_KEY_J ::Miriya::Key::J
#define MIR_KEY_K ::Miriya::Key::K
#define MIR_KEY_L ::Miriya::Key::L
#define MIR_KEY_M ::Miriya::Key::M
#define MIR_KEY_N ::Miriya::Key::N
#define MIR_KEY_O ::Miriya::Key::O
#define MIR_KEY_P ::Miriya::Key::P
#define MIR_KEY_Q ::Miriya::Key::Q
#define MIR_KEY_R ::Miriya::Key::R
#define MIR_KEY_S ::Miriya::Key::S
#define MIR_KEY_T ::Miriya::Key::T
#define MIR_KEY_U ::Miriya::Key::U
#define MIR_KEY_V ::Miriya::Key::V
#define MIR_KEY_W ::Miriya::Key::W
#define MIR_KEY_X ::Miriya::Key::X
#define MIR_KEY_Y ::Miriya::Key::Y
#define MIR_KEY_Z ::Miriya::Key::Z
#define MIR_KEY_LEFT_BRACKET ::Miriya::Key::LeftBracket   /* [ */
#define MIR_KEY_BACKSLASH ::Miriya::Key::Backslash        /* \ */
#define MIR_KEY_RIGHT_BRACKET ::Miriya::Key::RightBracket /* ] */
#define MIR_KEY_GRAVE_ACCENT ::Miriya::Key::GraveAccent   /* ` */
#define MIR_KEY_WORLD_1 ::Miriya::Key::World1             /* non-US #1 */
#define MIR_KEY_WORLD_2 ::Miriya::Key::World2             /* non-US #2 */

/* Function keys */
#define MIR_KEY_ESCAPE ::Miriya::Key::Escape
#define MIR_KEY_ENTER ::Miriya::Key::Enter
#define MIR_KEY_TAB ::Miriya::Key::Tab
#define MIR_KEY_BACKSPACE ::Miriya::Key::Backspace
#define MIR_KEY_INSERT ::Miriya::Key::Insert
#define MIR_KEY_DELETE ::Miriya::Key::Delete
#define MIR_KEY_RIGHT ::Miriya::Key::Right
#define MIR_KEY_LEFT ::Miriya::Key::Left
#define MIR_KEY_DOWN ::Miriya::Key::Down
#define MIR_KEY_UP ::Miriya::Key::Up
#define MIR_KEY_PAGE_UP ::Miriya::Key::PageUp
#define MIR_KEY_PAGE_DOWN ::Miriya::Key::PageDown
#define MIR_KEY_HOME ::Miriya::Key::Home
#define MIR_KEY_END ::Miriya::Key::End
#define MIR_KEY_CAPS_LOCK ::Miriya::Key::CapsLock
#define MIR_KEY_SCROLL_LOCK ::Miriya::Key::ScrollLock
#define MIR_KEY_NUM_LOCK ::Miriya::Key::NumLock
#define MIR_KEY_PRINT_SCREEN ::Miriya::Key::PrintScreen
#define MIR_KEY_PAUSE ::Miriya::Key::Pause
#define MIR_KEY_F1 ::Miriya::Key::F1
#define MIR_KEY_F2 ::Miriya::Key::F2
#define MIR_KEY_F3 ::Miriya::Key::F3
#define MIR_KEY_F4 ::Miriya::Key::F4
#define MIR_KEY_F5 ::Miriya::Key::F5
#define MIR_KEY_F6 ::Miriya::Key::F6
#define MIR_KEY_F7 ::Miriya::Key::F7
#define MIR_KEY_F8 ::Miriya::Key::F8
#define MIR_KEY_F9 ::Miriya::Key::F9
#define MIR_KEY_F10 ::Miriya::Key::F10
#define MIR_KEY_F11 ::Miriya::Key::F11
#define MIR_KEY_F12 ::Miriya::Key::F12
#define MIR_KEY_F13 ::Miriya::Key::F13
#define MIR_KEY_F14 ::Miriya::Key::F14
#define MIR_KEY_F15 ::Miriya::Key::F15
#define MIR_KEY_F16 ::Miriya::Key::F16
#define MIR_KEY_F17 ::Miriya::Key::F17
#define MIR_KEY_F18 ::Miriya::Key::F18
#define MIR_KEY_F19 ::Miriya::Key::F19
#define MIR_KEY_F20 ::Miriya::Key::F20
#define MIR_KEY_F21 ::Miriya::Key::F21
#define MIR_KEY_F22 ::Miriya::Key::F22
#define MIR_KEY_F23 ::Miriya::Key::F23
#define MIR_KEY_F24 ::Miriya::Key::F24
#define MIR_KEY_F25 ::Miriya::Key::F25

/* Keypad */
#define MIR_KEY_KP_0 ::Miriya::Key::KP0
#define MIR_KEY_KP_1 ::Miriya::Key::KP1
#define MIR_KEY_KP_2 ::Miriya::Key::KP2
#define MIR_KEY_KP_3 ::Miriya::Key::KP3
#define MIR_KEY_KP_4 ::Miriya::Key::KP4
#define MIR_KEY_KP_5 ::Miriya::Key::KP5
#define MIR_KEY_KP_6 ::Miriya::Key::KP6
#define MIR_KEY_KP_7 ::Miriya::Key::KP7
#define MIR_KEY_KP_8 ::Miriya::Key::KP8
#define MIR_KEY_KP_9 ::Miriya::Key::KP9
#define MIR_KEY_KP_DECIMAL ::Miriya::Key::KPDecimal
#define MIR_KEY_KP_DIVIDE ::Miriya::Key::KPDivide
#define MIR_KEY_KP_MULTIPLY ::Miriya::Key::KPMultiply
#define MIR_KEY_KP_SUBTRACT ::Miriya::Key::KPSubtract
#define MIR_KEY_KP_ADD ::Miriya::Key::KPAdd
#define MIR_KEY_KP_ENTER ::Miriya::Key::KPEnter
#define MIR_KEY_KP_EQUAL ::Miriya::Key::KPEqual

#define MIR_KEY_LEFT_SHIFT ::Miriya::Key::LeftShift
#define MIR_KEY_LEFT_CONTROL ::Miriya::Key::LeftControl
#define MIR_KEY_LEFT_ALT ::Miriya::Key::LeftAlt
#define MIR_KEY_LEFT_SUPER ::Miriya::Key::LeftSuper
#define MIR_KEY_RIGHT_SHIFT ::Miriya::Key::RightShift
#define MIR_KEY_RIGHT_CONTROL ::Miriya::Key::RightControl
#define MIR_KEY_RIGHT_ALT ::Miriya::Key::RightAlt
#define MIR_KEY_RIGHT_SUPER ::Miriya::Key::RightSuper
#define MIR_KEY_MENU ::Miriya::Key::Menu
