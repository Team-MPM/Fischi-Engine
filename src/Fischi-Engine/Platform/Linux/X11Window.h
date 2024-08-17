#pragma once

#include <X11/Xlib.h>
#include "Core/Window.h"


namespace FischiEngine {
    class X11Window final : public Window {
    public:
        X11Window(const Spec& spec);
        ~X11Window() override;
        void Maximize() override;
        std::pair<uint32_t, uint32_t> GetSize() const override;
        std::pair<uint32_t, uint32_t> GetPos() const override;
        void OnUpdate() override;
        bool OnEvent(Event* event) override;
        void Close() override;
        bool IsOpen() const override;
        void Minimize() override;
        void SetFullscreen(bool fullscreen) override;
        ::Window GetNativeWindow() const;
    private:
        ::Window m_Window;
        Atom m_WmDeleteMessage;
        bool m_IsOpen;
    };
}