#include "Window.h"

#ifdef FISCHI_PLATFORM_WINDOWS
#include "Platform/Windows/WindowWindow.h"
#endif

namespace FischiEngine
{
    Shared<Window> Window::Create(const Spec& spec)
    {
        #ifdef FISCHI_PLATFORM_WINDOWS
        return Memory::CreateShared<WindowsWindow>(MemoryUsage::Window, spec);
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
    }
}
