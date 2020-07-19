#include "DeviceModule.h"
#include "Device/Display/DisplayManager.h"
#include "Device/Input/InputManager.h"

#include "GLFW/glfw3.h"

namespace gb
{
	DEFINE_SINGLETON(DisplayManager, DisplayManager, GAMBIT_DEVICE_API);
	DEFINE_SINGLETON(InputManager, InputManager, GAMBIT_DEVICE_API);

	DeviceModule::DeviceModule() :
		m_ready(false)
	{

	}

	DeviceModule::~DeviceModule()
	{

	}

	void DeviceModule::RegisterSingletons()
	{
		Module::RegisterSingletons();

		REGISTER_SINGLETON(DisplayManager, DisplayManager);
		REGISTER_SINGLETON(InputManager, InputManager);
	}

	void DeviceModule::StartUp()
	{
		Module::StartUp();

		m_ready = glfwInit() == GLFW_TRUE;
		assert(m_ready && "glfwInit failed!");

		glfwSetErrorCallback(HandleGLFWError);
	}

	void DeviceModule::ShutDown()
	{
		Module::ShutDown();

		glfwTerminate();
	}

	void DeviceModule::HandleGLFWError(int error, const char* description)
	{
		
	}
}