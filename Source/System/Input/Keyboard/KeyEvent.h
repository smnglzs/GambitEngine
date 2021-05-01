#pragma once
#include "Base/GambitBasePCH.h"
#include "System/Export.h"

namespace gb
{
	struct GAMBIT_SYSTEM_API KeyEvent : public Event
	{
		enum class ECode : uint8
		{
			Press,
			Release,
			Repeat,
			Count
		};

		KeyEvent() = default;
		KeyEvent(const ECode _code, const uint8 _charCode) :
			charCode(_charCode)
		{ 
			code = ToUnderlyingType<ECode>(_code);
		}

		uint8 charCode;
	};
}