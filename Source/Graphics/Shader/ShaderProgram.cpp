#include "ShaderProgram.h"
#include "Graphics/RHI/RHI.h"
#include "Graphics/Shader/Shader.h"

namespace gb
{
	ShaderProgram::ShaderProgram() :
		m_numActiveUniforms(0),
		m_name("InvalidShaderProgram"),
		m_vertexShader(nullptr),
		m_fragmentShader(nullptr),
		m_valid(false)
	{
	}

	ShaderProgram::ShaderProgram(Shader* vertexShader, Shader* fragmentShader) :
		m_numActiveUniforms(0),
		m_name("InvalidShaderProgram"),
		m_vertexShader(nullptr),
		m_fragmentShader(nullptr),
		m_valid(false)
	{
		assert(vertexShader && fragmentShader && vertexShader->IsValid() && fragmentShader->IsValid());
		Create(vertexShader, fragmentShader);
	}

	ShaderProgram::~ShaderProgram()
	{
		Destroy();
	}

	bool ShaderProgram::Create(Shader* vertexShader, Shader* fragmentShader)
	{
		if (m_id = m_RHI->CreateShaderProgram())
		{
			m_vertexShader = vertexShader;
			m_fragmentShader = fragmentShader;

			m_RHI->AttachShaderToProgram(m_vertexShader->GetId(), m_id);
			m_RHI->AttachShaderToProgram(m_fragmentShader->GetId(), m_id);
			m_RHI->LinkShaderProgram(m_id);

			if (m_RHI->GetShaderProgramLinkStatus(m_id))
			{
				m_name = vertexShader->GetName() + fragmentShader->GetName();
				m_numActiveUniforms = m_RHI->GetNumActiveUniforms(m_id);
				m_valid = true;
				return true;
			}
			else
			{
				//char infoLog[g_ShaderProgramInfoLogSize];
				//m_RHI->GetShaderProgramInfoLog(m_id, infoLog);
				//std::cout << infoLog << std::endl;
				Destroy();
				return false;
			}
		}
		else
		{	
			assert(false && "RHI failed to create shader program!");
			return false;
		}
	}

	void ShaderProgram::Bind()
	{
		m_RHI->BindShaderProgram(m_id);
	}

	void ShaderProgram::Destroy()
	{
		// [?] iterate and delete through glGetAttachedShaders output
		m_RHI->DeleteShaderProgram(m_id);
		m_id = 0u;
		m_valid = false;
	}

	void ShaderProgram::SetUniform(const std::string& name, const float value)
	{
		m_RHI->SetUniform(m_id, GetUniformLocation(name), value);
	}

	void ShaderProgram::SetUniform(const std::string& name, const int32 value)
	{
		m_RHI->SetUniform(m_id, GetUniformLocation(name), value);
	}

	void ShaderProgram::SetUniform(const std::string& name, const vec2f& value)
	{
		m_RHI->SetUniform(m_id, GetUniformLocation(name), value);
	}

	void ShaderProgram::SetUniform(const std::string& name, const vec2i& value)
	{
		m_RHI->SetUniform(m_id, GetUniformLocation(name), value);
	}

	void ShaderProgram::SetUniform(const std::string& name, const vec3f& value)
	{
		m_RHI->SetUniform(m_id, GetUniformLocation(name), value);
	}

	void ShaderProgram::SetUniform(const std::string& name, const vec3i& value)
	{
		m_RHI->SetUniform(m_id, GetUniformLocation(name), value);
	}

	void ShaderProgram::SetUniform(const std::string& name, const vec4f& value)
	{
		m_RHI->SetUniform(m_id, GetUniformLocation(name), value);
	}

	void ShaderProgram::SetUniform(const std::string& name, const vec4i& value)
	{
		m_RHI->SetUniform(m_id, GetUniformLocation(name), value);
	}

	int32 ShaderProgram::GetUniformLocation(const std::string& name)
	{
		const auto uniformIt = m_uniformLookup.find(name);
		if (uniformIt == m_uniformLookup.end())
		{
			const int32 loc = m_RHI->GetUniformLocation(m_id, name.c_str());
			assert(loc >= 0);
			return loc;
		}
		else
		{
			return uniformIt->second;
		}
	}

	bool ShaderProgram::IsValid() const
	{
		return m_valid;
	}
}