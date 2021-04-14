#pragma once
#include "Base/GambitBasePCH.h"
#include "Graphics/Export.h"

namespace gb
{
	/*
		A simple mesh object with no attachments
	*/
	class GAMBIT_GRAPHICS_API Mesh
	{
	public:
		Mesh();
		virtual ~Mesh();

	protected:
		Weak<class VertexArray> m_vertexArray;
	};
}