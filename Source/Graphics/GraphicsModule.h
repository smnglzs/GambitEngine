#pragma once
#include "Base/Common/Common.h"
#include "Base/Module/Module.h"
#include "Graphics/Export.h"

namespace gb
{
	class GAMBIT_GRAPHICS_API GraphicsModule final : public Module
	{
	public:
		GraphicsModule();
		virtual ~GraphicsModule() override;

		virtual void RegisterSingletons() override;
		virtual void StartUp() override;
		virtual void ShutDown() override;

	private:
		class RHI* m_RHI;
	};
}
