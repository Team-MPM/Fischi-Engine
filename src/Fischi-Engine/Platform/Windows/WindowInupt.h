#pragma once
#include <windows.h>
#include "Core/KeyCodes.h"


namespace FischiEngine
{
    class WindowInupt
    {
    public:
        static KeyCode TranslateKeyCode(WPARAM wParam);
    };
}
