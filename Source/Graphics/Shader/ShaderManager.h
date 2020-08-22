#pragma once
#include "Base/Common/Common.h"
#include "Base/Singleton/Singleton.h"
#include "Graphics/Export.h"
#include "Graphics/RHI/RHIDefinitions.h"

namespace gb
{
	class Shader;
	class ShaderProgram;
	class GAMBIT_GRAPHICS_API ShaderManager final : public ISingleton
	{
	public:
		ShaderManager();
		~ShaderManager();

		bool LoadShader(const std::string& name, const std::string& source, const EShaderStage stage);
		bool LoadShader(const std::string& filePath);
		bool CreateShaderProgram(const std::string& vertexShaderName, const std::string& fragmentShaderName);

		void BindShaderProgram(const std::string& name);
		void SetUniform(const std::string& name, const float  value);
		void SetUniform(const std::string& name, const int32  value);
		void SetUniform(const std::string& name, const vec2f& value);
		void SetUniform(const std::string& name, const vec2i& value);
		void SetUniform(const std::string& name, const vec3f& value);
		void SetUniform(const std::string& name, const vec3i& value);
		void SetUniform(const std::string& name, const vec4f& value);
		void SetUniform(const std::string& name, const vec4i& value);

	private:
		Hashmap<Unique<Shader>>			m_shaderMap;
		Hashmap<Unique<ShaderProgram>>  m_shaderProgramMap;
		ShaderProgram*					m_boundShaderProgram;
	};
}

CREATE_SINGLETON_ACCESSOR(ShaderManager, ShaderManager, GAMBIT_GRAPHICS_API);