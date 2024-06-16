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
        std::pair<uint32_t, uint32_t> GetSize() const override;
        std::pair<uint32_t, uint32_t> GetPos() const override;
        void OnUpdate() override;
        bool OnEvent(Event* event) override;
        void Close() override;
        bool IsOpen() const override;
        void Minimize() override;
        void SetFullscreen(bool fullscreen) override;

        HWND GetWindowHandle() const { return m_WindowHandle; }
        RECT GetOldWindowRect() const { return m_OldWindowRect; }
    private:
        WNDCLASSEX m_WindowClass;
        HWND m_WindowHandle;
        RECT m_OldWindowRect;
    };
}
