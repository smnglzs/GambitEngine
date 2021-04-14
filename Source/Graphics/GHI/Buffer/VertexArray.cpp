#include "VertexArray.h"
#include "Graphics/GHI/GHI.h"

namespace gb
{
	VertexArray::VertexArray() :
		m_drawMode(EVertexDrawMode::NonIndexed),
		m_indexBuffer(),
		m_indexOffset(0u),
		m_numVertices(0u),
		m_primitiveType(EPrimitiveType::Invalid),
		m_vertexBuffers(),
		m_vertexOffset(0u)
	{

	}

	VertexArray::~VertexArray()
	{
		Destroy();
	}

	void VertexArray::Destroy()
	{
		GHI::DeleteVertexArray(m_handle);
	}

	void VertexArray::Create()
	{
		m_handle = GHI::CreateVertexArray();
		assert(IsValid() && "GHI failed to create a VertexArray!");
	}

	void VertexArray::AddAttribute(VertexBuffer* attributeBuffer)
	{
		if (attributeBuffer == nullptr)
		{
			assert(false && "Can't add attribute to VertexArray because corresponding VertexBuffer is null!");
			return;
		}

		const EVertexAttributeType attributeType = attributeBuffer->GetAttributeType();
		switch (attributeType)
		{
		case EVertexAttributeType::TexCoord:
		case EVertexAttributeType::Position2D:
		case EVertexAttributeType::Position3D:
			if (HasAttribute(attributeType))
			{
				assert(false && "Redundant add: VertexArray already has specified attribute!");
			}
			else
			{
				m_vertexBuffers[ToUnderlyingType(attributeType)] = attributeBuffer;
				GHI::AddAttributeToVertexArray(m_handle, GetAttributeByType(attributeType));
			}
			break;
		default:
			assert(false && "Specified vertex attribute does not exist!");
		}
	}

	void VertexArray::Draw(int32 numInstances = 1)
	{
		if (numInstances < 1)
			return;

		// TODO: Index offsets
		switch (m_drawMode)
		{
		case EVertexDrawMode::Indexed:
			if (HasIndexBuffer())
			{
				GHI::DrawIndexed(m_primitiveType, m_indexBuffer->GetNumElements(), m_indexBuffer->GetIndexFormat(), GetIndexOffsetPointer());
				break;
			}
		case EVertexDrawMode::NonIndexed:
			GHI::Draw(m_primitiveType, m_vertexOffset, m_numVertices);
			break;
		case EVertexDrawMode::IndexedInstanced:
			numInstances = numInstances > 0 ? numInstances : 1;
			if (HasIndexBuffer())
			{
				GHI::DrawIndexedInstanced(m_primitiveType, m_indexBuffer->GetNumElements(), m_indexBuffer->GetIndexFormat(), GetIndexOffsetPointer(), numInstances);
				break;
			}
		case EVertexDrawMode::NonIndexedInstanced:
			GHI::DrawInstanced(m_primitiveType, m_vertexOffset, m_numVertices, numInstances);
			break;
		default:
			assert(false && "Vertex array has an unrecognized draw mode!");
		}
	}

	bool VertexArray::IsValid() const
	{
		return GHI::IsVertexArray(m_handle);
	}
}