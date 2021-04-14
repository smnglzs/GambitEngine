#pragma once
#include "Graphics/Export.h"
#include "Graphics/GHI/GHICommon.h"

namespace gb
{
	class GAMBIT_GRAPHICS_API Shader final : public GHIResource
	{
	public:
		static Shader& GetInvalidShader()
		{
			static Shader invalid;
			return invalid;
		}

	public:
		Shader();
		Shader(const std::string& name, const std::string& source, const EShaderStage stage);
		~Shader();

		 const utils::HashedString& GetSourceHash() const { return m_sourceHash; }
		 const std::string&			GetName()	    const { return m_name; }
			   EShaderStage			GetStage()	    const { return m_stage; }

		virtual bool IsValid() const override { return m_valid; }

	protected:
		virtual void Destroy() override;

	private:
		bool Compile(const std::string& source);

	private:
		StringHashmap<int32>  m_uniformMap;
		utils::HashedString	  m_sourceHash;
		std::string			  m_name;
		EShaderStage		  m_stage;
		bool				  m_valid;
	};
}