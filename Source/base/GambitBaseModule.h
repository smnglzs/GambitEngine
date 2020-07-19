#pragma once
#include "Base/Common/Common.h"
#include "Base/Module/Module.h"

namespace gb
{
	class GAMBIT_BASE_API ModuleBase final : public Module
	{
	public:
		ModuleBase();
		virtual ~ModuleBase() override;

		virtual void StartUp() override;
		virtual void ShutDown() override;
		virtual void RegisterSingletons() override;
	};
}