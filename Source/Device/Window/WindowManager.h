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

		virtual void Init() override;
		
		bool CreateWindow(const WindowSettings& winSettings);
		bool ShouldClose() const;
		void SwapBuffers();
		void PollEvents();
	
		vec2i GetSize() const;

	private:
		Window* m_window;
	};
}

CREATE_SINGLETON_ACCESSOR(WindowManager, WindowManager, GAMBIT_DEVICE_API);