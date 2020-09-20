#pragma once
#include "Base/Common/Common.h"
#include "Base/Singleton/Singleton.h"
#include "Graphics/Export.h"
#include "Graphics/GraphicsModule.h"
#include "Graphics/RHI/RHIConstants.h"

namespace gb
{
	/*
		TODO: Implement precompiled shader/program cache.
	*/

	class Shader;
	class ShaderProgram;
	class GAMBIT_GRAPHICS_API ShaderManager final : public ISingleton
	{
	public:
		ShaderManager();
		~ShaderManager();

		void SetRootLoadPath(const std::string& loadPath);

		bool LoadShader(const std::string& name, const std::string& source, const EShaderStage stage);
		bool LoadShader(const std::string& filePath);
		bool CreateShaderProgram(const std::string& vertexShaderName, const std::string& fragmentShaderName, const std::string& programName);

		void BindFallbackShaderProgram();
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
		friend void GraphicsModule::Load();
		bool CreateFallbackShaders();

	private:
		StringHashmap<Unique<Shader>>		  m_shaderMap;
		StringHashmap<Unique<ShaderProgram>>  m_shaderProgramMap;
		std::string							  m_rootLoadPath;
		ShaderProgram*						  m_boundShaderProgram;

	};
}

CREATE_SINGLETON_ACCESSOR(ShaderManager, ShaderManager, GAMBIT_GRAPHICS_API);