#pragma once

#include "Base/Common/Common.h"
#include "Device/Display/Window/WindowSettings.h"

struct GLFWwindow;

namespace gb
{
	class Window
	{
	public:
		Window(const WindowSettings& settings);
		~Window();
		
		bool IsDecorated() const;
		bool IsFocused() const;
		bool IsFullscreen() const;
		bool IsMaximized() const;
		bool IsMinimized() const;
		bool IsResizable() const;
		bool IsValid() const;
		bool IsVisible() const;

		void SetAspectRatio(uint16 width, uint16 height);
		void SetFullscreen(bool value);
		void SetPosition(uint16 posX, uint16 posY);
		void SetPosition(const glm::u16vec2& position);
		void SetMaximumSize(uint16 width, uint16 height);
		void SetMaximumSize(const glm::u16vec2& size);
		void SetMinimumSize(uint16 width, uint16 height);
		void SetMinimumSize(const glm::u16vec2& size);
		void SetSize(uint16 width, uint16 height);
		void SetSize(const glm::u16vec2& size);
		void SetSizeLimits(uint16 minWidth, uint16 minHeight, uint16 maxWidth, uint16 maxHeight);
		void SetSizeLimits(const glm::u16vec2& minSize, const glm::u16vec2& maxSize);

	private:
		int32 GetAttrib(int32 glfwAttrib) const;

		std::string m_title;
		GLFWwindow* m_glfwWindow;
		glm::u16vec2 m_size;
		glm::u16vec2 m_position;
		bool m_fullscreen;
	};
}