#ifdef FISCHI_PLATFORM_WINDOWS
#include "Platform/Platform.h"
#include "WindowsPlatform.h"

namespace FischiEngine
{
    HINSTANCE WindowsPlatformState::hInstance;

    void Platform::Init()
    {
        WindowsPlatformState::hInstance = GetModuleHandle(nullptr);
    }

    void Platform::Shutdown()
    {
        
    }
}
#endif