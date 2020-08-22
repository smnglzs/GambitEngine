#pragma once
#include "Base/Common/Common.h"
#include "Graphics/Export.h"
#include "Graphics/RHI/RHIDefinitions.h"
#include "Graphics/RHI/RHIObject.h"

namespace gb
{
	class VertexBuffer;

	class GAMBIT_GRAPHICS_API VertexArray final : public RHIObject
	{
	public:
		VertexArray();
		~VertexArray();

		void AddAttribute(VertexBuffer* attributeBuffer);
		bool HasAttribute(const EVertexAttributeType attribute);
		//const bool IsValid();

	protected:
		void Create();
		virtual void Destroy() override;

	private:
		std::array<VertexBuffer*, (uint8)EVertexAttributeType::Count> m_attributeBuffers;
		bool m_valid;
	};
}