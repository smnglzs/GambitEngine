#include "IndexBuffer.h"

namespace gb
{
	IndexBuffer::IndexBuffer(const uint32 length, const void* data, const EBufferUsage usage) :
		Buffer(length, data, EBufferType::Index, usage)
	{

	}

	IndexBuffer::~IndexBuffer()
	{
		
	}
}