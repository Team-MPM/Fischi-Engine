#include "Core/Core.h"
#ifdef FISCHI_PLATFORM_LINUX

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <X11/X.h>

#include "X11Window.h"
#include "LinuxPlatform.h"
#include "Core/Application.h"
#include "Core/Event/EventDefs.h"
#include "LinuxInput.h"
#include "Utils/String.h"

// Resources:
// http://mech.math.msu.su/~vvb/2course/Borisenko/CppProjects/GWindow/xintro.html

namespace FischiEngine {

    X11Window::X11Window(const Window::Spec &spec) : Window(spec) {
        auto display = LinuxPlatformState::X11Display;
        int screen = DefaultScreen(display);
        m_Window = XCreateSimpleWindow(display, RootWindow(display, screen), spec.X, spec.Y, spec.Width, spec.Height, 1,
                                     BlackPixel(display, screen), WhitePixel(display, screen));

        XSetStandardProperties(display, m_Window, spec.Title.c_str(), spec.Title.c_str(), None, nullptr, 0, nullptr);

        XSelectInput(display, m_Window, ExposureMask | KeyPressMask | KeyReleaseMask | ButtonPressMask | ButtonReleaseMask | PointerMotionMask | StructureNotifyMask | FocusChangeMask | EnterWindowMask | LeaveWindowMask | ClientMessage);
        XMapWindow(display, m_Window);

        m_WmDeleteMessage = XInternAtom(display, "WM_DELETE_WINDOW", False);
        XSetWMProtocols(display, m_Window, &m_WmDeleteMessage, 1);

        m_IsOpen = true;
    }

    X11Window::~X11Window() {
        XDestroyWindow(LinuxPlatformState::X11Display, m_Window);
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
        while(XCheckTypedWindowEvent(display, m_Window, ClientMessage, &event)){
            if (event.xclient.data.l[0] == m_WmDeleteMessage) {
                Application::Get()->GetEventQueue().PushEvent(WindowCloseEvent((void*)m_Window));
                return;
            }
        }

        while (XCheckWindowEvent(display, m_Window, ExposureMask | KeyPressMask | KeyReleaseMask | ButtonPressMask | ButtonReleaseMask | PointerMotionMask | StructureNotifyMask | FocusChangeMask | EnterWindowMask | LeaveWindowMask, &event)) {
            switch (event.type) {
            case ConfigureNotify:
                Application::Get()->GetEventQueue().PushEvent(WindowResizeEvent((void*)m_Window, event.xconfigure.width, event.xconfigure.height));
                break;
            case MotionNotify:
                Application::Get()->GetEventQueue().PushEvent(MouseMovedEvent((void*)m_Window, event.xmotion.x, event.xmotion.y));
                break;
                case ButtonPress:
                    switch (event.xbutton.button) {
                        case 1:
                            Application::Get()->GetEventQueue().PushEvent(MouseButtonPressedEvent((void*)m_Window, MouseButton::Left));
                            break;
                        case 2:
                            Application::Get()->GetEventQueue().PushEvent(MouseButtonPressedEvent((void*)m_Window, MouseButton::Middle));
                            break;
                        case 3:
                            Application::Get()->GetEventQueue().PushEvent(MouseButtonPressedEvent((void*)m_Window, MouseButton::Right));
                            break;
                        case 4:
                            Application::Get()->GetEventQueue().PushEvent(MouseScrolledEvent((void*)m_Window, 0, 1));
                            break;
                        case 5:
                            Application::Get()->GetEventQueue().PushEvent(MouseScrolledEvent((void*)m_Window, 0, -1));
                            break;
                    }
                    break;
                case ButtonRelease:
                    switch (event.xbutton.button) {
                        case 1:
                            Application::Get()->GetEventQueue().PushEvent(MouseButtonReleasedEvent((void*)m_Window, MouseButton::Left));
                            break;
                        case 2:
                            Application::Get()->GetEventQueue().PushEvent(MouseButtonReleasedEvent((void*)m_Window, MouseButton::Middle));
                            break;
                        case 3:
                            Application::Get()->GetEventQueue().PushEvent(MouseButtonReleasedEvent((void*)m_Window, MouseButton::Right));
                            break;
                    }
                    break;
            case KeyPress:
                Application::Get()->GetEventQueue().PushEvent(KeyPressedEvent((void*)m_Window, LinuxInput::ParseX11KeyCode(XLookupKeysym(&event.xkey, 0)), 0));
                break;
            case KeyRelease:
                Application::Get()->GetEventQueue().PushEvent(KeyReleasedEvent((void*)m_Window, LinuxInput::ParseX11KeyCode(XLookupKeysym(&event.xkey, 0))));
                break;
            }
        }
    }

    bool X11Window::OnEvent(Event *event) {
        if (event->GetEventType() == EventType::WindowClose && dynamic_cast<WindowCloseEvent*>(event)->GetWindowHandle() == (void*)m_Window)
        {
            Close();
            return true;
        }
        return OnEventHandler(event);
    }

    void X11Window::Close() {
        XDestroyWindow(LinuxPlatformState::X11Display, m_Window);
        m_IsOpen = false;
    }

    bool X11Window::IsOpen() const {
        return m_IsOpen;
    }

    ::Window X11Window::GetNativeWindow() const {
        return m_Window;
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