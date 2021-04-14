#pragma once
#include "Graphics/GHI/Buffer/Buffer.h"

namespace gb
{
	/*
		A basic implementation of a single-attribute vertex buffer.
		TODO:
			- interleaved attributes
			- differentiate location and binding point
			- update GHIDefinitions accordingly
	*/
	class GAMBIT_GRAPHICS_API VertexBuffer final : public Buffer
	{
	public:
		inline static constexpr uint32 GetAttributeLocation(const EVertexAttributeType attribute) { return ToUnderlyingType(attribute); }

	public:
		VertexBuffer(const void* vertexData, const uint32 numElements, const EVertexAttributeType attributeType, const EBufferUsage usage);
		~VertexBuffer();

		inline EVertexAttributeType GetAttributeType()	   const { return m_attributeType; }
		inline uint32				GetAttributeLocation() const { return GetAttributeLocation(m_attributeType); }

	protected:
		static constexpr uint32	GetAttributeSize(const EVertexAttributeType attribute);

	protected:
		EVertexAttributeType m_attributeType;
	};
}