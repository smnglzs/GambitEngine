#pragma once

#include "Base/GambitBasePCH.h"
#include "Base/Module/Module.h"

#include "Runtime/Export.h"

namespace gb
{
	class GAMBIT_RUNTIME_API RuntimeModule final : public IModule
	{
	public:
		RuntimeModule();
		virtual ~RuntimeModule() override;

		virtual void RegisterSingletons() override;
		virtual void Init()				  override;
		virtual void Load()				  override;
		virtual void Start()			  override;
		virtual void Unload()			  override;

		virtual std::string GetID() const override { return "Runtime"; }

	private:

	};
}