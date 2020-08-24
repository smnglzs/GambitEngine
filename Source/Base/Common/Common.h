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
	using int8	 = int8_t;
	using int16  = int16_t;
	using int32  = int32_t;
	using int64  = int64_t;
	using uint8  = uint8_t;
	using uint16 = uint16_t;
	using uint32 = uint32_t;
	using uint64 = uint64_t;

	template<typename T>
	using Hashmap = std::unordered_map<std::string, T>;

	template<class T>
	using Unique = std::unique_ptr<T>;

	template<class T>
	using Shared = std::shared_ptr<T>;
}