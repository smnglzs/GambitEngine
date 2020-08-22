#pragma once
#include "Base/Common/Common.h"
#include "Graphics/Export.h"
#include "Graphics/RHI/RHIDefinitions.h"
#include "Graphics/RHI/RHIObject.h"

namespace gb
{
	class GAMBIT_GRAPHICS_API Shader final : public RHIObject
	{
	public:
		Shader();
		Shader(const std::string& name, const std::string& source, const EShaderStage stage);
		~Shader();

		uint64				GetHash()  const;
		const std::string&	GetName()  const;
		EShaderStage		GetStage() const;
		bool				IsValid()  const;

	protected:
		virtual void Destroy() override;

	private:
		bool Compile(const std::string& source);

	private:
		Hashmap<int32>  m_uniformMap;
		std::string		m_name;
		uint64			m_hash;
		EShaderStage	m_stage;
		bool			m_valid;
	};
}