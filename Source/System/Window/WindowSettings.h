#pragma once
#include "Base/GambitBasePCH.h"
#include "System/Export.h"

namespace gb
{
	struct WindowSettings
	{
		std::string  title   = "GambitEngine";
		vec2i		 size    = { 1900, 1080 };
		float		 opacity = 1.f;

		GB_FLAG(decorated,		  1);
		GB_FLAG(fixedAspectRatio, 0);
		GB_FLAG(floating,		  0);
		GB_FLAG(focused,		  1);
		GB_FLAG(fullscreen,		  0);
		GB_FLAG(maximized,		  0);
		GB_FLAG(resizable,		  1);
		GB_FLAG(visible,		  1);
		GB_FLAG(vsync,			  0);
	};
}