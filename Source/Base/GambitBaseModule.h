#pragma once
#include "Base/Common/Common.h"
#include "Base/Module/Module.h"

namespace gb
{
	class GAMBIT_BASE_API ModuleBase final : public IModule
	{
	public:
		ModuleBase();
		virtual ~ModuleBase() override;

		virtual void RegisterSingletons() override;

		virtual std::string GetID() const override { return "Base"; }
	};
}