#include "Shader.h"
#include "Base/LoggerManager/LoggerManager.h"
#include "Graphics/GHI/GHI.h"

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

	/* TODO:
		- distinguish nameHash & sourceHash
		- add logs for each error case
		- GLhandle recompile on non-zero id
		- refactor, possibly just returning compile result and setting + asserting m_valid in ctor
	*/
	bool Shader::Compile(const std::string& source)
	{
		if (m_handle != 0u)
		{
			// TODO: support recompilation
			LOG(EChannelComponent::EngineError, "Shader recompilation has not been implemented!");
			throw Exceptions::NotImplemented();
		}
		else if (source.empty())
		{
			LOG(EChannelComponent::EngineError, "Shader source is empty; nothing to compile.");
		}
		else if (m_handle = GHI::CreateShader(m_stage)) // let GHI error-handle its functions
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
				LOG(EChannelComponent::EngineWarning, "%s|%s\n", m_name.c_str(), std::string(infoLog));

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