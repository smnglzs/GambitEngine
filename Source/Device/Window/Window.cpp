#include "Window.h"
#include "Base/LoggerManager/LoggerManager.h"
#include "GLFW/glfw3.h"

namespace gb
{
	Window::Window(const WindowSettings& settings) :
		m_title(settings.title),
		m_position({0, 0}),
		m_size(settings.size),
		m_glfwWindow(nullptr),
		m_updateViewport(false),
		m_contextBound(false)
	{	
		glfwWindowHint(GLFW_RESIZABLE, Bitmask::Contains(settings.flags, EWindowFlags::Resizable));
		glfwWindowHint(GLFW_DECORATED, Bitmask::Contains(settings.flags, EWindowFlags::Decorated));
		glfwWindowHint(GLFW_FOCUSED,   Bitmask::Contains(settings.flags, EWindowFlags::Focused));
		glfwWindowHint(GLFW_MAXIMIZED, Bitmask::Contains(settings.flags, EWindowFlags::Maximized));
		glfwWindowHint(GLFW_VISIBLE,   Bitmask::Contains(settings.flags, EWindowFlags::Visible));
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);

		if (Bitmask::Contains(settings.flags, EWindowFlags::Fullscreen))
		{
			GLFWmonitor* monitor = glfwGetPrimaryMonitor();
			const GLFWvidmode* videoMode = glfwGetVideoMode(monitor);

			glfwWindowHint(GLFW_RED_BITS, videoMode->redBits);
			glfwWindowHint(GLFW_GREEN_BITS, videoMode->greenBits);
			glfwWindowHint(GLFW_BLUE_BITS, videoMode->blueBits);
			glfwWindowHint(GLFW_REFRESH_RATE, videoMode->refreshRate);

			m_glfwWindow = glfwCreateWindow(videoMode->width, videoMode->height, m_title.c_str(), monitor, nullptr);
		}
		else
		{
			m_glfwWindow = glfwCreateWindow(m_size.x, m_size.y, m_title.c_str(), nullptr, nullptr);
		}
		assert(m_glfwWindow && "Window creation failed!");

		glfwSetWindowUserPointer(m_glfwWindow, this);
	}

	Window::~Window()
	{
		glfwDestroyWindow(m_glfwWindow);
	}

#pragma region State Getters
	bool Window::IsFocused() const
	{
		return GetAttrib(GLFW_FOCUSED) == GLFW_TRUE;
	}

	bool Window::IsFullscreen() const
	{
		return glfwGetWindowMonitor(m_glfwWindow);
	}

	bool Window::IsVisible() const
	{
		return GetAttrib(GLFW_VISIBLE) == GLFW_TRUE;
	}

	bool Window::IsMaximized() const
	{
		return GetAttrib(GLFW_MAXIMIZED) == GLFW_TRUE;
	}

	bool Window::IsMinimized() const
	{
		return GetAttrib(GLFW_ICONIFIED) == GLFW_TRUE;
	}

	bool Window::IsResizable() const
	{
		return GetAttrib(GLFW_RESIZABLE) == GLFW_TRUE;
	}

	bool Window::IsDecorated() const
	{
		return GetAttrib(GLFW_DECORATED) == GLFW_TRUE;
	}

	bool Window::ShouldClose() const
	{
		return glfwWindowShouldClose(m_glfwWindow) == GLFW_TRUE;
	}
#pragma endregion

#pragma region Setters
	void Window::SetAspectRatio(int32 width, int32 height)
	{
		glfwSetWindowAspectRatio(m_glfwWindow, width, height);
	}

	void Window::BindContext()
	{
		glfwMakeContextCurrent(m_glfwWindow);
		m_contextBound = true;
	}

	void Window::UnbindContext()
	{
		glfwMakeContextCurrent(nullptr);
		m_contextBound = false;
	}

	void Window::SetFullscreen(bool fullscreen)
	{
		if (IsFullscreen() == fullscreen)
		{
			return;
		}

		if (fullscreen)
		{
			glfwGetWindowPos(m_glfwWindow, &m_position.x, &m_position.y);
			glfwGetWindowSize(m_glfwWindow, &m_size.x, &m_size.y);

			GLFWmonitor* monitor = glfwGetPrimaryMonitor();
			const GLFWvidmode* videoMode = glfwGetVideoMode(monitor);

			glfwSetWindowMonitor(m_glfwWindow, monitor, m_position.x, 0, 0, videoMode->width, videoMode->height);
		}
		else
		{
			glfwSetWindowMonitor(m_glfwWindow, nullptr, m_position.x, m_position.y, m_size.x, m_size.y, 0);
		}

		m_updateViewport = true;
	}

	void Window::SetPosition(int32 posX, int32 posY)
	{
		glfwSetWindowPos(m_glfwWindow, posX, posY);
	}

	void Window::SetPosition(const vec2i& position)
	{
		glfwSetWindowPos(m_glfwWindow, position.x, position.y);
	}

	void Window::SetSize(int32 width, int32 height)
	{
		glfwSetWindowSize(m_glfwWindow, width, height);
	}

	void Window::SetSize(const vec2i& size)
	{
		glfwSetWindowSize(m_glfwWindow, size.x, size.y);
	}

	void Window::SetSizeLimits(int32 minWidth, int32 minHeight, int32 maxWidth, int32 maxHeight)
	{
		glfwSetWindowSizeLimits(m_glfwWindow, minWidth, minHeight, maxWidth, maxHeight);
	}

	void Window::SetSizeLimits(const vec2i& minSize, const vec2i& maxSize)
	{
		glfwSetWindowSizeLimits(m_glfwWindow, minSize.x, minSize.y, maxSize.x, maxSize.y);
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
}