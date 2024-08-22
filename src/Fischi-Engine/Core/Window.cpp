#include "Window.h"

#include "Core/Core.h"
#include "Platform/RenderPlatform.h"

#ifdef FISCHI_PLATFORM_WINDOWS
#include "Platform/Windows/WindowsWindow.h"
#endif

#ifdef FISCHI_PLATFORM_LINUX
#include "Platform/Linux/X11Window.h"
#endif

namespace FischiEngine
{
    Shared<Window> Window::Create(const Spec& spec)
    {
        #ifdef FISCHI_PLATFORM_WINDOWS
        return Memory::CreateShared<WindowsWindow>(MemoryUsage::Window, spec);
        #elif defined(FISCHI_PLATFORM_LINUX)
        return Memory::CreateShared<X11Window>(MemoryUsage::Window, spec);
        #else
        #error Unsupported Platform
        #endif
    }

    bool Window::OnEventHandler(Event* event)
    {
        // TODO: Layers and event propagation
        return false;
    }

    Window::Window(const Spec& spec)
        : m_Spec(spec)
    {
        const auto rp = RenderPlatform::Get(RenderPlatform::Type::Vulkan);
        rp->Init();
    }
}
