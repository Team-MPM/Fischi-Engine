#pragma once

#include "Event.h"

namespace FischiEngine 
{
    class MouseMovedEvent : public Event
	{
	public:
		EVENT_CLASS_TYPE(MouseMoved)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
		
		MouseMovedEvent(void* windowHandle, float x, float y)
			: m_MouseX(x), m_MouseY(y), m_WindowHandle(windowHandle) {}

		float GetX() const { return m_MouseX; }
		float GetY() const { return m_MouseY; }
    	void* GetWindowHandle() const { return m_WindowHandle; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseMovedEvent: " << m_MouseX << ", " << m_MouseY;
			return ss.str();
		}
	private:
		float m_MouseX, m_MouseY;
    	void* m_WindowHandle;
	};

	class MouseScrolledEvent : public Event
	{
	public:
		EVENT_CLASS_TYPE(MouseScrolled)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

		MouseScrolledEvent(void* windowHandle, float xOffset, float yOffset)
			: m_XOffset(xOffset), m_YOffset(yOffset), m_WindowHandle(windowHandle) {}

		float GetXOffset() const { return m_XOffset; }
		float GetYOffset() const { return m_YOffset; }
		void* GetWindowHandle() const { return m_WindowHandle; }
		
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseScrolledEvent: " << GetXOffset() << ", " << GetYOffset();
			return ss.str();
		}
	private:
		float m_XOffset, m_YOffset;
		void* m_WindowHandle;
	};

	class MouseButtonPressedEvent : public Event
	{
	public:
		EVENT_CLASS_TYPE(MouseButtonPressed)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
		
		MouseButtonPressedEvent(void* windowHandle, MouseButton button)
			: m_Button(button), m_WindowHandle(windowHandle) {}
		
		MouseButton GetMouseButton() const { return m_Button; }
		void* GetWindowHandle() const { return m_WindowHandle; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonPressedEvent: " << static_cast<int>(m_Button);
			return ss.str();
		}

	private:
		MouseButton m_Button;
		void* m_WindowHandle;
	};

	class MouseButtonReleasedEvent : public Event
	{
	public:
		EVENT_CLASS_TYPE(MouseButtonReleased)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
		
		MouseButtonReleasedEvent(void* windowHandle, MouseButton button)
			: m_Button(button), m_WindowHandle(windowHandle) {}
		
		MouseButton GetMouseButton() const { return m_Button; }
		void* GetWindowHandle() const { return m_WindowHandle; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent: " << static_cast<int>(m_Button);
			return ss.str();
		}

	private:
		MouseButton m_Button;
		void* m_WindowHandle;
	};

	class KeyPressedEvent : public Event
	{
	public:
		EVENT_CLASS_TYPE(KeyPressed)
		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
		
		KeyPressedEvent(void* windowHandle, KeyCode keyCode, uint32_t repeatCount)
			: m_KeyCode(keyCode), m_RepeatCount(repeatCount), m_WindowHandle(windowHandle) {}
		
		KeyCode GetKeyCode() const { return m_KeyCode; }
		uint32_t GetRepeatCount() const { return m_RepeatCount; }
		void* GetWindowHandle() const { return m_WindowHandle; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << static_cast<int>(m_KeyCode);
			return ss.str();
		}

	private:
		KeyCode m_KeyCode;
		uint32_t m_RepeatCount;
		void* m_WindowHandle;
	};

	class KeyReleasedEvent : public Event
	{
	public:
		EVENT_CLASS_TYPE(KeyReleased)
		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
		
		KeyReleasedEvent(void* windowHandle, KeyCode keyCode)
			: m_KeyCode(keyCode), m_WindowHandle(windowHandle) {}
		
		KeyCode GetKeyCode() const { return m_KeyCode; }
		void* GetWindowHandle() const { return m_WindowHandle; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << static_cast<int>(m_KeyCode);
			return ss.str();
		}

	private:
		KeyCode m_KeyCode;
		void* m_WindowHandle;
	};

	class WindowCloseEvent : public Event
	{
	public:
		EVENT_CLASS_TYPE(WindowClose)
		EVENT_CLASS_CATEGORY(EventCategoryWindow)
		
		WindowCloseEvent(void* windowHandle)
			: m_WindowHandle(windowHandle) {}
		
		void* GetWindowHandle() const { return m_WindowHandle; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowCloseEvent: " << m_WindowHandle;
			return ss.str();
		}

	private:
		void* m_WindowHandle;
	};
}
