#pragma once

#include "Base/Common/Common.h"
#include "Device/Display/DisplayManager.h"
#include "Device/Input/InputManager.h"

namespace gb
{
	class GAMBIT_API Device final
	{
	public:
		Device();
		~Device();

		bool StartUp();
		void ShutDown();

	private:
		static void OnGLFWError(int error, const char* description);

		bool m_glfwInitialized;
	};
}