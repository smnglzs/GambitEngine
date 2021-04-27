#pragma once
#include "Base/GambitBasePCH.h"
#include "System/Export.h"

namespace gb
{
	struct GAMBIT_SYSTEM_API KeyEvent : public Event
	{
		KeyEvent() = default;

		enum class Code : uint8
		{
			Press,
			Release,
			Repeat,
			Count
		};

		KeyEvent(const Code _code, const uint8 _charCode) :
			charCode(_charCode)
		{ 
			code = ToUnderlyingType<Code>(_code);
		}

		uint8 charCode;
	};
}