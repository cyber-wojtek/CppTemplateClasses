#pragma once

#include "base.hpp"
#include <algorithm>
#include <array>

#ifndef WOJ_VECTOR_HPP
#define WOJ_VECTOR_HPP
#endif

namespace woj
{
	class out_of_vector_range final : public exception
	{
	public:
		constexpr out_of_vector_range() noexcept : exception{ static_cast<uint64_t>(-1), "Out of vector range", nullptr, nullptr } {}

		constexpr out_of_vector_range(const size_t line, const char* const file, const char* const function) noexcept : exception{ line, "Out of vector range", file, function } {}
	};

	namespace stack
	{
		template <typename ElementType, size_t Size>
		class vector
		{
		public:
			using value_type = ElementType;
			using size_type = size_t;
			using difference_type = ptrdiff_t;
			using reference = ElementType&;
			using const_reference = const ElementType&;
			using pointer = ElementType*;
			using const_pointer = const ElementType*;
			//using reverse_iterator = std::reverse_iterator<iterator>;
			//using const_reverse_iterator = std::reverse_iterator<const_iterator>;

			class iterator;

			class const_iterator final
			{
			public:
				using iterator_category = std::random_access_iterator_tag;
				using value_type = ElementType;
				using difference_type = ptrdiff_t;
				using pointer = const ElementType*;
				using reference = const ElementType&;

				const_pointer m_ptr;

				constexpr const_iterator() noexcept : m_ptr{ nullptr } {}

				explicit constexpr const_iterator(const pointer ptr) noexcept : m_ptr{ ptr } {}

				constexpr const_iterator(const const_iterator& other) noexcept = default;

				constexpr const_iterator(const iterator& other) noexcept : m_ptr{ other.m_ptr } {}

				~const_iterator() noexcept = default;

				constexpr const_iterator& operator=(const const_iterator& other) noexcept
				{
					if (this == &other)
					{
						return *this;
					}
					m_ptr = other.m_ptr;
					return *this;
				}

				constexpr const_iterator& operator++() noexcept
				{
					++m_ptr;
					return *this;
				}

				constexpr const_iterator operator++(int) noexcept
				{
					const_iterator temp{ m_ptr };
					++m_ptr;
					return temp;
				}

				constexpr const_iterator& operator--() noexcept
				{
					--m_ptr;
					return *this;
				}

				constexpr const_iterator operator--(int) noexcept
				{
					const_iterator temp{ m_ptr };
					--m_ptr;
					return temp;
				}

				constexpr const_iterator& operator+=(const difference_type offset) noexcept
				{
					m_ptr += offset;
					return *this;
				}

				constexpr const_iterator& operator-=(const difference_type offset) noexcept
				{
					m_ptr -= offset;
					return *this;
				}

				constexpr reference operator*() const noexcept
				{
					return *m_ptr;
				}

				constexpr const_pointer operator->() const noexcept
				{
					return m_ptr;
				}

				constexpr reference get() const noexcept
				{
					return *m_ptr;
				}

				constexpr reference operator[](const difference_type offset) const noexcept
				{
					return m_ptr[offset];
				}

				constexpr const_iterator operator+(const difference_type offset) const noexcept
				{
					return const_iterator{ m_ptr + offset };
				}

				constexpr const_iterator operator-(const difference_type offset) const noexcept
				{
					return const_iterator{ m_ptr - offset };
				}

				constexpr difference_type operator-(const const_iterator& other) const noexcept
				{
					return m_ptr - other.m_ptr;
				}

				constexpr bool operator==(const const_iterator& other) const noexcept
				{
					return m_ptr == other.m_ptr;
				}

				constexpr bool operator!=(const const_iterator& other) const noexcept
				{
					return m_ptr != other.m_ptr;
				}

				constexpr bool operator<(const const_iterator& other) const noexcept
				{
					return m_ptr < other.m_ptr;
				}

				constexpr bool operator>(const const_iterator& other) const noexcept
				{
					return m_ptr > other.m_ptr;
				}

				constexpr bool operator<=(const const_iterator& other) const noexcept
				{
					return m_ptr <= other.m_ptr;
				}

				constexpr bool operator>=(const const_iterator& other) const noexcept
				{
					return m_ptr >= other.m_ptr;
				}

				constexpr pointer unwrap() const noexcept
				{
					return m_ptr;
				}
			};

			class iterator final
			{
			public:
				using iterator_category = std::random_access_iterator_tag;
				using value_type = ElementType;
				using difference_type = ptrdiff_t;
				using pointer = ElementType*;
				using reference = ElementType&;

				pointer m_ptr;

				constexpr iterator() noexcept : m_ptr{ nullptr } {}

				explicit constexpr iterator(const pointer ptr) noexcept : m_ptr{ ptr } {}

				constexpr iterator(const iterator& other) noexcept = default;

				~iterator() noexcept = default;

				constexpr iterator& operator=(const iterator& other) noexcept
				{
					if (this == &other)
					{
						return *this;
					}
					m_ptr = other.m_ptr;
					return *this;
				}

				constexpr iterator& operator++() noexcept
				{
					++m_ptr;
					return *this;
				}

				constexpr iterator operator++(int) noexcept
				{
					iterator temp{ m_ptr };
					++m_ptr;
					return temp;
				}

				constexpr iterator& operator--() noexcept
				{
					--m_ptr;
					return *this;
				}

				constexpr iterator operator--(int) noexcept
				{
					iterator temp{ m_ptr };
					--m_ptr;
					return temp;
				}

				constexpr iterator& operator+=(const difference_type offset) noexcept
				{
					m_ptr += offset;
					return *this;
				}

				constexpr iterator& operator-=(const difference_type offset) noexcept
				{
					m_ptr -= offset;
					return *this;
				}

				constexpr reference operator*() const noexcept
				{
					return *m_ptr;
				}

				constexpr pointer operator->() const noexcept
				{
					return m_ptr;
				}

				constexpr reference get() const noexcept
				{
					return *m_ptr;
				}

				constexpr reference operator[](const difference_type offset) const noexcept
				{
					return m_ptr[offset];
				}

				constexpr iterator operator+(const difference_type offset) const noexcept
				{
					return iterator{ m_ptr + offset };
				}

				constexpr iterator operator-(const difference_type offset) const noexcept
				{
					return iterator{ m_ptr - offset };
				}

				constexpr difference_type operator-(const iterator& other) const noexcept
				{
					return m_ptr - other.m_ptr;
				}

				constexpr bool operator==(const iterator& other) const noexcept
				{
					return m_ptr == other.m_ptr;
				}

				constexpr bool operator!=(const iterator& other) const noexcept
				{
					return m_ptr != other.m_ptr;
				}

				constexpr bool operator<(const iterator& other) const noexcept
				{
					return m_ptr < other.m_ptr;
				}

				constexpr bool operator>(const iterator& other) const noexcept
				{
					return m_ptr > other.m_ptr;
				}

				constexpr bool operator<=(const iterator& other) const noexcept
				{
					return m_ptr <= other.m_ptr;
				}

				constexpr bool operator>=(const iterator& other) const noexcept
				{
					return m_ptr >= other.m_ptr;
				}

				constexpr operator const_iterator() const noexcept
				{
					return { m_ptr };
				}

				constexpr pointer unwrap() const noexcept
				{
					return m_ptr;
				}
			};

			class reverse_iterator;

			class const_reverse_iterator final
			{
			public:
				using iterator_category = std::random_access_iterator_tag;
				using value_type = ElementType;
				using difference_type = ptrdiff_t;
				using pointer = const ElementType*;
				using reference = const ElementType&;

				const_pointer m_ptr;

				constexpr const_reverse_iterator() noexcept : m_ptr{ nullptr } {}

				constexpr const_reverse_iterator(const pointer ptr) noexcept : m_ptr{ ptr } {}

				constexpr const_reverse_iterator(const const_reverse_iterator& other) noexcept = default;

				constexpr const_reverse_iterator(const reverse_iterator& other) noexcept : m_ptr{ other.m_ptr } {}

				~const_reverse_iterator() noexcept = default;

				constexpr const_reverse_iterator& operator=(const const_reverse_iterator& other) noexcept
				{
					if (this == &other)
					{
						return *this;
					}
					m_ptr = other.m_ptr;
					return *this;
				}

				constexpr const_reverse_iterator& operator++() noexcept
				{
					--m_ptr;
					return *this;
				}

				constexpr const_reverse_iterator operator++(int) noexcept
				{
					const_reverse_iterator temp{ m_ptr };
					--m_ptr;
					return temp;
				}

				constexpr const_reverse_iterator& operator--() noexcept
				{
					++m_ptr;
					return *this;
				}

				constexpr const_reverse_iterator operator--(int) noexcept
				{
					const_reverse_iterator temp{ m_ptr };
					++m_ptr;
					return temp;
				}

				constexpr const_reverse_iterator& operator+=(const difference_type offset) noexcept
				{
					m_ptr -= offset;
					return *this;
				}

				constexpr const_reverse_iterator& operator-=(const difference_type offset) noexcept
				{
					m_ptr += offset;
					return *this;
				}

				constexpr reference operator*() const noexcept
				{
					return *m_ptr;
				}

				constexpr const_pointer operator->() const noexcept
				{
					return m_ptr;
				}

				constexpr reference get() const noexcept
				{
					return *m_ptr;
				}

				constexpr reference operator[](const difference_type offset) const noexcept
				{
					return m_ptr[offset];
				}

				constexpr const_reverse_iterator operator+(const difference_type offset) const noexcept
				{
					return const_reverse_iterator{ m_ptr - offset };
				}

				constexpr const_reverse_iterator operator-(const difference_type offset) const noexcept
				{
					return const_reverse_iterator{ m_ptr + offset };
				}

				constexpr difference_type operator-(const const_reverse_iterator& other) const noexcept
				{
					return m_ptr - other.m_ptr;
				}

				constexpr bool operator==(const const_reverse_iterator& other) const noexcept
				{
					return m_ptr == other.m_ptr;
				}

				constexpr bool operator!=(const const_reverse_iterator& other) const noexcept
				{
					return m_ptr != other.m_ptr;
				}

				constexpr bool operator<(const const_reverse_iterator& other) const noexcept
				{
					return m_ptr > other.m_ptr;
				}

				constexpr bool operator>(const const_reverse_iterator& other) const noexcept
				{
					return m_ptr < other.m_ptr;
				}

				constexpr bool operator<=(const const_reverse_iterator& other) const noexcept
				{
					return m_ptr >= other.m_ptr;
				}

				constexpr bool operator>=(const const_reverse_iterator& other) const noexcept
				{
					return m_ptr <= other.m_ptr;
				}

				constexpr pointer unwrap() const noexcept
				{
					return m_ptr;
				}
			};

			class reverse_iterator final
			{
			public:
				using iterator_category = std::random_access_iterator_tag;
				using value_type = ElementType;
				using difference_type = ptrdiff_t;
				using pointer = ElementType*;
				using reference = ElementType&;

				pointer m_ptr;

				constexpr reverse_iterator() noexcept : m_ptr{ nullptr } {}

				explicit constexpr reverse_iterator(const pointer ptr) noexcept : m_ptr{ ptr } {}

				constexpr reverse_iterator(const reverse_iterator& other) noexcept = default;

				~reverse_iterator() noexcept = default;

				constexpr reverse_iterator& operator=(const reverse_iterator& other) noexcept
				{
					if (this == &other)
					{
						return *this;
					}
					m_ptr = other.m_ptr;
					return *this;
				}

				constexpr reverse_iterator& operator++() noexcept
				{
					--m_ptr;
					return *this;
				}

				constexpr reverse_iterator operator++(int) noexcept
				{
					reverse_iterator temp{ m_ptr };
					--m_ptr;
					return temp;
				}

				constexpr reverse_iterator& operator--() noexcept
				{
					++m_ptr;
					return *this;
				}

				constexpr reverse_iterator operator--(int) noexcept
				{
					reverse_iterator temp{ m_ptr };
					++m_ptr;
					return temp;
				}

				constexpr reverse_iterator& operator+=(const difference_type offset) noexcept
				{
					m_ptr -= offset;
					return *this;
				}

				constexpr reverse_iterator& operator-=(const difference_type offset) noexcept
				{
					m_ptr += offset;
					return *this;
				}

				constexpr reference operator*() const noexcept
				{
					return *m_ptr;
				}

				constexpr pointer operator->() const noexcept
				{
					return m_ptr;
				}

				constexpr reference get() const noexcept
				{
					return *m_ptr;
				}

				constexpr reference operator[](const difference_type offset) const noexcept
				{
					return m_ptr[offset];
				}

				constexpr reverse_iterator operator+(const difference_type offset) const noexcept
				{
					return reverse_iterator{ m_ptr - offset };
				}

				constexpr reverse_iterator operator-(const difference_type offset) const noexcept
				{
					return reverse_iterator{ m_ptr + offset };
				}

				constexpr difference_type operator-(const reverse_iterator& other) const noexcept
				{
					return m_ptr - other.m_ptr;
				}

				constexpr bool operator==(const reverse_iterator& other) const noexcept
				{
					return m_ptr == other.m_ptr;
				}

				constexpr bool operator!=(const reverse_iterator& other) const noexcept
				{
					return m_ptr != other.m_ptr;
				}

				constexpr bool operator<(const reverse_iterator& other) const noexcept
				{
					return m_ptr > other.m_ptr;
				}

				constexpr bool operator>(const reverse_iterator& other) const noexcept
				{
					return m_ptr < other.m_ptr;
				}

				constexpr bool operator<=(const reverse_iterator& other) const noexcept
				{
					return m_ptr >= other.m_ptr;
				}

				constexpr bool operator>=(const reverse_iterator& other) const noexcept
				{
					return m_ptr <= other.m_ptr;
				}

				constexpr operator const_reverse_iterator() const noexcept
				{
					return { m_ptr };
				}

				constexpr pointer unwrap() const noexcept
				{
					return m_ptr;
				}
			};

			union
			{
				alignas(ElementType) ElementType m_data[Size];
			};

			constexpr vector() noexcept : m_data{} {}

			explicit constexpr vector(const none_t) noexcept : m_data{} {}

			explicit constexpr vector(const noinit_t noinit) noexcept
			{
				if (is_constant_evaluated())
				{
					m_data = {};
				}
			}
			
			explicit constexpr vector(const ElementType& value) noexcept
			{
				if (is_constant_evaluated())
				{
					std::fill_n(m_data, Size, value);
				}
				if constexpr (std::is_same_v<ElementType, unsigned char> || std::is_same_v<ElementType, char> || std::is_same_v<ElementType, wchar_t> || std::is_same_v<ElementType, char8_t>)
				{
					memset(m_data, value, Size * sizeof(ElementType));
				}
				else
				{
					std::fill_n(m_data, Size, value);
				}
			}

			explicit constexpr vector(const ElementType (&other)[Size]) noexcept
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
			explicit constexpr vector(const ElementType(&other)[OtherSize]) noexcept
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
			explicit constexpr vector(in_place_t, OthersValueTypes&&... other_values) noexcept : m_data{ std::forward<OthersValueTypes>(other_values)...} {}

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
#ifndef NDEBUG
			(false)
#endif
			{
#ifndef NDEBUG
				if (index >= Size)
				{
					throw out_of_vector_range{ 449ull, "vector.hpp", "woj::stack::vector<ElementType, Size>::operator[]" };
				}
#endif

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

			static WOJ_CONSTEVAL size_t size() noexcept
			{
				return Size;
			}

			static WOJ_CONSTEVAL size_t max_size() noexcept
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
			explicit constexpr vector(const ElementType(&)[OtherSize]) noexcept {}

			constexpr vector(const std::initializer_list<ElementType>&) noexcept {}

			template <typename... OthersValueTypes>
			explicit constexpr vector(in_place_t, OthersValueTypes&&...) noexcept {}

			constexpr vector(const vector&) noexcept {}

			~vector() noexcept = default;

			constexpr vector& operator=(const vector&) noexcept = default;

			explicit constexpr operator bool() const noexcept
			{
				return false;
			}

#ifndef NDEBUG
			WOJ_NORETURN
#endif
			constexpr ElementType operator[](const size_t) const noexcept
			{
#ifndef NDEBUG
				throw out_of_vector_range{ 512ull, "vector.hpp", "woj::stack::vector<ElementType, 0ull>::operator[]" };
#else
				return ElementType{};
#endif
			}

#ifndef NDEBUG
			WOJ_NORETURN
#endif
			static WOJ_CONSTEVAL const ElementType(& data() noexcept)[1]
			{
#ifndef NDEBUG
				throw out_of_vector_range{ 524ull, "vector.hpp", "woj::stack::vector<ElementType, 0ull>::data" };
#else
				char c = 0;
				return reinterpret_cast<const ElementType(&)[1]>(c);
#endif
			}

			static WOJ_CONSTEVAL size_t size() noexcept
			{
				return 0ull;
			}

			static WOJ_CONSTEVAL size_t max_size() noexcept
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
