#pragma once
#include "Graphics/Buffer/Buffer.h"

namespace gb
{
	/*
		A basic implementation of a single-attribute vertex buffer.
		TODO: 
			- interleaved attributes
			- differentiate location and binding point
			- update RHIDefinitions accordingly
	*/
	class GAMBIT_GRAPHICS_API VertexBuffer final : public Buffer
	{
	public:
		VertexBuffer(const EVertexAttributeType attributeType, const uint32 length, const void* data, const EBufferUsage usage);
		~VertexBuffer();

		EVertexAttributeType GetAttributeType() const;
		uint32 GetAttributeLocation() const;
		static constexpr uint32 GetAttributeLocation(const EVertexAttributeType attribute);

	private:
		static constexpr uint32 GetAttributeSize(const EVertexAttributeType attribute);

	private:
		EVertexAttributeType m_attributeType;
	};
}