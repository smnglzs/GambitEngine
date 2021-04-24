#include "Renderer.h"
#include "Base/LoggerManager/LoggerManager.h"
#include "System/Window/WindowManager.h"
#include "Graphics/GHI/GHI.h"
#include "Graphics/GHI/Buffer/VertexArrayManager.h"
#include "Graphics/GHI/Shader/ShaderManager.h"
#include "Graphics/GHI/Texture/TextureManager.h"

namespace gb
{
	Renderer::Renderer() :
		m_shaderManager(GetShaderManager()),
		m_textureManager(GetTextureManager()),
		m_vertexManager(GetVertexArrayManager()),
		m_windowManager(GetWindowManager()),
		m_frameStart(0),
		m_frameEnd(0)
	{
		if (!(m_shaderManager && m_textureManager && m_vertexManager && m_windowManager))
		{
			LOG(gb::EChannelComponent::EngineError, "One/more GHI managers is/are null!");
			assert(false);
		}
	}

	void Renderer::BeginFrame()
	{
		//m_frameStart = GetTimeStamp();
		GHI::BeginFrame();
		Clear();
	}

	void Renderer::EndFrame()
	{
		GHI::EndFrame();
		//m_frameEnd = GetTimeStamp();
	}

	void Renderer::Clear()
	{
		GHI::SetClearColor(m_camera->GetClearColor().RGB);
		GHI::ClearRenderTarget(m_camera->GetClearMask());
	}

	void Renderer::Render(const RenderScene& scene)
	{
		throw Exceptions::NotImplemented();
	}

	void Renderer::Draw(const DrawCallData& drawData)
	{
		const auto primitiveType = drawData.mesh.GetPrimitiveType();

		// Bind shader (TODO: tweak bind)
		ShaderProgram& prog = m_shaderManager->BindShaderProgram(drawData.shader.GetName());

		if (const IndexBuffer* indexBuffer = drawData.mesh.GetIndexBuffer())
		{
			// TODO: check num and offset
			const uint32	   numIndices  = indexBuffer->GetNumElements();
			const EIndexFormat indexFormat = indexBuffer->GetIndexFormat();
			const void*		   indexOffset = drawData.mesh.GetIndexOffsetPointer();

			if (auto* transform = std::get_if<mat4f>(&drawData.transforms))
			{
				prog.SetUniform("u_model", *transform, false);
				GHI::DrawIndexed(primitiveType, numIndices, indexFormat, indexOffset);
			}
			else if (auto* transforms = std::get_if<std::vector<mat4f>*>(&drawData.transforms))
			{
				// TODO: Set transform in shader uniform buffer.
				throw Exceptions::NotImplemented();

				const int32 numInstances = static_cast<int32>((*transforms)->size());
				GHI::DrawIndexedInstanced(primitiveType, numIndices, indexFormat, indexOffset, numInstances);
			}
		}
		else
		{
			// TODO: check num and offset, make offset like index offset / vice versa
			const uint32 numVertices  = drawData.mesh.GetNumVertices();
			const uint32 vertexOffset = drawData.mesh.GetVertexOffset();

			if (auto* transform = std::get_if<mat4f>(&drawData.transforms))
			{
				prog.SetUniform("u_model", *transform, false);
				GHI::Draw(primitiveType, vertexOffset, numVertices);
			}
			else if (auto* transforms = std::get_if<std::vector<mat4f>*>(&drawData.transforms))
			{
				// TODO: Set transform in shader uniform buffer.
				throw Exceptions::NotImplemented();

				const int32 numInstances = static_cast<int32>((*transforms)->size());
				GHI::DrawInstanced(primitiveType, vertexOffset, numVertices, numInstances);
			}
		}
	}
}