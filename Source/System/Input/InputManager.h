#pragma once
#include "Base/GambitBasePCH.h"
#include "Base/Singleton/Singleton.h"
#include "System/Export.h"

namespace gb
{
	class GAMBIT_SYSTEM_API InputManager : public ISingleton
	{
	public:
		InputManager();
		~InputManager();
	};
}

GB_CREATE_SINGLETON_ACCESSOR(InputManager, InputManager, GAMBIT_SYSTEM_API);