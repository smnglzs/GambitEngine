#include "Buffer.h"
#include "Graphics/RHI/RHI.h"

namespace gb
{
	Buffer::Buffer(const uint32 size, const void* data, const EBufferType type, const EBufferUsage usage) :
		m_size(size),
		m_type(type),
		m_usage(usage)
	{
		m_id = m_RHI->CreateBuffer(size, data, type, usage);
		assert(m_id && "RHI failed to create buffer!");
	}

	Buffer::~Buffer()
	{
		Destroy();
	}

	void Buffer::Destroy()
	{
		m_RHI->DeleteBuffer(m_id);
		m_id = 0u;
		m_size = 0u;
	}

	void Buffer::Update(const uint32 offset, const uint32 size, const void* data)
	{
		if (m_size >= offset + size)
		{
			m_RHI->UpdateBuffer(m_id, offset, size, data);
		}
		else
		{
			// reallocate?
			assert(false);
		}
	}

	uint32 Buffer::GetSize() const
	{
		return m_size;
	}

	EBufferType Buffer::GetType() const
	{
		return m_type;
	}

	EBufferUsage Buffer::GetUsage() const
	{
		return m_usage;
	}
}