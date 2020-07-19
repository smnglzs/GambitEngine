#pragma once

#include "Base/Common/Common.h"
#include "Base/Singleton/Singleton.h"
#include "Device/Export.h"
#include "Device/Display/Window/Window.h"

namespace gb
{
	class GAMBIT_DEVICE_API DisplayManager final : public ISingleton
	{
	public:
		DisplayManager();
		virtual ~DisplayManager();

		bool CreatePrimaryWindow(const WindowSettings& winSettings);

	private:
		Window* m_primaryWindow;
	};
}

CREATE_SINGLETON_ACCESSOR(DisplayManager, DisplayManager, GAMBIT_DEVICE_API);