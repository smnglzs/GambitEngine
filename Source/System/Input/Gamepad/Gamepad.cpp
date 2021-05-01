#include "Gamepad.h"

namespace gb
{
	Gamepad::Gamepad()
	{

	}

	Gamepad::~Gamepad()
	{

	}

	Gamepad::ListenerId Gamepad::AddEventListener(const uint8 eventCode, EventClassListener&& listener)
	{
		return m_eventCaster[eventCode].Add(std::move(listener));
	}

	void Gamepad::RemoveEventListener(const uint8 eventCode, ListenerId listenerId)
	{
		m_eventCaster[eventCode].Remove(listenerId);
	}

	void Gamepad::DispatchEvent(const KeyEvent keyEvent)
	{
		m_eventCaster[keyEvent.code].Broadcast(keyEvent);
	}

	void Gamepad::OnKeyEvent(GLFWwindow* window, int32 key, int32 scancode, int32 action, int32 mods)
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
		Gamepad::Get(->DispatchEvent(keyEvent);
	}
}