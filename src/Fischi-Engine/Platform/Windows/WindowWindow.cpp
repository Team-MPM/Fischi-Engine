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
        case WM_CLOSE:
            PostQuitMessage(0);
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

        m_WindowHandle = CreateWindowEx(
            0,
            spec.Title.c_str(),
            spec.Title.c_str(),
            WS_OVERLAPPEDWINDOW,
            spec.X, spec.Y, spec.Width, spec.Height,
            NULL, NULL, WindowsPlatformState::hInstance, NULL
        );

        if (m_WindowHandle == NULL)
        {
            Log::Error("Window creation failed");
            FISCHI_DEBUG_BREAK();
            return;
        }

        ShowWindow(m_WindowHandle, SW_SHOW);
        UpdateWindow(m_WindowHandle);
    }

    WindowsWindow::~WindowsWindow()
    {
        Close();
        UnregisterClass(m_WindowClass.lpszClassName, m_WindowClass.hInstance);
    }

    void WindowsWindow::Close()
    {
        if (m_WindowHandle != NULL)
        {
            DestroyWindow(m_WindowHandle);
            m_WindowHandle = NULL;
        }
    }

    void WindowsWindow::Maximize()
    {
    }

    void WindowsWindow::CenterWindow()
    {
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
        while (GetMessage(&msg, m_WindowHandle, 0, 0))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    bool WindowsWindow::OnEvent(Event* event)
    {
        return false;
    }
}
#endif