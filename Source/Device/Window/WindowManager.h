#pragma once

#include "Base/Common/Common.h"
#include "Base/Singleton/Singleton.h"
#include "Device/Export.h"
#include "Device/Window/Window.h"

namespace gb
{
	class GAMBIT_DEVICE_API WindowManager final : public ISingleton
	{
	public:
		WindowManager();
		~WindowManager();

		bool CreateWindow(const WindowSettings& winSettings);
		void PollEvents();
		bool ShouldClose() const;
		void SwapBuffers();

	private:
		static constexpr uint8 MAX_WINDOW_COUNT = 1;
		Window* m_windows[MAX_WINDOW_COUNT];

		uint8 m_windowCount;
		uint8 m_currentWindowIdx;
	};
}

CREATE_SINGLETON_ACCESSOR(WindowManager, WindowManager, GAMBIT_DEVICE_API);