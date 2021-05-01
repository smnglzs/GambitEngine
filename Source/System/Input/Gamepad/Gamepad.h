#pragma once
#include "Base/GambitBasePCH.h"
#include "System/Export.h"
#include "System/Input/Gamepad/GamepadEvent.h"

struct GLFWwindow;
namespace gb
{
	enum GamepadId : uint8
	{
		GB_GAMEPAD_0,
		GB_GAMEPAD_1,
		GB_GAMEPAD_2,
		GB_GAMEPAD_3,
		GB_GAMEPAD_4,
		GB_GAMEPAD_5,
		GB_GAMEPAD_6,
		GB_GAMEPAD_7,
		GB_GAMEPAD_8,
		GB_GAMEPAD_9,
		GB_GAMEPAD_10,
		GB_GAMEPAD_11,
		GB_GAMEPAD_12,
		GB_GAMEPAD_13,
		GB_GAMEPAD_14,
		GB_GAMEPAD_15,
		GB_GAMEPAD_MAX
	};

	class GAMBIT_SYSTEM_API Gamepad final : public IEventDispatcher<GamepadEvent>
	{
	public:
		Gamepad();
		virtual ~Gamepad() override;

		static Gamepad& Get(const GamepadId gpid) {}

		GB_DEFINE_LISTENER(GamepadEvent);
		virtual ListenerId AddEventListener(const uint8 eventCode, EventClassListener&& listener) override;
		virtual void RemoveEventListener(const uint8 eventCode, ListenerId listenerId) override;

	private:
		GB_MULTICASTER(GamepadEvent) m_eventCaster;
		virtual void DispatchEvent(const GamepadEvent gamepadEvent) override;

		friend class InputManager;
	};
}