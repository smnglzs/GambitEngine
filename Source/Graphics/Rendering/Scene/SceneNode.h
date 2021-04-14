#pragma once
#include "Base/GambitBasePCH.h"
#include "Graphics/Common/Color.h"
#include "Graphics/Export.h"

namespace gb
{
	class GAMBIT_GRAPHICS_API SceneNode
	{
	public:
		SceneNode();
		virtual ~SceneNode();

	protected:
		std::vector<SceneNode*> m_children;
		Color					m_color;
		SceneNode*				m_parent;
	};
}