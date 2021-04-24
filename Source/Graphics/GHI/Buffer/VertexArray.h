#pragma once
#include "Graphics/GHI/Buffer/IndexBuffer.h"
#include "Graphics/GHI/Buffer/VertexBuffer.h"

namespace gb
{
	class GAMBIT_GRAPHICS_API VertexArray : public GHIResource
	{
		using VertexBufferArray = std::vector<Unique<VertexBuffer>>;
	public:
		VertexArray();
		virtual ~VertexArray();

		void AddAttribute(Unique<VertexBuffer>&& attributeBuffer);

		virtual void Draw(int32 numInstances);

		inline IndexBuffer*	   GetIndexBuffer()						   const { return m_indexBuffer.get(); }
		inline uint32		   GetIndexOffset()						   const { return m_indexOffset; }
		inline const void*	   GetIndexOffsetPointer()				   const { return reinterpret_cast<const void*>(m_indexOffset * m_indexBuffer->GetElementSize()); }
		inline uint32		   GetNumVertices()						   const { return m_numVertices; }
		inline EPrimitiveType  GetPrimitiveType()					   const { return m_primitiveType; }
		inline EVertexDrawMode GetVertexDrawMode()					   const { return m_drawMode; }
		inline uint32		   GetVertexOffset()					   const { return m_vertexOffset; }
		inline bool			   HasAllAttributes()					   const { for (const auto& vbo : m_vertexBuffers) { if (vbo == nullptr) return false; } return true; };
		inline bool			   HasAttribute(EVertexAttributeType attr) const { return m_vertexBuffers[static_cast<uint8>(attr)].get() != nullptr; }
		inline bool			   HasIndexBuffer()						   const { return m_indexBuffer.get() != nullptr; }
		virtual bool		   IsValid()							   const override;

		inline void SetIndexBuffer  (Unique<IndexBuffer>&& indexBuffer ) { if (HasIndexBuffer()) m_indexBuffer = std::move(indexBuffer); } // TODO
		inline void SetIndexOffset  (const uint32		   indexOffset ) { if (HasIndexBuffer() && CheckIndexOffset(indexOffset)) m_indexOffset = indexOffset; }
		inline void SetVertexOffset (const uint32		   vertexOffset) { if (CheckVertexOffset(vertexOffset)) m_vertexOffset = vertexOffset; }

	protected:
		void Create();
		virtual void Destroy() override;

		inline bool CheckIndexOffset  (const uint32 indexOffset ) const { return indexOffset < m_indexBuffer->GetSize(); }
		inline bool CheckVertexOffset (const uint32 vertexOffset) const { return vertexOffset < m_numVertices; }

	private:
		VertexBufferArray	m_vertexBuffers;
		Unique<IndexBuffer>	m_indexBuffer;
		uint32				m_indexOffset;
		uint32				m_numVertices;
		uint32				m_vertexOffset;
		EPrimitiveType		m_primitiveType;
		EVertexDrawMode		m_drawMode;
	};
}