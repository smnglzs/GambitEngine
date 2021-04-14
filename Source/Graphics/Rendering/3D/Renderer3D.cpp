#include "Renderer3D.h"
#include "Base/LoggerManager/LoggerManager.h"
#include "Graphics/GHI/GHI.h"
#include "Graphics/GHI/Shader/ShaderProgram.h"

namespace gb
{
	Renderer3D::Renderer3D()
	{

	}

	Renderer3D::~Renderer3D()
	{

	}

	void Renderer3D::Init()
	{

	}

#if 0
	void Renderer3D::DebugDrawScene()
	{
		//GHI::SetWireframe(true);

		GHI::SetViewport(m_camera->GetView());
		GHI::SetRenderCapEnabled(RenderCaps::Blend, true);
		GHI::SetBlendFunc(EBlendFunc::SrcAlpha, EBlendFunc::OneMinusSrcAlpha);

		ShaderProgram& shader = m_shaderManager->BindShaderProgram("SP_Grid");
		shader.SetUniform("u_projection", m_camera->GetProjection(), false);
		shader.SetUniform("u_texture", 0);

		const auto texture = m_textureManager->BindTexture("QuestionBlock");
		assert(texture && texture->IsValid());

		const float tileSize = 64.0f;
		shader.SetUniform("u_tileSize", vec2u{ tileSize, tileSize });

		static const std::vector<Vertex2D> vertices =
		{
			{ {0.0f, 0.0f}, {0.0f, 0.0f} },
			{ {1.0f, 0.0f}, {1.0f, 0.0f} },
			{ {1.0f, 1.0f}, {1.0f, 1.0f} },
			{ {0.0f, 0.0f}, {0.0f, 0.0f} },
			{ {1.0f, 1.0f}, {1.0f, 1.0f} },
			{ {0.0f, 1.0f}, {0.0f, 1.0f} }
		};

		mat4f model{ 1.0f };
		const mat4f scale = glm::scale(model, vec3f{ tileSize, tileSize, 1.0f });
		for (int x = 0; x < 100; ++x)
		{
			for (int y = 0; y < 64; ++y)
			{
				if (true)
				{
					shader.SetUniform("u_tileCoords", vec2u{ 0u, 0u });

					model = mat4f{ 1.0f };
					model = glm::translate(model, vec3f{ tileSize * x, tileSize * y, 0.0f });
					model = glm::scale(	   model, vec3f{ tileSize,	   tileSize,	 1.0f });
					shader.SetUniform("u_model", model, false);

					GHI::DebugDraw(EPrimitiveType::Triangles, vertices);
				}
			}
		}

	}
#endif
}