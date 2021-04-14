#include "Base/GambitBasePCH.h"
#include "BaseModule.h"

#include "Base/LoggerManager/LoggerManager.h"
#include "Base/FileManager/FileManager.h"

namespace gb
{
	DEFINE_SINGLETON(LoggerManager, LoggerManager, GAMBIT_BASE_API);
	DEFINE_SINGLETON(FileManager, FileManager, GAMBIT_BASE_API);

	BaseModule::BaseModule()
	{

	}

	BaseModule::~BaseModule()
	{
		// assert in ~IModule that we are unloaded
	}

	void BaseModule::RegisterSingletons()
	{
		IModule::RegisterSingletons();

		REGISTER_SINGLETON(LoggerManager, LoggerManager);
		REGISTER_SINGLETON(FileManager, FileManager);
	}
}