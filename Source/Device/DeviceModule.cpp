#include "DeviceModule.h"
#include "Device/Window/WindowManager.h"
#include "Device/Input/InputManager.h"

#include "GLFW/glfw3.h"

namespace gb
{
	DEFINE_SINGLETON(WindowManager, WindowManager, GAMBIT_DEVICE_API);
	DEFINE_SINGLETON(InputManager,  InputManager,  GAMBIT_DEVICE_API);

	DeviceModule::DeviceModule() :
		m_ready(false)
	{

	}

	DeviceModule::~DeviceModule()
	{
		// assert that ShutDown was called before dtor
	}

	void DeviceModule::RegisterSingletons()
	{
		Module::RegisterSingletons();

		REGISTER_SINGLETON(WindowManager, WindowManager);
		REGISTER_SINGLETON(InputManager,  InputManager);
	}

	void DeviceModule::StartUp()
	{
		Module::StartUp();

		const bool m_ready = glfwInit() == GLFW_TRUE;
		assert(m_ready && "glfwInit failed!");

		glfwSetErrorCallback(HandleGLFWError);
	}

	void DeviceModule::ShutDown()
	{
		Module::ShutDown();

		// destroy input manager
		// destroy window manager

		glfwTerminate();
	}

	void DeviceModule::HandleGLFWError(int error, const char* description)
	{
		
	}
}