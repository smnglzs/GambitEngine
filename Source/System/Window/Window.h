#pragma once

#include "Base/GambitBasePCH.h"
#include "System/Export.h"
#include "System/Window/Backend/OpenGL/GLContextSettings.h" // TODO: change this
#include "System/Window/WindowSettings.h"

struct GLFWwindow;
namespace gb
{
	class GAMBIT_SYSTEM_API Window
	{
	public:
		Window(const WindowSettings& winSettings, const GLContextSettings ctxSettings);
		virtual ~Window();
		
		void	BindContext();
		void	UnbindContext();
		void	PollEvents();
		void	SwapBuffers();

		bool	IsDecorated()  const;
		bool	IsFocused()	   const;
		bool	IsFullscreen() const;
		bool	IsMaximized()  const;
		bool	IsMinimized()  const;
		bool	IsResizable()  const;
		bool	IsVisible()	   const;
		bool	ShouldClose()  const;

		vec2i	GetSize() const;
		void*	GetWindowPtr() const { return m_windowImpl; }

		void	SetAspectRatio(const int32 width, const int32 height);
		void	SetFullscreen(const bool fullscreen);
		void	SetPosition(const int32 posX, const int32 posY);
		void	SetPosition(const vec2i& position);
		void	SetSize(const int32 width, const int32 height);
		void	SetSize(const vec2i& size);
		void	SetSizeLimits(const int32 minWidth, const int32 minHeight, const int32 maxWidth, const int32 maxHeight);
		void	SetSizeLimits(const vec2i& minSize, const vec2i& maxSize);

		void	ToggleFullscreen();
		 
	private:
		int32	GetAttrib(int32 glfwAttrib) const;
		void	SetCallbacks();

	private:
		GLFWwindow* m_windowImpl; // TODO: replace GLFW w/ API allowing for D3D contexts?
		std::string	m_title;
		vec2i		m_position;
		vec2i		m_size;
		bool		m_isContextBound;
		bool		m_isFullscreen;
		bool		m_updateViewport;
	};
}