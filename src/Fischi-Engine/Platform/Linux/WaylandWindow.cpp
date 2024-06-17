#include "Core/Core.h"
#ifdef FISCHI_PLATFORM_LINUX

#include "WaylandWindow.h"

namespace FischiEngine {

    WaylandWindow::WaylandWindow(const Window::Spec &spec) : Window(spec) {

    }

    WaylandWindow::~WaylandWindow() {

    }

    void WaylandWindow::Maximize() {

    }

    std::pair<uint32_t, uint32_t> WaylandWindow::GetSize() const {
        return std::pair<uint32_t, uint32_t>();
    }

    std::pair<uint32_t, uint32_t> WaylandWindow::GetPos() const {
        return std::pair<uint32_t, uint32_t>();
    }

    void WaylandWindow::OnUpdate() {

    }

    bool WaylandWindow::OnEvent(Event *event) {
        return false;
    }

    void WaylandWindow::Close() {

    }

    bool WaylandWindow::IsOpen() const {
        return false;
    }

    void WaylandWindow::Minimize() {

    }

    void WaylandWindow::SetFullscreen(bool fullscreen) {

    }
}

#endif