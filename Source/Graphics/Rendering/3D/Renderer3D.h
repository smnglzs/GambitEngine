#pragma once
#include "Base/GambitBasePCH.h"
#include "Base/Singleton/Singleton.h"
#include "Graphics/Common/Common.h"
#include "Graphics/Export.h"
#include "Graphics/GHI/Buffer/VertexArray.h"
#include "Graphics/Rendering/Renderer.h"

namespace gb
{
	class GAMBIT_GRAPHICS_API Renderer3D : public Renderer
	{
	public:
		Renderer3D();
		virtual ~Renderer3D();

		virtual void Init()	override;

		// void DebugDrawScene();
	};
}

GB_CREATE_SINGLETON_ACCESSOR(Renderer3D, Renderer3D, GAMBIT_GRAPHICS_API);


// TODO: 
//	- Set globals in shader (Time, TimeElapsed...)
//  - Consider making some static functions. Maybe end up like GHI; what state do we actually need per Renderer?
