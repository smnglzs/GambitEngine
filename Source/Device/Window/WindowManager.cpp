#include "WindowManager.h"
#include "Base/LoggerManager/LoggerManager.h"
#include "GLFW/glfw3.h"

namespace gb
{
	WindowManager::WindowManager() :
		m_window(nullptr)
	{
	}

	WindowManager::~WindowManager()
	{
		// kill windows
	}

	void WindowManager::Init()
	{
		ISingleton::Init();
		
	}

	bool WindowManager::CreateWindow(const WindowSettings& winSettings)
	{
		if (m_window)
		{
			LOG(gb::EChannelComponent::EngineInfo, "{}: A Window has already been created!\n", __func__);
		}
		else
		{
			m_window = new Window(winSettings);
			if (m_window)
			{
				m_window->BindContext();
				glfwSwapInterval(1); // vsync
				return true;
			}
		}
		LOG(gb::EChannelComponent::EngineError, "Window creation failed!\n");
		return false;
	}

	void WindowManager::PollEvents()
	{
		if (m_window)
		{
			m_window->PollEvents();
		}
		else
		{
			LOG(gb::EChannelComponent::EngineInfo, "{}: Window no longer exists!\n", __func__);
		}
	}

	bool WindowManager::ShouldClose() const
	{
		if (m_window)
		{
			return m_window->ShouldClose();
		}
		else
		{
			LOG(gb::EChannelComponent::EngineInfo, "{}: Window no longer exists!\n", __func__);
			return true;
		}
	}

	void WindowManager::SwapBuffers()
	{
		if (m_window)
		{
			m_window->SwapBuffers();
		}
		else
		{
			LOG(gb::EChannelComponent::EngineInfo, "{}: Window no longer exists!\n", __func__);
		}
	}

	vec2i WindowManager::GetSize() const
	{
		return m_window ? m_window->GetSize() : vec2i{INT_MIN, INT_MIN};
	}
}