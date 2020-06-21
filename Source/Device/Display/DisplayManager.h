#pragma once

#include "Base/Common/Common.h"
#include "Base/Singleton/Singleton.h"
#include "Device/Display/Window/Window.h"

namespace gb
{
	class GAMBIT_API DisplayManager final : public ISingleton
	{
	public:
		DisplayManager();
		~DisplayManager();

		bool CreatePrimaryWindow(const WindowSettings& winSettings);

	private:
		Window* m_primaryWindow;
	};
}