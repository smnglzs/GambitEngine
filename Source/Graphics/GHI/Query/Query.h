#pragma once
#include "Base/GambitBasePCH.h"
#include "Graphics/Export.h"
#include "Graphics/GHI/GHICommon.h"

namespace gb
{
	class GAMBIT_GRAPHICS_API Query : public GHIResource
	{
	public:
		Query(const EQueryType type);
		virtual ~Query();

		void BeginQuery();
		void EndQuery();

		virtual void Destroy() override;

	private:
		EQueryType m_type;
		bool m_querying;
	};
}