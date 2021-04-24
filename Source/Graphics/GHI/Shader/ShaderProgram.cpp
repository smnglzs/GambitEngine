#include "ShaderProgram.h"
#include "Base/LoggerManager/LoggerManager.h"
#include "Graphics/GHI/GHI.h"

namespace gb
{
#pragma region Helper Objects
	class ScopedShaderLinker final
	{
	public:
		explicit ScopedShaderLinker(const uint32 programId, const uint32* shaderIds) :
			m_programId(programId),
			m_shaderIds(shaderIds),
			m_numShaders(0u),
			m_success(false)
		{
			for (uint8 i = 0u; i < ShaderGlobals::NumShaderStages; ++i)
			{
				if (m_shaderIds[0] > 0u)
				{
					GHI::AttachShaderToProgram(m_shaderIds[i], m_programId);
					++m_numShaders;
				}
			}
			m_success = GHI::LinkShaderProgram(m_programId);
		}

		~ScopedShaderLinker()
		{
			for (uint32 i = 0; i < m_numShaders; ++i)
				GHI::DetachShaderFromProgram(m_shaderIds[i], m_programId);
		}

		inline bool GetSuccess() const { return m_success; }

	private:
		const uint32* m_shaderIds;
		const uint32  m_programId;
		uint32		  m_numShaders;
		bool		  m_success;
	};
/* Helper Objects */ #pragma endregion

	ShaderProgram::ShaderProgram() :
		m_valid(false),
		m_name("InvalidShaderProgram"),
		m_shaders({}),
		m_numActiveUniforms(0)
	{
	}

	ShaderProgram::ShaderProgram(LinkedShaders& shaders, const std::string& name) :
		m_numActiveUniforms(0),
		m_name(name),
		m_shaders(shaders),
		m_valid(false)
	{
		for (auto shader : shaders.shaders)
			if (shader) assert(shader->IsValid());

		Create(shaders.GetShader(EShaderStage::Vertex), shaders.GetShader(EShaderStage::Fragment));
	}

	/*
	ShaderProgram::ShaderProgram(Shader& vertexShader, Shader& fragmentShader, const std::string& name) :
		m_numActiveUniforms(0),
		m_name(name),
		m_vertexShader(vertexShader),
		m_fragmentShader(fragmentShader),
		m_valid(false)
	{
		assert(vertexShader.IsValid() && fragmentShader.IsValid());
		Create(vertexShader, fragmentShader);
	}
	*/

	ShaderProgram::~ShaderProgram()
	{
		Destroy();
	}

	bool ShaderProgram::Create(Shader& vertexShader, Shader& fragmentShader)
	{
		if (m_handle = GHI::CreateShaderProgram())
		{
			if (m_valid = Link())
			{
				m_name = vertexShader.GetName() + fragmentShader.GetName();
				m_numActiveUniforms = GHI::GetNumActiveUniforms(m_handle);
				return true;
			}
			else
			{
				// char infoLog[ShaderGlobals::ProgramInfoLogSize];
				// GHI::GetShaderProgramInfoLog(m_handle, infoLog);
				Destroy();
				assert(false && "Failed to link shader program!");
				return false;
			}
		}
		else
		{
			assert(false && "GHI failed to create shader program!");
			return false;
		}
	}

	bool ShaderProgram::Link()
	{
		// TODO: Write helper for this.
		uint32 shaderIds[ShaderGlobals::NumShaderStages];
		memset(shaderIds, 0, ShaderGlobals::NumShaderStages * sizeof(uint32));

		for (uint32 stage = 0u; stage < ToUnderlyingType(EShaderStage::Count); ++stage)
			shaderIds[stage] = m_shaders.shaders[stage]->GetHandle();

		ScopedShaderLinker linker(m_handle, shaderIds);
		return linker.GetSuccess();
	}

	void ShaderProgram::Bind()
	{
		GHI::BindShaderProgram(m_handle);
	}

	void ShaderProgram::Destroy()
	{
		GHI::DeleteShaderProgram(m_handle);
		m_handle = 0u;
		m_valid = false;
		m_uniformLocationTable.clear();
	}

	void ShaderProgram::GetActiveUniforms()
	{
		throw Exceptions::NotImplemented();
	}

	int32 ShaderProgram::GetUniformLocation(const std::string& name)
	{
		const auto uniformIt = m_uniformLocationTable.find(name);
		if (uniformIt == m_uniformLocationTable.end())
		{
			const int32 location = GHI::GetUniformLocation(m_handle, name.c_str());
			if (GHI::CheckUniformLocation(location))
			{
				m_uniformLocationTable.insert(std::make_pair(name, location));
			}
			return location;
		}
		else
		{
			return uniformIt->second;
		}
	}

	void ShaderProgram::GetUniformLocations(const int32 numUniforms, const char** names, uint32* locations)
	{
		GHI::GetUniformLocations(m_handle, numUniforms, names, locations);
	}

	#define GHISetUniform(name, val) GHI::SetUniform(m_handle, GetUniformLocation(name), val);
	void ShaderProgram::SetUniform(const std::string& name, const float  f)	  { GHISetUniform(name, f);	  }
	void ShaderProgram::SetUniform(const std::string& name, const int32  i)	  { GHISetUniform(name, i);	  }
	void ShaderProgram::SetUniform(const std::string& name, const double d)	  { GHISetUniform(name, d);	  }
	void ShaderProgram::SetUniform(const std::string& name, const vec2f& v2f) { GHISetUniform(name, v2f); }
	void ShaderProgram::SetUniform(const std::string& name, const vec3f& v3f) { GHISetUniform(name, v3f); }
	void ShaderProgram::SetUniform(const std::string& name, const vec4f& v4f) { GHISetUniform(name, v4f); }
	void ShaderProgram::SetUniform(const std::string& name, const vec2i& v2i) { GHISetUniform(name, v2i); }
	void ShaderProgram::SetUniform(const std::string& name, const vec3i& v3i) { GHISetUniform(name, v3i); }
	void ShaderProgram::SetUniform(const std::string& name, const vec4i& v4i) { GHISetUniform(name, v4i); }
	void ShaderProgram::SetUniform(const std::string& name, const vec2u& v2u) { GHISetUniform(name, v2u); }
	void ShaderProgram::SetUniform(const std::string& name, const vec3u& v3u) { GHISetUniform(name, v3u); }
	void ShaderProgram::SetUniform(const std::string& name, const vec4u& v4u) { GHISetUniform(name, v4u); }

	#define GHISetUniformMatrix(name, mat, xpose) GHI::SetUniform(m_handle, GetUniformLocation(name), mat, xpose);
	void ShaderProgram::SetUniform(const std::string& name, const mat2f& m2f, bool xpose) { GHISetUniformMatrix(name, m2f, xpose); }
	void ShaderProgram::SetUniform(const std::string& name, const mat3f& m3f, bool xpose) { GHISetUniformMatrix(name, m3f, xpose); }
	void ShaderProgram::SetUniform(const std::string& name, const mat4f& m4f, bool xpose) { GHISetUniformMatrix(name, m4f, xpose); }
}

/* TODO: 
	- Hashed string names for uniforms
*/