#pragma once
#include "Base/GambitBasePCH.h"
#include "Base/Singleton/Singleton.h"
#include "System/Window/WindowManager.h"
#include "Graphics/Export.h"
#include "Graphics/Camera/Camera.h"
#include "Graphics/GHI/Shader/ShaderManager.h"
#include "Graphics/GHI/Texture/TextureManager.h"
#include "Graphics/GHI/Buffer/VertexArrayManager.h"
#include "Graphics/Rendering/RenderScene.h"

namespace gb
{
	struct DrawCallData
	{
		const MatrixVariant  transforms;
		const VertexArray&   mesh;
		const ShaderProgram& shader;
	};

	// TODO: Draw high-level meshes, not VAOs
	class GAMBIT_GRAPHICS_API Renderer : public ISingleton
	{
	public:
		Renderer();
		virtual ~Renderer() = default;

		virtual void Init() = 0;
		virtual void Clear();
		virtual void Render(const RenderScene& scene);
		virtual void Draw(const DrawCallData& drawData);

	protected:
		virtual void BeginFrame();
		virtual void EndFrame();

	protected:
		ShaderManager*		m_shaderManager;
		TextureManager*		m_textureManager;
		VertexArrayManager* m_vertexManager;
		WindowManager*		m_windowManager;
		Shared<Camera>		m_camera;	// TODO: support multiple cameras
		int64				m_frameStart;
		int64				m_frameEnd;
	};
}

GB_CREATE_SINGLETON_ACCESSOR(Renderer, Renderer, GAMBIT_GRAPHICS_API);
