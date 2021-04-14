#include "UniformBuffer.h"
#include "Graphics/GHI/GHI.h"

namespace gb
{
	UniformBuffer::UniformBuffer(const void* data, const uint32 numElements, const uint64 elementSize, const EBufferUsage usage) :
		Buffer(data, numElements, elementSize, usage, EBufferType::Uniform)
	{

	}

	UniformBuffer::~UniformBuffer()
	{

	}
}