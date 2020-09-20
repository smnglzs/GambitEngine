#pragma once

#include "Base/Common/Common.h"
#include "Device/Window/WindowSettings.h"
#include "Device/Export.h"

struct GLFWwindow;

namespace gb
{
	class GAMBIT_DEVICE_API Window final
	{
	public:
		Window(const WindowSettings& settings);
		~Window();

		bool  IsDecorated()  const;
		bool  IsFocused()	 const;
		bool  IsFullscreen() const;
		bool  IsMaximized()  const;
		bool  IsMinimized()  const;
		bool  IsResizable()  const;
		bool  IsVisible()	 const;
		bool  ShouldClose()  const;
		vec2i GetSize()		 const;

		void SetAspectRatio	(int32 width, int32 height);
		void SetFullscreen(bool fullscreen);
		void SetPosition(int32 posX, int32 posY);
		void SetPosition(const vec2i& position);
		void SetSize(int32 width, int32 height);
		void SetSize(const vec2i& size);
		void SetSizeLimits(int32 minWidth, int32 minHeight, int32 maxWidth, int32 maxHeight);
		void SetSizeLimits(const vec2i& minSize, const vec2i& maxSize);

		void BindContext();
		void UnbindContext();
		void PollEvents();
		void SwapBuffers();

	private:
		int32 GetAttrib(int32 glfwAttrib) const;
		
	private:
		std::string m_title;
		vec2i		m_position;
		vec2i		m_size;
		GLFWwindow* m_glfwWindow;
		bool		m_contextBound;
		bool		m_updateViewport;
	};
}