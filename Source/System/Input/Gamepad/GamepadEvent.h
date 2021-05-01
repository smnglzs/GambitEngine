#pragma once
#include "Base/GambitBasePCH.h"
#include "System/Export.h"

namespace gb
{
	struct GAMBIT_SYSTEM_API GamepadEvent : public Event
	{
		enum class ECode : uint8
		{
			Count
		};

		GamepadEvent() = default;
	};
}