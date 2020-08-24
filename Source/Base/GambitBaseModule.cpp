#include "GambitBaseModule.h"

#include "Base/LoggerManager/LoggerManager.h"
#include "Base/FileManager/FileManager.h"

namespace gb
{
	DEFINE_SINGLETON(LoggerManager, LoggerManager, GAMBIT_BASE_API);
	DEFINE_SINGLETON(FileManager, FileManager, GAMBIT_BASE_API);

	ModuleBase::ModuleBase()
	{

	}

	ModuleBase::~ModuleBase()
	{

	}

	void ModuleBase::RegisterSingletons()
	{
		IModule::RegisterSingletons();

		REGISTER_SINGLETON(LoggerManager, LoggerManager);
		REGISTER_SINGLETON(FileManager, FileManager);
	}
}