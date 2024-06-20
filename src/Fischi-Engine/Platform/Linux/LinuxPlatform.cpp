#include "Core/Core.h"
#ifdef FISCHI_PLATFORM_LINUX

#include "LinuxPlatform.h"
#include "Platform/Platform.h"
#include "Core/Log.h"
#include <X11/Xlib.h>

namespace FischiEngine
{
    bool LinuxPlatformState::UseWayland = false;
    Display* LinuxPlatformState::X11Display;

    void Platform::Init()
    {
        const char* x11Display = std::getenv("DISPLAY");
        const char* waylandDisplay = std::getenv("WAYLAND_DISPLAY");

        if (waylandDisplay != nullptr) {
            LinuxPlatformState::UseWayland = true;
            Log::Info("The system uses Wayland.");
            Log::Error("Wayland is not supported yet.");
        } else if (x11Display != nullptr) {
            LinuxPlatformState::UseWayland = false;
            Log::Info("The system uses X11.");
            LinuxPlatformState::X11Display = XOpenDisplay(NULL);
            if (LinuxPlatformState::X11Display == NULL) {
                Log::Error("Cannot open display");
                return;
            }
        } else {
            Log::Info("No display variable found.");
        }
    }


    void Platform::Shutdown()
    {
        if (LinuxPlatformState::UseWayland) {

        } else {
            XCloseDisplay(LinuxPlatformState::X11Display);
        }
    }
}

#endif