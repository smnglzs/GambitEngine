#include "ShaderManager.h"
#include "Base/FileManager/FileManager.h"
#include "Base/LoggerManager/LoggerManager.h"
#include "Graphics/GHI/Shader/Shader.h"
#include "Graphics/GHI/Shader/ShaderProgram.h"

namespace gb
{
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
			LOG(EChannelComponent::EngineWarning, "{}: Shader load path is empty! Current path will be unchanged.", __func__);
		}
		else
		{
			m_rootLoadPath = loadPath;
		}
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
			// TODO: Check source hash; if match found, don't create copy of shader.
			auto shader = std::make_unique<Shader>(name, source.c_str(), stage);
			if (shader.get() && shader->IsValid())
			{
				m_shaderMap.insert(std::make_pair(name, std::move(shader)));
				loadResult = true;
			}
			else
			{
				throw Exceptions::LoadFailed();
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
		else if (filePath.ends_with(ShaderGlobals::FileExtension))
		{
			std::string	source = "";
			std::string	name = filePath.substr(0u, filePath.length() - strlen(ShaderGlobals::FileExtension));
			const EShaderStage stage = ShaderGlobals::GetStageFromFilePrefix(filePath.substr(0u, ShaderGlobals::FilePrefixLength));

			loadResult = GetFileManager()->ReadFromFile(m_rootLoadPath + filePath, source) && LoadShader(name, source, stage);
		}
		else
		{
			LOG(EChannelComponent::EngineError, "Please provide a {} file!", ShaderGlobals::FileExtension);
			assert(false);
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

		bool creationResult = false;
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
				auto linkedShaders = ShaderProgram::LinkedShaders({vs->second.get(), fs->second.get()});
				auto shaderProgram = std::make_unique<ShaderProgram>(linkedShaders, programName);
				if (shaderProgram && shaderProgram->IsValid())
				{
					m_shaderProgramMap.insert(std::make_pair(programName, std::move(shaderProgram)));
					creationResult = true;
				}
				else
				{
					LOG(EChannelComponent::EngineError, "Shader program isn't valid after creation!");
				}
			}
		}
		return creationResult;
	}

	ShaderProgram& ShaderManager::BindShaderProgram(const std::string& name)
	{
		const auto prog = m_shaderProgramMap.find(name);
		if (prog == m_shaderProgramMap.end())
		{
			LOG(EChannelComponent::EngineError, "ShaderProgram named '{}' does not exist!", name);
			assert(false);
			return ShaderProgram::GetInvalidShaderProgram();
		}
		else
		{
			prog->second->Bind();
			m_boundShaderProgram = prog->second.get();
			return *m_boundShaderProgram;
		}
	}
}