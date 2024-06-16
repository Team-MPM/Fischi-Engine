#include "WindowInupt.h"
#include "Core/Application.h"
#include "Core/Event/EventDefs.h"
#ifdef FISCHI_PLATFORM_WINDOWS
#include "WindowsPlatform.h"
#include "Core/Log.h"
#include "WindowWindow.h"

namespace FischiEngine
{
    LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
        switch (msg)
        {
        // case WM_CREATE:
        //     break;
        // case WM_DESTROY:
        //     break;
        case WM_CLOSE:
            Application::Get()->GetEventQueue().PushEvent(WindowCloseEvent(hwnd));
            break;
        // case WM_MOVE:
        //     break;
        // case WM_SIZE:
        //     break;
        case WM_KEYDOWN:
            Application::Get()->GetEventQueue().PushEvent(KeyPressedEvent(hwnd, WindowInupt::TranslateKeyCode(wParam), 0));
            break;
        case WM_KEYUP:
            Application::Get()->GetEventQueue().PushEvent(KeyReleasedEvent(hwnd, WindowInupt::TranslateKeyCode(wParam)));
            break;
        case WM_LBUTTONDOWN:
            Application::Get()->GetEventQueue().PushEvent(MouseButtonPressedEvent(hwnd, MouseButton::Left));
            break;
        case WM_LBUTTONUP:
            Application::Get()->GetEventQueue().PushEvent(MouseButtonReleasedEvent(hwnd, MouseButton::Left));
            break;
        case WM_RBUTTONDOWN:
            Application::Get()->GetEventQueue().PushEvent(MouseButtonPressedEvent(hwnd, MouseButton::Right));
            break;
        case WM_RBUTTONUP:
            Application::Get()->GetEventQueue().PushEvent(MouseButtonReleasedEvent(hwnd, MouseButton::Right));
            break;
        case WM_MBUTTONDOWN:
            Application::Get()->GetEventQueue().PushEvent(MouseButtonPressedEvent(hwnd, MouseButton::Middle));
            break;
        case WM_MBUTTONUP:
            Application::Get()->GetEventQueue().PushEvent(MouseButtonReleasedEvent(hwnd, MouseButton::Middle));
            break;
        case WM_MOUSEMOVE:
            Application::Get()->GetEventQueue().PushEvent(MouseMovedEvent(hwnd, LOWORD(lParam), HIWORD(lParam)));
            break;
        case WM_MOUSEWHEEL:
            Application::Get()->GetEventQueue().PushEvent(MouseScrolledEvent(hwnd, 0.0f, 0.0f));//GET_WHEEL_DELTA_WPARAM(wParam)));
            break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
        }
        return 0;
    }
    
    WindowsWindow::WindowsWindow(const Spec& spec)
        : Window(spec)
    {
        m_WindowClass = {};
        m_WindowClass.cbSize = sizeof(WNDCLASSEX);
        m_WindowClass.style = CS_HREDRAW | CS_VREDRAW;
        m_WindowClass.lpfnWndProc = WindowProcedure;
        m_WindowClass.hInstance = WindowsPlatformState::hInstance;
        m_WindowClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
        m_WindowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
        m_WindowClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
        m_WindowClass.lpszClassName = spec.Title.c_str();
        m_WindowClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

        if (!RegisterClassEx(&m_WindowClass))
        {
            Log::Error("Window registration failed");
            FISCHI_DEBUG_BREAK();
            return;
        }

        LONG style = {};
        style |= WS_TABSTOP;
        if (spec.Minimized)
            style |= WS_MINIMIZE;
        else
            style |= WS_VISIBLE;
        if (spec.Decorated)
            style |= WS_OVERLAPPEDWINDOW;
        else
            style |= WS_POPUP;
        if (spec.Maximized)
            style |= WS_MAXIMIZE;
        
        m_WindowHandle = CreateWindowEx(
            0,
            spec.Title.c_str(),
            spec.Title.c_str(),
            style,
            spec.X, spec.Y, spec.Width, spec.Height,
            NULL, NULL, WindowsPlatformState::hInstance, NULL
        );

        if (m_WindowHandle == NULL)
        {
            Log::Error("Window creation failed");
            FISCHI_DEBUG_BREAK();
            return;
        }

        GetWindowRect(m_WindowHandle, &m_OldWindowRect);

        if (spec.Fullscreen)
            SetFullscreen(true);

        ShowWindow(m_WindowHandle, SW_SHOW);
        UpdateWindow(m_WindowHandle);
    }

    WindowsWindow::~WindowsWindow()
    {
        Close();
        UnregisterClass(m_WindowClass.lpszClassName, m_WindowClass.hInstance);
    }

    void WindowsWindow::SetFullscreen(bool fullscreen)
    {
        if (fullscreen)
        {
            GetWindowRect(m_WindowHandle, &m_OldWindowRect);

            SetWindowLong(m_WindowHandle, GWL_STYLE, WS_POPUP);

            HMONITOR hmon = MonitorFromWindow(m_WindowHandle, MONITOR_DEFAULTTONEAREST);
            MONITORINFO mi = {sizeof(mi)};
            GetMonitorInfo(hmon, &mi);

            SetWindowPos(m_WindowHandle, HWND_TOP,
                         mi.rcMonitor.left, mi.rcMonitor.top,
                         mi.rcMonitor.right - mi.rcMonitor.left,
                         mi.rcMonitor.bottom - mi.rcMonitor.top,
                         SWP_FRAMECHANGED | SWP_NOACTIVATE);
        }
        else
        {
            SetWindowLong(m_WindowHandle, GWL_STYLE, WS_OVERLAPPEDWINDOW);

            SetWindowPos(m_WindowHandle, HWND_NOTOPMOST,
                         m_OldWindowRect.left, m_OldWindowRect.top,
                         m_OldWindowRect.right - m_OldWindowRect.left,
                         m_OldWindowRect.bottom - m_OldWindowRect.top,
                         SWP_FRAMECHANGED | SWP_NOACTIVATE);
        }
    }

    void WindowsWindow::Close()
    {
        if (m_WindowHandle != NULL)
        {
            DestroyWindow(m_WindowHandle);
            m_WindowHandle = NULL;
        }
    }

    bool WindowsWindow::IsOpen() const
    {
        return m_WindowHandle != NULL;
    }

    void WindowsWindow::Minimize()
    {
        ShowWindow(m_WindowHandle, SW_MINIMIZE);
    }

    void WindowsWindow::Maximize()
    {
        ShowWindow(m_WindowHandle, SW_MAXIMIZE);
    }
    
    std::pair<uint32_t, uint32_t> WindowsWindow::GetSize() const
    {
        return std::make_pair(0, 0);
    }

    std::pair<uint32_t, uint32_t> WindowsWindow::GetPos() const
    {
        return std::make_pair(0, 0);
    }

    void WindowsWindow::OnUpdate()
    {
        MSG msg = {};
        while (PeekMessage(&msg, m_WindowHandle, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    bool WindowsWindow::OnEvent(Event* event)
    {
        if (event->GetEventType() == EventType::WindowClose && dynamic_cast<WindowCloseEvent*>(event)->GetWindowHandle() == m_WindowHandle)
        {
            Close();
            return true;
        }
        return OnEventHandler(event);
    }
}
#endif