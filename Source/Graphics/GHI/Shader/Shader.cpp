#include "Shader.h"
#include "Base/LoggerManager/LoggerManager.h"
#include "Graphics/GHI/GHI.h"

#include <iostream> // TODO: replace with Logger

namespace gb
{
	Shader::Shader() :
		m_valid(false),
		m_sourceHash(),
		m_stage(EShaderStage::Invalid)
	{
	}

	Shader::Shader(const std::string& name, const std::string& source, const EShaderStage stage) :
		m_name(name),
		m_sourceHash(),
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
		assert(m_handle == 0u); // break on existing shader for now, i.e. disable recompile

		/* TODO:
			- distinguish nameHash & sourceHash
			- add logs for each error case
			- GLhandle recompile on non-zero id
			- refactor, possibly just returning compile result and setting + asserting m_valid in ctor
		*/
		if (!source.empty() && (m_handle = GHI::CreateShader(m_stage)))
		{
			if (m_valid = GHI::CompileShader(m_handle, source.c_str()))
			{
				m_sourceHash.SetString(source);
				return true;
			}
			else
			{
				char infoLog[ShaderGlobals::ShaderInfoLogSize];
				GHI::GetShaderInfoLog(m_handle, infoLog);
				printf("%s|%s\n", m_name.c_str(), infoLog);

				Destroy();
			}
		}
		return false;
	}

	void Shader::Destroy()
	{
		GHI::DeleteShader(m_handle);
		m_handle = 0u;
		m_valid = false;
	}
}