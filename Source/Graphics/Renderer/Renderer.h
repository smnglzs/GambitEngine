#pragma once
#include "Base/Common/Common.h"
#include "Base/Singleton/Singleton.h"
#include "Graphics/Export.h"

namespace gb
{
	class GAMBIT_GRAPHICS_API Renderer : public ISingleton
	{
	public:
		Renderer();
		virtual ~Renderer();

		void BeginFrame();
		void EndFrame();

	private:
		void DrawScene();

	private:
		class RHI*			  m_RHI;
		class ShaderManager*  m_shaderManager;
		class TextureManager* m_textureManager;

		vec4f m_clearColor;
	};
}

CREATE_SINGLETON_ACCESSOR(Renderer, Renderer, GAMBIT_GRAPHICS_API);