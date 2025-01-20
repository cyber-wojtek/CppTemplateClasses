#pragma once

#ifndef WOJ_STRING_HPP
#define WOJ_STRING_HPP
#include <cassert>

#include "string.hpp"
#endif

#ifndef WOJ_DEFS_HPP
#include "base.hpp"
#endif

#include <type_traits>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <cwchar>
#include <algorithm>
#include <iostream>
#if defined(WOJ_HAS_CXX20)
#include <concepts>
#endif

namespace woj
{
	#if defined(WOJ_HAS_CXX20)
	template <typename T>
	concept char_type = std::is_same_v<T, char> || std::is_same_v<T, char8_t> || std::is_same_v<T, wchar_t> || std::is_same_v<T, char16_t> || std::is_same_v<T, char32_t>;
	#else
	template <typename T>
	struct is_char
	{
		static constexpr bool value = std::is_same<T, char>::value     ||
									  std::is_same<T, wchar_t>::value  ||
									  std::is_same<T, char16_t>::value ||
									  std::is_same<T, char32_t>::value;
	};

	template <typename T>
	constexpr bool is_char_v = is_char<T>::value;
	#endif

	namespace stack
	{
#if defined(WOJ_HAS_CXX20)
		/**
		 * Class representing a stack-allocated string
		 * @tparam Elem Type of the string's elements
		 * @tparam MemSize Size of the string's memory buffer
		 */
		template <char_type Elem, size_t MemSize>
#else
		template <typename Elem, size_t MemSize, typename = std::enable_if_t<is_char_v<Elem>>>
#endif
		class string 
		{
		public:
			using value_type = Elem;
			using size_type = size_t;
			using difference_type = std::ptrdiff_t;
			using pointer = Elem*;
			using const_pointer = const Elem*;
			using reference = Elem&;
			using const_reference = const Elem&;

			class const_reverse_iterator;
			class reverse_reverse_iterator;
			class const_reverse_reverse_iterator;

			class reverse_iterator
			{
			public:
				pointer p_elem;

				constexpr reverse_iterator() noexcept : p_elem(nullptr) {}

				constexpr reverse_iterator(const noinit_t) noexcept {}

				explicit constexpr reverse_iterator(const pointer p_elem) noexcept : p_elem(p_elem) {}

				constexpr reverse_iterator(const reverse_iterator& other) noexcept : p_elem(other.p_elem) {}

				constexpr reverse_iterator(reverse_iterator&& other) noexcept : p_elem(other.p_elem)
				{
					other.p_elem = nullptr;
				}

				WOJ_CONSTEXPR20 ~reverse_iterator() noexcept = default;

				explicit constexpr operator const_reverse_iterator() const noexcept
				{
					return const_reverse_iterator(p_elem);
				}

				explicit constexpr operator reverse_reverse_iterator() const noexcept
				{
					return reverse_reverse_iterator(p_elem);
				}

				explicit constexpr operator const_reverse_reverse_iterator() const noexcept
				{
					return const_reverse_reverse_iterator(p_elem);
				}

				constexpr reverse_iterator& operator=(const reverse_iterator& other) noexcept = default;

				constexpr reverse_iterator& operator=(reverse_iterator&& other) noexcept
				{
					p_elem = other.p_elem;
					other.p_elem = nullptr;
					return *this;
				}

				constexpr reference operator*() const noexcept
				{
					return *p_elem;
				}

				constexpr pointer operator->() const noexcept
				{
					return p_elem;
				}

				constexpr reverse_iterator& operator++() noexcept
				{
					++p_elem;
					return *this;
				}

				constexpr reverse_iterator operator++(int) noexcept
				{
					reverse_iterator temp(*this);
					++p_elem;
					return temp;
				}

				constexpr reverse_iterator& operator--() noexcept
				{
					--p_elem;
					return *this;
				}

				constexpr reverse_iterator operator--(int) noexcept
				{
					reverse_iterator temp(*this);
					--p_elem;
					return temp;
				}

				constexpr reverse_iterator& operator+=(const difference_type value) noexcept
				{
					p_elem += value;
					return *this;
				}

				constexpr reverse_iterator operator+(const difference_type value) const noexcept
				{
					reverse_iterator temp(*this);
					temp += value;
					return *this;
				}

				constexpr reverse_iterator& operator-=(const difference_type value) noexcept
				{
					p_elem -= value;
					return *this;
				}

				constexpr reverse_iterator operator-(const difference_type value) const noexcept
				{
					reverse_iterator temp(*this);
					temp += value;
					return *this;
				}

				constexpr reverse_iterator& operator-(const reverse_iterator other) const noexcept
				{
					return p_elem - other.p_elem;
				}

				constexpr const reverse_iterator& as_const() const noexcept
				{
					return *this;
				}

				constexpr const_reverse_iterator constified() const noexcept
				{
					return const_reverse_iterator(p_elem);
				}

				constexpr reverse_reverse_iterator reversed() const noexcept
				{
					return reverse_reverse_iterator(p_elem);
				}

				constexpr const_reverse_reverse_iterator creversed() const noexcept
				{
					return const_reverse_reverse_iterator(p_elem);
				}
			};

			class const_reverse_iterator
			{
				const_pointer p_elem;

				constexpr const_reverse_iterator() noexcept : p_elem(nullptr) {}

				constexpr const_reverse_iterator(const noinit_t) noexcept {}

				explicit constexpr const_reverse_iterator(const const_pointer p_elem) noexcept : p_elem(p_elem) {}

				constexpr const_reverse_iterator(const const_reverse_iterator& other) noexcept : p_elem(other.p_elem) {}

				constexpr const_reverse_iterator(const_reverse_iterator&& other) noexcept : p_elem(other.p_elem)
				{
					other.p_elem = nullptr;
				}

				WOJ_CONSTEXPR20 ~const_reverse_iterator() noexcept = default;

				constexpr const_reverse_iterator& operator=(const const_reverse_iterator& other) noexcept = default;

				constexpr const_reverse_iterator& operator=(const_reverse_iterator&& other) noexcept
				{
					p_elem = other.p_elem;
					other.p_elem = nullptr;
					return *this;
				}

				constexpr reference operator*() const noexcept
				{
					return *p_elem;
				}

				constexpr pointer operator->() const noexcept
				{
					return p_elem;
				}

				constexpr const_reverse_iterator& operator++() noexcept
				{
					++p_elem;
					return *this;
				}

				constexpr const_reverse_iterator operator++(int) noexcept
				{
					const_reverse_iterator temp(*this);
					++p_elem;
					return temp;
				}

				constexpr const_reverse_iterator& operator--() noexcept
				{
					--p_elem;
					return *this;
				}

				constexpr const_reverse_iterator operator--(int) noexcept
				{
					const_reverse_iterator temp(*this);
					--p_elem;
					return temp;
				}

				constexpr const_reverse_iterator& operator+=(const difference_type value) noexcept
				{
					p_elem += value;
					return *this;
				}

				constexpr const_reverse_iterator operator+(const difference_type value) const noexcept
				{
					const_reverse_iterator temp(*this);
					temp += value;
					return *this;
				}

				constexpr const_reverse_iterator& operator-=(const difference_type value) noexcept
				{
					p_elem -= value;
					return *this;
				}

				constexpr const_reverse_iterator operator-(const difference_type value) const noexcept
				{
					const_reverse_iterator temp(*this);
					temp += value;
					return *this;
				}

				constexpr const_reverse_iterator& operator-(const const_reverse_iterator other) const noexcept
				{
					return p_elem - other.p_elem;
				}

				constexpr const const_reverse_iterator& as_const() const noexcept
				{
					return *this;
				}
			};

			class reverse_iterator
			{
			public:
				pointer p_elem;

				constexpr reverse_iterator() noexcept : p_elem(nullptr) {}

				constexpr reverse_iterator(const noinit_t) noexcept {}

				explicit constexpr reverse_iterator(const pointer p_elem) noexcept : p_elem(p_elem) {}

				constexpr reverse_iterator(const reverse_iterator& other) noexcept : p_elem(other.p_elem) {}

				constexpr reverse_iterator(reverse_iterator&& other) noexcept : p_elem(other.p_elem)
				{
					other.p_elem = nullptr;
				}

				WOJ_CONSTEXPR20 ~reverse_iterator() noexcept = default;

				constexpr reverse_iterator& operator=(const reverse_iterator& other) noexcept = default;

				constexpr reverse_iterator& operator=(reverse_iterator&& other) noexcept
				{
					p_elem = other.p_elem;
					other.p_elem = nullptr;
					return *this;
				}

				constexpr reference operator*() const noexcept
				{
					return *p_elem;
				}

				constexpr pointer operator->() const noexcept
				{
					return p_elem;
				}

				constexpr reverse_iterator& operator++() noexcept
				{
					++p_elem;
					return *this;
				}

				constexpr reverse_iterator operator++(int) noexcept
				{
					reverse_iterator temp(*this);
					++p_elem;
					return temp;
				}

				constexpr reverse_iterator& operator--() noexcept
				{
					--p_elem;
					return *this;
				}

				constexpr reverse_iterator operator--(int) noexcept
				{
					reverse_iterator temp(*this);
					--p_elem;
					return temp;
				}

				constexpr reverse_iterator& operator+=(const difference_type value) noexcept
				{
					p_elem += value;
					return *this;
				}

				constexpr reverse_iterator operator+(const difference_type value) const noexcept
				{
					reverse_iterator temp(*this);
					temp += value;
					return *this;
				}

				constexpr reverse_iterator& operator-=(const difference_type value) noexcept
				{
					p_elem -= value;
					return *this;
				}

				constexpr reverse_iterator operator-(const difference_type value) const noexcept
				{
					reverse_iterator temp(*this);
					temp += value;
					return *this;
				}

				constexpr reverse_iterator& operator-(const reverse_iterator other) const noexcept
				{
					return p_elem - other.p_elem;
				}

				constexpr const reverse_iterator& as_const() const noexcept
				{
					return *this;
				}

				constexpr const_reverse_iterator constified() const noexcept
				{
					return const_reverse_iterator(p_elem);
				}

				constexpr reverse_reverse_iterator reversed() const noexcept
				{
					return reverse_reverse_iterator(p_elem);
				}

				constexpr const_reverse_reverse_iterator creversed() const noexcept
				{
					return const_reverse_reverse_iterator(p_elem);
				}
			};

			class const_reverse_iterator
			{
				const_pointer p_elem;

				constexpr const_reverse_iterator() noexcept : p_elem(nullptr) {}

				constexpr const_reverse_iterator(const noinit_t) noexcept {}

				explicit constexpr const_reverse_iterator(const const_pointer p_elem) noexcept : p_elem(p_elem) {}

				constexpr const_reverse_iterator(const const_reverse_iterator& other) noexcept : p_elem(other.p_elem) {}

				constexpr const_reverse_iterator(const_reverse_iterator&& other) noexcept : p_elem(other.p_elem)
				{
					other.p_elem = nullptr;
				}

				WOJ_CONSTEXPR20 ~const_reverse_iterator() noexcept = default;

				constexpr const_reverse_iterator& operator=(const const_reverse_iterator& other) noexcept = default;

				constexpr const_reverse_iterator& operator=(const_reverse_iterator&& other) noexcept
				{
					p_elem = other.p_elem;
					other.p_elem = nullptr;
					return *this;
				}

				constexpr reference operator*() const noexcept
				{
					return *p_elem;
				}

				constexpr pointer operator->() const noexcept
				{
					return p_elem;
				}

				constexpr const_reverse_iterator& operator++() noexcept
				{
					++p_elem;
					return *this;
				}

				constexpr const_reverse_iterator operator++(int) noexcept
				{
					const_reverse_iterator temp(*this);
					++p_elem;
					return temp;
				}

				constexpr const_reverse_iterator& operator--() noexcept
				{
					--p_elem;
					return *this;
				}

				constexpr const_reverse_iterator operator--(int) noexcept
				{
					const_reverse_iterator temp(*this);
					--p_elem;
					return temp;
				}

				constexpr const_reverse_iterator& operator+=(const difference_type value) noexcept
				{
					p_elem += value;
					return *this;
				}

				constexpr const_reverse_iterator operator+(const difference_type value) const noexcept
				{
					const_reverse_iterator temp(*this);
					temp += value;
					return *this;
				}

				constexpr const_reverse_iterator& operator-=(const difference_type value) noexcept
				{
					p_elem -= value;
					return *this;
				}

				constexpr const_reverse_iterator operator-(const difference_type value) const noexcept
				{
					const_reverse_iterator temp(*this);
					temp += value;
					return *this;
				}

				constexpr const_reverse_iterator& operator-(const const_reverse_iterator other) const noexcept
				{
					return p_elem - other.p_elem;
				}

				constexpr const const_reverse_iterator& as_const() const noexcept
				{
					return *this;
				}
			};

			alignas(Elem) Elem m_data[MemSize];

			/**
			 * Output stream operator (outputs str_size() characters)
			 * @tparam IStrElem Type of the output stream's elements
			 * @tparam IStrTraits Type of the output stream's traits
			 * @param ostr Output stream to output to
			 * @param str String to output from
			 * @return Output stream reference
			 */
			template <typename IStrElem, typename IStrTraits = std::char_traits<IStrElem>>
			constexpr friend std::ostream& operator<<(std::basic_ostream<IStrElem, IStrTraits>& ostr, const string& str)
			{
				using ostr_type = std::basic_ostream<IStrElem, IStrTraits>;
				typename ostr_type::iostate state{ ostr_type::goodbit };

				std::string s;
				std::cout << s;

				if (typename ostr_type::sentry{ ostr }) WOJ_LIKELY
				{
					size_type pad = (ostr.width() <= 0) ? 0 : static_cast<size_type>(ostr.width());
					ostr.rdbuf()->sputn(str.c_str(), str.str_size());
				}
				else
					state |= ostr_type::badbit;

				return ostr;
			}

			/**
			 * Input stream operator (inputs MemSize/width characters)
			 * @tparam IStrElem Type of the input stream's elements
			 * @tparam IStrTraits Type of the input stream's traits
			 * @param istr Input stream to input from
			 * @param str String to input to
			 * @return Input stream reference
			 */
			template <typename IStrElem, typename IStrTraits = std::char_traits<IStrElem>>
			constexpr friend std::istream& operator>>(std::basic_istream<IStrElem, IStrTraits>& istr, string& str)
			{
				using istr_type = std::basic_istream<IStrElem, IStrTraits>;
				using ctype = std::ctype<IStrElem>;
				typename istr_type::iostate state{ istr_type::goodbit };
				
				if (typename istr_type::sentry{ istr }) WOJ_LIKELY
				{
					const ctype& ctype_facet = std::use_facet<ctype>(istr.getloc());

					typename IStrTraits::int_type chr = istr.rdbuf()->sgetc();
					bool changed{ false };

					size_type i = 0;

					for (; i < (istr.width() > 0 ? (std::min)(str.max_size(), istr.width()) : str.max_size()); ++i, chr = istr.rdbuf()->snextc()) WOJ_LIKELY
					{
						if (IStrTraits::eq_int_type(chr, IStrTraits::eof())) WOJ_UNLIKELY
						{
							state |= istr_type::eofbit;
							break;
						}
						if (ctype_facet.is(ctype::space, IStrTraits::to_char_type(chr))) WOJ_UNLIKELY
						{
							break;
						}
						str[i] = IStrTraits::to_char_type(chr);

						if (!changed) WOJ_UNLIKELY
						{
							changed = true;
						}
					}

					str[i] = 0;

					if (!changed) WOJ_UNLIKELY
						state |= istr_type::failbit;
				}
				else WOJ_UNLIKELY
					state |= istr_type::failbit;

				istr.setstate(state);

				return istr;
			}

			// ----- Constructors -----

			/**
			 * Default constructor (empty string)
			 */
			constexpr string() = default;

			// ----- Copy constructors from buffers -----

			/**
			 * Copy constructor from array buffer
			 * @tparam OtherMemSize MemSize of the buffer to copy from
			 * @param other Buffer to copy from
			 */
			template <size_type OtherMemSize>
			constexpr string(const Elem(&other)[OtherMemSize]) noexcept
			{
				copy(other);
			}

			/**
			 * Copy constructor from array buffer with count of characters
			 * @tparam OtherMemSize MemSize of the buffer to copy from
			 * @param other Buffer to copy from
			 * @param count Count of characters to copy
			 */
			template <size_type OtherMemSize>
			constexpr string(const Elem(&other)[OtherMemSize], const size_type count) noexcept
			{
				copy(other, count);
			}

#if defined(WOJ_HAS_CXX20)
			/**
			 * Copy constructor from pointer buffer until null terminator is found or maximum size is reached (MemSize)
			 * @tparam ElemPtr Type of the pointer buffer (Default: const Elem* const)
			 * @param other Buffer to copy from
			 */
			template <typename ElemPtr = const Elem* const>
				requires std::is_pointer<ElemPtr>::value &&
						 std::is_same<typename std::remove_const<typename std::remove_pointer<typename std::remove_const<ElemPtr>::type>::type>::type, Elem>::value &&
						 (!std::is_array<ElemPtr>::value)
#else
			/**
			 * Copy constructor from pointer buffer
			 * @tparam ElemPtr Type of the pointer buffer (Default: const Elem* const)
			 * @param other Buffer to copy from
			 */
			template <typename ElemPtr = const Elem* const, typename = std::enable_if_t<
				std::is_pointer<ElemPtr>::value &&
				std::is_same<typename std::remove_const<typename std::remove_pointer<typename std::remove_const<ElemPtr>::type>::type>::type, Elem>::value &&
				!std::is_array<ElemPtr>::value>>
#endif
				explicit constexpr string(ElemPtr other) noexcept : m_data{}
			{
				copy(other);
			}

#if defined(WOJ_HAS_CXX20)
			/**
			 * Copy constructor from pointer buffer with count of characters
			 * @tparam ElemPtr Type of the pointer buffer (Default: const Elem* const)
			 * @param other Buffer to copy from
			 * @param count Count of characters to copy
			 */
			template <typename ElemPtr = const Elem* const>
			requires std::is_pointer<ElemPtr>::value &&
					 std::is_same<typename std::remove_const<typename std::remove_pointer<typename std::remove_const<ElemPtr>::type>::type>::type, Elem>::value &&
					 (!std::is_array<ElemPtr>::value)
#else
			/**
			 * Copy constructor from pointer buffer with count of characters
			 * @tparam ElemPtr Type of the pointer buffer (Default: const Elem* const)
			 * @param other Buffer to copy from
			 * @param count Count of characters to copy
			 */
			template <typename ElemPtr = const Elem* const, typename = std::enable_if_t<
				std::is_pointer<ElemPtr>::value &&
				std::is_same<typename std::remove_const<typename std::remove_pointer<typename std::remove_const<ElemPtr>::type>::type>::type, Elem>::value &&
				!std::is_array<ElemPtr>::value>>
#endif
			constexpr string(ElemPtr other, const size_type count) noexcept : m_data{}
			{
				copy(other, count);
			}


			/**
			 * Copy constructor from another string
			 * @param other String to copy from
			 */
			template <char_type OtherElem, size_type OtherMemSize>
			constexpr string(const string<OtherElem, OtherMemSize>& other) noexcept : m_data{}
			{
				copy(other);
			}

			/**
			 * Copy constructor from another string
			 * @tparam OtherElem Type of the other string's elements
			 * @tparam OtherMemSize MemSize of the other string
			 * @param other String to copy from
			 * @param count Count of characters to copy
			 */
			template <char_type OtherElem, size_type OtherMemSize>
#endif
			constexpr string(const string<OtherElem, OtherMemSize>& other, const size_type count) noexcept : m_data{}
			{
				copy(other, count);
			}

			/**
			 * Move constructor is deleted
			 */
			constexpr string(string&&) = delete;

			/**
			 * Destructs the string
			 */
			WOJ_CONSTEXPR20 ~string() = default;

			// ----- Assignment operators -----

			/**
			 * Assign from array buffer operator
			 * @tparam OtherMemSize Size of the buffer to copy from
			 * @param other Buffer to copy from
			 * @return Reference to self
			 */
			template <size_type OtherMemSize>
			constexpr string& operator=(const Elem (&other)[OtherMemSize]) noexcept
			{
				return copy(other);
			}

#if defined(WOJ_HAS_CXX20)
			/**
			 * Assign from pointer buffer operator
			 * @tparam ElemPtr Type of the pointer buffer to copy from (Default: const Elem* const)
			 * @param other Buffer to copy from
			 * @return Reference to self
			 */
		template <typename ElemPtr = const Elem* const>
		requires std::is_pointer<ElemPtr>::value &&
				 std::is_same<std::remove_const_t<std::remove_pointer_t<std::remove_const_t<std::remove_pointer_t<ElemPtr>>>>, Elem>::value &&
				 (!std::is_array<ElemPtr>::value)
#else
			/**
			 * Assign from pointer buffer operator
			 * @tparam ElemPtr Type of the pointer buffer to copy from (Default: const Elem* const)
			 * @param other Buffer to copy from
			 * @return Reference to self
			 */
			template <typename ElemPtr = const Elem* const, typename = std::enable_if_t<
				std::is_pointer<ElemPtr>::value &&
				std::is_same<std::remove_const_t<std::remove_pointer_t<std::remove_const_t<std::remove_pointer_t<ElemPtr>>>>, Elem>::value &&
				!std::is_array<ElemPtr>::value>>
#endif
				constexpr string& operator=(ElemPtr other) noexcept
			{
				return copy(other);
			}

			/**
			 * Assign from another string operator
			 * @param other String to copy from
			 * @return Reference to self
			 */
			constexpr string& operator=(const string& other) noexcept
			{
				return copy(other);
			}


#if defined(WOJ_HAS_CXX20)
			/**
			 * Assign from another string of different params operator
			 * @tparam OtherElem Type of the other string's elements
			 * @tparam OtherMemSize MemSize of the other string
			 * @param other String to copy from
			 * @return Reference to self
			 */
			template <char_type OtherElem, size_type OtherMemSize> requires (OtherMemSize != MemSize)
#else
			/**
			 * Assign from another string of different params operator
			 * @tparam OtherElem Type of the other string's elements
			 * @tparam OtherMemSize MemSize of the other string
			 * @param other String to copy from
			 * @return Reference to self
			 */
			template <typename OtherElem, size_type OtherMemSize, typename = std::enable_if_t<OtherMemSize != MemSize>>
#endif
			constexpr string& operator=(const string<OtherElem, OtherMemSize>& other) noexcept
			{
				return copy(other);
			}

			/**
			 * Assign from move operator is deleted, use copy constructor instead
			 */
			constexpr string& operator=(string&&) = delete;

			/**
			 * Index operator (unchecked & UB if index >= MemSize)
			 * @param index Index of the element to access
			 * @return Reference to the element at the index
			 */
			WOJ_NODISCARD constexpr Elem& operator[](const size_type index) noexcept
			{
				return at(index);
			}

			/**
			 * Const index operator (unchecked & UB if index >= MemSize)
			 * @param index Index of the element to access
			 * @return Const reference to the element at the index
			 */
			WOJ_NODISCARD constexpr const Elem& operator[](const size_type index) const noexcept
			{
				return at(index);
			}

			// ----- Iteration functions -----

			/**
			 * Begin reverse_iterator
			 * @return Iterator to the beginning of the string
			 */
			WOJ_NODISCARD constexpr reverse_iterator begin() noexcept
			{
				return m_data;
			}

			/**
			 * Const begin reverse_iterator
			 * @return Const reverse_iterator to the beginning of the string
			 */
			WOJ_NODISCARD constexpr const_reverse_iterator begin() const noexcept
			{
				return m_data;
			}

			/**
			 * Const begin reverse_iterator
			 * @return Const reverse_iterator to the beginning of the string
			 */
			WOJ_NODISCARD constexpr const_reverse_iterator cbegin() const noexcept
			{
				return begin();
			}

			/**
			 * End reverse_iterator
			 * @return Iterator to the end of the string (after the null terminator)
			 */
			WOJ_NODISCARD constexpr reverse_iterator end() noexcept
			{
				return m_data + MemSize;
			}

			WOJ_NODISCARD constexpr const_reverse_iterator end() const noexcept
			{
				return m_data + MemSize;
			}

			WOJ_NODISCARD constexpr const_reverse_iterator cend() const noexcept
			{
				return end();
			}

			WOJ_NODISCARD constexpr reverse_reverse_iterator rbegin() noexcept
			{
				return m_data + MemSize - 1;
			}

			WOJ_NODISCARD constexpr const_reverse_reverse_iterator rbegin() const noexcept
			{
				return m_data + MemSize - 1;
			}

			WOJ_NODISCARD constexpr const_reverse_reverse_iterator crbegin() const noexcept
			{
				return rbegin();
			}

			WOJ_NODISCARD constexpr reverse_reverse_iterator rend() noexcept
			{
				return m_data - 1;
			}

			WOJ_NODISCARD constexpr const_reverse_reverse_iterator rend() const noexcept
			{
				return m_data - 1;
			}

			WOJ_NODISCARD constexpr const_reverse_reverse_iterator crend() const noexcept
			{
				return rend();
			}

			// ----- Copy functions from buffers -----

			/**
			 * Copy from array buffer
			 * @tparam BufferOverlaps Whether the buffer overlaps with internal buffer
			 * @tparam OtherMemSize Size of the buffer to copy from
			 * @param other Buffer to copy from
			 * @return Reference to self
			 */
			template <bool BufferOverlaps = false, size_type OtherMemSize>
			constexpr string& copy(const Elem(&other)[OtherMemSize]) noexcept
			{
				WOJ_ASSERT_ASSUME(other != nullptr);

				if (is_constant_evaluated())
				{
					constexpr bool buffer_smaller = OtherMemSize < MemSize;
					constexpr size_type size = (buffer_smaller ? OtherMemSize : MemSize) * sizeof(Elem);


					for (size_type i = 0; i < size; ++i)
					{
						m_data[i] = other[i];
					}

					if constexpr  (buffer_smaller)
					{
						m_data[OtherMemSize] = 0;
					}
				}
				else
				{
					constexpr bool buffer_smaller = OtherMemSize < MemSize;
					constexpr size_type byte_size = (buffer_smaller ? OtherMemSize : MemSize) * sizeof(Elem);


					if constexpr  (BufferOverlaps)
					{
						std::memmove(m_data, other, byte_size);
					}
					else
					{
						std::memcpy(m_data, other, byte_size);
					}


					if constexpr  (buffer_smaller)
					{
						m_data[OtherMemSize] = 0;
					}
				}

				return *this;
			}

			/**
			 * Copy from array buffer
			 * @tparam OtherMemSize Size of the buffer to copy from
			 * @param other Buffer to copy from
			 * @param buffer_overlaps Whether the buffer overlaps with internal buffer
			 * @return Reference to self
			 */
			template <size_type OtherMemSize>
			constexpr string& copy(const Elem(&other)[OtherMemSize], const bool buffer_overlaps) noexcept
			{
				WOJ_ASSERT_ASSUME(other != nullptr);

				if (is_constant_evaluated())
				{
					constexpr bool buffer_smaller = OtherMemSize < MemSize;
					constexpr size_type size = (buffer_smaller ? OtherMemSize : MemSize) * sizeof(Elem);


					for (size_type i = 0; i < size; ++i)
					{
						m_data[i] = other[i];
					}

					if constexpr  (buffer_smaller)
					{
						m_data[OtherMemSize] = 0;
					}
				}
				else
				{
					constexpr bool buffer_smaller = OtherMemSize < MemSize;
					constexpr size_type byte_size = (buffer_smaller ? OtherMemSize : MemSize) * sizeof(Elem);


					if (buffer_overlaps) WOJ_LIKELY
					{
						std::memmove(m_data, other, byte_size);
					}
					else WOJ_UNLIKELY
					{
						std::memcpy(m_data, other, byte_size);
					}


					if constexpr  (buffer_smaller)
					{
						m_data[OtherMemSize] = 0;
					}
				}

				return *this;
			}

			/**
			 * Copy from array buffer with count of characters
			 * @tparam BufferOverlaps Whether the buffer overlaps with internal buffer
			 * @tparam OtherMemSize Size of the buffer to copy from
			 * Copy from array m_data with count of characters
			 * @tparam BufferOverlaps Whether the m_data overlaps with the string's m_data
			 * @tparam Count Count of characters to copy
			 * @tparam OtherMemSize Size of the m_data to copy from
			 * @param other Buffer to copy from
			 * @param count Count of characters to copy
			 * @return Reference to self
			 */
			template <bool BufferOverlaps, size_type Count, size_type OtherMemSize>
			constexpr string& copy(const Elem(&other)[OtherMemSize]) noexcept
			{
				WOJ_ASSERT_ASSUME(other != nullptr);

				if (is_constant_evaluated())
				{
					constexpr bool buffer_smaller = Count < MemSize;
					constexpr size_type size = (buffer_smaller ? Count : MemSize) * sizeof(Elem);

					
					for (size_type i = 0; i < size; ++i)
					{
						m_data[i] = other[i];
					}

					if constexpr  (buffer_smaller)
					{
						m_data[Count] = 0;
					}
				}
				else
				{
					constexpr bool buffer_smaller = Count < MemSize;
					constexpr size_type byte_size = (buffer_smaller ? Count : MemSize) * sizeof(Elem);


					if constexpr  (BufferOverlaps)
					{
						std::memmove(m_data, other, byte_size);
					}
					else WOJ_UNLIKELY
					{
						std::memcpy(m_data, other, byte_size);
					}


					if constexpr  (buffer_smaller)
					{
						m_data[Count] = 0;
					}
				}

				return *this;
			}

			/**
			 * Copy from array m_data with count of characters
			 * @tparam OtherMemSize Size of the m_data to copy from
			 * @param other Buffer to copy from
			 * @param count Count of characters to copy
			 * @return Reference to self
			 */
			template <size_type OtherMemSize>
			WOJ_CONSTEXPR20 string& copy(const Elem(&other)[OtherMemSize], const size_type count) noexcept
			{
				WOJ_ASSERT_ASSUME(other != nullptr);
				//[[assume(other != nullptr)]]

				if (is_constant_evaluated())
				{
					constexpr bool buffer_smaller = OtherMemSize < MemSize;
					constexpr size_type size = (buffer_smaller ? OtherMemSize : MemSize) * sizeof(Elem);


					for (size_type i = 0; i < size; ++i)
					{
						m_data[i] = other[i];
					}

					if constexpr (buffer_smaller)
					{
						m_data[OtherMemSize] = 0;
					}
				}
				else
				{
					if (count < MemSize) WOJ_LIKELY
					{
						const size_type byte_size = count * sizeof(Elem);
						std::memcpy(m_data, other, byte_size);

						m_data[count - 1] = 0;
					}
					else WOJ_UNLIKELY
					{
						constexpr size_type byte_size = MemSize * sizeof(Elem);
						std::memcpy(m_data, other, byte_size);
					}
				}

				return *this;
			}

			/**
			 * Copy from array m_data with count of characters
			 * @tparam OtherMemSize Size of the m_data to copy from
			 * @param other Buffer to copy from
			 * @param buffer_overlaps Whether the m_data overlaps with the string's m_data
			 * @param count Count of characters to copy
			 * @param buffer_overlaps Whether the buffer overlaps with internal buffer
			 * @return Reference to self
			 */
			template <size_type OtherMemSize>
			WOJ_CONSTEXPR20 string& copy(const Elem(&other)[OtherMemSize], const bool buffer_overlaps, const size_type count) noexcept
			{
				WOJ_ASSERT_ASSUME(other != nullptr);

				if (is_constant_evaluated())
				{
					const bool buffer_smaller = count < MemSize;
					const size_type size = (buffer_smaller ? count : MemSize) * sizeof(Elem);


					for (size_type i = 0; i < size; ++i)
					{
						m_data[i] = other[i];
					}

					if (buffer_smaller)
					{
						m_data[count] = 0;
					}
				}
				else
				{
					if (count < MemSize) WOJ_LIKELY
					{
						const size_type byte_size = count * sizeof(Elem);
						if constexpr  (buffer_overlaps)
						{
							std::memmove(m_data, other, byte_size);
						}
						else
						{
							std::memcpy(m_data, other, byte_size);
						}

						m_data[count - 1] = 0;
					}
					else WOJ_UNLIKELY
					{
						constexpr size_type byte_size = MemSize * sizeof(Elem);
						if constexpr  (buffer_overlaps)
						{
							std::memmove(m_data, other, byte_size);
						}
						else
						{
							std::memcpy(m_data, other, byte_size);
						}	
					}
				}

				return *this;
			}

#if defined(WOJ_HAS_CXX20)
			/**
			 * Copy from pointer buffer until null terminator is found or maximum size is reached (MemSize)
			 * @tparam BufferOverlaps Whether the buffer overlaps with internal buffer
			 * @tparam ElemPtr Type of the pointer buffer (Default: const Elem* const)
			 * Copy from pointer m_data until null terminator is found or maximum size is reached (MemSize)
			 * @tparam BufferOverlaps Whether the m_data overlaps with the string's m_data (unused, kept for compatibility)
			 * @tparam ElemPtr Type of the pointer m_data (Default: const Elem* const)
			 * @param other Buffer to copy from
			 * @return Reference to self
			 */
			template <bool BufferOverlaps, typename ElemPtr = const Elem* const>
				requires std::is_pointer<ElemPtr>::value &&
						 std::is_same<typename std::remove_const<typename std::remove_pointer<typename std::remove_const<ElemPtr>::type>::type>::type, Elem>::value &&
						 (!std::is_array<ElemPtr>::value)
#else
			/**
			 * Copy from pointer buffer until null terminator is found or maximum size is reached (MemSize)
			 * @tparam BufferOverlaps Whether the buffer overlaps with internal buffer
			 * @tparam ElemPtr Type of the pointer buffer (Default: const Elem* const)
			 * @param other Buffer to copy from
			 * @return Reference to self
			 */
			template <bool BufferOverlaps = false, typename ElemPtr = const Elem* const, typename = std::enable_if_t<
			/**
			 * Copy from pointer m_data until null terminator is found or maximum size is reached (MemSize)
			 * @tparam BufferOverlaps Whether the m_data overlaps with the string's m_data (unused, kept for compatibility)
			 * @tparam ElemPtr Type of the pointer m_data (Default: const Elem* const)
			 * @param other Buffer to copy from
			 * @return Reference to self
			 */
			template <bool BufferOverlaps, typename ElemPtr = const Elem* const, typename = std::enable_if_t<
				std::is_pointer<ElemPtr>::value &&
				std::is_same<typename std::remove_const<typename std::remove_pointer<typename std::remove_const<ElemPtr>::type>::type>::type, Elem>::value &&
				(!std::is_array<ElemPtr>::value), void>>
#endif
				constexpr string& copy(ElemPtr other) noexcept
			{
				WOJ_ASSERT_ASSUME(other != nullptr);

				size_type i = 0;

				while (i < MemSize - 1 && !(m_data[i] = other[i++])) WOJ_LIKELY {}

				if (i < MemSize - 1) WOJ_LIKELY
				{
					m_data[i] = 0;
				}

				return *this;
			}

#if defined(WOJ_HAS_CXX20)
			/**
			 * Copy from pointer m_data until null terminator is found or maximum size is reached (MemSize)
			 * @tparam ElemPtr Type of the pointer m_data (Default: const Elem* const)
			 * @param other Buffer to copy from
			 * @param buffer_overlaps Whether the m_data overlaps with the string's m_data
			 * @return Reference to self
			 */
			template <typename ElemPtr = const Elem* const>
				requires std::is_pointer<ElemPtr>::value &&
			std::is_same<typename std::remove_const<typename std::remove_pointer<typename std::remove_const<ElemPtr>::type>::type>::type, Elem>::value &&
				(!std::is_array<ElemPtr>::value)
#else
			/**
			 * Copy from pointer m_data until null terminator is found or maximum size is reached (MemSize)
			 * @tparam ElemPtr Type of the pointer m_data (Default: const Elem* const)
			 * @param other Buffer to copy from
			 * @param buffer_overlaps Whether the m_data overlaps with the string's m_data
			 * @return Reference to self
			 */
			template < typename ElemPtr = const Elem* const, typename = std::enable_if_t<
				std::is_pointer<ElemPtr>::value&&
				std::is_same<typename std::remove_const<typename std::remove_pointer<typename std::remove_const<ElemPtr>::type>::type>::type, Elem>::value &&
				(!std::is_array<ElemPtr>::value)>>
#endif
				constexpr string& copy(ElemPtr other, const bool buffer_overlaps) noexcept
			{
				WOJ_ASSERT_ASSUME(other != nullptr);

				size_type i = 0;

				while (i < MemSize - 1 && !(m_data[i] = other[i++])) WOJ_LIKELY;

				if (i < MemSize - 1) WOJ_LIKELY
				{
					m_data[i] = 0;
				}

				return *this;
			}

#if defined(WOJ_HAS_CXX20)
			/**
			 * Copy from pointer m_data count of characters
			 * @tparam Count Count of characters to copy
			 * @tparam ElemPtr Type of the pointer m_data (Default: const Elem* const)
			 * @param other Buffer to copy from
			 * @return Reference to self
			 */
			template <size_type Count, typename ElemPtr = const Elem* const>
				requires std::is_pointer<ElemPtr>::value&&
			std::is_same<typename std::remove_const<typename std::remove_pointer<typename std::remove_const<ElemPtr>::type>::type>::type, Elem>::value &&
				(!std::is_array<ElemPtr>::value)
#else
			/**
			 * Copy from pointer m_data count of characters
			 * @tparam Count Count of characters to copy
			 * @tparam ElemPtr Type of the pointer m_data (Default: const Elem* const)
			 * @param other Buffer to copy from
			 * @return Reference to self
			 */
			template <size_type Count, typename ElemPtr, typename = std::enable_if_t<
				std::is_pointer<ElemPtr>::value&&
				std::is_same<typename std::remove_const<typename std::remove_pointer<typename std::remove_const<ElemPtr>::type>::type>::type, Elem>::value &&
				(!std::is_array<ElemPtr>::value)>>
#endif
				constexpr string& copy(ElemPtr other) noexcept
			{
				WOJ_ASSERT_ASSUME(other != nullptr);

				if (is_constant_evaluated())
				{
					constexpr bool buffer_smaller = Count < MemSize;
					constexpr size_type size = (buffer_smaller ? Count : MemSize) * sizeof(Elem);


					for (size_type i = 0; i < size; ++i)
					{
						m_data[i] = other[i];
					}

					if constexpr  (buffer_smaller)
					{
						m_data[Count] = 0;
					}
				}
				else
				{
					if constexpr (Count < MemSize)
					{
						constexpr size_type byte_size = Count * sizeof(Elem);
						std::memcpy(m_data, other, byte_size);

						m_data[Count] = 0;
					}
					else
					{
						constexpr size_type byte_size = MemSize * sizeof(Elem);
						std::memcpy(m_data, other, byte_size);
					}
				}

				return *this;
			}

#if defined(WOJ_HAS_CXX20)
			/**
			 * Copy from pointer buffer count of characters
			 * @tparam BufferOverlaps Whether the buffer overlaps with internal buffer
			 * @tparam ElemPtr Type of the pointer buffer (Default: const Elem* const)
			 * Copy from pointer m_data count of characters
			 * @tparam ElemPtr Type of the pointer m_data (Default: const Elem* const)
			 * @param other Buffer to copy from
			 * @param count MemSize of the m_data to copy from
			 * @return Reference to self
			 */
			template <bool BufferOverlaps = false, typename ElemPtr = const Elem* const>
				requires std::is_pointer<ElemPtr>::value &&
						 std::is_same<typename std::remove_const<typename std::remove_pointer<typename std::remove_const<ElemPtr>::type>::type>::type, Elem>::value &&
						 (!std::is_array<ElemPtr>::value)
#else
			/**
			 * Copy from pointer buffer count of characters
			 * @tparam BufferOverlaps Whether the buffer overlaps with internal buffer
			 * @tparam ElemPtr Type of the pointer buffer (Default: const Elem* const)
			 * @param other Buffer to copy from
			 * @param count MemSize of the buffer to copy from
			 * @return Reference to self
			 */
			template <bool BufferOverlaps = false,<typename ElemPtr = const Elem* const, typename = std::enable_if_t<
				std::is_pointer<ElemPtr>::value&&
				std::is_same<typename std::remove_const<typename std::remove_pointer<typename std::remove_const<ElemPtr>::type>::type>::type, Elem>::value &&
				(!std::is_array<ElemPtr>::value)>>
#endif
				constexpr string& copy(ElemPtr other, const size_type count) noexcept
			{
				WOJ_ASSERT_ASSUME(other != nullptr);

				if (is_constant_evaluated())
				{
					if (count < MemSize) WOJ_LIKELY
					{
						for (size_type i = 0; i < count; ++i) WOJ_LIKELY
						{
							m_data[i] = other[i];
						}

						m_data[count - 1] = 0;
					}
					else WOJ_UNLIKELY
					{
						for (size_type i = 0; i < MemSize; ++i) WOJ_LIKELY
						{
							m_data[i] = other[i];
						}
					}
				}
				else
				{
					if (count < MemSize) WOJ_LIKELY
					{
						if constexpr  (BufferOverlaps)
						{
							std::memmove(m_data, other, count * sizeof(Elem));
						}
						else
						{
							std::memcpy(m_data, other, count * sizeof(Elem));
						}

						m_data[count] = 0;
					}
					else WOJ_UNLIKELY
					{
						if constexpr  (BufferOverlaps)
						{
							std::memmove(m_data, other, MemSize * sizeof(Elem));
						}
						else
						{
							std::memcpy(m_data, other, MemSize * sizeof(Elem));
						}
					}
				}

				return *this;
			}

#if defined(WOJ_HAS_CXX20)
			/**
			 * Copy from pointer m_data count of characters
			 * @tparam BufferOverlaps Whether the m_data overlaps with the string's m_data
			 * @tparam Count Count of characters to copy
			 * @tparam BufferOverlaps Whether the buffer overlaps with internal buffer
			 * @tparam ElemPtr Type of the pointer buffer (Default: const Elem* const)
			 * @tparam ElemPtr Type of the pointer m_data (Default: const Elem* const)
			 * @param other Buffer to copy from
			 * @return Reference to self
			 */
			template <bool BufferOverlaps, size_type Count, typename ElemPtr = const Elem* const>
				requires std::is_pointer<ElemPtr>::value &&
						 std::is_same<typename std::remove_const<typename std::remove_pointer<typename std::remove_const<ElemPtr>::type>::type>::type, Elem>::value &&
						 (!std::is_array<ElemPtr>::value)
#else
			/**
			 * Copy from pointer buffer count of characters
			 * @tparam Count Count of characters to copy
			 * @tparam BufferOverlaps Whether the buffer overlaps with internal buffer
			 * @tparam ElemPtr Type of the pointer buffer (Default: const Elem* const)
			 * @param other Buffer to copy from
			 * @return Reference to self
			 */
			template <size_type Count, bool BufferOverlaps = false, typename ElemPtr = const Elem* const, typename = std::enable_if_t<
			/**
			 * Copy from pointer m_data count of characters
			 * @tparam BufferOverlaps Whether the m_data overlaps with the string's m_data
			 * @tparam Count Count of characters to copy
			 * @tparam ElemPtr Type of the pointer m_data (Default: const Elem* const)
			 * @param other Buffer to copy from
			 * @return Reference to self
			 */
			template <size_type Count, typename ElemPtr, typename = std::enable_if_t<
				std::is_pointer<ElemPtr>::value &&
				std::is_same<typename std::remove_const<typename std::remove_pointer<typename std::remove_const<ElemPtr>::type>::type>::type, Elem>::value &&
				(!std::is_array<ElemPtr>::value)>>
#endif
				constexpr string& copy(ElemPtr other) noexcept
			{
				WOJ_ASSERT_ASSUME(other != nullptr);

				if (is_constant_evaluated())
				{
					constexpr bool buffer_smaller = Count < MemSize;
					constexpr size_type size = (buffer_smaller ? Count : MemSize) * sizeof(Elem);


					for (size_type i = 0; i < size; ++i)
					{
						m_data[i] = other[i];
					}

					if constexpr (buffer_smaller)
					{
						m_data[Count] = 0;
					}
				}
				else
				{
					constexpr bool buffer_smaller = Count < MemSize;
					constexpr size_type byte_size = (buffer_smaller ? Count : MemSize) * sizeof(Elem);


					if constexpr (BufferOverlaps)
					{
						std::memmove(m_data, other, byte_size);
					}
					else
					{
						std::memcpy(m_data, other, byte_size);
					}


					if constexpr (buffer_smaller)
					{
						m_data[Count] = 0;
					}
				}
				return *this;
			}

#if defined(WOJ_HAS_CXX20)
			/**
			 * Copy from pointer m_data count of characters
			 * @tparam ElemPtr Type of the pointer m_data (Default: const Elem* const)
			 * @param other Buffer to copy from
			 * @param buffer_overlaps Whether the m_data overlaps with the string's m_data
			 * @param count Count of characters to copy
			 * @return Reference to self
			 */
			template <typename ElemPtr = const Elem* const>
				requires std::is_pointer<ElemPtr>::value&&
			std::is_same<typename std::remove_const<typename std::remove_pointer<typename std::remove_const<ElemPtr>::type>::type>::type, Elem>::value &&
				(!std::is_array<ElemPtr>::value)
#else
			/**
			 * Copy from pointer m_data count of characters
			 * @tparam ElemPtr Type of the pointer m_data (Default: const Elem* const)
			 * @param other Buffer to copy from
			 * @param buffer_overlaps Whether the m_data overlaps with the string's m_data
			 * @param count Count of characters to copy
			 * @return Reference to self
			 */
			template <size_type Count, typename ElemPtr, typename = std::enable_if_t<
				std::is_pointer<ElemPtr>::value&&
				std::is_same<typename std::remove_const<typename std::remove_pointer<typename std::remove_const<ElemPtr>::type>::type>::type, Elem>::value &&
				(!std::is_array<ElemPtr>::value)>>
#endif
				constexpr string& copy(ElemPtr other, const bool buffer_overlaps, const size_type count) noexcept
			{
				WOJ_ASSERT_ASSUME(other != nullptr);

				if (is_constant_evaluated())
				{
					const bool buffer_smaller = count < MemSize;
					const size_type size = (buffer_smaller ? count : MemSize) * sizeof(Elem);


					for (size_type i = 0; i < size; ++i)
					{
						m_data[i] = other[i];
					}

					if constexpr (buffer_smaller)
					{
						m_data[count] = 0;
					}
				}
				else
				{
					if (count < MemSize) WOJ_LIKELY
					{
						const size_type byte_size = count * sizeof(Elem);
						if constexpr (buffer_overlaps)
						{
							std::memmove(m_data, other, byte_size);
						}
						else
						{
							std::memcpy(m_data, other, byte_size);
						}

						m_data[count - 1] = 0;
					}
					else WOJ_UNLIKELY
					{
						constexpr size_type byte_size = MemSize * sizeof(Elem);
						if constexpr (buffer_overlaps)
						{
							std::memmove(m_data, other, byte_size);
						}
						else
						{
							std::memcpy(m_data, other, byte_size);
						}
					}
				}

				return *this;
			}

#if defined(WOJ_HAS_CXX20)
			template <char_type OtherElem, size_type OtherMemSize>
#else
			template <typename OtherElem, size_type OtherMemSize>
#endif
			constexpr string& copy(const string<OtherElem, OtherMemSize>& other)
			{
				WOJ_ASSERT_ASSUME(this != &other);

				copy(other.data());

				return *this;
			}

#if defined(WOJ_HAS_CXX20)
			template <char_type OtherElem, size_type OtherMemSize>
#else
			template <typename OtherElem, size_type OtherMemSize>
#endif
			constexpr string& copy(const string<OtherElem, OtherMemSize>& other, const size_type count)
			{
				WOJ_ASSERT_ASSUME(this != &other);

				copy(other.data(), count);

				return *this;
			}

			/**
			 * Access the element at the index (unchecked)
			 * @param index Index of the element to access
			 * @return Reference to the element at the index
			 */
			WOJ_NODISCARD constexpr Elem& at(const size_type index) noexcept
			{
				WOJ_ASSERT_ASSUME(index < MemSize);

				return m_data[index];
			}

			/**
			 * Returns a const reference to the element at the index (unchecked)
			 * @param index Index of the element to access
			 * @return Const reference to the element at the index
			 */
			WOJ_NODISCARD constexpr const Elem& at(const size_type index) const noexcept
			{
				WOJ_ASSERT_ASSUME(index < MemSize);

				return m_data[index];
			}

			/**
			 * Fill the string with a value
			 * @param val Value to fill the string with
			 * @return Reference to self
			 */
			constexpr string& fill(const Elem val) noexcept
			{
				if (is_constant_evaluated())
				{
					for (size_type i = 0; i < MemSize; ++i)
					{
						m_data[i] = val;
					}
					return *this;
				}
				if constexpr  (std::is_same<Elem, char>::value)
				{
					std::memset(m_data, val, MemSize);
				}
				else if constexpr  (std::is_same<Elem, wchar_t>::value)
				{
					std::wmemset(m_data, val, MemSize);
				}
				else
				{
					std::fill(m_data, m_data + MemSize, val);
				}

				return *this;
			}

			/**
			 * Swaps two elements in the string
			 * @param index1 Index of the first element to swap
			 * @param index2 Index of the second element to swap
			 * @return Reference to self
			 */
			constexpr string& swap(const size_type index1, const size_type index2) noexcept
			{
				WOJ_ASSERT_ASSUME(index1 >= 0 && index1 < MemSize);
				WOJ_ASSERT_ASSUME(index2 >= 0 && index2 < MemSize);

				m_data[index1] ^= m_data[index2];
				m_data[index2] ^= m_data[index1];
				m_data[index1] ^= m_data[index2];
				return *this;
			}

			/**
			 * Swaps the contents of two strings
			 * @param other Other string to swap with
			 * @return Reference to self
			 */
			constexpr string& swap(string& other) noexcept
			{
				WOJ_ASSERT_ASSUME(this != &other);

				for (size_type i = 0; i < MemSize; ++i)
				{
					m_data[i] ^= other.m_data[i];
					other.m_data[i] ^= m_data[i];
					m_data[i] ^= other.m_data[i];
				}

				return *this;
			}

			/**
			 * Returns a reference to self as const, useful for const-correctness e.g. when iterating
			 * @return Reference to self as const
			 */
			WOJ_NODISCARD constexpr const string& as_const() const noexcept
			{
				return *this;
			}

			/**
			 * @return Array representing string data
			 */
			WOJ_NODISCARD constexpr Elem(&data() noexcept)[MemSize]
			{
				return m_data;
			}

			/**
			 * @return Const array representing string data
			 */
			WOJ_NODISCARD constexpr const Elem(&data() const noexcept)[MemSize]
			{
				return m_data;
			}

			/**
			 * @return C-String representation of the string (not necessarily null-terminated)
			 */
			WOJ_NODISCARD constexpr const Elem(&c_str() const noexcept)[MemSize]
			{
				return m_data;
			}


			/**
			 * @return Size of the string (until null terminator)
			 */
			WOJ_NODISCARD constexpr size_type str_size() const noexcept
			{
				if constexpr  (!MemSize)
					return 0;

				if constexpr  (MemSize == 1)
					return static_cast<bool>(m_data[0]);

				if (is_constant_evaluated())
				{
					size_type len{ 0 };

					for (; len < mem_size() && m_data[len]; ++len);

					return len;
				}

				if constexpr  (std::is_same<Elem, char>::value)
				{
#if !defined(WOJ_HAS_CXX17) // C++14 fails to recognize type restriction
					return strnlen(reinterpret_cast<const char*>(m_data), MemSize);
#else
					return strnlen(m_data, MemSize);
#endif
				}

				if constexpr  (std::is_same<Elem, wchar_t>::value)
				{
#if !defined(WOJ_HAS_CXX17) // C++14 fails to recognize type restriction
					return wcsnlen(reinterpret_cast<const wchar_t*>(m_data), MemSize);
#else
					return wcsnlen(m_data, MemSize);
#endif
				}

				size_type len{ 0 };

				for (; len < mem_size() && m_data[len]; ++len);

				return len;
			}

			/**
			 * @return Size of the string (until null terminator)
			 */
			WOJ_NODISCARD constexpr size_type size() const noexcept
			{
				return str_size();
			}

			/**
			 * @return Size of the string memory m_data
			 */
			WOJ_NODISCARD static
#if defined(WOJ_HAS_CXX20)
			WOJ_CONSTEVAL20
#else
			constexpr
#endif
			size_type mem_size() noexcept
			{
				return MemSize;
			}

			/**
			 * @return Size of the string memory m_data
			 */
			WOJ_NODISCARD static
#if defined(WOJ_HAS_CXX20)
				WOJ_CONSTEVAL20
#else
				constexpr
#endif
			size_type max_size() noexcept
			{
				return mem_size();
			}
		};

		// ----- Deduction guides -----
#if defined(WOJ_HAS_CXX17)
		template <typename Elem, size_t Size>
		string(const Elem(&)[Size]) -> string<Elem, Size - 1>;

		template <typename Elem, size_t Size>
		string(const Elem(&)[Size], size_t) -> string<Elem, Size - 1>;
#endif
	}
}