#pragma once
#include "Base/GambitBasePCH.h"
//#include "Device/Export.h"

namespace gb
{
	struct GLContextSettings
	{
		uint8 majorVersion   : 3 = 4;
		uint8 minorVersion   : 3 = 6;

		GB_FLAG(isCoreProfile,  1);
		GB_FLAG(isDebugContext, 0);
	};
}