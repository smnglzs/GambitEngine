#pragma once

#include "Base/Common/Common.h"
#include "Base/Module/Module.h"

#include "Device/Export.h"

namespace gb
{
	class GAMBIT_DEVICE_API DeviceModule final : public IModule
	{
	public:
		DeviceModule();
		virtual ~DeviceModule() override;

		virtual void RegisterSingletons() override;
		virtual void Init() override;
		virtual void Load() override;
		virtual void Unload() override;

		virtual std::string GetID() const override { return "Device"; }

	private:
		void InitGLFW();
		void CreateWindowContext();

		static void HandleGLFWError(int error, const char* description);
	};
}