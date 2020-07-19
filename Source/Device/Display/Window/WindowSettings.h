#pragma once

#include "Base/Common/Common.h"
#include "Base/Common/Math.h"
#include "Device/Export.h"

namespace gb
{
	enum class GAMBIT_DEVICE_API EWindowFlags : uint8_t
	{
		Decorated  = (1 << 0),
		Focused	   = (1 << 1),
		Fullscreen = (1 << 2),
		Maximized  = (1 << 3),
		Resizable  = (1 << 4),
		Visible	   = (1 << 5),

		Default	= Decorated | Resizable | Focused | Visible
	};
	ENABLE_BITMASK_OPERATORS(EWindowFlags);

	struct GAMBIT_DEVICE_API WindowSettings final
	{
		std::string title;
		glm::u16vec2 size = { 1280u, 720u };
		EWindowFlags flags = EWindowFlags::Default;
		bool fullscreen = false;
	};
}