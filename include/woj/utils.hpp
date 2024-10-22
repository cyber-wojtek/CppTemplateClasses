#pragma once

#include <type_traits>
#include <limits>
#include <cstdint>
#include <optional>
#include <string>

#include "base.hpp"
#include "defs.hpp"

namespace woj
{
	namespace utils
	{
		template <size_t Min, size_t Max>
		struct auto_integer
		{
			using type = typename std::conditional<Min < 0,
				typename std::conditional<Max <= (std::numeric_limits<int8_t>::max)(), int8_t,
					typename std::conditional<Max <= (std::numeric_limits<int16_t>::max)(), int16_t,
						typename std::conditional<Max <= (std::numeric_limits<int32_t>::max)(), int32_t,
							typename std::conditional<Max <= (std::numeric_limits<int64_t>::max)(), int64_t, void>::type
						>::type
					>::type
				>::type,
				typename std::conditional<Max <= (std::numeric_limits<uint8_t>::max)(), uint8_t,
					typename std::conditional<Max <= (std::numeric_limits<uint16_t>::max)(), uint16_t,
						typename std::conditional<Max <= (std::numeric_limits<uint32_t>::max)(), uint32_t,
							typename std::conditional<Max <= (std::numeric_limits<uint64_t>::max)(), uint64_t, void>::type
						>::type
					>::type
				>::type
			>::type;
		};

		template <size_t Min, size_t Max>
		using auto_integer_t = typename auto_integer<Min, Max>::type;

		template <long double Max>
		struct auto_float
		{
			using type = typename std::conditional < Max <= (std::numeric_limits<float>::max)(), float,
				typename std::conditional < Max <= (std::numeric_limits<double>::max)(), double,
					typename std::conditional < Max <= (std::numeric_limits<long double>::max)(), long double, void>::type
				>::type
			>::type;
		};

		template <long double Max>
		using auto_float_t = typename auto_float<Max>::type;

		template <typename T>
		constexpr T& as_lvalue(T&& t) noexcept
		{
			return t;
		}

		template <typename T>
		constexpr T&& as_rvalue(T&& t) noexcept
		{
			return static_cast<T&&>(t);
		}

		namespace creval
		{
			constexpr size_t strlen(char const* str) noexcept
			{
				if (is_constant_evaluated())
				{
					size_t i;
					for (i = 0; str[i]; ++i);
					return i;
				}

				return ::strlen(str);
			}

			constexpr size_t strnlen(char const* str, const size_t max_count) noexcept
			{
				if (is_constant_evaluated())
				{
					size_t i;
					for (i = 0; i < max_count && str[i]; ++i);
					return i;
				}

				return ::strnlen(str, max_count);
			}

			constexpr size_t wcslen(wchar_t const* str) noexcept
			{
				if (is_constant_evaluated())
				{
					size_t i;
					for (i = 0; str[i]; ++i);
					return i;
				}

				return ::wcslen(str);
			}

			constexpr size_t wcsnlen(wchar_t const* str, const size_t max_count) noexcept
			{
				if (is_constant_evaluated())
				{
					size_t i;
					for (i = 0; i < max_count && str[i]; ++i);
					return i;
				}

				return ::wcsnlen(str, max_count);
			}

			constexpr char* strcpy(char* dest, char const* src) noexcept
			{
				if (is_constant_evaluated())
				{
					for (size_t i = 0; (dest[i] = src[i]); ++i);
					return dest;
				}

				return ::strcpy(dest, src);
			}

			constexpr char* strncpy(char* dest, char const* src, const size_t max_count) noexcept
			{
				if (is_constant_evaluated())
				{
					size_t i;
					for (i = 0; i < max_count && src[i]; ++i)
					{
						dest[i] = src[i];
					}
					// Fill the remaining space with null characters
					for (; i < max_count; ++i)
					{
						dest[i] = '\0';
					}
					return dest;
				}

				return ::strncpy(dest, src, max_count);
			}

			constexpr wchar_t* wcscpy(wchar_t* dest, wchar_t const* src) noexcept
			{
				if (is_constant_evaluated())
				{
					for (size_t i = 0; (dest[i] = src[i]); ++i);
					return dest;
				}

				return ::wcscpy(dest, src);
			}

			constexpr wchar_t* wcsncpy(wchar_t* dest, wchar_t const* src, const size_t max_count) noexcept
			{
				if (is_constant_evaluated())
				{
					size_t i;
					for (i = 0; i < max_count && src[i]; ++i)
					{
						dest[i] = src[i];
					}
					// Fill the remaining space with null characters
					for (; i < max_count; ++i)
					{
						dest[i] = '\0';
					}
					return dest;
				}

				return ::wcsncpy(dest, src, max_count);
			}

			constexpr char* strcat(char* dest, char const* src) noexcept
			{
				if (is_constant_evaluated())
				{
					size_t i;
					
					for (i = 0; dest[i]; ++i);

					for (size_t j = 0; (dest[i + j] = src[j]); ++j);

					return dest;
				}

				return ::strcat(dest, src);
			}

			constexpr char* strncat(char* dest, char const* src, const size_t max_count) noexcept
			{
				if (is_constant_evaluated())
				{
					size_t i;
					for (i = 0; dest[i]; ++i);  // Find end of dest

					size_t j;
					for (j = 0; j < max_count && src[j]; ++j)
					{
						dest[i + j] = src[j];
					}
					// Null terminate the result
					dest[i + j] = '\0';
					return dest;
				}

				return ::strncat(dest, src, max_count);
			}

			constexpr wchar_t* wcscat(wchar_t* dest, wchar_t const* src) noexcept
			{
				if (is_constant_evaluated())
				{
					size_t i;

					for (i = 0; dest[i]; ++i);

					for (size_t j = 0; (dest[i + j] = src[j]); ++j);

					return dest;
				}

				return ::wcscat(dest, src);
			}

			constexpr wchar_t* wcsncat(wchar_t* dest, wchar_t const* src, const size_t max_count) noexcept
			{
				if (is_constant_evaluated())
				{
					size_t i;
					for (i = 0; dest[i]; ++i);  // Find end of dest

					size_t j;
					for (j = 0; j < max_count && src[j]; ++j)
					{
						dest[i + j] = src[j];
					}
					// Null terminate the result
					dest[i + j] = '\0';
					return dest;
				}
				return ::wcsncat(dest, src, max_count);
			}
		}
	}
}