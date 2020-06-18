#pragma once

#include "Base/Common/Common.h"
#include "Base/Common/Export.h"
#include "Window/Window/WindowManager.h"

namespace gb
{
	class GAMBIT_API GambitWindow final
	{
	public:
		GambitWindow();
		~GambitWindow();

		// TODO (Simon): Add startUp/shutDown definition requirement in common module interface
		void startUp();
		void shutDown();

	private:
		WindowManager* m_windowManager;

	};
}