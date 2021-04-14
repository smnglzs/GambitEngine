#pragma once

#include "Base/GambitBasePCH.h"
#include "Base/Module/Module.h"

#include "System/Export.h"

namespace gb
{
	class GAMBIT_SYSTEM_API SystemModule final : public IModule
	{
	public:
		SystemModule();
		virtual ~SystemModule() override;

		virtual void RegisterSingletons() override;
		virtual void Init()				  override;
		virtual void Load()				  override;
		virtual void Start()			  override;
		virtual void Unload()			  override;

		virtual std::string GetID() const override { return "Device"; }

	private:
		void InitGLFW();

		static void HandleGLFWError(int error, const char* description);
	};
}