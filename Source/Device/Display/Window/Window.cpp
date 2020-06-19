#include "Window.h"

namespace gb
{
	Window::Window(const WindowSettings& settings) :
		m_title(settings.title),
		m_glfwWindow(nullptr),
		m_size(settings.size),
		m_fullscreen(settings.fullscreen)
	{
		//m_glfwWindow = glfwCreateWindow(width, height, title, nullptr, nullptr);
	}

	Window::~Window()
	{
		glfwDestroyWindow(m_glfwWindow);
	}

	void Window::SetFullscreen(bool value)
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

	bool Window::IsFocused() const
	{
		return glfwGetWindowAttrib(m_glfwWindow, GLFW_FOCUSED) == GLFW_TRUE;
	}
	
	bool Window::IsFullscreen() const
	{
		return m_fullscreen;
	}

	bool Window::IsVisible() const
	{
		return glfwGetWindowAttrib(m_glfwWindow, GLFW_VISIBLE) == GLFW_TRUE;
	}

	bool Window::IsMaximized() const
	{
		return glfwGetWindowAttrib(m_glfwWindow, GLFW_MAXIMIZED) == GLFW_TRUE;
	}

	bool Window::IsMinimized() const
	{
		return glfwGetWindowAttrib(m_glfwWindow, GLFW_MAXIMIZED) == GLFW_FALSE;
	}

	bool Window::IsResizable() const
	{
		return glfwGetWindowAttrib(m_glfwWindow, GLFW_RESIZABLE) == GLFW_TRUE;
	}

	bool Window::IsDecorated() const
	{
		return glfwGetWindowAttrib(m_glfwWindow, GLFW_DECORATED) == GLFW_TRUE;;
	}
}