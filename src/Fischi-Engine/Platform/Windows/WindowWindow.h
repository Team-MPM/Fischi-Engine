#pragma once

#include <windows.h>

#include "Core/Window.h"

namespace FischiEngine
{
    class WindowsWindow final : public Window
    {
    public:
        WindowsWindow(const Spec& spec);
        ~WindowsWindow() override;
        void Maximize() override;
        void CenterWindow() override;
        std::pair<uint32_t, uint32_t> GetSize() const override;
        std::pair<uint32_t, uint32_t> GetPos() const override;
        void OnUpdate() override;
        bool OnEvent(Event* event) override;
        void Close() override;

    private:
        WNDCLASSEX m_WindowClass;
        HWND m_WindowHandle;
    };
    
}
