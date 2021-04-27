#include "Window.h"
#include "Base/LoggerManager/LoggerManager.h"
#include "GLFW/glfw3.h"

#include <iostream>

namespace gb
{
	Window::Window(const WindowSettings& winSettings, const GLContextSettings ctxSettings) :
		m_windowPtr(nullptr),
		m_title(winSettings.title),
		m_position({0, 0}),
		m_size(winSettings.size),
		m_opacity(winSettings.opacity),
		m_updateViewport(false),
		m_isContextBound(false),
		m_isFullscreen(winSettings.fullscreen)
	{	
		// Window settings
		glfwWindowHint(GLFW_RESIZABLE, winSettings.resizable);
		glfwWindowHint(GLFW_DECORATED, winSettings.decorated);
		glfwWindowHint(GLFW_FOCUSED,   winSettings.focused);
		glfwWindowHint(GLFW_MAXIMIZED, winSettings.maximized);
		glfwWindowHint(GLFW_VISIBLE,   winSettings.visible);

		// TODO: OpenGL hints force a RenderWindow, consider distinguishing the two
		// Context settings
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, ctxSettings.majorVersion);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, ctxSettings.majorVersion);
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT,  ctxSettings.isDebugContext);
		glfwWindowHint(GLFW_OPENGL_PROFILE,		   ctxSettings.isCoreProfile ? GLFW_OPENGL_CORE_PROFILE : GLFW_OPENGL_COMPAT_PROFILE);

		GLFWmonitor* monitor = nullptr;
		if (m_isFullscreen)
		{
			monitor = glfwGetPrimaryMonitor();
			const GLFWvidmode* videoMode = glfwGetVideoMode(monitor);

			glfwWindowHint(GLFW_RED_BITS,	  videoMode->redBits);
			glfwWindowHint(GLFW_GREEN_BITS,   videoMode->greenBits);
			glfwWindowHint(GLFW_BLUE_BITS,	  videoMode->blueBits);
			glfwWindowHint(GLFW_REFRESH_RATE, videoMode->refreshRate);

			m_size.x = videoMode->width;
			m_size.y = videoMode->height;
		}

		if (m_windowPtr = glfwCreateWindow(m_size.x, m_size.y, m_title.c_str(), monitor, nullptr))
		{
			glfwMakeContextCurrent(m_windowPtr);
			SetCallbacks();
			SetOpacity(m_opacity);
		}
		else
		{
			const char* description;
			int error = glfwGetError(&description); // TODO: glfw error log/check macro
			std::cout << "Window creation failed! Error #" << error << " : " << description << "\n";
			assert(false);
		}
	}

	Window::~Window()
	{
		glfwDestroyWindow(m_windowPtr);
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
	bool  Window::IsFocused()	 const { return GetAttrib(GLFW_FOCUSED)			   == GLFW_TRUE; }
	bool  Window::IsVisible()	 const { return GetAttrib(GLFW_VISIBLE)			   == GLFW_TRUE; }
	bool  Window::IsMaximized()  const { return GetAttrib(GLFW_MAXIMIZED)		   == GLFW_TRUE; }
	bool  Window::IsMinimized()  const { return GetAttrib(GLFW_ICONIFIED)		   == GLFW_TRUE; }
	bool  Window::IsResizable()  const { return GetAttrib(GLFW_RESIZABLE)		   == GLFW_TRUE; }
	bool  Window::IsDecorated()  const { return GetAttrib(GLFW_DECORATED)		   == GLFW_TRUE; }
	bool  Window::ShouldClose()  const { return glfwWindowShouldClose(m_windowPtr) == GLFW_TRUE; }
#pragma endregion

#pragma region Setters
	void Window::BindContext()
	{
		glfwMakeContextCurrent(m_windowPtr);
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
			glfwGetWindowPos(m_windowPtr, &m_position.x, &m_position.y);
			glfwGetWindowSize(m_windowPtr, &m_size.x, &m_size.y);

			GLFWmonitor* monitor = glfwGetPrimaryMonitor();
			const GLFWvidmode* videoMode = glfwGetVideoMode(monitor);
			glfwSetWindowMonitor(m_windowPtr, monitor, 0, 0, videoMode->width, videoMode->height, 0);
		}
		else
		{
			glfwSetWindowMonitor(m_windowPtr, nullptr, m_position.x, m_position.y, m_size.x, m_size.y, 0);
		}

		m_updateViewport = true;
	}

	void Window::SetIcon(const Image& image)
	{
		GLFWimage icon = { image.GetWidth(), image.GetHeight(), (byte*)image.GetPixelData() };
		glfwSetWindowIcon(m_windowPtr, 1, &icon);
	}

	void Window::ResetIcon()
	{
		glfwSetWindowIcon(m_windowPtr, 0, NULL);
	}

	void Window::RequestAttention()
	{
		glfwRequestWindowAttention(m_windowPtr);
	}

	// TODO: (SetSize overloads) 
	//	- Add range checks
	//	- Check if resize or not! Update width & height!
	void Window::SetSize(const vec2i& size) 
	{ 
		glfwSetWindowSize(m_windowPtr, size.x, size.y); 
	}

	void Window::SetSize(const int32 width, const int32 height) 
	{ 
		glfwSetWindowSize(m_windowPtr, width, height); 
	} 

	void Window::SetOpacity(const float opacity)
	{
		gbCheckRange(opacity >= 0.f && opacity <= 1.f);
		m_opacity = opacity;
		glfwSetWindowOpacity(m_windowPtr, m_opacity);
	}

	void Window::SetPosition(const vec2i& pos) 
	{ 
		glfwSetWindowPos(m_windowPtr, pos.x, pos.y); 
	}

	void Window::SetPosition(const int32 posX, const int32  posY) 
	{ 
		glfwSetWindowPos(m_windowPtr, posX, posY); 
	}

	void Window::SetAspectRatio(const int32 width, const int32  height) 
	{ 
		glfwSetWindowAspectRatio(m_windowPtr, width, height);
	}

	void Window::SetSizeLimits(const vec2i& minSize, const vec2i& maxSize) 
	{ 
		glfwSetWindowSizeLimits(m_windowPtr, minSize.x, minSize.y, maxSize.x, maxSize.y); 
	}

	void Window::SetSizeLimits(const int32 minWidth, const int32 minHeight, const int32 maxWidth, const int32 maxHeight) 
	{ 
		glfwSetWindowSizeLimits(m_windowPtr, minWidth, minHeight, maxWidth, maxHeight); 
	}

	void Window::SetTitle(const std::string& title)
	{
		glfwSetWindowTitle(m_windowPtr, title.c_str());
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
		glfwSwapBuffers(m_windowPtr);
	}

	int32 Window::GetAttrib(int32 glfwAttrib) const
	{
		return glfwGetWindowAttrib(m_windowPtr, glfwAttrib);
	}

	void Window::GiveFocus()
	{
		glfwFocusWindow(m_windowPtr);
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
			winEvent.code = (uint8)WindowEvent::Code::FocusChanged;
			winEvent.focused = focused;
			win->DispatchEvent(winEvent);
		}
		else
		{
			// TODO: window lost warning
		}
	}

	void Window::OnSetClose(GLFWwindow* window)
	{
		
	}

	void Window::SetCallbacks()
	{
		// Sets the user pointer, retrievable with GetGambitPointer.
		// This pointer affords the below C-style callbacks the ability to pipe GLFW events to specific windows.
		glfwSetWindowUserPointer(m_windowPtr, this);

		glfwSetWindowCloseCallback(m_windowPtr, OnSetClose);
		glfwSetWindowFocusCallback(m_windowPtr, OnSetFocus);
	}
#pragma endregion

}

/* [NOTES]
	- GLFWWindow could be GLWindow
	- State getters could be simplified/macrofied
*/
