#pragma once
#include "Base/Common/Common.h"
#include "Graphics/Export.h"
#include "Graphics/Geometry/Geometry.h"
#include "Graphics/RHI/RHIDefinitions.h"

namespace gb
{
	class VertexBuffer;
	class GAMBIT_GRAPHICS_API VertexArray final : public Geometry
	{
	public:
		VertexArray();
		~VertexArray();

		void AddAttribute(VertexBuffer* attributeBuffer);
		bool HasAttribute(const EVertexAttributeType attribute) const;
		bool HasAllAttributes() const;

		virtual void Draw() override;

	protected:
		void Create();
		virtual void Destroy() override;

	private:
		std::array<VertexBuffer*, (uint8)EVertexAttributeType::Count> m_attributeBuffers;
		bool m_valid;
	};
}