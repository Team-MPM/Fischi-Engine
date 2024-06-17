#include "Core/Core.h"
#ifdef FISCHI_PLATFORM_WINDOWS
#include "WindowInupt.h"
#include "Core/Application.h"
#include "Core/Event/EventDefs.h"
#include "WindowsPlatform.h"
#include "Core/Log.h"
#include "WindowsWindow.h"

namespace FischiEngine
{
    LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
        switch (msg)
        {
        case WM_CREATE:
        case WM_DESTROY:
        case WM_ENTERSIZEMOVE:
        case WM_EXITSIZEMOVE:
        case WM_MOVE:
            break;
        case WM_NCLBUTTONDOWN:
            if (wParam == HTCAPTION || wParam == HTLEFT || wParam == HTRIGHT || wParam == HTTOP || wParam == HTBOTTOM ||
                wParam == HTTOPLEFT || wParam == HTTOPRIGHT || wParam == HTBOTTOMLEFT || wParam == HTBOTTOMRIGHT)
            {
                int edge = -1;
                if (wParam == HTTOP) edge = WMSZ_TOP;
                else if (wParam == HTBOTTOM) edge = WMSZ_BOTTOM;
                else if (wParam == HTLEFT) edge = WMSZ_LEFT;
                else if (wParam == HTRIGHT) edge = WMSZ_RIGHT;
                else if (wParam == HTTOPLEFT) edge = WMSZ_TOPLEFT;
                else if (wParam == HTTOPRIGHT) edge = WMSZ_TOPRIGHT;
                else if (wParam == HTBOTTOMLEFT) edge = WMSZ_BOTTOMLEFT;
                else if (wParam == HTBOTTOMRIGHT) edge = WMSZ_BOTTOMRIGHT;

                if (edge != -1)
                {
                    SendMessage(hwnd, WM_SYSCOMMAND, SC_SIZE + edge, lParam);
                    return 0;
                }
            }
            return DefWindowProc(hwnd, msg, wParam, lParam);
        case WM_CLOSE:
            Application::Get()->GetEventQueue().PushEvent(WindowCloseEvent(hwnd));
            break;
        case WM_SIZE:
            RECT rect;
            GetWindowRect(hwnd, &rect);
            Application::Get()->GetEventQueue().PushEvent(WindowResizeEvent(hwnd, rect.right - rect.left, rect.bottom - rect.top));
            return 0;
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
        : Window(spec), m_StopFlag(false)
    {
        m_WindowThread = std::thread(&WindowsWindow::WindowThread, this);
        std::unique_lock lock(m_WindowStateMutex);
        m_WindowCreated.wait(lock);
    }

    WindowsWindow::~WindowsWindow()
    {
        m_StopFlag.store(true);
        m_WindowThread.join();
        Close();
    }

    void WindowsWindow::SetFullscreen(bool fullscreen)
    {
        std::lock_guard lock(m_Mutex);
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

    void WindowsWindow::WindowThread()
    {
        static WNDCLASSEX windowClass = {};
        windowClass.cbSize = sizeof(WNDCLASSEX);
        windowClass.style = CS_HREDRAW | CS_VREDRAW;
        windowClass.lpfnWndProc = WindowProcedure;
        windowClass.hInstance = WindowsPlatformState::hInstance;
        windowClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
        windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
        windowClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
        windowClass.lpszClassName = L"Fischi Engine";
        windowClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

        WNDCLASSEX existingWindowClass = {};
        if (!GetClassInfoEx(WindowsPlatformState::hInstance, L"Fischi Engine", &existingWindowClass))
        {
            DWORD error = GetLastError();
            if (error == ERROR_CLASS_DOES_NOT_EXIST)
            {
                if (!RegisterClassEx(&windowClass))
                {
                    Log::Error("Window registration failed");
                    FISCHI_DEBUG_BREAK();
                    return;
                }
            }
        }

        LONG style = {};
        style |= WS_TABSTOP;
        if (m_Spec.Minimized)
            style |= WS_MINIMIZE;
        else
            style |= WS_VISIBLE;
        if (m_Spec.Decorated)
            style |= WS_OVERLAPPEDWINDOW;
        else
            style |= WS_POPUP;
        if (m_Spec.Maximized)
            style |= WS_MAXIMIZE;

        m_WindowHandle = CreateWindowEx(
            0,
            L"Fischi Engine",
            m_Spec.Title.c_str(),
            style,
            m_Spec.X, m_Spec.Y, m_Spec.Width, m_Spec.Height,
            NULL, NULL, WindowsPlatformState::hInstance, NULL
        );

        if (m_WindowHandle == NULL)
        {
            Log::Error("Window creation failed");
            FISCHI_DEBUG_BREAK();
            return;
        }

        GetWindowRect(m_WindowHandle, &m_OldWindowRect);

        if (m_Spec.Fullscreen)
            SetFullscreen(true);

        ShowWindow(m_WindowHandle, SW_SHOW);
        UpdateWindow(m_WindowHandle);

        Log::Info("WindowThread Thread started for HWND {0}!", static_cast<void*>(m_WindowHandle));

        {
            std::unique_lock windowStateLock(m_WindowStateMutex);
            m_WindowCreated.notify_all();
        }

        MSG msg = {};
        while (!m_StopFlag.load() && GetMessage(&msg, m_WindowHandle, 0, 0))
        {
            std::lock_guard lock(m_Mutex);
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        DestroyWindow(m_WindowHandle);
        m_WindowHandle = NULL;
    }

    void WindowsWindow::Close()
    {
        m_StopFlag.store(true);
        SendMessage(m_WindowHandle, WM_CLOSE, 0, 0);
    }

    bool WindowsWindow::IsOpen() const
    {
        return m_WindowHandle != NULL;
    }

    void WindowsWindow::Minimize()
    {
        std::lock_guard lock(m_Mutex);
        ShowWindow(m_WindowHandle, SW_MINIMIZE);
    }

    void WindowsWindow::Maximize()
    {
        std::lock_guard lock(m_Mutex);
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