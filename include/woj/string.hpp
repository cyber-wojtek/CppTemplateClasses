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

namespace woj
{
	template <typename T>
	concept char_t = std::is_same_v<T, char> || std::is_same_v<T, wchar_t> || std::is_same_v<T, char16_t> || std::is_same_v<T, char32_t>;

	namespace stack
	{
		template <char_t TElem, size_t Size>
		class string;
	}
}