#pragma once

#ifndef WOJ_STRING_HPP
#define WOJ_STRING_HPP
#endif

#ifndef WOJ_DEFS_HPP
#include "defs.hpp"
#endif

#include <type_traits>
#include <cstddef>
#include <cstdint>
#if defined(HAS_CXX20)
#include <concepts>
#endif

namespace woj
{
	#if defined(HAS_CXX20)
	template <typename T>
	concept is_char = std::is_same_v<T, char> || std::is_same_v<T, wchar_t> || std::is_same_v<T, char16_t> || std::is_same_v<T, char32_t>;
	#else
	template <typename T>
	constexpr bool is_char = std::is_same_v<T, char> || std::is_same_v<T, wchar_t> || std::is_same_v<T, char16_t> || std::is_same_v<T, char32_t>;
	#endif

	namespace stack
	{
		template <typename TElem, size_t Size> requires is_char<TElem>
		class string;
	}
}