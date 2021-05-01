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

	void Gamepad::DispatchEvent(const GamepadEvent gamepadEvent)
	{
		m_eventCaster[gamepadEvent.code].Broadcast(gamepadEvent);
	}
}