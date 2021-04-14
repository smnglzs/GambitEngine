#pragma once
#include "Base/GambitBasePCH.h"
#include "Graphics/Export.h"
#include "Graphics/GHI/GHICommon.h"

namespace gb
{
	/*
		A generic GHI buffer object.
	*/
	class GAMBIT_GRAPHICS_API Buffer : public GHIResource, public NonCopyable
	{
	public:
		Buffer(const void* data, const uint32 numElements, const uint64 elementSize, const EBufferUsage usage, const EBufferType type);
		virtual ~Buffer();

		virtual void Create(const void* data, const uint64 size, const EBufferUsage usage, const EBufferType type) = 0;
		virtual void UpdateBuffer(const void* data, const uint64 offset, const uint64 size) = 0;
		virtual void Bind(const uint32 bufferTarget) = 0;
		virtual void Release() = 0;

		void Update(const void* data, const uint32 offset, const uint64 size);

		inline uint64		GetSize()		 const { return m_size; }
		inline uint64		GetElementSize() const { return m_elementSize; }
		inline uint32		GetNumElements() const { return m_numElements; }
		inline EBufferType  GetType()		 const { return m_type; }
		inline EBufferUsage GetUsage()		 const { return m_usage; }

	protected:
		virtual void Destroy() override;

	protected:
		uint64		 m_size;
		uint64		 m_elementSize;
		uint32		 m_numElements;
		EBufferType  m_type;
		EBufferUsage m_usage;

	private:
		Buffer() = delete;
	};
}