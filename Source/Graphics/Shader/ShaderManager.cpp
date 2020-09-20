#include "ShaderManager.h"
#include "Base/FileManager/FileManager.h"
#include "Base/LoggerManager/LoggerManager.h"
#include "Graphics/Shader/Shader.h"
#include "Graphics/Shader/ShaderProgram.h"

namespace gb
{
	static const char* g_fallbackVSName	= "FS_Fallback";
	static const char* g_fallbackFSName = "VS_Fallback";
	static const char* g_fallbackSPName = "Fallback";

	ShaderManager::ShaderManager() :
		m_shaderMap(),
		m_shaderProgramMap(),
		m_rootLoadPath(""),
		m_boundShaderProgram(nullptr)
	{

	}

	ShaderManager::~ShaderManager()
	{
		// TODO: destroy shaders and shader programs
	}

	void ShaderManager::SetRootLoadPath(const std::string& loadPath)
	{
		if (loadPath.empty())
		{
			LOG(EChannelComponent::EngineInfo, "Shader load path is empty! Preserving original path.");
		}
		else
		{
			m_rootLoadPath = loadPath;
		}
	}

	bool ShaderManager::CreateFallbackShaders()
	{
		if (LoadShader("VS_Fallback.glsl") && LoadShader("FS_Fallback.glsl") && CreateShaderProgram(g_fallbackVSName, g_fallbackFSName, g_fallbackSPName))
		{
			LOG(EChannelComponent::EngineInfo, "Successfully created fallback shaders.");
			return true;
		}
		else
		{
			LOG(EChannelComponent::EngineError, "Fallback shader creation was unsuccessful!");
			assert(false);
			return false;
		}
	}

	void ShaderManager::BindFallbackShaderProgram()
	{
		BindShaderProgram(g_fallbackSPName);
	}

	bool ShaderManager::LoadShader(const std::string& name, const std::string& source, const EShaderStage stage)
	{
		bool loadResult = false;
		if (name.empty())
		{
			LOG(EChannelComponent::EngineError, "Shader name is empty!");
		}
		else if (source.empty())
		{
			LOG(EChannelComponent::EngineError, "Shader source code is empty!");

		}
		else
		{
			Unique<Shader> shader = std::make_unique<Shader>(name, source.c_str(), stage);
			if (shader.get() && shader->IsValid())
			{
				m_shaderMap.insert(std::make_pair(name, std::move(shader)));
				loadResult = true;
			}
			else
			{
				LOG(EChannelComponent::EngineError, "Shader load failed!");
			}
		}
		return loadResult;
	}

	bool ShaderManager::LoadShader(const std::string& filePath)
	{
		bool loadResult = false;
		if (filePath.empty())
		{
			LOG(EChannelComponent::EngineError, "Shader file path is empty!");
		}
		else if (filePath.ends_with(ShaderConstants::FileExtension))
		{
			const std::string fullPath  = m_rootLoadPath + filePath;
			std::string		  name		= filePath.substr(0u, filePath.length() - strlen(ShaderConstants::FileExtension));
			std::string		  prefix	= filePath.substr(0u, ShaderConstants::FilePrefixLength);
			std::string		  source	= "";

			loadResult = GetFileManager()->ReadFromFile(fullPath, source) && LoadShader(name, source, ShaderConstants::GetStageFromFilePrefix(prefix));
		}
		else
		{
			LOG(EChannelComponent::EngineError, "Please provide a {} file!", ShaderConstants::FileExtension);
		}
		return loadResult;
	}

	bool ShaderManager::CreateShaderProgram(const std::string& vertexShaderName, const std::string& fragmentShaderName, const std::string& programName = "")
	{
		if (vertexShaderName.empty() || fragmentShaderName.empty())
		{
			LOG(EChannelComponent::EngineError, "ShaderPrograms require named vertex and fragment shaders.");
			return false;
		}

		const auto vs = m_shaderMap.find(vertexShaderName);
		if (vs == m_shaderMap.end())
		{
			LOG(EChannelComponent::EngineError, "Vertex shader named '{}' does not exist!", vertexShaderName);
		}
		else
		{
			const auto fs = m_shaderMap.find(fragmentShaderName);
			if (fs == m_shaderMap.end())
			{
				LOG(EChannelComponent::EngineError, "Fragment shader named '{}' does not exist!", fragmentShaderName);
			}
			else if (vs->second->IsValid() && fs->second->IsValid())
			{
				const std::string newProgramName = programName == "" ? vertexShaderName + fragmentShaderName : programName;
				Unique<ShaderProgram> shaderProgram = std::make_unique<ShaderProgram>(vs->second.get(), fs->second.get(), newProgramName);
				if (shaderProgram && shaderProgram->IsValid())
				{
					m_shaderProgramMap.insert(std::make_pair(newProgramName, std::move(shaderProgram)));
					return true;
				}
				else
				{
					LOG(EChannelComponent::EngineError, "Shader program isn't valid after creation!");
				}
			}
		}

		return false;
	}

	void ShaderManager::BindShaderProgram(const std::string& name)
	{
		const auto prog = m_shaderProgramMap.find(name);
		if (prog == m_shaderProgramMap.end())
		{
			LOG(EChannelComponent::EngineError, "ShaderProgram named '{}' does not exist!", name);
			assert(false);
		}
		else
		{
			prog->second->Bind();
			m_boundShaderProgram = prog->second.get();
		}
	}

	void ShaderManager::SetUniform(const std::string& name, const float value)
	{
		assert(m_boundShaderProgram);
		m_boundShaderProgram->SetUniform(name, value);
	}

	void ShaderManager::SetUniform(const std::string& name, const int32 value)
	{
		assert(m_boundShaderProgram);
		m_boundShaderProgram->SetUniform(name, value);
	}

	void ShaderManager::SetUniform(const std::string& name, const vec2f& value)
	{
		assert(m_boundShaderProgram);
		m_boundShaderProgram->SetUniform(name, value);
	}

	void ShaderManager::SetUniform(const std::string& name, const vec2i& value)
	{
		assert(m_boundShaderProgram);
		m_boundShaderProgram->SetUniform(name, value);
	}

	void ShaderManager::SetUniform(const std::string& name, const vec3f& value)
	{
		assert(m_boundShaderProgram);
		m_boundShaderProgram->SetUniform(name, value);
	}

	void ShaderManager::SetUniform(const std::string& name, const vec3i& value)
	{
		assert(m_boundShaderProgram);
		m_boundShaderProgram->SetUniform(name, value);
	}

	void ShaderManager::SetUniform(const std::string& name, const vec4f& value)
	{
		assert(m_boundShaderProgram);
		m_boundShaderProgram->SetUniform(name, value);
	}

	void ShaderManager::SetUniform(const std::string& name, const vec4i& value)
	{
		assert(m_boundShaderProgram);
		m_boundShaderProgram->SetUniform(name, value);
	}
}