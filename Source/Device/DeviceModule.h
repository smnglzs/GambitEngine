#pragma once

#include "Base/Common/Common.h"
#include "Base/Module/Module.h"
#include "Device/Export.h"

namespace gb
{
	class GAMBIT_DEVICE_API DeviceModule final : public Module
	{
	public:
		DeviceModule();
		virtual ~DeviceModule() override;

		virtual void RegisterSingletons() override;
		virtual void StartUp() override;
		virtual void ShutDown() override;

	private:
		static void HandleGLFWError(int error, const char* description);

		bool m_ready;
	};
}