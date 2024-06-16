#pragma once

namespace FischiEngine
{
    enum class KeyCode
    {
        Unknown = -1,
        F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12,
        F13, F14, F15, F16, F17, F18, F19, F20, F21, F22, F23, F24,
        Escape, PrintScreen, ScrollLock, Pause, Insert, Home, PageUp,
        Delete, End, PageDown, Right, Left, Down, Up, Help, Apps, Separator,
        NumLock, NumpadDivide, NumpadMultiply, NumpadSubtract, NumpadAdd,
        NumpadEnter, Numpad1, Numpad2, Numpad3, Numpad4, Numpad5, Numpad6,
        Numpad7, Numpad8, Numpad9, Numpad0, NumpadDecimal, NumpadEqual,
        LeftShift, LeftControl, LeftAlt, LeftSuper, RightShift, RightControl,
        RightAlt, RightSuper, Menu, Apostrophe, Comma, Minus, Period, Slash,
        Semicolon, Equal, LeftBracket, Backslash, RightBracket, GraveAccent,
        World1, World2, Space, Enter, Tab, Backspace, CapsLock, Clear, Execute,
        Num0, Num1, Num2, Num3, Num4, Num5, Num6, Num7, Num8, Num9,
        A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
        OEM1, OEM2, OEM3, OEM4, OEM5, OEM6, OEM7, OEM8, OEM102
    };

    enum class MouseButton
    {
        Left,
        Right,
        Middle,
        XButton1,
        XButton2
    };
}
