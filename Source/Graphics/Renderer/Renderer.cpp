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

	static const std::vector<gb::vec2f> vertices =
	{
		{  0.5f,   0.5f  },
		{ -0.5f,   0.25f },
		{  0.65f, -0.5f  }
	};

	void Renderer::DrawScene()
	{
		m_RHI->DebugDraw(EPrimitiveMode::Triangles, vertices.data(), (uint32)vertices.size());
	}
}