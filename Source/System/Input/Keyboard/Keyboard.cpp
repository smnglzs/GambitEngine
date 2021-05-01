#include "Keyboard.h"
#include "GLFW/glfw3.h"

namespace gb
{
	Keyboard::Keyboard()
	{

	}

	Keyboard::~Keyboard()
	{

	}

	Keyboard::ListenerId Keyboard::AddEventListener(const uint8 eventCode, EventClassListener&& listener)
	{
		return m_eventCaster[eventCode].Add(std::move(listener));
	}

	void Keyboard::RemoveEventListener(const uint8 eventCode, ListenerId listenerId)
	{
		m_eventCaster[eventCode].Remove(listenerId);
	}

	void Keyboard::DispatchEvent(const KeyEvent keyEvent)
	{
		m_eventCaster[keyEvent.code].Broadcast(keyEvent);
	}

	void Keyboard::OnKeyEvent(GLFWwindow* window, int32 key, int32 scancode, int32 action, int32 mods)
	{
		KeyEvent keyEvent;
		switch (action)
		{
		case GLFW_PRESS:   keyEvent.code = (uint8)KeyEvent::ECode::Press;   break;
		case GLFW_RELEASE: keyEvent.code = (uint8)KeyEvent::ECode::Release; break;
		case GLFW_REPEAT:  keyEvent.code = (uint8)KeyEvent::ECode::Repeat;  break;
		default:
			keyEvent.code = (uint8)KeyEvent::ECode::Count;
		}
		gbKeyboard->DispatchEvent(keyEvent);
	}
}