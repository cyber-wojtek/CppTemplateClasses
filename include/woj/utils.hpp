#pragma once

#include <type_traits>
#include <limits>
#include <cstdint>
#include <optional>

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
	}
}