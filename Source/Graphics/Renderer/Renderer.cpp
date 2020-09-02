#include "Renderer.h"
#include "Base/LoggerManager/LoggerManager.h"
#include "Graphics/RHI/RHI.h"
#include "Graphics/Shader/ShaderManager.h"
#include "Graphics/Texture/TextureManager.h"

namespace gb
{
	Renderer::Renderer() :
		m_RHI(GetRHI())
	{
		assert(m_RHI);
	}

	Renderer::~Renderer()
	{

	}

	void Renderer::BeginFrame()
	{
		m_RHI->SetClearColor({ 0.1f, 0.5f, 0.6f, 1.f });
		m_RHI->ClearRenderTarget();
		m_RHI->BeginFrame();

		DrawScene();
	}

	void Renderer::EndFrame()
	{
		m_RHI->EndFrame();
	}

	void Renderer::DrawScene()
	{
		static const std::vector<Vertex1P1UV> vertices =
		{
			{ {-0.50f, -0.50f}, {0.0f, 0.0f} },
			{ { 0.50f, -0.50f}, {1.0f, 0.0f} },
			{ { 0.50f,  0.50f}, {1.0f, 1.0f} },
			{ {-0.50f, -0.50f}, {0.0f, 0.0f} },
			{ { 0.50f,  0.50f}, {1.0f, 1.0f} },
			{ {-0.50f,  0.50f}, {0.0f, 1.0f} }
		};

		m_RHI->DebugDraw(EPrimitiveMode::Triangles, vertices.data(), (uint32)vertices.size());
	}
}