#pragma once
#include "Graphics/GHI/Buffer/IndexBuffer.h"
#include "Graphics/GHI/Buffer/VertexBuffer.h"

namespace gb
{
	// TODO: Change how an IndexBuffer is created and associated with a VertexArray.
	class GAMBIT_GRAPHICS_API VertexArray : public GHIResource
	{
		using VertexBuffers = std::array<VertexBuffer*, static_cast<uint8>(EVertexAttributeType::Count)>;
	public:
		VertexArray();
		virtual ~VertexArray();

		void AddAttribute(VertexBuffer* attributeBuffer);

		inline bool	HasAttribute(EVertexAttributeType attr) const { return m_vertexBuffers[static_cast<uint8>(attr)]; }
		inline bool	HasAllAttributes() const { for (const auto& attr : m_vertexBuffers) { if (attr == nullptr) return false; } return true; };
		inline bool	HasIndexBuffer() const { return m_indexBuffer != nullptr; }

		inline Shared<IndexBuffer> GetIndexBuffer() const { return m_indexBuffer; }
		inline uint32 GetIndexOffset() const { return m_indexOffset; }
		inline const void* GetIndexOffsetPointer() const { return reinterpret_cast<const void*>(m_indexOffset * m_indexBuffer->GetElementSize()); }
		inline uint32 GetNumVertices() const { return m_numVertices; }
		inline uint32 GetVertexOffset() const { return m_vertexOffset; }

		inline EPrimitiveType  GetPrimitiveType() const { return m_primitiveType; }
		inline EVertexDrawMode GetVertexDrawMode() const { return m_drawMode; }

		inline void SetIndexBuffer(Shared<IndexBuffer> indexBuffer) { if (indexBuffer != nullptr) m_indexBuffer = indexBuffer; }
		inline void SetIndexOffset(const uint32 indexOffset) { if (m_indexBuffer && CheckIndexOffset(indexOffset)) m_indexOffset = indexOffset; }
		inline void SetVertexOffset(const uint32 vertexOffset) { if (CheckVertexOffset(vertexOffset)) m_vertexOffset = vertexOffset; }

		virtual bool IsValid() const override;

		virtual void Draw(int32 numInstances);

	protected:
		void Create();
		virtual void Destroy() override;

		inline bool CheckIndexOffset(const uint32 indexOffset)  const { return indexOffset < m_indexBuffer->GetSize(); }
		inline bool CheckVertexOffset(const uint32 vertexOffset) const { return vertexOffset < m_numVertices; }

	private:
		VertexBuffers		m_vertexBuffers; // TODO: ???
		Shared<IndexBuffer> m_indexBuffer;
		uint32				m_indexOffset;
		uint32				m_numVertices;
		uint32				m_vertexOffset;
		EPrimitiveType		m_primitiveType;
		EVertexDrawMode		m_drawMode;
	};
}