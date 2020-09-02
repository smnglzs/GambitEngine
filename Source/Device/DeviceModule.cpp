#include "DeviceModule.h"
#include "Device/Window/WindowManager.h"
#include "Device/Input/InputManager.h"

#include "GLFW/glfw3.h"

namespace gb
{
	DEFINE_SINGLETON(WindowManager, WindowManager, GAMBIT_DEVICE_API);
	DEFINE_SINGLETON(InputManager, InputManager, GAMBIT_DEVICE_API);

	DeviceModule::DeviceModule()
	{

	}

	DeviceModule::~DeviceModule()
	{

	}

	void DeviceModule::RegisterSingletons()
	{
		IModule::RegisterSingletons();

		REGISTER_SINGLETON(WindowManager, WindowManager);
		REGISTER_SINGLETON(InputManager, InputManager);
	}

	void DeviceModule::Load()
	{
		IModule::Load();

		InitGLFW();
		CreateWindowContext(/* pass in initial window and context settings */);
	}

	void DeviceModule::Unload()
	{
		IModule::Unload();

		glfwTerminate();
	}

	void DeviceModule::InitGLFW()
	{
		const bool glfwInitRes = glfwInit() == GLFW_TRUE;
		assert(glfwInitRes && "glfwInit failed!");

		glfwSetErrorCallback(HandleGLFWError);
	}

	void DeviceModule::CreateWindowContext()
	{
		WindowSettings defaultSettings;
		GetWindowManager()->CreateWindow(defaultSettings);
	}

	void DeviceModule::HandleGLFWError(int error, const char* description)
	{

	}
}