#pragma once
#include "Base/GambitBasePCH.h"
#include "Base/Singleton/Singleton.h"
#include "Graphics/Common/Common.h"
#include "Graphics/Export.h"
#include "Graphics/Rendering/Camera/Camera.h"

namespace gb
{
	struct DrawCallData
	{
		const		MatrixVariant  transforms;
		const class	VertexArray&   mesh;
		const class ShaderProgram& shader;
	};

	class GAMBIT_GRAPHICS_API Renderer : public ISingleton
	{
	public:
		Renderer();
		virtual ~Renderer() = default;

		virtual void Init() = 0;
		virtual void Clear();
		//virtual void Render(const RenderScene& scene);
		virtual void Draw(const DrawCallData& drawData);

		inline virtual Camera& GetCamera() { return *m_camera; }
		inline virtual const Camera& GetCamera() const { return *m_camera; }

	protected:
		virtual void BeginFrame();
		virtual void EndFrame();

	protected:
		class ShaderManager*	  m_shaderManager;
		class TextureManager*	  m_textureManager;
		class VertexArrayManager* m_vertexManager;
		class WindowManager*	  m_windowManager;
		Shared<Camera>			  m_camera;	// TODO: support multiple cameras
		int64					  m_frameStart;
		int64					  m_frameEnd;
	};
}

GB_CREATE_SINGLETON_ACCESSOR(Renderer, Renderer, GAMBIT_GRAPHICS_API);
