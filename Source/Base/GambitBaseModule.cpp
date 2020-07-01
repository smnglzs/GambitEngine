#include "GambitBaseModule.h"

#include "Base/LoggerManager/LoggerManager.h"

namespace gb
{
	DEFINE_SINGLETON(LoggerManager, LoggerManager, GAMBIT_BASE_API);

	ModuleBase::ModuleBase()
	{

	}

	ModuleBase::~ModuleBase()
	{

	}

	void ModuleBase::StartUp()
	{
		Module::StartUp();
	}

	void ModuleBase::ShutDown()
	{
		Module::ShutDown();
	}

	void ModuleBase::RegisterSingletons()
	{
		Module::RegisterSingletons();

		REGISTER_SINGLETON(LoggerManager, LoggerManager);
	}
}