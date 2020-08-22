#include "VertexArray.h"
#include "Graphics/Buffer/VertexBuffer.h"
#include "Graphics/RHI/RHI.h"

namespace gb
{
	VertexArray::VertexArray() :
		m_attributeBuffers({}),
		m_valid(false)
	{

	}

	VertexArray::~VertexArray()
	{
		Destroy();
	}

	void VertexArray::Destroy()
	{
		m_RHI->DeleteVertexArray(m_id);
	}

	void VertexArray::Create()
	{
		m_id = m_RHI->CreateVertexArray();
		m_valid = m_id > 0u;
		assert(m_valid && "RHI failed to create a VertexArray!");
	}

	void VertexArray::AddAttribute(VertexBuffer* attributeBuffer)
	{
		assert(attributeBuffer && "Can't add attribute to VertexArray because corresponding VertexBuffer is null!");

		const EVertexAttributeType attributeType = attributeBuffer->GetAttributeType();
		switch (attributeType)
		{
		case EVertexAttributeType::Position:
		case EVertexAttributeType::TexCoord:
			if (HasAttribute(attributeType))
			{
				assert(false && "Redundant add: VertexArray already has specified attribute!");
			}
			else
			{
				m_attributeBuffers[(uint8)attributeType] = attributeBuffer;
				m_RHI->AddAttributeToVertexArray(m_id, g_VertexAttributes[(uint8)attributeType]);
			}
			break;
		default:
			assert(false && "Specified vertex attribute does not exist!");
		}
	}

	bool VertexArray::HasAttribute(const EVertexAttributeType attributeType)
	{
		return m_attributeBuffers[(uint8)attributeType];
	}
}