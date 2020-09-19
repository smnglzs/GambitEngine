#pragma once
#include "Base/Common/Common.h"
#include "Graphics/Export.h"
#include "Graphics/Geometry/VertexArray.h"
#include "Graphics/Shader/ShaderManager.h"
#include "Graphics/Texture/TextureManager.h"
#include "Graphics/Texture/TextureManager.h"

namespace gb
{
	class GAMBIT_GRAPHICS_API RenderObject
	{
	public:
		RenderObject(const std::string& name);
		virtual ~RenderObject();
		
		const std::string& GetName() const;

		static uint32 GetNumCreated();
		static uint32 GetNumExisting();
		
		void SetMesh();
		void SetTexture();
		void SetShaderProgram();

	protected:
		static uint32 s_numCreated;
		static uint32 s_numExisting;

	protected:
		std::string			  m_name;
		VertexArray			  m_mesh;
		Shared<Texture>		  m_texture;
		Shared<ShaderProgram> m_shaderProgram;
	};
}