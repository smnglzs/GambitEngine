#include "ShaderManager.h"
#include "Base/LoggerManager/LoggerManager.h"
#include "Graphics/Shader/Shader.h"
#include "Graphics/Shader/ShaderProgram.h"

namespace gb
{
	ShaderManager::ShaderManager() :
		m_boundShaderProgram(nullptr)
	{
		
	}

	ShaderManager::~ShaderManager()
	{
		// TODO: destroy shaders and shader programs
	}

	bool ShaderManager::LoadShader(const std::string& name, const std::string& source, const EShaderStage stage)
	{
		/* TODO:
			- check name.empty() to avoid collisions in m_shaderMap
		*/

		bool loadResult = false;
		if (source.empty())
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
		LOG(EChannelComponent::EngineWarning, "{} not implemented yet!", __func__);
		assert(false);

		bool loadResult = false;
		/*
		// check filePath.empty()
		for (uint8 stageIdx = EShaderStage::Vertex; stageIdx < EShaderStage::Count; ++stageIdx)
		{
			if (filePath.ends_with(g_ShaderFileExtensions[stageIdx]))
			{
				filePath.substr(0u, filePath.length() - strlen(g_ShaderFileExtensions[stageIdx]));

				UniqueResource<Shader> shader = std::make_unique<Shader>(source.c_str(), stage);
				if (shader.get() + check shader creation + compilation)
				{
					// check shader creation + compilation
					m_shaderMap.insert(std::make_pair(source, shader));
				}
				else
				{
				
				}
		}
		*/
		return loadResult;
	}

	bool ShaderManager::CreateShaderProgram(const std::string& vertexShaderName, const std::string& fragmentShaderName)
	{
		if (vertexShaderName.empty() || fragmentShaderName.empty())
		{
			LOG(EChannelComponent::EngineError, "ShaderPrograms require named vertex and fragment shaders.");
			return false;
		}

		bool createResult = false;

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
				Unique<ShaderProgram> shaderProgram = std::make_unique<ShaderProgram>(vs->second.get(), fs->second.get());
				if (shaderProgram && shaderProgram->IsValid())
				{
					m_shaderProgramMap.insert(std::make_pair(vertexShaderName + fragmentShaderName, std::move(shaderProgram)));
					createResult = true;
				}
				else
				{
					LOG(EChannelComponent::EngineError, "Shader program isn't valid after creation!");
				}
			}
		}

		return createResult;
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