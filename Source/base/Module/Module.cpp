#include "Module.h"

#include <iostream>

namespace gb
{
	Module::Module()
	{

	}

	Module::~Module()
	{

	}

	void Module::StartUp()
	{
		std::cout << "Module StartUp\n";
	}
	
	void Module::ShutDown()
	{
		std::cout << "Module ShutDown\n";
	}

	void Module::RegisterSingletons()
	{
		std::cout << "Registering Module Singletons\n";
	}
}