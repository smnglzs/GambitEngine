#pragma once
#include "Base/GambitBasePCH.h"
#include <optional>

#include <nlohmann/json.hpp>

#include "Base/Export.h"

namespace gb
{
	class GAMBIT_BASE_API BaseConfig
	{
	public:
		BaseConfig();
		~BaseConfig() = default;

		void SetJson(const nlohmann::json& json) { m_json = json; }

		const nlohmann::json& GetJson() const { return m_json; }

		bool HasMember(const std::string& name) const;
		bool HasMember(const char* name) const;

		template <typename Type>
		void SetMember(const std::string& name, Type arg);

		template <typename Type>
		std::optional<Type> GetMember(const std::string& name);

		template <int N, typename T, glm::qualifier Q = glm::defaultp>
		static std::optional<glm::vec<N, T, Q>> GetVec(const nlohmann::json& json, const std::string& name);

	protected:
		nlohmann::json m_json;
	};

	template <typename Type>
	void BaseConfig::SetMember(const std::string& name, Type arg)
	{
		if (m_json.is_null())
		{
			return;
		}

		if (!m_json.is_object())
		{
			return;
		}

		m_json[name] = arg;
	}

	template <typename Type>
	std::optional<Type> BaseConfig::GetMember(const std::string& name)
	{
		if (m_json.is_null())
		{
			return {};
		}

		if (!m_json.is_object())
		{
			return {};
		}

		if (!HasMember(name))
		{
			return {};
		}

		return m_json[name].get<Type>();
	}

	template <const int N, typename T, glm::qualifier Q>
	std::optional<glm::vec<N, T, Q>> BaseConfig::GetVec(const nlohmann::json& json, const std::string& name)
	{
		auto arr = json[name].get<nlohmann::json::array_t>();
		if (arr.size() > 0)
		{
			glm::vec<N, T, Q> vec{};
			for (int n = 0; n < N; ++n)
			{
				vec[n] = arr[n];
			}
			return vec;
		}
		return {};
	}
}
