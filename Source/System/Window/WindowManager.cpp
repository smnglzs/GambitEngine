#include "WindowManager.h"
#include "Base/LoggerManager/LoggerManager.h"
#include "GLFW/glfw3.h"

namespace gb
{
	WindowManager::WindowManager()
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

	void WindowManager::CreateTransientWindow()
	{
		if (m_transientWindow.get())
			throw "[SystemModule] One or more windows already exist; there is no need for a transient one now.";

		WindowSettings winSet{};
		winSet.title	 = "";
		winSet.size		 = { 1, 1 };
		winSet.focused	 = false;
		winSet.decorated = false;
		winSet.visible	 = false;

		GLContextSettings ctxSet{};

		// Create transient window.
		m_transientWindow = std::make_unique<Window>(winSet, ctxSet);
		if (m_transientWindow.get() == nullptr)
			throw "[SystemModule] Failed to create transient window!";
	}

	void WindowManager::DestroyTransientWindow()
	{
		if (m_transientWindow)
			m_transientWindow.reset();
		else
			throw "[SystemModule] There is no transient window to destroy!";
	}

	Window* WindowManager::CreateWindow(const WindowSettings& winSettings, const GLContextSettings ctxSettings)
	{
		if (Shared<Window> newWindow = std::make_shared<Window>(winSettings, ctxSettings))
		{
			m_windows.push_back(newWindow);
			glfwSwapInterval(winSettings.vsync);
			return newWindow.get();
		}
		else
		{
			LOG(gb::EChannelComponent::EngineError, "Window creation failed!\n");
			assert(false);
			return nullptr;
		}
	}

	Window* WindowManager::GetWindow(const EWindowSlot winSlot /* = EWindowSlot::PrimaryWindows */)
	{
		// TODO: add logs / error-handling
		return winSlot >= m_windows.size() ? nullptr : m_windows[winSlot].get();

	}
}
/*
	- Callbacks:
		glfwSetWindowCloseCallback
		glfwSetWindowSizeCallback
		glfwSetFramebufferSizeCallback
		glfwSetWindowPosCallback
		glfwSetWindowRefreshCallback
		glfwSetWindowFocusCallback
		glfwSetWindowIconifyCallback
		glfwSetWindowMaximizeCallback
		glfwSetWindowContentScaleCallback
	
	- glfwFocusWindow
	- glfwRequestWindowAttention
*/