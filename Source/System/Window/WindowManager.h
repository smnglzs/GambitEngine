#pragma once
#include "Base/GambitBasePCH.h"
#include "Base/Singleton/Singleton.h"
#include "System/Export.h"
#include "System/Window/Window.h"

namespace gb
{
	class GAMBIT_SYSTEM_API WindowManager final : public ISingleton
	{
	public:
		WindowManager();
		~WindowManager();

		virtual void Init() override;
		
		void CreateTransientWindow();
		void DestroyTransientWindow();

		Window* CreateWindow(const WindowSettings& winSettings, const GLContextSettings ctxSettings);

		enum class EWindowSlot : uint8
		{
			PrimaryWindow,
			SecondaryWindow
		};

		Window* GetWindow(const EWindowSlot winSlot = EWindowSlot::PrimaryWindow);

	private:
		std::vector<Shared<Window>> m_windows;
		Unique<Window> m_transientWindow;
	};
}

GB_CREATE_SINGLETON_ACCESSOR(WindowManager, WindowManager, GAMBIT_SYSTEM_API);