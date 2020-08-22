#pragma once
#include "Base/Utils/EnumUtils.h"
#include "Base/Common/Math.h"

#include <array>
#include <functional>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace gb
{
	typedef int8_t   int8;
	typedef int16_t  int16;
	typedef int32_t  int32;
	typedef int64_t  int64;

	typedef uint8_t  uint8;
	typedef uint16_t uint16;
	typedef uint32_t uint32;
	typedef uint64_t uint64;

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