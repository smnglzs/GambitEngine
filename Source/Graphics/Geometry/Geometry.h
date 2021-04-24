#pragma once
#include "Base/GambitBasePCH.h"
#include "Graphics/Export.h"

namespace gb
{
	class VertexArray;
	class IndexBuffer;

	/// <summary>
	/// Vertex data rendered with a vertex array, with or without an index buffer. No attachment chain.
	/// </summary>
	class GAMBIT_GRAPHICS_API Geometry
	{
	public:
		Geometry();
		virtual ~Geometry();

		inline void SetVertexArray(Weak<class VertexArray> vertexArray) { m_vertexArray = vertexArray; }
		inline void SetIndexBuffer(Weak<class IndexBuffer> indexBuffer) { m_indexBuffer = indexBuffer; }

	protected:
		Weak<class VertexArray> m_vertexArray;
		Weak<class IndexBuffer> m_indexBuffer;
	};
}