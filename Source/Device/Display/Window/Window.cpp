#include "Window.h"

#include "GLFW/glfw3.h"

namespace gb
{

	Window::Window(const WindowSettings& settings) :
		m_title(settings.title),
		m_glfwWindow(nullptr),
		m_size(settings.size),
		m_position({0u, 0u}),
		m_fullscreen(settings.fullscreen)
	{
		m_glfwWindow = glfwCreateWindow(m_size.x, m_size.y, m_title.c_str(), nullptr, nullptr);
		assert(m_glfwWindow && "Window creation failed!");
	}

	Window::~Window()
	{
		glfwDestroyWindow(m_glfwWindow);
	}

	void Window::SetAspectRatio(uint16 width, uint16 height)
	{
		GB_TODO_IMPL
	}

	void Window::SetFullscreen(bool value)
	{
		GB_TODO_IMPL
	}

	void Window::SetPosition(uint16 posX, uint16 posY)
	{
		GB_TODO_IMPL
	}

	void Window::SetPosition(const glm::u16vec2& position)
	{
		GB_TODO_IMPL
	}

	void Window::SetMaximumSize(const glm::u16vec2& size)
	{
		GB_TODO_IMPL
	}

	void Window::SetMaximumSize(uint16 width, uint16 height)
	{
		GB_TODO_IMPL
	}

	void Window::SetMinimumSize(const glm::u16vec2& size)
	{
		GB_TODO_IMPL
	}

	void Window::SetMinimumSize(uint16 width, uint16 height)
	{
		GB_TODO_IMPL
	}

	void Window::SetSize(uint16 width, uint16 height)
	{
		GB_TODO_IMPL
	}

	void Window::SetSize(const glm::u16vec2& size)
	{
		GB_TODO_IMPL
	}

	void Window::SetSizeLimits(uint16 minWidth, uint16 minHeight, uint16 maxWidth, uint16 maxHeight)
	{
		GB_TODO_IMPL
	}

	void Window::SetSizeLimits(const glm::u16vec2& minSize, const glm::u16vec2& maxSize)
	{
		GB_TODO_IMPL
	}

	bool Window::IsFocused() const
	{
		return GetAttrib(GLFW_FOCUSED) == GLFW_TRUE;
	}
	
	bool Window::IsFullscreen() const
	{
		return m_fullscreen;
	}

	bool Window::IsValid() const
	{
		return m_glfwWindow;
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

	int32 Window::GetAttrib(int32 glfwAttrib) const
	{
		return glfwGetWindowAttrib(m_glfwWindow, glfwAttrib);
	}
}