#include "Core/Core.h"
#ifdef FISCHI_PLATFORM_LINUX

#include "X11Window.h"

namespace FischiEngine {

    X11Window::X11Window(const Window::Spec &spec) : Window(spec) {

    }

    X11Window::~X11Window() {

    }

    void X11Window::Maximize() {

    }

    std::pair<uint32_t, uint32_t> X11Window::GetSize() const {
        return std::pair<uint32_t, uint32_t>();
    }

    std::pair<uint32_t, uint32_t> X11Window::GetPos() const {
        return std::pair<uint32_t, uint32_t>();
    }

    void X11Window::OnUpdate() {

    }

    bool X11Window::OnEvent(Event *event) {
        return false;
    }

    void X11Window::Close() {

    }

    bool X11Window::IsOpen() const {
        return true;
    }

    void X11Window::Minimize() {

    }

    void X11Window::SetFullscreen(bool fullscreen) {

    }
}

#endif