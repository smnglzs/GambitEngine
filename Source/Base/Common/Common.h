#pragma once
#include "Base/Common/Export.h"
#include "Base/Common/Math.h"
#include "Base/Utils/AssertUtils.h"
#include "Base/Utils/EnumUtils.h"

#include <array>
#include <functional>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace gb
{
	template<typename T>
	using Hashmap = std::unordered_map<std::string, T>;

	template<class T>
	using Unique = std::unique_ptr<T>;

	template<class T>
	using Shared = std::shared_ptr<T>;

	inline static uint64 HashString(const std::string& str)
	{
		return std::hash<std::string>{}(str);
	}
}