#pragma once
#include "Base/GambitBasePCH.h"
//#include "Device/Export.h"

namespace gb
{
	struct GLContextSettings
	{
		uint8 majorVersion   : 3 = 4;
		uint8 minorVersion   : 3 = 6;
		uint8 isCoreProfile  : 1 = 1;
		uint8 isDebugContext : 1 = 0;
	};
}