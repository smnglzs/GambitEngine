#include "ShaderManager.h"
#include "Base/LoggerManager/LoggerManager.h"
#include "Graphics/Shader/Shader.h"
#include "Graphics/Shader/ShaderProgram.h"

namespace gb
{
#pragma region Fallback Shaders
	static const char* g_fallbackVsCode =
		"#version 450 core\n"
		"layout(location = 0) in vec2 Position;\n"
		"layout(location = 1) in vec2 TexCoord;\n"
		"uniform vec3 Color;\n"
		"uniform vec2 Offset = { 0.f, 0.f };\n"
		"out VS_OUT\n"
		"{\n"
		"   vec2 pos;\n"
		"   vec2 uv;\n"
		"   vec3 color;\n"
		"} vertex;\n"
		"void main()\n"
		"{\n"
		"   vertex.pos = Position + Offset;\n"
		"   vertex.uv = TexCoord;\n"
		"   vertex.color = Color;\n"
		"   gl_Position = vec4(vertex.pos, 0.0, 1.0);\n"
		"}";

	static const char* g_fallbackFsCode =
		"#version 450 core\n"
		"uniform float Time;\n"
		"uniform sampler2D Texture;\n"
		"in VS_OUT\n"
		"{\n"
		"   vec2 pos;\n"
		"   vec2 uv;\n"
		"   vec3 color;\n"
		"} vertex;\n"
		"out vec4 fragmentColor;\n"
		"void main()\n"
		"{\n"
		"   float g = abs(sin(Time));\n"
		"   float b = abs(cos(Time));\n"
		"   fragmentColor = mix(vec4(0.5, g, b, 1.0), texture2D(Texture, vertex.uv), 0.5);\n"
		"}";

	static const char* g_fallbackVSName	= "FallbackVS";
	static const char* g_fallbackFSName = "FallbackFS";
	static const char* g_fallbackSPName = "FallbackSP";
#pragma endregion

	ShaderManager::ShaderManager() :
		m_boundShaderProgram(nullptr)
	{

	}

	ShaderManager::~ShaderManager()
	{
		// TODO: destroy shaders and shader programs
	}

	bool ShaderManager::CreateFallbackShaders()
	{
		if (LoadShader(g_fallbackVSName, g_fallbackVsCode, EShaderStage::Vertex)	&&
			LoadShader(g_fallbackFSName, g_fallbackFsCode, EShaderStage::Fragment)	&&
			CreateShaderProgram(g_fallbackVSName, g_fallbackFSName, g_fallbackSPName))
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