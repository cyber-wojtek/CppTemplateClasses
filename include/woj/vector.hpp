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
		public:
			using value_type = ElementType;

			alignas(ElementType) ElementType m_data[Size];

			constexpr vector() noexcept : m_data{} {}

			explicit constexpr vector(const none_t) noexcept : m_data{} {}
			
			explicit constexpr vector(const ElementType& value) noexcept
			{
				if (is_constant_evaluated())
				{
					std::fill_n(m_data, Size, value);
				}
				IF_CONSTEXPR (std::is_same_v<ElementType, char> || std::is_same_v<ElementType, wchar_t> || std::is_same_v<ElementType, char8_t>)
				{
					memset(m_data, value, Size);
				}
				else
				{
					std::fill_n(m_data, Size, value);
				}
			}

			constexpr vector(const ElementType (&other)[Size]) noexcept
			{
				if (is_constant_evaluated())
				{
					std::copy_n(other, Size, m_data);
				}
				else
				{
					memcpy(m_data, other, Size * sizeof(ElementType));
				}
			}

			template <size_t OtherSize> requires (OtherSize != Size)
			constexpr vector(const ElementType(&other)[OtherSize]) noexcept
			{
				constexpr size_t min_size = Size < OtherSize ? Size : OtherSize;
				if (is_constant_evaluated())
				{
					std::copy_n(other, min_size, m_data);
				}
				else
				{
					memcpy(m_data, other, min_size * sizeof(ElementType));
				}
			}

			constexpr vector(const std::initializer_list<ElementType>& other) noexcept
			{
				const size_t min_size = Size < other.size() ? Size : other.size();
				if (is_constant_evaluated())
				{
					std::copy_n(other.begin(), min_size, m_data);
				}
				else
				{
					memcpy(m_data, other.begin(), min_size);
				}
			}

			template <typename... OthersValueTypes>
			constexpr vector(in_place_t, OthersValueTypes&&... other_values) noexcept : m_data{ std::forward<OthersValueTypes>(other_values)...} {}

			constexpr vector(const vector& other) noexcept
			{
				if (is_constant_evaluated())
				{
					std::copy_n(other.m_data, Size, m_data);
				}
				else
				{
					memcpy(m_data, other.m_data, Size * sizeof(ElementType));
				}
			}

			~vector() noexcept = default;

			constexpr vector& operator=(const vector& other) noexcept
			{
#ifndef NDEBUG
				if (this == &other)
				{
					return *this;
				}
#endif
				if (is_constant_evaluated())
				{
					std::copy_n(other.m_data, Size, m_data);
				}
				else
				{
					memcpy(m_data, other.m_data, Size * sizeof(ElementType));
				}
				return *this;
			}

			explicit constexpr operator bool() const noexcept
			{
				return true;
			}

			constexpr const ElementType& operator[](const size_t index) const noexcept
			{
				return m_data[index];
			}

			constexpr ElementType& operator[](const size_t index) noexcept
			{
				return m_data[index];
			}

			constexpr const ElementType(&data() const noexcept)[Size]
			{
				return m_data;
			}

			constexpr ElementType (& data() noexcept)[Size]
			{
				return m_data;
			}

			static 
#ifdef HAS_CXX20
				CONSTEVAL20
#else
				CONSTEXPR
#endif
				size_t size() noexcept
			{
				return Size;
			}
		};

		template <typename ElementType>
		class vector<ElementType, 0ull>
		{
		public:
			using value_type = ElementType;

			constexpr vector() noexcept = default;

			explicit constexpr vector(const none_t) noexcept {}

			explicit constexpr vector(const ElementType&) noexcept {}

			template <size_t OtherSize>
			constexpr vector(const ElementType(&)[OtherSize]) noexcept {}

			constexpr vector(const std::initializer_list<ElementType>&) noexcept {}

			template <typename... OthersValueTypes>
			constexpr vector(in_place_t, OthersValueTypes&&...) noexcept {}

			constexpr vector(const vector&) noexcept {}

			~vector() noexcept = default;

			constexpr vector& operator=(const vector&) noexcept
			{
				return *this;
			}

			explicit constexpr operator bool() const noexcept
			{
				return false;
			}

#ifndef NDEBUG
			NORETURN
#endif
			constexpr ElementType operator[](const size_t) const noexcept
			{
#ifndef NDEBUG
				throw std::out_of_range("woj::stack::vector<ElementType, 0ull>::operator[]");
#else
				return ElementType{};
#endif
			}

#ifndef NDEBUG
			NORETURN
#endif
				static
#ifdef HAS_CXX20
				CONSTEVAL20
#else
				CONSTEXPR
#endif
				const ElementType(& data() noexcept)[1]
			{
#ifndef NDEBUG
				throw std::out_of_range("woj::stack::vector<ElementType, 0ull>::data");
#else
				char c = 0;
				return reinterpret_cast<const ElementType(&)[1]>(c);
#endif
			}
			static
#ifdef HAS_CXX20
				CONSTEVAL20
#else
				CONSTEXPR
#endif
				size_t size() noexcept
			{
				return 0ull;
			}
		};

		// Deduction guides

		vector() -> vector<char, 0ull>;

		vector(const none_t) -> vector<char, 0ull>;

		vector(const empty_t) -> vector<char, 0ull>;

		template <typename ElementType, size_t Size>
		vector(const ElementType(&)[Size]) -> vector<ElementType, Size>;

		template <typename... OthersValueTypes>
		vector(const in_place_t, OthersValueTypes&&...) -> vector<std::common_type_t<std::remove_cvref_t<OthersValueTypes>...>, sizeof...(OthersValueTypes)>;
	}
}
