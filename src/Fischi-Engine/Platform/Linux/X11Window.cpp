#include "Core/Core.h"
#ifdef FISCHI_PLATFORM_LINUX

#include <X11/Xlib.h>

#include "X11Window.h"
#include "LinuxPlatform.h"
#include "Core/Log.h"


namespace FischiEngine {

    X11Window::X11Window(const Window::Spec &spec) : Window(spec) {
        auto display = LinuxPlatformState::X11Display;
        int screen = DefaultScreen(display);
        m_Window = XCreateSimpleWindow(display, RootWindow(display, screen), spec.X, spec.Y, spec.Width, spec.Height, 1,
                                     BlackPixel(display, screen), WhitePixel(display, screen));

        XSelectInput(display, m_Window, ExposureMask | KeyPressMask);
        XMapWindow(display, m_Window);
    }

    X11Window::~X11Window() {
        XDestroyWindow(LinuxPlatformState::X11Display, m_Window);
        XCloseDisplay(LinuxPlatformState::X11Display);
    }

    void X11Window::Maximize() {
        auto display = LinuxPlatformState::X11Display;
        XEvent xev;
        Atom wm_state = XInternAtom(display, "_NET_WM_STATE", False);
        Atom maximize = XInternAtom(display, "_NET_WM_STATE_MAXIMIZED_VERT", False);

        memset(&xev, 0, sizeof(xev));
        xev.type = ClientMessage;
        xev.xclient.window = m_Window;
        xev.xclient.message_type = wm_state;
        xev.xclient.format = 32;
        xev.xclient.data.l[0] = 1;
        xev.xclient.data.l[1] = maximize;

        XSendEvent(display, DefaultRootWindow(display), False, SubstructureRedirectMask | SubstructureNotifyMask, &xev);
    }

    std::pair<uint32_t, uint32_t> X11Window::GetSize() const {
        auto display = LinuxPlatformState::X11Display;
        XWindowAttributes attr;
        XGetWindowAttributes(display, m_Window, &attr);
        return std::make_pair(attr.width, attr.height);
    }

    std::pair<uint32_t, uint32_t> X11Window::GetPos() const {
        auto display = LinuxPlatformState::X11Display;
        int x, y;
        ::Window child;
        XTranslateCoordinates(display, m_Window, RootWindow(display, DefaultScreen(display)), 0, 0, &x, &y, &child);
        return std::make_pair(x, y);
    }

    void X11Window::OnUpdate() {
        auto display = LinuxPlatformState::X11Display;
        XEvent event;
        while (XPending(display)) {
            XNextEvent(display, &event);
            // Handle events here
        }
    }

    bool X11Window::OnEvent(Event *event) {
        return false;
    }

    void X11Window::Close() {
        XDestroyWindow(LinuxPlatformState::X11Display, m_Window);
    }

    bool X11Window::IsOpen() const {
        return true;
    }

    void X11Window::Minimize() {
        auto display = LinuxPlatformState::X11Display;
        XIconifyWindow(display, m_Window, DefaultScreen(display));
    }

    void X11Window::SetFullscreen(bool fullscreen) {
        auto display = LinuxPlatformState::X11Display;

        XEvent xev;
        Atom wm_state = XInternAtom(display, "_NET_WM_STATE", False);
        Atom fullscreen_atom = XInternAtom(display, "_NET_WM_STATE_FULLSCREEN", False);

        memset(&xev, 0, sizeof(xev));
        xev.type = ClientMessage;
        xev.xclient.window = m_Window;
        xev.xclient.message_type = wm_state;
        xev.xclient.format = 32;
        xev.xclient.data.l[0] = fullscreen ? 1 : 0;
        xev.xclient.data.l[1] = fullscreen_atom;

        XSendEvent(display, DefaultRootWindow(display), False, SubstructureRedirectMask | SubstructureNotifyMask, &xev);

    }
}

#endif