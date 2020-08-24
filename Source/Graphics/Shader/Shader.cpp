#include "Shader.h"

#include "Base/Utils/StringUtils.h"

#include "Graphics/RHI/RHI.h"

#include <iostream> // TODO: replace with Logger

namespace gb
{
	Shader::Shader() :
		m_name("InvalidShader"),
		m_hash(0u),
		m_stage(EShaderStage::Count),
		m_valid(false)
	{
	}

	Shader::Shader(const std::string& name, const std::string& source, const EShaderStage stage) :
		m_name(name),
		m_hash(0u),
		m_stage(stage),
		m_valid(false)
	{
		Compile(source);
	}

	Shader::~Shader()
	{
		Destroy();
	}

	bool Shader::Compile(const std::string& source)
	{
		assert(m_id == 0); // break on existing shader for now

		/* TODO: 
			- add logs for each error case
			- handle recompile on non-zero id
		*/

		m_valid = false;

		if (source.empty())
		{
			return false;
		}
		else
		{
			m_id = m_RHI->CreateShader(m_stage); // combine this in CompileShader?
			if (m_id)
			{
				m_valid = m_RHI->CompileShader(m_id, source.c_str());
				if (m_valid)
				{
					m_hash = utils::HashString(source);
				}
				else
				{
					char infoLog[g_ShaderInfoLogSize];
					m_RHI->GetShaderInfoLog(m_id, infoLog);
					std::cout << infoLog << std::endl;

					Destroy();
					return false;
				}
			}
			else
			{
				m_valid = false;
			}
		}
	}

	void Shader::Destroy()
	{
		m_RHI->DeleteShader(m_id);
		m_id = 0u;
		m_valid = false;
	}

	const std::string& Shader::GetName() const
	{
		return m_name;
	}

	uint64 Shader::GetHash() const
	{
		return m_hash;
	}

	EShaderStage Shader::GetStage() const
	{
		return m_stage;
	}

	bool Shader::IsValid() const
	{
		return m_valid;
	}
}