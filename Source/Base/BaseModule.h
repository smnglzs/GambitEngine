#pragma once
#include "Base/GambitBasePCH.h"
#include "Base/Module/Module.h"

namespace gb
{
	class GAMBIT_BASE_API BaseModule final : public IModule
	{
	public:
		BaseModule();
		virtual ~BaseModule() override;

		virtual void RegisterSingletons() override;

		virtual std::string GetID() const override { return "Base"; }
	};
}