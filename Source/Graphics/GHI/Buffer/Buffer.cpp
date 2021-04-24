#include "Buffer.h"
#include "Graphics/GHI/GHI.h"

namespace gb
{
	Buffer::Buffer(const void* data, const uint32 numElements, const uint64 elementSize, const EBufferUsage usage, const EBufferType type) :
		m_size(numElements* elementSize),
		m_numElements(numElements),
		m_elementSize(elementSize),
		m_usage(usage),
		m_type(type)
	{
		m_handle = GHI::CreateBuffer(data, m_size, m_usage, m_type);
		assert(m_handle && "GHI failed to create buffer!");
	}

	Buffer::~Buffer()
	{
		Destroy();
	}

	void Buffer::Destroy()
	{
		GHI::DeleteBuffer(m_handle);
		m_handle = 0u;
		m_size = 0u;
	}

	void Buffer::Update(const void* data, const uint32 offset, const uint64 size)
	{
		if (m_size >= offset + size)
		{
			UpdateBuffer(data, offset, size);
		}
		else
		{
			// Reallocate?
			throw Exceptions::NotImplemented();
		}
	}
}