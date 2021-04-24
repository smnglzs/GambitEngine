#include "RuntimeModule.h"
#include "Base/LoggerManager/LoggerManager.h"

namespace gb
{
	RuntimeModule::RuntimeModule()
	{

	}

	RuntimeModule::~RuntimeModule()
	{
		// assert in ~IModule that we are unloaded
	}

	void RuntimeModule::RegisterSingletons()
	{
		IModule::RegisterSingletons();
	}

	void RuntimeModule::Start()
	{
		IModule::Start();
	}

	void RuntimeModule::Init()
	{
		IModule::Init();
	}

	void RuntimeModule::Load()
	{
		IModule::Load();
	}

	void RuntimeModule::Unload()
	{
		IModule::Unload();
	}
}