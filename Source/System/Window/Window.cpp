#include "Window.h"
#include "Base/LoggerManager/LoggerManager.h"
#include "GLFW/glfw3.h"

#include <iostream>

namespace gb
{
	Window::Window(const WindowSettings& winSettings, const GLContextSettings ctxSettings) :
		m_title(winSettings.title),
		m_position({0, 0}),
		m_size(winSettings.size),
		m_windowImpl(nullptr),
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

		// TODO: OpenGL hints force a RenderWindow, considering distinguishing the two
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

		if (m_windowImpl = glfwCreateWindow(m_size.x, m_size.y, m_title.c_str(), monitor, nullptr))
		{
			glfwSetWindowUserPointer(m_windowImpl, this);
			glfwMakeContextCurrent(m_windowImpl);
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
		glfwDestroyWindow(m_windowImpl);
	}

#pragma region Getters
	bool  Window::IsFocused()	 const { return GetAttrib(GLFW_FOCUSED) == GLFW_TRUE; }
	bool  Window::IsFullscreen() const { return m_isFullscreen; }
	bool  Window::IsVisible()	 const { return GetAttrib(GLFW_VISIBLE) == GLFW_TRUE; }
	bool  Window::IsMaximized()  const { return GetAttrib(GLFW_MAXIMIZED) == GLFW_TRUE; }
	bool  Window::IsMinimized()  const { return GetAttrib(GLFW_ICONIFIED) == GLFW_TRUE; }
	bool  Window::IsResizable()  const { return GetAttrib(GLFW_RESIZABLE) == GLFW_TRUE; }
	bool  Window::IsDecorated()  const { return GetAttrib(GLFW_DECORATED) == GLFW_TRUE; }
	bool  Window::ShouldClose()  const { return glfwWindowShouldClose(m_windowImpl) == GLFW_TRUE; }
	vec2i Window::GetSize()		 const { return m_size; }
#pragma endregion

#pragma region Setters
	void Window::BindContext()
	{
		glfwMakeContextCurrent(m_windowImpl);
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
		if (IsFullscreen() == fullscreen)
			return;

		if (fullscreen)
		{
			glfwGetWindowPos(m_windowImpl, &m_position.x, &m_position.y);
			glfwGetWindowSize(m_windowImpl, &m_size.x, &m_size.y);

			GLFWmonitor* monitor = glfwGetPrimaryMonitor();
			const GLFWvidmode* videoMode = glfwGetVideoMode(monitor);
			glfwSetWindowMonitor(m_windowImpl, monitor, 0, 0, videoMode->width, videoMode->height, 0);
		}
		else
		{
			glfwSetWindowMonitor(m_windowImpl, nullptr, m_position.x, m_position.y, m_size.x, m_size.y, 0);
		}

		m_updateViewport = true;
	}

	// TODO: add range checks
	void Window::SetSize(const vec2i& size) 
	{ 
		glfwSetWindowSize(m_windowImpl, size.x, size.y); 
	}

	void Window::SetSize(const int32 width, const int32 height) 
	{ 
		glfwSetWindowSize(m_windowImpl, width, height); 
	} // TODO: Check if resize or not! Update width & height!

	void Window::SetPosition(const vec2i& pos) 
	{ 
		glfwSetWindowPos(m_windowImpl, pos.x, pos.y); 
	}

	void Window::SetPosition(const int32 posX, const int32  posY) 
	{ 
		glfwSetWindowPos(m_windowImpl, posX, posY); 
	}

	void Window::SetAspectRatio(const int32 width, const int32  height) 
	{ 
		glfwSetWindowAspectRatio(m_windowImpl, width, height);
	}

	void Window::SetSizeLimits(const vec2i& minSize, const vec2i& maxSize) 
	{ 
		glfwSetWindowSizeLimits(m_windowImpl, minSize.x, minSize.y, maxSize.x, maxSize.y); 
	}

	void Window::SetSizeLimits(const int32 minWidth, const int32 minHeight, const int32 maxWidth, const int32 maxHeight) 
	{ 
		glfwSetWindowSizeLimits(m_windowImpl, minWidth, minHeight, maxWidth, maxHeight); 
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
		glfwSwapBuffers(m_windowImpl);
	}

	int32 Window::GetAttrib(int32 glfwAttrib) const
	{
		return glfwGetWindowAttrib(m_windowImpl, glfwAttrib);
	}

#pragma region Callbacks
	// For multiple windows, we can find GLFWwindow* in linear search
	// Called directly after the GLFW close flag has been set
	void OnSetClose(GLFWwindow* window)
	{
		
	}

	void Window::SetCallbacks()
	{
		glfwSetWindowCloseCallback(m_windowImpl, OnSetClose);
	}
#pragma endregion

}

/* [NOTES]
	- GLFWWindow could be GLWindow
	- State getters could be simplified/macrofied
*/
