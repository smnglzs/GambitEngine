#pragma once

#include "GLFW/glfw3.h"

#include "Base/Common/Common.h"
#include "Base/Common/Export.h"
#include "Device/Display/Window/WindowSettings.h"

namespace gb
{
	class GAMBIT_API Window
	{
	public:
		Window(const WindowSettings& settings);
		~Window();
		
		void SetFullscreen(bool value);
		void SetSize(uint16 width, uint16 height);
		void SetSize(const glm::u16vec2& size);
		//void SetPosition()

		bool IsDecorated()	const;
		bool IsFocused()	const;
		bool IsFullscreen() const;
		bool IsMaximized()  const;
		bool IsMinimized()  const;
		bool IsResizable()  const;
		bool IsVisible()	const;

	private:
		std::string m_title;
		GLFWwindow* m_glfwWindow;
		glm::u16vec2 m_size;
		bool m_fullscreen;
	};
}