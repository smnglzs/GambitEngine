#include "GambitBaseModule.h"

namespace gb
{
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
	}
}