#pragma once
#include "Base/GambitBasePCH.h"
#include "System/Export.h"

namespace gb
{
	struct WindowSettings
	{
		std::string  title   = "GambitEngine";
		vec2i		 size    = { 1600, 900 };
		float		 opacity = 1.f;

		uint8 decorated  : 1 = 1;
		uint8 focused	 : 1 = 1;
		uint8 fullscreen : 1 = 0;
		uint8 maximized  : 1 = 0;
		uint8 resizable  : 1 = 0;
		uint8 visible	 : 1 = 1;
		uint8 vsync		 : 1 = 1;
	};
}