#pragma once
#include "Graphics/GHI/Buffer/Buffer.h"

namespace gb
{
	/*
		A buffer containing indices for indexed drawing.
	*/
	class GAMBIT_GRAPHICS_API IndexBuffer final : public Buffer
	{
	public:
		IndexBuffer(const void* indexData, const uint32 numIndices, const EIndexFormat indexType, const EBufferUsage usage);
		~IndexBuffer();

		inline const void*	GetIndexData()   const { return m_indexData; }
		inline EIndexFormat	GetIndexFormat() const { return m_indexFormat; }

	protected:
		const void*  m_indexData;
		EIndexFormat m_indexFormat;
	};
}