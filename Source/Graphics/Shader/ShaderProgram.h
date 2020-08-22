#pragma once
#include "Base/Common/Common.h"
#include "Graphics/Export.h"
#include "Graphics/RHI/RHIObject.h"

namespace gb
{
	class Shader;

	class GAMBIT_GRAPHICS_API ShaderProgram final : public RHIObject
	{
	public:
		ShaderProgram();
		explicit ShaderProgram(Shader* vertexShader, Shader* fragmentShader);
		~ShaderProgram();

		void Bind();
		void SetUniform(const std::string& name, const float value);
		void SetUniform(const std::string& name, const int32 value);
		void SetUniform(const std::string& name, const vec2f& value);
		void SetUniform(const std::string& name, const vec2i& value);
		void SetUniform(const std::string& name, const vec3f& value);
		void SetUniform(const std::string& name, const vec3i& value);
		void SetUniform(const std::string& name, const vec4f& value);
		void SetUniform(const std::string& name, const vec4i& value);

		bool IsValid() const;

	protected:
		virtual void Destroy() override;

	private:
		bool Create(Shader* vertexShader, Shader* fragmentShader);
		int32 GetUniformLocation(const std::string& name);

	private:
		Hashmap<int32>  m_uniformLookup;
		std::string		m_name;
		Shader*			m_vertexShader;
		Shader*			m_fragmentShader;
		int32			m_numActiveUniforms;
		bool			m_valid;
	};
}