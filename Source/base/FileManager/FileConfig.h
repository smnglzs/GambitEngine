#pragma once
#include <optional>
#include <rapidjson/document.h>

#include "Base/Common/Common.h"

namespace gb
{
	class FileConfig final
	{
	public:
		FileConfig() = default;
		~FileConfig() = default;

		std::optional<int32> GetInt(const std::string& name);
		std::optional<int32> GetInt(const std::string_view& name);
		std::optional<int32> GetInt(const char* name);

		void SetInt(const std::string& name, int32 value);
		void SetInt(const std::string_view& name, int32 value);
		void SetInt(const char* name, int32 value);

	private:
		rapidjson::Document m_doc;
	};
}