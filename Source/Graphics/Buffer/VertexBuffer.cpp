#include "VertexBuffer.h"
#include "Graphics/RHI/RHI.h"

namespace gb
{
	VertexBuffer::VertexBuffer(const EVertexAttributeType attributeType, const uint32 length, const void* data, const EBufferUsage usage) :
		Buffer(length * GetAttributeSize(attributeType), data, EBufferType::Attribute, usage),
		m_attributeType(attributeType)
	{
		assert(m_id > 0 && "RHI buffer creation failed!");
	}

	VertexBuffer::~VertexBuffer()
	{
		
	}
	
	constexpr uint32 VertexBuffer::GetAttributeSize(const EVertexAttributeType attributeType)
	{
		switch (attributeType)
		{
		case EVertexAttributeType::Position:
		case EVertexAttributeType::TexCoord: return sizeof(vec2f) * 2u;
		default: 
			assert(false && "Invalid vertex attribute."); 
			return 0u;
		}
	}

	constexpr uint32 VertexBuffer::GetAttributeLocation(const EVertexAttributeType attributeType)
	{
		return (uint8)attributeType;
	}

	uint32 VertexBuffer::GetAttributeLocation() const
	{
		return GetAttributeLocation(m_attributeType);
	}

	EVertexAttributeType VertexBuffer::GetAttributeType() const
	{
		return m_attributeType;
	}
}