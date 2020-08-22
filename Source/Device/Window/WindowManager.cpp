#include "WindowManager.h"
#include "Base/LoggerManager/LoggerManager.h"

#include "GLFW/glfw3.h"

CREATE_LOG_CHANNEL(WindowManagerInfo, "WindowManagerInfo", gb::EOutputType::Both, gb::ELogLevel::Info, "Device.txt");

namespace gb
{
	WindowManager::WindowManager() :
		m_windows(),
		m_windowCount(0u),
		m_currentWindowIdx(0u)
	{
		ADD_LOG_CHANNEL(WindowManagerInfo, "WindowManagerInfo");
		glfwSwapInterval(1);
	}

	WindowManager::~WindowManager()
	{
		// kill windows
	}

	bool WindowManager::CreateWindow(const WindowSettings& winSettings)
	{
		if (m_windowCount >= MAX_WINDOW_COUNT)
		{
			LOG("WindowManagerInfo", "{}: The maximum number of windows have been created!\n", __func__);
			return false;
		}
		else
		{
			m_windows[m_currentWindowIdx] = new Window(winSettings); // TODO: Refactor for multiple windows
			m_windowCount++;
			return true;
		}
	}

	void WindowManager::PollEvents()
	{
		if (m_windows[m_currentWindowIdx])
		{
			m_windows[m_currentWindowIdx]->PollEvents();
		}
		else
		{
			LOG("WindowManagerInfo", "{}: Window #{} no longer exists!\n", __func__, m_currentWindowIdx);
		}
	}

	bool WindowManager::ShouldClose() const
	{
		if (m_windows[m_currentWindowIdx])
		{
			return m_windows[m_currentWindowIdx]->ShouldClose();
		}
		else
		{
			LOG("WindowManagerInfo", "{}: Window #{} no longer exists!\n", __func__, m_currentWindowIdx);
			return false;
		}
	}

	void WindowManager::SwapBuffers()
	{
		if (m_windows[m_currentWindowIdx])
		{
			m_windows[m_currentWindowIdx]->SwapBuffers();
		}
		else
		{
			LOG("WindowManagerInfo", "{}: Window #{} no longer exists!\n", __func__, m_currentWindowIdx);
		}
	}
}