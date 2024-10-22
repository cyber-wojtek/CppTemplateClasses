#pragma once

#include "base.hpp"
#include <algorithm>

#ifndef WOJ_VECTOR_HPP
#define WOJ_VECTOR_HPP
#endif

namespace woj
{
	namespace stack
	{
		template <typename ElementType, size_t Size>
		class vector
		{
			using value_type = ElementType;

			union 
			{
				none_t m_none;
				alignas(ElementType) ElementType m_data[Size];
			};

			constexpr vector() requires (Size > 0) : m_data{} {}

			constexpr vector() requires (!Size) : m_none{} {}

			template <size_t OtherSize>
			explicit constexpr vector(const ElementType (&other)[OtherSize])
			{
				constexpr size_t min_size = Size < OtherSize ? Size : OtherSize;
				if (is_constant_evaluated())
				{
					std::copy_n(other, other + min_size, m_data);
				}
				else
				{
					memcpy(m_data, other, min_size);
				}

				return *this;
			}

			explicit constexpr vector(const std::initializer_list<ElementType>& other)
			{
				const size_t min_size = Size < other.size() ? Size : other.size();
				if (is_constant_evaluated())
				{
					std::copy_n(other.begin(), other.begin() + min_size, m_data);
				}
				else
				{
					memcpy(m_data, other.begin(), min_size);
				}

				return *this;
			}
		};
	}
}
