#include "Base/GambitBasePCH.h"
#include "BaseConfig.h"

namespace gb
{
	BaseConfig::BaseConfig()
	{
		m_json = nlohmann::json::object();
	}

	bool BaseConfig::HasMember(const std::string& name) const
	{
		if (m_json.is_null())
		{
			return false;
		}

		if (!m_json.is_object())
		{
			return false;
		}

		return m_json.contains(name);
	}

	bool BaseConfig::HasMember(const char* name) const
	{
		return HasMember(std::string(name));
	}
}