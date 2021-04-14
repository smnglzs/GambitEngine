#pragma once
#include "Base/GambitBasePCH.h"
#include "Graphics/Export.h"
#include "Graphics/GHI/GHICommon.h"

namespace gb
{
	class GAMBIT_GRAPHICS_API Framebuffer : public GHIResource
	{
	public:
		Framebuffer();
		virtual ~Framebuffer();

		virtual bool IsValid() const override { return m_valid; }

	private:
		bool m_valid;
	};
}