#pragma once

#include "Base/Common/Common.h"
#include "Base/Singleton/Singleton.h"
#include "Device/Export.h"

namespace gb
{
	class GAMBIT_DEVICE_API InputManager : public ISingleton
	{
	public:
		InputManager();
		~InputManager();
	};
}

CREATE_SINGLETON_ACCESSOR(InputManager, InputManager, GAMBIT_DEVICE_API);