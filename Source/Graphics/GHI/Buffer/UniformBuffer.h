#pragma once
#include "Graphics/GHI/Buffer/Buffer.h"

namespace gb
{
	/*
		A basic implementation of a uniform buffer.
		TODO:
			- data upload
			- usage in shader
	*/
	class GAMBIT_GRAPHICS_API UniformBuffer final : public Buffer
	{
	public:
		UniformBuffer(const void* data, const uint32 numElements, const uint64 elementSize, const EBufferUsage usage);
		~UniformBuffer();

	protected:

	};
}