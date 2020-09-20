#include "Renderer.h"
#include "Base/LoggerManager/LoggerManager.h"
#include "Graphics/RHI/RHI.h"
#include "Graphics/Shader/ShaderManager.h"
#include "Graphics/Texture/TextureManager.h"
#include "Device/Window/WindowManager.h"

namespace gb
{
	/*
		TODO: Set globals in shader (Time, TimeElapsed...)
	*/

	Renderer::Renderer() :
		m_RHI(GetRHI()),
		m_shaderManager(GetShaderManager()),
		m_textureManager(GetTextureManager()),
		m_clearColor({0.1f, 0.5f, 0.6f, 1.f})
	{
		assert(m_RHI && m_shaderManager && m_textureManager);

		m_startTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
	}

	Renderer::~Renderer()
	{
		// Will there be anything to tear down? Apart from textures and shaders,
		// what resources will we need? Will the Renderer always be a consumer?
	}

	void Renderer::BeginFrame()
	{
		m_RHI->SetClearColor(m_clearColor);
		m_RHI->ClearRenderTarget(); // TODO: Make sure right RT is bound and correct mask is used.
		m_RHI->BeginFrame();

		DrawScene();
	}

	void Renderer::EndFrame()
	{
		m_RHI->EndFrame();
	}

	void Renderer::DrawScene()
	{
		static const std::vector<Vertex2PT> vertices =
		{
			{ {-0.50f, -0.50f}, {0.0f, 0.0f} },
			{ { 0.50f, -0.50f}, {1.0f, 0.0f} },
			{ { 0.50f,  0.50f}, {1.0f, 1.0f} },
			{ {-0.50f, -0.50f}, {0.0f, 0.0f} },
			{ { 0.50f,  0.50f}, {1.0f, 1.0f} },
			{ {-0.50f,  0.50f}, {0.0f, 1.0f} }
		};

		m_shaderManager->BindFallbackShaderProgram();
		m_textureManager->BindFallbackTexture();
		m_shaderManager->SetUniform("Texture", 0);

		const vec2i screenSize = {1600, 1600}; // GetWindowManager()->GetSize();
		m_shaderManager->SetUniform("ScreenSize", screenSize);

		std::chrono::milliseconds elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()) - m_startTime;
		float uniformTime = elapsedTime.count() / 1000.f;

		// Draw 4 textured chests, 1 per screen space corner.
		m_shaderManager->SetUniform("Offset", vec2f{0.0f, 0.0f});
		m_shaderManager->SetUniform("Time", uniformTime);
		m_RHI->DebugDraw(EPrimitiveType::Triangles, vertices.data(), (uint32)vertices.size());
		m_shaderManager->SetUniform("Offset", vec2f{0.0f, -1.0f});
		m_shaderManager->SetUniform("Time", uniformTime * 1.01f);
		m_RHI->DebugDraw(EPrimitiveType::Triangles, vertices.data(), (uint32)vertices.size());
		m_shaderManager->SetUniform("Offset", vec2f{-1.0f, -1.0f});
		m_shaderManager->SetUniform("Time", uniformTime * 1.02f);
		m_RHI->DebugDraw(EPrimitiveType::Triangles, vertices.data(), (uint32)vertices.size());
		m_shaderManager->SetUniform("Offset", vec2f{-1.0f, 0.0f});
		m_shaderManager->SetUniform("Time", uniformTime * 1.01f);
		m_RHI->DebugDraw(EPrimitiveType::Triangles, vertices.data(), (uint32)vertices.size());
	}
}