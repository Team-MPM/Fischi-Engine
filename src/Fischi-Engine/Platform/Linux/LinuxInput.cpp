#include "Core/Core.h"
#ifdef FISCHI_PLATFORM_LINUX
#include "LinuxInput.h"
#include "Core/Log.h"

#include <X11/keysym.h>
#include <X11/X.h>

namespace FischiEngine {

    KeyCode LinuxInput::ParseX11KeyCode(int code) {
        switch (code)
        {
            case XK_Escape: return KeyCode::Escape;
            case XK_F1: return KeyCode::F1;
            case XK_F2: return KeyCode::F2;
            case XK_F3: return KeyCode::F3;
            case XK_F4: return KeyCode::F4;
            case XK_F5: return KeyCode::F5;
            case XK_F6: return KeyCode::F6;
            case XK_F7: return KeyCode::F7;
            case XK_F8: return KeyCode::F8;
            case XK_F9: return KeyCode::F9;
            case XK_F10: return KeyCode::F10;
            case XK_F11: return KeyCode::F11;
            case XK_F12: return KeyCode::F12;
            case XK_F13: return KeyCode::F13;
            case XK_F14: return KeyCode::F14;
            case XK_F15: return KeyCode::F15;
            case XK_F16: return KeyCode::F16;
            case XK_F17: return KeyCode::F17;
            case XK_F18: return KeyCode::F18;
            case XK_F19: return KeyCode::F19;
            case XK_F20: return KeyCode::F20;
            case XK_F21: return KeyCode::F21;
            case XK_F22: return KeyCode::F22;
            case XK_F23: return KeyCode::F23;
            case XK_F24: return KeyCode::F24;
            case XK_Print: return KeyCode::PrintScreen;
            case XK_Scroll_Lock: return KeyCode::ScrollLock;
            case XK_Pause: return KeyCode::Pause;
            case XK_Insert: return KeyCode::Insert;
            case XK_Home: return KeyCode::Home;
            case XK_Page_Up: return KeyCode::PageUp;
            case XK_Delete: return KeyCode::Delete;
            case XK_End: return KeyCode::End;
            case XK_Page_Down: return KeyCode::PageDown;
            case XK_Right: return KeyCode::Right;
            case XK_Left: return KeyCode::Left;
            case XK_Down: return KeyCode::Down;
            case XK_Up: return KeyCode::Up;
            case XK_Num_Lock: return KeyCode::NumLock;
            case XK_KP_Divide: return KeyCode::NumpadDivide;
            case XK_KP_Multiply: return KeyCode::NumpadMultiply;
            case XK_KP_Subtract: return KeyCode::NumpadSubtract;
            case XK_KP_Add: return KeyCode::NumpadAdd;
            case XK_KP_Enter: return KeyCode::NumpadEnter;
            case XK_Return: return KeyCode::Enter;
            case XK_ISO_Enter: return KeyCode::Enter;
            case XK_BackSpace: return KeyCode::Backspace;
            case XK_Tab: return KeyCode::Tab;
            case XK_Clear: return KeyCode::Clear;
            case XK_Shift_L: return KeyCode::LeftShift;
            case XK_Shift_R: return KeyCode::RightShift;
            case XK_Control_L: return KeyCode::LeftControl;
            case XK_Control_R: return KeyCode::RightControl;
            case XK_Alt_L:
            case XK_Menu: return KeyCode::Menu;
            case XK_Alt_R: return KeyCode::RightAlt;
            case XK_Caps_Lock: return KeyCode::CapsLock;
            case XK_space: return KeyCode::Space;
            case XK_Select: return KeyCode::Menu;
            case XK_Execute: return KeyCode::Execute;
            case XK_Help: return KeyCode::Help;
            case XK_0: return KeyCode::Num0;
            case XK_1: return KeyCode::Num1;
            case XK_2: return KeyCode::Num2;
            case XK_3: return KeyCode::Num3;
            case XK_4: return KeyCode::Num4;
            case XK_5: return KeyCode::Num5;
            case XK_6: return KeyCode::Num6;
            case XK_7: return KeyCode::Num7;
            case XK_8: return KeyCode::Num8;
            case XK_9: return KeyCode::Num9;
            case XK_a: return KeyCode::A;
            case XK_b: return KeyCode::B;
            case XK_c: return KeyCode::C;
            case XK_d: return KeyCode::D;
            case XK_e: return KeyCode::E;
            case XK_f: return KeyCode::F;
            case XK_g: return KeyCode::G;
            case XK_h: return KeyCode::H;
            case XK_i: return KeyCode::I;
            case XK_j: return KeyCode::J;
            case XK_k: return KeyCode::K;
            case XK_l: return KeyCode::L;
            case XK_m: return KeyCode::M;
            case XK_n: return KeyCode::N;
            case XK_o: return KeyCode::O;
            case XK_p: return KeyCode::P;
            case XK_q: return KeyCode::Q;
            case XK_r: return KeyCode::R;
            case XK_s: return KeyCode::S;
            case XK_t: return KeyCode::T;
            case XK_u: return KeyCode::U;
            case XK_v: return KeyCode::V;
            case XK_w: return KeyCode::W;
            case XK_x: return KeyCode::X;
            case XK_y: return KeyCode::Y;
            case XK_z: return KeyCode::Z;
            case XK_Super_L: return KeyCode::LeftSuper;
            case XK_Super_R: return KeyCode::RightSuper;
            case XK_KP_0: return KeyCode::Numpad0;
            case XK_KP_1: return KeyCode::Numpad1;
            case XK_KP_2: return KeyCode::Numpad2;
            case XK_KP_3: return KeyCode::Numpad3;
            case XK_KP_4: return KeyCode::Numpad4;
            case XK_KP_5: return KeyCode::Numpad5;
            case XK_KP_6: return KeyCode::Numpad6;
            case XK_KP_7: return KeyCode::Numpad7;
            case XK_KP_8: return KeyCode::Numpad8;
            case XK_KP_9: return KeyCode::Numpad9;
            case XK_KP_Separator: return KeyCode::Separator;
            case XK_bracketleft: return KeyCode::LeftBracket;
            case XK_bracketright: return KeyCode::RightBracket;
            case XK_semicolon: return KeyCode::Semicolon;
            default: Log::Error("Unknown key code: ", code);
                return KeyCode::Unknown;
        }
    }

    KeyCode LinuxInput::ParseWaylandKeyCode(int code) {
        return KeyCode::Unknown;
    }
}

#endif