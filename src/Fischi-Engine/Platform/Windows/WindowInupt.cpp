#include "Core/Core.h"
#ifdef FISCHI_PLATFORM_WINDOWS
#include "WindowInupt.h"

#include "Core/Log.h"

namespace FischiEngine
{
    KeyCode WindowInupt::TranslateKeyCode(WPARAM wParam)
    {
        switch (wParam)
        {
        case VK_ESCAPE: return KeyCode::Escape;
        case VK_F1: return KeyCode::F1;
        case VK_F2: return KeyCode::F2;
        case VK_F3: return KeyCode::F3;
        case VK_F4: return KeyCode::F4;
        case VK_F5: return KeyCode::F5;
        case VK_F6: return KeyCode::F6;
        case VK_F7: return KeyCode::F7;
        case VK_F8: return KeyCode::F8;
        case VK_F9: return KeyCode::F9;
        case VK_F10: return KeyCode::F10;
        case VK_F11: return KeyCode::F11;
        case VK_F12: return KeyCode::F12;
        case VK_F13: return KeyCode::F13;
        case VK_F14: return KeyCode::F14;
        case VK_F15: return KeyCode::F15;
        case VK_F16: return KeyCode::F16;
        case VK_F17: return KeyCode::F17;
        case VK_F18: return KeyCode::F18;
        case VK_F19: return KeyCode::F19;
        case VK_F20: return KeyCode::F20;
        case VK_F21: return KeyCode::F21;
        case VK_F22: return KeyCode::F22;
        case VK_F23: return KeyCode::F23;
        case VK_F24: return KeyCode::F24;
        case VK_SNAPSHOT: return KeyCode::PrintScreen;
        case VK_SCROLL: return KeyCode::ScrollLock;
        case VK_PAUSE: return KeyCode::Pause;
        case VK_INSERT: return KeyCode::Insert;
        case VK_HOME: return KeyCode::Home;
        case VK_PRIOR: return KeyCode::PageUp;
        case VK_DELETE: return KeyCode::Delete;
        case VK_END: return KeyCode::End;
        case VK_NEXT: return KeyCode::PageDown;
        case VK_RIGHT: return KeyCode::Right;
        case VK_LEFT: return KeyCode::Left;
        case VK_DOWN: return KeyCode::Down;
        case VK_UP: return KeyCode::Up;
        case VK_NUMLOCK: return KeyCode::NumLock;
        case VK_DIVIDE: return KeyCode::NumpadDivide;
        case VK_MULTIPLY: return KeyCode::NumpadMultiply;
        case VK_SUBTRACT: return KeyCode::NumpadSubtract;
        case VK_ADD: return KeyCode::NumpadAdd;
        case VK_RETURN: return KeyCode::NumpadEnter;
        case VK_BACK: return KeyCode::Backspace;
        case VK_TAB: return KeyCode::Tab;
        case VK_CLEAR: return KeyCode::Clear;
        case VK_SHIFT: return KeyCode::LeftShift;
        case VK_CONTROL: return KeyCode::LeftControl;
        case VK_MENU: return KeyCode::LeftAlt;
        case VK_CAPITAL: return KeyCode::CapsLock;
        case VK_SPACE: return KeyCode::Space;
        case VK_SELECT: return KeyCode::Menu;
        case VK_PRINT: return KeyCode::PrintScreen;
        case VK_EXECUTE: return KeyCode::Execute;
        case VK_HELP: return KeyCode::Help;
        case 0x30: return KeyCode::Num0;
        case 0x31: return KeyCode::Num1;
        case 0x32: return KeyCode::Num2;
        case 0x33: return KeyCode::Num3;
        case 0x34: return KeyCode::Num4;
        case 0x35: return KeyCode::Num5;
        case 0x36: return KeyCode::Num6;
        case 0x37: return KeyCode::Num7;
        case 0x38: return KeyCode::Num8;
        case 0x39: return KeyCode::Num9;
        case 0x41: return KeyCode::A;
        case 0x42: return KeyCode::B;
        case 0x43: return KeyCode::C;
        case 0x44: return KeyCode::D;
        case 0x45: return KeyCode::E;
        case 0x46: return KeyCode::F;
        case 0x47: return KeyCode::G;
        case 0x48: return KeyCode::H;
        case 0x49: return KeyCode::I;
        case 0x4A: return KeyCode::J;
        case 0x4B: return KeyCode::K;
        case 0x4C: return KeyCode::L;
        case 0x4D: return KeyCode::M;
        case 0x4E: return KeyCode::N;
        case 0x4F: return KeyCode::O;
        case 0x50: return KeyCode::P;
        case 0x51: return KeyCode::Q;
        case 0x52: return KeyCode::R;
        case 0x53: return KeyCode::S;
        case 0x54: return KeyCode::T;
        case 0x55: return KeyCode::U;
        case 0x56: return KeyCode::V;
        case 0x57: return KeyCode::W;
        case 0x58: return KeyCode::X;
        case 0x59: return KeyCode::Y;
        case 0x5A: return KeyCode::Z;
        case VK_LWIN: return KeyCode::LeftSuper;
        case VK_RWIN: return KeyCode::RightSuper;
        case VK_APPS: return KeyCode::Apps;
        case VK_SLEEP: return KeyCode::Unknown;
        case VK_NUMPAD0: return KeyCode::Numpad0;
        case VK_NUMPAD1: return KeyCode::Numpad1;
        case VK_NUMPAD2: return KeyCode::Numpad2;
        case VK_NUMPAD3: return KeyCode::Numpad3;
        case VK_NUMPAD4: return KeyCode::Numpad4;
        case VK_NUMPAD5: return KeyCode::Numpad5;
        case VK_NUMPAD6: return KeyCode::Numpad6;
        case VK_NUMPAD7: return KeyCode::Numpad7;
        case VK_NUMPAD8: return KeyCode::Numpad8;
        case VK_NUMPAD9: return KeyCode::Numpad9;
        case VK_SEPARATOR: return KeyCode::Separator;
        case VK_OEM_1: return KeyCode::OEM1;
        case VK_OEM_2: return KeyCode::OEM2;
        case VK_OEM_3: return KeyCode::OEM3;
        case VK_OEM_4: return KeyCode::OEM4;
        case VK_OEM_5: return KeyCode::OEM5;
        case VK_OEM_6: return KeyCode::OEM6;
        case VK_OEM_7: return KeyCode::OEM7;
        case VK_OEM_8: return KeyCode::OEM8;
        case VK_OEM_COMMA: return KeyCode::Comma;
        case VK_OEM_MINUS: return KeyCode::Minus;
        case VK_OEM_PERIOD: return KeyCode::Period;
        case VK_OEM_PLUS: return KeyCode::Equal;
        case VK_OEM_102: return KeyCode::OEM102;
        case VK_PACKET: return KeyCode::Unknown; // Not supported at this point in time
        default: Log::Error("Unknown key code: ", wParam);
            return KeyCode::Unknown;
        }
    }
}
#endif
