#pragma once
#include "Base/Common/Common.h"
#include "Graphics/Export.h"
#include "Graphics/RHI/RHIDefinitions.h"
#include "Graphics/RHI/RHIObject.h"

namespace gb
{
	class GAMBIT_GRAPHICS_API Geometry : public RHIObject
	{
	public:
		Geometry();
		virtual ~Geometry();

		virtual void Draw() = 0;
		EPrimitiveType GetPrimitiveType() const;

	protected:
		virtual void Destroy() = 0;

	protected:
		EPrimitiveType m_primitiveType;
	};
}