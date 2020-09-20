#pragma once
#include "Base/Common/Common.h"
#include "Base/Module/Module.h"
#include "Graphics/Export.h"

namespace gb
{
	class GAMBIT_GRAPHICS_API GraphicsModule final : public IModule
	{
	public:
		GraphicsModule();
		virtual ~GraphicsModule() override;

		virtual void RegisterSingletons() override;
		virtual void Load() override;
		virtual void Unload() override;

		virtual std::string GetID() const override { return "Graphics"; }
	};
}
