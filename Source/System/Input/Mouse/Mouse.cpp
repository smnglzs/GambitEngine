#include "Mouse.h"
#include "GLFW/glfw3.h"

namespace gb
{
	Mouse::Mouse()
	{

	}

	Mouse::~Mouse()
	{
		
	}

	Mouse::ListenerId Mouse::AddEventListener(const uint8 channel, MouseEventListener&& listener)
	{
		return m_eventCaster[channel].Add(std::move(listener));
	}

	void Mouse::RemoveEventListener(const uint8 eventCode, ListenerId listenerId)
	{
		m_eventCaster[eventCode].Remove(listenerId);
	}

	void Mouse::DispatchEvent(const MouseEvent mouseEvent)
	{
		m_eventCaster[mouseEvent.code].Broadcast(mouseEvent);
	}

	void Mouse::OnButtonEvent(GLFWwindow* window, int button, int action, int /*mods*/)
	{
		MouseEvent mouseEvent;
		mouseEvent.code = action ? (uint8)MouseEvent::Code::ButtonPress : (uint8)MouseEvent::Code::ButtonRelease;
		switch (button)
		{
		case GLFW_MOUSE_BUTTON_LEFT:   mouseEvent.button = MouseEvent::Button::Left;   break;
		case GLFW_MOUSE_BUTTON_RIGHT:  mouseEvent.button = MouseEvent::Button::Right;  break;
		case GLFW_MOUSE_BUTTON_MIDDLE: mouseEvent.button = MouseEvent::Button::Middle; break;
		default:
			mouseEvent.button = MouseEvent::Button::Count;
		}
		gbMouse->DispatchEvent(mouseEvent);
	}

	void Mouse::OnEnterContentArea(GLFWwindow* window, int entered)
	{
		MouseEvent mouseEvent;
		mouseEvent.code = (uint8)MouseEvent::Code::EnterContentArea;
		mouseEvent.enteredContentArea = entered;
		gbMouse->DispatchEvent(mouseEvent);
	}

	void Mouse::OnMove(GLFWwindow* window, double xpos, double ypos)
	{
		MouseEvent mouseEvent;
		mouseEvent.position = { xpos, ypos };
		mouseEvent.code = (uint8)MouseEvent::Code::Move;
		gbMouse->DispatchEvent(mouseEvent);
	}
}