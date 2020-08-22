#pragma once
#include "Graphics/Buffer/Buffer.h"

namespace gb
{
	class GAMBIT_GRAPHICS_API IndexBuffer final : public Buffer
	{
	public:
		IndexBuffer(const uint32 length, const void* data, const EBufferUsage usage);
		~IndexBuffer();

	private:
		
	};
}