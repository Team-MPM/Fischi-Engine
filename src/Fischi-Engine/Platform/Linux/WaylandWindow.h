#pragma once
#include "Core/Window.h"

namespace FischiEngine {
    class WaylandWindow final : public Window {
    public:
        WaylandWindow(const Spec& spec);
        ~WaylandWindow() override;
        void Maximize() override;
        std::pair<uint32_t, uint32_t> GetSize() const override;
        std::pair<uint32_t, uint32_t> GetPos() const override;
        void OnUpdate() override;
        bool OnEvent(Event* event) override;
        void Close() override;
        bool IsOpen() const override;
        void Minimize() override;
        void SetFullscreen(bool fullscreen) override;
    };
}