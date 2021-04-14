#include "IndexBuffer.h"
#include "Graphics/GHI/GHI.h"

namespace gb
{
	IndexBuffer::IndexBuffer(const void* indexData, const uint32 numIndices, const EIndexFormat indexType, const EBufferUsage usage) :
		Buffer(indexData, numIndices, GetIndexSize(indexType), usage, EBufferType::Index),
		m_indexData(indexData),
		m_indexFormat(indexType)
	{

	}

	IndexBuffer::~IndexBuffer()
	{

	}
}