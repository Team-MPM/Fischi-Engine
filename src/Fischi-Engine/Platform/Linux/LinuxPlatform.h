#pragma once

#include <X11/Xlib.h>

namespace FischiEngine
{
    struct LinuxPlatformState
    {
        static bool UseWayland;
        static Display* X11Display;
    };
}