#include "SystemModule.h"
#include "System/Window/WindowManager.h"
#include "System/Input/InputManager.h"
#include "Base/LoggerManager/LoggerManager.h"

#include "GLFW/glfw3.h"

namespace gb
{
	DEFINE_SINGLETON(WindowManager, WindowManager, GAMBIT_SYSTEM_API);
	DEFINE_SINGLETON(InputManager,  InputManager,  GAMBIT_SYSTEM_API);
	DEFINE_SINGLETON(Keyboard,		Keyboard,	   GAMBIT_SYSTEM_API);
	DEFINE_SINGLETON(Mouse,			Mouse,		   GAMBIT_SYSTEM_API);

	SystemModule::SystemModule()
	{

	}

	SystemModule::~SystemModule()
	{
		// assert in ~IModule that we are unloaded
	}

	void SystemModule::RegisterSingletons()
	{
		IModule::RegisterSingletons();

		REGISTER_SINGLETON(WindowManager, WindowManager);
		REGISTER_SINGLETON(InputManager,  InputManager);
		REGISTER_SINGLETON(Keyboard,	  Keyboard);
		REGISTER_SINGLETON(Mouse,		  Mouse);

	}

	void SystemModule::Start()
	{
		IModule::Start();
	}

	void SystemModule::Init()
	{
		IModule::Init();

		InitGLFW();
		GetWindowManager()->CreateTransientWindow();
	}

	void SystemModule::Load()
	{
		IModule::Load();
	}

	void SystemModule::Unload()
	{
		IModule::Unload();

		glfwTerminate();
	}

	void SystemModule::InitGLFW()
	{
		const bool glfwInitRes = glfwInit() == GLFW_TRUE;
		assert(glfwInitRes && "glfwInit failed!");

		glfwSetErrorCallback(HandleGLFWError);
	}

	void SystemModule::HandleGLFWError(int error, const char* description)
	{
		LOG(gb::EChannelComponent::EngineWarning, "GLFW Error #{}: {}\n", error, description);
	}
}