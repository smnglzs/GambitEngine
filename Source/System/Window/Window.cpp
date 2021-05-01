#include "Window.h"
#include "Base/LoggerManager/LoggerManager.h"
#include <iostream>

// TODO: GB_GLFW_PLATFORM
#include "GLFW/glfw3.h"

// TODO: GB_PLATFORM
#define GLFW_EXPOSE_NATIVE_WIN32
#include "GLFW/glfw3native.h"

namespace gb
{
	Window::Window(const WindowSettings& winSettings, const GLContextSettings ctxSettings) :
		m_glfwWindow(nullptr),
		m_title(winSettings.title),
		m_position({0, 0}),
		m_size(winSettings.size),
		m_opacity(winSettings.opacity),
		m_updateViewport(false),
		m_isContextBound(false),
		m_fixedAspectRatio(winSettings.fixedAspectRatio),
		m_isFullscreen(winSettings.fullscreen)
	{	
		// void* winPtr = (void*)GetWindowLongPtr(glfwGetWin32Window(m_glfwWindow), 0);

		// Set window creation hints.
		glfwWindowHint(GLFW_RESIZABLE, winSettings.resizable);
		glfwWindowHint(GLFW_DECORATED, winSettings.decorated);
		glfwWindowHint(GLFW_FOCUSED,   winSettings.focused);
		glfwWindowHint(GLFW_MAXIMIZED, winSettings.maximized);
		glfwWindowHint(GLFW_VISIBLE,   winSettings.visible);
		glfwWindowHint(GLFW_FLOATING,  winSettings.floating);

		// TODO: OpenGL hints force a RenderWindow; consider distinguishing the two context settings.
		// Set (window's) context creation hints.
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, ctxSettings.majorVersion);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, ctxSettings.majorVersion);
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT,  ctxSettings.isDebugContext);
		glfwWindowHint(GLFW_OPENGL_PROFILE,		   ctxSettings.isCoreProfile ? GLFW_OPENGL_CORE_PROFILE : GLFW_OPENGL_COMPAT_PROFILE);

		GLFWmonitor* monitor = nullptr;
		if (m_isFullscreen)
		{
			monitor = glfwGetPrimaryMonitor();
			const GLFWvidmode* videoMode = glfwGetVideoMode(monitor);

			// Set fullscreen video mode hints.
			glfwWindowHint(GLFW_RED_BITS,	  videoMode->redBits);
			glfwWindowHint(GLFW_GREEN_BITS,   videoMode->greenBits);
			glfwWindowHint(GLFW_BLUE_BITS,	  videoMode->blueBits);
			glfwWindowHint(GLFW_REFRESH_RATE, videoMode->refreshRate);

			m_size.x = videoMode->width;
			m_size.y = videoMode->height;
		}

		// Attempt to create the window.
		if (m_glfwWindow = glfwCreateWindow(m_size.x, m_size.y, m_title.c_str(), monitor, nullptr))
		{
			glfwMakeContextCurrent(m_glfwWindow);
			SetCallbacks();
			SetOpacity(m_opacity);
			if (m_fixedAspectRatio) // TODO: Move to function.
				glfwSetWindowAspectRatio(m_glfwWindow, m_size.x, m_size.y);
		}
		else
		{
			const char* description;
			int error = glfwGetError(&description); // TODO: GLFW error log/check macro.
			std::cout << "Window creation failed! Error #" << error << " : " << description << "\n";
			assert(false);
		}
	}

	Window::~Window()
	{
		glfwDestroyWindow(m_glfwWindow);
	}

#pragma region Event-handling
	Window::ListenerId Window::AddEventListener(const uint8 eventCode, WindowEventListener&& listener)
	{
		return m_eventCaster[eventCode].Add(std::move(listener));
	}

	void Window::RemoveEventListener(const uint8 eventCode, ListenerId listenerId)
	{
		m_eventCaster[eventCode].Remove(listenerId);
	}

	void Window::DispatchEvent(const WindowEvent winEvent)
	{
		m_eventCaster[winEvent.code].Broadcast(winEvent);
	}
#pragma endregion
	
#pragma region Getters
	bool  Window::IsFocused()	 const { return GetBoolAttrib(GLFW_FOCUSED);   }
	bool  Window::IsVisible()	 const { return GetBoolAttrib(GLFW_VISIBLE);   }
	bool  Window::IsMaximized()  const { return GetBoolAttrib(GLFW_MAXIMIZED); }
	bool  Window::IsMinimized()  const { return GetBoolAttrib(GLFW_ICONIFIED); }
	bool  Window::IsResizable()  const { return GetBoolAttrib(GLFW_RESIZABLE); }
	bool  Window::IsDecorated()  const { return GetBoolAttrib(GLFW_DECORATED); }

	bool  Window::ShouldClose()  const { return glfwWindowShouldClose(m_glfwWindow) == GLFW_TRUE; }
#pragma endregion

#pragma region Setters
	void Window::BindContext()
	{
		glfwMakeContextCurrent(m_glfwWindow);
		m_isContextBound = true;
	}

	void Window::UnbindContext()
	{
		glfwMakeContextCurrent(nullptr);
		m_isContextBound = false;
	}

	// TODO: Broadcast event to resize viewports and update cameras
	void Window::SetFullscreen(bool fullscreen)
	{
		if (m_isFullscreen == fullscreen)
			return;

		if (fullscreen)
		{
			glfwGetWindowPos(m_glfwWindow, &m_position.x, &m_position.y);
			glfwGetWindowSize(m_glfwWindow, &m_size.x, &m_size.y);

			GLFWmonitor* monitor = glfwGetPrimaryMonitor();
			const GLFWvidmode* videoMode = glfwGetVideoMode(monitor);
			glfwSetWindowMonitor(m_glfwWindow, monitor, 0, 0, videoMode->width, videoMode->height, 0);
		}
		else
		{
			glfwSetWindowMonitor(m_glfwWindow, nullptr, m_position.x, m_position.y, m_size.x, m_size.y, 0);
		}

		m_updateViewport = true;
	}

	void Window::SetIcon(const Image& image)
	{
		if (!image.IsValid())
		{
			// TODO: Warn invalid image
			return;
		}

		GLFWimage icon = { image.GetWidth(), image.GetHeight(), (byte*)image.GetPixelData() };
		glfwSetWindowIcon(m_glfwWindow, 1, &icon);
	}

	void Window::ResetIcon()
	{
		glfwSetWindowIcon(m_glfwWindow, 0, NULL);
	}

	void Window::RequestAttention()
	{
		glfwRequestWindowAttention(m_glfwWindow);
	}

	// TODO: (SetSize overloads) 
	//	- Add range checks
	//	- Check if resize or not! Update width & height!
	void Window::SetSize(const vec2i& size) 
	{ 
		glfwSetWindowSize(m_glfwWindow, size.x, size.y); 
	}

	void Window::SetSize(const int32 width, const int32 height) 
	{ 
		glfwSetWindowSize(m_glfwWindow, width, height); 
	} 

	void Window::SetOpacity(const float opacity)
	{
		gbCheckRange(opacity >= 0.f && opacity <= 1.f);
		m_opacity = opacity;
		glfwSetWindowOpacity(m_glfwWindow, m_opacity);
	}

	void Window::SetPosition(const vec2i& pos) 
	{ 
		glfwSetWindowPos(m_glfwWindow, pos.x, pos.y); 
	}

	void Window::SetPosition(const int32 posX, const int32  posY) 
	{ 
		glfwSetWindowPos(m_glfwWindow, posX, posY); 
	}

	void Window::SetAspectRatio(const int32 width, const int32  height) 
	{ 
		glfwSetWindowAspectRatio(m_glfwWindow, width, height);
	}

	void Window::SetSizeLimits(const vec2i& minSize, const vec2i& maxSize) 
	{ 
		glfwSetWindowSizeLimits(m_glfwWindow, minSize.x, minSize.y, maxSize.x, maxSize.y); 
	}

	void Window::SetSizeLimits(const int32 minWidth, const int32 minHeight, const int32 maxWidth, const int32 maxHeight) 
	{ 
		glfwSetWindowSizeLimits(m_glfwWindow, minWidth, minHeight, maxWidth, maxHeight); 
	}

	void Window::SetTitle(const std::string& title)
	{
		glfwSetWindowTitle(m_glfwWindow, title.c_str());
	}
	 
	void Window::ToggleFullscreen() 
	{
		SetFullscreen(!m_isFullscreen);
		m_isFullscreen = !m_isFullscreen;
	}
#pragma endregion

	void Window::PollEvents()
	{
		glfwPollEvents();
	}

	void Window::SwapBuffers()
	{
		glfwSwapBuffers(m_glfwWindow);
	}

	int32 Window::GetAttrib(int32 glfwAttrib) const
	{
		return glfwGetWindowAttrib(m_glfwWindow, glfwAttrib);
	}

	bool Window::GetBoolAttrib(int32 glfwBoolAttrib) const
	{
		return GetAttrib(glfwBoolAttrib) == GLFW_TRUE;
	}

	void Window::GiveFocus()
	{
		glfwFocusWindow(m_glfwWindow);
	}

	Window* Window::GetGambitPointer(GLFWwindow* window)
	{
		return window ? (Window*)glfwGetWindowUserPointer(window) : nullptr;
	}

#pragma region Callbacks
	void Window::OnSetFocus(GLFWwindow* window, int focused)
	{
		if (Window* win = GetGambitPointer(window))
		{
			WindowEvent winEvent;
			winEvent.window = win;
			winEvent.code = (uint8)WindowEvent::ECode::FocusChanged;
			winEvent.focused = focused;
			win->DispatchEvent(winEvent);
		}
		else
		{
			// TODO: Invoke OnWindowLost.
		}
	}

	void Window::OnSetClose(GLFWwindow* window)
	{
		
	}

	void Window::SetCallbacks()
	{
		// Sets the user pointer, retrievable with GetGambitPointer.
		// This pointer affords the below C-style callbacks the ability to pipe GLFW events to specific windows.
		glfwSetWindowUserPointer(m_glfwWindow, this);

		glfwSetWindowCloseCallback(m_glfwWindow, OnSetClose);
		glfwSetWindowFocusCallback(m_glfwWindow, OnSetFocus);
	}
#pragma endregion

}

/* [NOTES]
	- GLFWWindow could be GLWindow.
	- State getters could be simplified/macrofied.
	- TODO: 
		- glfwRestoreWindow, maximize
		- hide, show
		- refresh callback
		- get GLFW_HOVERED
		- SetFloating, SetFocusOnShow, AutoIconify
*/
