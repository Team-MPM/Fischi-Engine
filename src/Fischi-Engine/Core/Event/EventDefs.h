#pragma once

#include "Event.h"

namespace FischiEngine 
{
    class MouseMovedEvent : public Event
	{
	public:
		EVENT_CLASS_TYPE(MouseMoved)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
		
		MouseMovedEvent(float x, float y)
			: m_MouseX(x), m_MouseY(y) {}

		float GetX() const { return m_MouseX; }
		float GetY() const { return m_MouseY; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseMovedEvent: " << m_MouseX << ", " << m_MouseY;
			return ss.str();
		}
	private:
		float m_MouseX, m_MouseY;
	};

	class MouseScrolledEvent : public Event
	{
	public:
		EVENT_CLASS_TYPE(MouseScrolled)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

		MouseScrolledEvent(float xOffset, float yOffset)
			: m_XOffset(xOffset), m_YOffset(yOffset) {}

		float GetXOffset() const { return m_XOffset; }
		float GetYOffset() const { return m_YOffset; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseScrolledEvent: " << GetXOffset() << ", " << GetYOffset();
			return ss.str();
		}
	private:
		float m_XOffset, m_YOffset;
	};

	class MouseButtonPressedEvent : public Event
	{
	public:
		EVENT_CLASS_TYPE(MouseButtonPressed)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
		
		MouseButtonPressedEvent(MouseButton button)
			: m_Button(button) {}
		
		MouseButton GetMouseButton() const { return m_Button; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonPressedEvent: " << static_cast<int>(m_Button);
			return ss.str();
		}

	private:
		MouseButton m_Button;
	};

	class MouseButtonReleasedEvent : public Event
	{
	public:
		EVENT_CLASS_TYPE(MouseButtonReleased)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
		
		MouseButtonReleasedEvent(MouseButton button)
			: m_Button(button) {}
		
		MouseButton GetMouseButton() const { return m_Button; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent: " << static_cast<int>(m_Button);
			return ss.str();
		}

	private:
		MouseButton m_Button;
	};

	class KeyPressedEvent : public Event
	{
	public:
		EVENT_CLASS_TYPE(KeyPressed)
		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
		
		KeyPressedEvent(KeyCode keyCode, uint32_t repeatCount)
			: m_KeyCode(keyCode), m_RepeatCount(repeatCount) {}
		
		KeyCode GetKeyCode() const { return m_KeyCode; }
		uint32_t GetRepeatCount() const { return m_RepeatCount; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonPressedEvent: " << static_cast<int>(m_KeyCode);
			return ss.str();
		}

	private:
		KeyCode m_KeyCode;
		uint32_t m_RepeatCount;
	};

	class KeyReleasedEvent : public Event
	{
	public:
		EVENT_CLASS_TYPE(KeyReleased)
		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
		
		KeyReleasedEvent(KeyCode keyCode)
			: m_KeyCode(keyCode) {}
		
		KeyCode GetKeyCode() const { return m_KeyCode; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent: " << static_cast<int>(m_KeyCode);
			return ss.str();
		}

	private:
		KeyCode m_KeyCode;
	};
}
