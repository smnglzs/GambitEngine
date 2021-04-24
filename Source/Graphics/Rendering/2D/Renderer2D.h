#pragma once
#include "Base/GambitBasePCH.h"
#include "Base/Singleton/Singleton.h"
#include "Graphics/Common/Common.h"
#include "Graphics/Export.h"
#include "Graphics/GHI/Buffer/VertexArray.h"
#include "Graphics/Rendering/Renderer.h"

namespace gb
{
	class GAMBIT_GRAPHICS_API Renderer2D : public Renderer
	{
	public:
		Renderer2D();
		virtual ~Renderer2D();

		virtual void Init() override;
		virtual void Render(const RenderScene& scene) override;
		
		void DrawRect(const IntRect rect, const Color color, ShaderProgram& shader);

		// void DebugDrawScene();
	};
}

GB_CREATE_SINGLETON_ACCESSOR(Renderer2D, Renderer2D, GAMBIT_GRAPHICS_API);

// TODO: 
//	- Set globals in shader (Time, TimeElapsed...)
//  - Consider making some static functions. Maybe end up like GHI; what state do we need per Renderer?
