#pragma once

#include "GLFW/glfw3.h"

#include "Base/Common/Common.h"
#include "Base/Common/Export.h"

namespace gb
{
	class GAMBIT_API Window
	{
	public:
		

	protected:
		

	private:
		Window(int width, int height, const char* title);
		~Window();

		GLFWwindow* m_glfwWindow;

		
	};
}