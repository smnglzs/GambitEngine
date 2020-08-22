#pragma once

#include "Base/Common/Common.h"
#include "Base/Common/Math.h"
#include "Device/Export.h"

namespace gb
{
	enum class GAMBIT_DEVICE_API EWindowFlags : uint8_t
	{
		Decorated	= (1 << 0),
		Focused		= (1 << 1),
		Fullscreen  = (1 << 2),
		Maximized	= (1 << 3),
		Resizable	= (1 << 4),
		Visible		= (1 << 5),

		Default	= Decorated | Resizable | Focused | Visible
	};
	ENABLE_BITMASK_OPERATORS(EWindowFlags);

	struct GAMBIT_DEVICE_API WindowSettings final
	{
		std::string  title  = "GambitEngine";
		vec2i		 size	= { 1900, 1080 };
		EWindowFlags flags	= EWindowFlags::Default;
	};
}