#include "Renderer2D.h"
#include "Base/LoggerManager/LoggerManager.h"
#include "System/Window/WindowManager.h"
#include "Graphics/GHI/GHI.h"
#include "Graphics/GHI/Buffer/VertexArrayManager.h"
#include "Graphics/GHI/Shader/ShaderManager.h"
#include "Graphics/GHI/Texture/TextureManager.h"
#include "Graphics/Rendering/2D/Tilesheet.h"

namespace gb
{
	Renderer2D::Renderer2D()
	{

	}

	Renderer2D::~Renderer2D()
	{
		
	}

	void Renderer2D::Init(/* TODO: camera params */)
	{
		Window* window = GetWindowManager()->GetWindow();
		assert(window);

		const auto windowSize = window->GetSize();
		FloatRect viewport = { 0.f, 0.f, (float)windowSize.x, (float)windowSize.y };
		/* TODO: 
			- don't allocate cameras in renderer, get refs from camera manager
			- get near/far from params
		*/
		m_camera = std::make_shared<Camera>(viewport, ClipPlanes{-0.001f, 1000.f}, Camera::EProjection::Orthographic);
		m_camera->SetClearColor(Color::Cyan);
	}

	//void Renderer2D::Render(const RenderScene& scene)
	//{
	//	throw Exceptions::NotImplemented();
	//}

	void Renderer2D::DrawRect(const IntRect rect, const Color color, ShaderProgram& shader)
	{
		throw Exceptions::NotImplemented();
	}

#if 0
	void Renderer2D::DebugDrawScene()
	{
		//GHI::SetWireframe(true);

		GHI::SetViewport(m_camera->GetView());
		GHI::SetRenderCapEnabled(RenderCaps::Blend, true);
		GHI::SetBlendFunc(EBlendFunc::SrcAlpha, EBlendFunc::OneMinusSrcAlpha);

		ShaderProgram& shader = m_shaderManager->BindShaderProgram("SP_Grid");
		//shader.SetUniform("u_texture", 0);

		//const auto texture = m_textureManager->BindTexture("QuestionBlock");
		//assert(texture && texture->IsValid());
		//static const Tilesheet tilesheet(texture, 16);

		shader.SetUniform("u_gridSize", vec2u{ 1600, 900 });

		const int cellSize = 10;
		shader.SetUniform("u_cellSize", cellSize);

		static const std::vector<Vertex2D> vertices =
		{
			{ {-1.0f, -1.0f}, {-1.0f, -1.0f} },
			{ { 1.0f, -1.0f}, { 1.0f, -1.0f} },
			{ { 1.0f,  1.0f}, { 1.0f,  1.0f} },
			{ {-1.0f, -1.0f}, {-1.0f, -1.0f} },
			{ { 1.0f,  1.0f}, { 1.0f,  1.0f} },
			{ {-1.0f,  1.0f}, {-1.0f,  1.0f} }
		};

		GHI::DebugDraw(EPrimitiveType::Triangles, vertices);
		
	}
#endif
}