#pragma once
#include <type_traits>

template <typename E>
constexpr std::underlying_type_t<E> ToUnderlyingType(E e) noexcept
{
	return static_cast<std::underlying_type_t<E>>(e);
}

// EXAMPLE : this is how you can use the bitmask operator on an enum
// enum class TestEnum  : int32
// {
//		Value1 = 0x1,
//		Value2 = 0x2,
//		Value3 = 0x4,
// };
// ENABLE_BITMASK_OPERATORS(TestEnum);

template<typename E>
struct enable_bitmask_operators
{
	static constexpr bool enable = false;
};

#define ENABLE_BITMASK_OPERATORS(E)			\
template<>									\
struct enable_bitmask_operators<E>			\
{											\
	static constexpr bool enable = true;	\
}

template<typename E>
constexpr typename std::enable_if<enable_bitmask_operators<E>::enable, E>::type operator|(E lhs, E rhs)
{
	return static_cast<E>(ToUnderlyingType(lhs) | ToUnderlyingType(rhs));
}

template<typename E>
constexpr typename std::enable_if<enable_bitmask_operators<E>::enable, E>::type operator&(E lhs, E rhs)
{
	return static_cast<E>(ToUnderlyingType(lhs) & ToUnderlyingType(rhs));
}

template<typename E>
constexpr typename std::enable_if<enable_bitmask_operators<E>::enable, E>::type operator^(E lhs, E rhs)
{
	return static_cast<E>(ToUnderlyingType(lhs) ^ ToUnderlyingType(rhs));
}

template<typename E>
constexpr typename std::enable_if<enable_bitmask_operators<E>::enable, E>::type operator~(E lhs)
{
	return static_cast<E>(~ToUnderlyingType(lhs));
}

template<typename E>
constexpr typename std::enable_if<enable_bitmask_operators<E>::enable, E&>::type operator|=(E& lhs, E rhs)
{
	lhs = lhs | rhs;
	return lhs;
}

template<typename E>
constexpr typename std::enable_if<enable_bitmask_operators<E>::enable, E&>::type operator&=(E& lhs, E rhs)
{
	lhs = lhs & rhs;
	return lhs;
}

template<typename E>
constexpr typename std::enable_if<enable_bitmask_operators<E>::enable, E&>::type operator^=(E& lhs, E rhs)
{
	lhs = lhs ^ rhs;
	return lhs;
}

namespace Bitmask
{
	template<typename E>
	constexpr typename std::enable_if<enable_bitmask_operators<E>::enable, bool>::type Contains(E lhs, E rhs)
	{
		return (lhs & rhs) == rhs;
	}

	template<typename E>
	constexpr typename std::enable_if<enable_bitmask_operators<E>::enable, bool>::type IsEmpty(E lhs)
	{
		return lhs == E();
	}
}
