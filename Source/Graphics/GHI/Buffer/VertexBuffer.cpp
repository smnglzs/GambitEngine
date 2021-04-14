#include "VertexBuffer.h"
#include "Graphics/GHI/GHI.h"

namespace gb
{
	VertexBuffer::VertexBuffer(const void* vertexData, const uint32 numElements, const EVertexAttributeType attributeType, const EBufferUsage usage) :
		Buffer(vertexData, numElements, GetAttributeSize(attributeType), usage, EBufferType::Vertex),
		m_attributeType(attributeType)
	{
		assert(m_handle && "GHI buffer creation failed!");
	}

	VertexBuffer::~VertexBuffer()
	{

	}

	constexpr uint32 VertexBuffer::GetAttributeSize(const EVertexAttributeType attributeType)
	{
		switch (attributeType)
		{
		case EVertexAttributeType::TexCoord:   
		case EVertexAttributeType::Position2D: return sizeof(vec2f);
		case EVertexAttributeType::Position3D: return sizeof(vec3f);
		default:
			assert(false && "Invalid vertex attribute.");
			return 0u;
		}
	}
}