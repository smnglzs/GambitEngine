#pragma once
#include "Base/GambitBasePCH.h"
#include "Graphics/Export.h"
#include "Graphics/GHI/GHICommon.h"
#include "Graphics/GHI/Shader/Shader.h"

namespace gb
{
	class GAMBIT_GRAPHICS_API ShaderProgram final : public GHIResource, public NoCopyNoMove
	{
	public:
		using ShaderArray = std::array<Shader*, ShaderGlobals::NumShaderStages>;

		struct LinkedShaders
		{
			LinkedShaders(ShaderArray&& shaders) :
				shaders(shaders)
			{
			}

			inline Shader& GetShader(const EShaderStage stage) const
			{
				// todo(simon): replace w/ operator[] overload
				const auto stageIdx = ToUnderlyingType(stage);
				if (stageIdx < ShaderGlobals::NumShaderStages && shaders[stageIdx])
					return *shaders[stageIdx];
		
				assert(false && "LinkedShaders has no shader bound to the specified stage!");
				return Shader::GetInvalidShader();
			}

			ShaderArray shaders;
		};

	public:
		ShaderProgram();
		ShaderProgram(LinkedShaders& shaders, const std::string& name);
		~ShaderProgram();

		void Bind();

		inline const std::string& GetName()	const { return m_name; }
		inline int32 GetNumActiveUniforms() const { return m_numActiveUniforms; }
		inline bool	 IsValid()				const { return m_valid; }

		// TODO: Make these setters const?
		void SetUniform(const std::string& name, const float  f);
		void SetUniform(const std::string& name, const int32  i);
		void SetUniform(const std::string& name, const double d);
		void SetUniform(const std::string& name, const vec2f& v2f);
		void SetUniform(const std::string& name, const vec3f& v3f);
		void SetUniform(const std::string& name, const vec4f& v4f);
		void SetUniform(const std::string& name, const vec2i& v2i);
		void SetUniform(const std::string& name, const vec3i& v3i);
		void SetUniform(const std::string& name, const vec4i& v4i);
		void SetUniform(const std::string& name, const vec2u& v2u);
		void SetUniform(const std::string& name, const vec3u& v3u);
		void SetUniform(const std::string& name, const vec4u& v4u);
		void SetUniform(const std::string& name, const mat2f& m2f, bool xpose);
		void SetUniform(const std::string& name, const mat3f& m3f, bool xpose);
		void SetUniform(const std::string& name, const mat4f& m4f, bool xpose);

	private:
		bool  Create(Shader& vertexShader, Shader& fragmentShader);
		void  GetActiveUniforms();
		int32 GetUniformLocation(const std::string& name);
		void  GetUniformLocations(const int32 numUniforms, const char** names, uint32* locations);
		bool  Link();

		virtual void Destroy() override;

	private:
		StringHashmap<int32> m_uniformLocationTable;
		std::string			 m_name;
		LinkedShaders		 m_shaders;
		int32				 m_numActiveUniforms;
		bool				 m_valid;

	public:
		static ShaderProgram& GetInvalidShaderProgram()
		{
			static ShaderProgram invalid;
			return invalid;
		}
	};

	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
}

/*  TODO:
	- Shader variants w/ globals/flags (to eliminate branching in shaders)
	- Implement copy/move ctor/operator
	- Program Introspection
		- Uniforms
		- Resources
			- Uniform block
			- Shader storage block
			- Buffer variable
			- ...

		struct InterfaceQuery
		{
			enum class EInterface : uint8
			{
				Uniform,
				UniformBlock,
				// ...
			};
		} m_piq;

		struct ResourceQuery
		{
			enum class EResource : uint8
			{

			};
		};
*/