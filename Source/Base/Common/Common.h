#pragma once
#include <array>
#include <forward_list>
#include <functional>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <variant>
#include <vector>

namespace gb
{
	// Integral types
	using int8   = int8_t;
	using int16  = int16_t;
	using int32  = int32_t;
	using int64  = int64_t;
	using uint8  = uint8_t;
	using uint16 = uint16_t;
	using uint32 = uint32_t;
	using uint64 = uint64_t;

	// Smart pointers
	template<class T>
	using Unique = std::unique_ptr<T>;

	template<class T>
	using Shared = std::shared_ptr<T>;

	template<class T>
	using Weak = std::weak_ptr<T>;

	// Containers
	template<typename T>
	using StringHashmap = std::unordered_map<std::string, T>;
}