#pragma once
#include "Base/GambitBasePCH.h"
#include "System/Export.h"

namespace gb
{
	struct GAMBIT_SYSTEM_API MouseEvent : public Event
	{
		MouseEvent() = default;

		enum class Code : uint8
		{
			EnterContentArea,
			ButtonPress,
			ButtonRelease,
			Move,
			Count
		};
		
		enum Button : uint8
		{
			Left,
			Right,
			Middle,
			Count
		} button = Button::Count;

		vec2d position;
		bool enteredContentArea:1 = false;
	};
}