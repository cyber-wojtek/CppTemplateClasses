#pragma once

#ifndef WOJ_STRING_HPP
#define WOJ_STRING_HPP
#include <cassert>
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
#if defined(HAS_CXX20)
#include <concepts>
#endif

namespace woj
{
	namespace impl
	{
		template <typename Elem, typename Traits = std::char_traits<Elem>>
		class basic_streambuf_publicized final : public std::basic_streambuf<Elem, Traits>
		{
		public:
			using base_type = std::basic_streambuf<Elem, Traits>;

			// Private
			using base_type::base_type;
			using base_type::operator=;
			using base_type::swap;

			// Public
			using base_type::pubseekoff;
			using base_type::pubseekpos;
			using base_type::pubsetbuf;
			using base_type::pubimbue;
			using base_type::getloc;
			using base_type::in_avail;
			using base_type::pubsync;
			using base_type::sbumpc;
			using base_type::sgetc;
			using base_type::sgetn;
			using base_type::snextc;
			using base_type::sputbackc;
#if !defined(HAS_CXX17)
			using base_type::stossc;
#endif
			using base_type::sungetc;
			using base_type::sputc;
			using base_type::sputn;

			// Protected
			using base_type::eback;
			using base_type::gptr;
			using base_type::pbase;
			using base_type::pptr;
			using base_type::egptr;
			using base_type::gbump;
			using base_type::setg;
			using base_type::epptr;
			using base_type::pbump;
			using base_type::setp;
			using base_type::overflow;
			using base_type::pbackfail;
			using base_type::showmanyc;
			using base_type::underflow;
			using base_type::uflow;
			using base_type::xsgetn;
			using base_type::xsputn;
			using base_type::seekoff;
			using base_type::seekpos;
			using base_type::setbuf;
			using base_type::sync;
			using base_type::imbue;
		};
	}

	#if defined(HAS_CXX20)
	template <typename T>
	concept char_type = std::is_same<T, char>::value || std::is_same<T, char8_t>::value || std::is_same<T, wchar_t>::value || std::is_same<T, char16_t>::value || std::is_same<T, char32_t>::value;
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
#if defined(HAS_CXX20)
		/**
		 * Class representing a stack-allocated string
		 * @tparam Elem Type of the string's elements
		 * @tparam MemSize Size of the string's memory m_data
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
			using const_pointer = Elem*;
			using reference = Elem&;
			using const_reference = const Elem&;

			using iterator = pointer;
			using const_iterator = const_pointer;
			using reverse_iterator = pointer;
			using const_reverse_iterator = const_pointer;

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

				if (typename ostr_type::sentry{ ostr }) LIKELY
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
				
				if (typename istr_type::sentry{ istr }) LIKELY
				{
					const ctype& ctype_facet = std::use_facet<ctype>(istr.getloc());

					typename IStrTraits::int_type chr = istr.rdbuf()->sgetc();
					bool changed{ false };

					size_type i = 0;

					for (; i < (istr.width() > 0 ? (std::min)(str.max_size(), istr.width()) : str.max_size()); ++i, chr = istr.rdbuf()->snextc()) LIKELY
					{
						if (IStrTraits::eq_int_type(chr, IStrTraits::eof())) UNLIKELY
						{
							state |= istr_type::eofbit;
							break;
						}
						if (ctype_facet.is(ctype::space, IStrTraits::to_char_type(chr))) UNLIKELY
						{
							break;
						}
						str[i] = IStrTraits::to_char_type(chr);

						if (!changed) UNLIKELY
						{
							changed = true;
						}
					}

					str[i] = 0;

					if (!changed) UNLIKELY
						state |= istr_type::failbit;
				}
				else UNLIKELY
					state |= istr_type::failbit;

				istr.setstate(state);

				return istr;
			}

			// ----- Constructors -----

			/**
			 * Default constructor (empty string)
			 */
			constexpr string() = default;

			/**
			 * Constructor from array m_data
			 * @param other Buffer to copy from
			 */
			constexpr string(const Elem(&other)[MemSize + 1]) noexcept : m_data{}
			{
				copy(other);
			}

			/**
			 * Constructor from array m_data with count of characters
			 * @param other Buffer to copy from
			 * @param count Count of characters to copy
			 */
			constexpr string(const Elem(&other)[MemSize + 1], const size_type count) noexcept : m_data{}
			{
				copy(other, count);
			}

			// ----- Copy constructors from m_datas -----

#if defined(HAS_CXX20)
			/**
			 * Copy constructor from array m_data
			 * @tparam OtherMemSize MemSize of the m_data to copy from
			 * @param other Buffer to copy from
			 */
			template <size_type OtherMemSize> requires (OtherMemSize != MemSize)
#else
			/**
			 * Copy constructor from array m_data
			 * @tparam OtherMemSize MemSize of the m_data to copy from
			 * @param other Buffer to copy from
			 */
			template <size_type OtherMemSize, typename = std::enable_if_t<OtherMemSize != MemSize>>
#endif
				constexpr string(const Elem(&other)[OtherMemSize]) noexcept : m_data{}
			{
				copy(other);
			}

#if defined(HAS_CXX20)
			/**
			 * Copy constructor from array m_data with count of characters
			 * @tparam OtherMemSize MemSize of the m_data to copy from
			 * @param other Buffer to copy from
			 * @param count Count of characters to copy
			 */
			template <size_type OtherMemSize> requires (OtherMemSize != MemSize)
#else
			/**
			 * Copy constructor from array m_data with count of characters
			 * @tparam OtherMemSize MemSize of the m_data to copy from
			 * @param other Buffer to copy from
			 * @param count Count of characters to copy
			 */
			template <size_type OtherMemSize, typename = std::enable_if_t<OtherMemSize != MemSize>>
#endif
				constexpr string(const Elem(&other)[OtherMemSize], const size_type count) noexcept : m_data{}
			{
				copy(other, count);
			}

#if defined(HAS_CXX20)
			/**
			 * Copy constructor from pointer m_data until null terminator is found or maximum size is reached (MemSize)
			 * @tparam ElemPtr Type of the pointer m_data (Default: const Elem* const)
			 * @param other Buffer to copy from
			 */
			template <typename ElemPtr = const Elem* const>
				requires std::is_pointer<ElemPtr>::value &&
						 std::is_same<typename std::remove_const<typename std::remove_pointer<typename std::remove_const<ElemPtr>::type>::type>::type, Elem>::value &&
						 (!std::is_array<ElemPtr>::value)
#else
			/**
			 * Copy constructor from pointer m_data
			 * @tparam ElemPtr Type of the pointer m_data (Default: const Elem* const)
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

#if defined(HAS_CXX20)
			/**
			 * Copy constructor from pointer m_data with count of characters
			 * @tparam ElemPtr Type of the pointer m_data (Default: const Elem* const)
			 * @param other Buffer to copy from
			 * @param count Count of characters to copy
			 */
			template <typename ElemPtr = const Elem* const>
				requires std::is_pointer<ElemPtr>::value &&
						 std::is_same<typename std::remove_const<typename std::remove_pointer<typename std::remove_const<ElemPtr>::type>::type>::type, Elem>::value &&
						 (!std::is_array<ElemPtr>::value)
#else
			/**
			 * Copy constructor from pointer m_data with count of characters
			 * @tparam ElemPtr Type of the pointer m_data (Default: const Elem* const)
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
			constexpr string(const string& other) noexcept : m_data{}
			{
				copy(other);
			}

			/**
			 * Copy constructor from another string count of characters
			 * @param other String to copy from
			 * @param count Count of characters to copy
			 */
			constexpr string(const string& other, const size_type count) noexcept : m_data{}
			{
				copy(other, count);
			}

			/**
			 * Copy constructor from another string of different params 
			 * @param other String to copy from
			 */
#if defined(HAS_CXX20)
			template <char_type OtherElem, size_type OtherMemSize> requires (OtherMemSize != MemSize)
#else
			template <typename OtherElem, size_type OtherMemSize, typename = std::enable_if_t<OtherMemSize != MemSize>>
#endif
				constexpr string(const string<OtherElem, OtherMemSize>& other) noexcept : m_data{}
			{
				copy(other);
			}

#if defined(HAS_CXX20)
			/**
			 * Copy constructor from another string of different params count of characters
			 * @tparam OtherElem Type of the other string's elements
			 * @tparam OtherMemSize MemSize of the other string
			 * @param other String to copy from
			 * @param count Count of characters to copy
			 */
			template <char_type OtherElem, size_type OtherMemSize> requires (OtherMemSize != MemSize)
#else
			/**
			 * Copy constructor from another string of different params count of characters
			 * @tparam OtherElem Type of the other string's elements
			 * @tparam OtherMemSize MemSize of the other string
			 * @param other String to copy from
			 * @param count Count of characters to copy
			 */
			template <typename OtherElem, size_type OtherMemSize, typename = std::enable_if_t<OtherMemSize != MemSize>>
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
			CONSTEXPR20 ~string() = default;

			// ----- Assignment operators -----

			/**
			 * Assign from array m_data operator
			 * @tparam OtherMemSize Size of the m_data to copy from
			 * @param other Buffer to copy from
			 * @return Reference to self
			 */
			template <size_type OtherMemSize>
			constexpr string& operator=(const Elem (&other)[OtherMemSize]) noexcept
			{
				return copy(other);
			}

#if defined(HAS_CXX20)
			/**
			 * Assign from pointer m_data operator
			 * @tparam ElemPtr Type of the pointer m_data to copy from (Default: const Elem* const)
			 * @param other Buffer to copy from
			 * @return Reference to self
			 */
		template <typename ElemPtr = const Elem* const>
			requires std::is_pointer<ElemPtr>::value &&
					 std::is_same<typename std::remove_const<typename std::remove_pointer<typename std::remove_const<ElemPtr>::type>::type>::type, Elem>::value &&
					 (!std::is_array<ElemPtr>::value)
#else
			/**
			 * Assign from pointer m_data operator
			 * @tparam ElemPtr Type of the pointer m_data to copy from (Default: const Elem* const)
			 * @param other Buffer to copy from
			 * @return Reference to self
			 */
			template <typename ElemPtr = const Elem* const, typename = std::enable_if_t<
				std::is_pointer<ElemPtr>::value &&
				std::is_same<typename std::remove_const<typename std::remove_pointer<typename std::remove_const<ElemPtr>::type>::type>::type, Elem>::value &&
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


#if defined(HAS_CXX20)
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
			NODISCARD constexpr Elem& operator[](const size_type index) noexcept
			{
				return at(index);
			}

			/**
			 * Const index operator (unchecked & UB if index >= MemSize)
			 * @param index Index of the element to access
			 * @return Const reference to the element at the index
			 */
			NODISCARD constexpr const Elem& operator[](const size_type index) const noexcept
			{
				return at(index);
			}

			// ----- Iteration functions -----

			/**
			 * Begin iterator
			 * @return Iterator to the beginning of the string
			 */
			NODISCARD constexpr iterator begin() noexcept
			{
				return m_data;
			}

			/**
			 * Const begin iterator
			 * @return Const iterator to the beginning of the string
			 */
			NODISCARD constexpr const_iterator begin() const noexcept
			{
				return m_data;
			}

			/**
			 * Const begin iterator
			 * @return Const iterator to the beginning of the string
			 */
			NODISCARD constexpr const_iterator cbegin() const noexcept
			{
				return begin();
			}

			/**
			 * End iterator
			 * @return Iterator to the end of the string (after the null terminator)
			 */
			NODISCARD constexpr iterator end() noexcept
			{
				return m_data + MemSize;
			}

			NODISCARD constexpr const_iterator end() const noexcept
			{
				return m_data + MemSize;
			}

			NODISCARD constexpr const_iterator cend() const noexcept
			{
				return end();
			}

			NODISCARD constexpr reverse_iterator rbegin() noexcept
			{
				return m_data + MemSize - 1;
			}

			NODISCARD constexpr const_reverse_iterator rbegin() const noexcept
			{
				return m_data + MemSize - 1;
			}

			NODISCARD constexpr const_reverse_iterator crbegin() const noexcept
			{
				return rbegin();
			}

			NODISCARD constexpr reverse_iterator rend() noexcept
			{
				return m_data - 1;
			}

			NODISCARD constexpr const_reverse_iterator rend() const noexcept
			{
				return m_data - 1;
			}

			NODISCARD constexpr const_reverse_iterator crend() const noexcept
			{
				return rend();
			}

			// ----- Copy functions from m_datas -----

			/**
			 * Copy from array m_data
			 * @tparam BufferOverlaps Whether the m_data overlaps with the string's m_data
			 * @tparam OtherMemSize Size of the m_data to copy from
			 * @param other Buffer to copy from
			 * @return Self reference
			 */
			template <bool BufferOverlaps = false, size_type OtherMemSize>
			CONSTEXPR17 string& copy(const Elem(&other)[OtherMemSize]) noexcept
			{
				ASSERT_ASSUME(other != nullptr);

				if (is_constant_evaluated())
				{
					constexpr bool m_data_smaller = OtherMemSize < MemSize;
					constexpr size_type size = (m_data_smaller ? OtherMemSize : MemSize) * sizeof(Elem);


					for (size_type i = 0; i < size; ++i)
					{
						m_data[i] = other[i];
					}

					IF_CONSTEXPR (m_data_smaller)
					{
						m_data[OtherMemSize] = 0;
					}
				}
				else
				{
					constexpr bool m_data_smaller = OtherMemSize < MemSize;
					constexpr size_type byte_size = (m_data_smaller ? OtherMemSize : MemSize) * sizeof(Elem);


					IF_CONSTEXPR (BufferOverlaps)
					{
						std::memmove(m_data, other, byte_size);
					}
					else
					{
						std::memcpy(m_data, other, byte_size);
					}


					IF_CONSTEXPR (m_data_smaller)
					{
						m_data[OtherMemSize] = 0;
					}
				}

				return *this;
			}

			/**
			 * Copy from array m_data
			 * @tparam OtherMemSize Size of the m_data to copy from
			 * @param other Buffer to copy from
			 * @param m_data_overlaps Whether the m_data overlaps with the string's m_data
			 * @return Self reference
			 */
			template <size_type OtherMemSize>
			CONSTEXPR17 string& copy(const Elem(&other)[OtherMemSize], const bool m_data_overlaps) noexcept
			{
				ASSERT_ASSUME(other != nullptr);

				if (is_constant_evaluated())
				{
					constexpr bool m_data_smaller = OtherMemSize < MemSize;
					constexpr size_type size = (m_data_smaller ? OtherMemSize : MemSize) * sizeof(Elem);


					for (size_type i = 0; i < size; ++i)
					{
						m_data[i] = other[i];
					}

					IF_CONSTEXPR (m_data_smaller)
					{
						m_data[OtherMemSize] = 0;
					}
				}
				else
				{
					constexpr bool m_data_smaller = OtherMemSize < MemSize;
					constexpr size_type byte_size = (m_data_smaller ? OtherMemSize : MemSize) * sizeof(Elem);


					if (m_data_overlaps) LIKELY
					{
						std::memmove(m_data, other, byte_size);
					}
					else UNLIKELY
					{
						std::memcpy(m_data, other, byte_size);
					}


					IF_CONSTEXPR (m_data_smaller)
					{
						m_data[OtherMemSize] = 0;
					}
				}

				return *this;
			}

			/**
			 * Copy from array m_data with count of characters
			 * @tparam BufferOverlaps Whether the m_data overlaps with the string's m_data
			 * @tparam Count Count of characters to copy
			 * @tparam OtherMemSize Size of the m_data to copy from
			 * @param other Buffer to copy from
			 * @return Self reference
			 */
			template <bool BufferOverlaps, size_type Count, size_type OtherMemSize>
			CONSTEXPR17 string& copy(const Elem(&other)[OtherMemSize]) noexcept
			{
				ASSERT_ASSUME(other != nullptr);

				if (is_constant_evaluated())
				{
					constexpr bool m_data_smaller = Count < MemSize;
					constexpr size_type size = (m_data_smaller ? Count : MemSize) * sizeof(Elem);

					
					for (size_type i = 0; i < size; ++i)
					{
						m_data[i] = other[i];
					}

					IF_CONSTEXPR (m_data_smaller)
					{
						m_data[Count] = 0;
					}
				}
				else
				{
					constexpr bool m_data_smaller = Count < MemSize;
					constexpr size_type byte_size = (m_data_smaller ? Count : MemSize) * sizeof(Elem);


					IF_CONSTEXPR (BufferOverlaps)
					{
						std::memmove(m_data, other, byte_size);
					}
					else
					{
						std::memcpy(m_data, other, byte_size);
					}


					IF_CONSTEXPR (m_data_smaller)
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
			 * @return Self reference
			 */
			template <size_type OtherMemSize>
			CONSTEXPR20 string& copy(const Elem(&other)[OtherMemSize], const size_type count) noexcept
			{
				ASSERT_ASSUME(other != nullptr);
				//[[assume(other != nullptr)]]

				if (is_constant_evaluated())
				{
					constexpr bool m_data_smaller = OtherMemSize < MemSize;
					constexpr size_type size = (m_data_smaller ? OtherMemSize : MemSize) * sizeof(Elem);


					for (size_type i = 0; i < size; ++i)
					{
						m_data[i] = other[i];
					}

					IF_CONSTEXPR(m_data_smaller)
					{
						m_data[OtherMemSize] = 0;
					}
				}
				else
				{
					if (count < MemSize) LIKELY
					{
						const size_type byte_size = count * sizeof(Elem);
						std::memcpy(m_data, other, byte_size);

						m_data[count - 1] = 0;
					}
					else UNLIKELY
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
			 * @param m_data_overlaps Whether the m_data overlaps with the string's m_data
			 * @param count Count of characters to copy
			 * @return Self reference
			 */
			template <size_type OtherMemSize>
			CONSTEXPR20 string& copy(const Elem(&other)[OtherMemSize], const bool m_data_overlaps, const size_type count) noexcept
			{
				ASSERT_ASSUME(other != nullptr);
				//[[assume(other != nullptr)]]

				if (is_constant_evaluated())
				{
					const bool m_data_smaller = count < MemSize;
					const size_type size = (m_data_smaller ? count : MemSize) * sizeof(Elem);


					for (size_type i = 0; i < size; ++i)
					{
						m_data[i] = other[i];
					}

					if (m_data_smaller)
					{
						m_data[count] = 0;
					}
				}
				else
				{
					if (count < MemSize) LIKELY
					{
						const size_type byte_size = count * sizeof(Elem);
						IF_CONSTEXPR (m_data_overlaps)
						{
							std::memmove(m_data, other, byte_size);
						}
						else
						{
							std::memcpy(m_data, other, byte_size);
						}

						m_data[count - 1] = 0;
					}
					else UNLIKELY
					{
						constexpr size_type byte_size = MemSize * sizeof(Elem);
						IF_CONSTEXPR (m_data_overlaps)
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

#if defined(HAS_CXX20)
			/**
			 * Copy from pointer m_data until null terminator is found or maximum size is reached (MemSize)
			 * @tparam BufferOverlaps Whether the m_data overlaps with the string's m_data (unused, kept for compatibility)
			 * @tparam ElemPtr Type of the pointer m_data (Default: const Elem* const)
			 * @param other Buffer to copy from
			 * @return Self reference
			 */
			template <bool BufferOverlaps, typename ElemPtr = const Elem* const>
				requires std::is_pointer<ElemPtr>::value &&
						 std::is_same<typename std::remove_const<typename std::remove_pointer<typename std::remove_const<ElemPtr>::type>::type>::type, Elem>::value &&
						 (!std::is_array<ElemPtr>::value)
#else
			/**
			 * Copy from pointer m_data until null terminator is found or maximum size is reached (MemSize)
			 * @tparam BufferOverlaps Whether the m_data overlaps with the string's m_data (unused, kept for compatibility)
			 * @tparam ElemPtr Type of the pointer m_data (Default: const Elem* const)
			 * @param other Buffer to copy from
			 * @return Self reference
			 */
			template <bool BufferOverlaps, typename ElemPtr = const Elem* const, typename = std::enable_if_t<
				std::is_pointer<ElemPtr>::value &&
				std::is_same<typename std::remove_const<typename std::remove_pointer<typename std::remove_const<ElemPtr>::type>::type>::type, Elem>::value &&
				(!std::is_array<ElemPtr>::value)>>
#endif
				constexpr string& copy(ElemPtr other) noexcept
			{
				ASSERT_ASSUME(other != nullptr);

				size_type i = 0;

				while (i < MemSize - 1 && !(m_data[i] = other[i++])) LIKELY {}

				if (i < MemSize - 1) LIKELY
				{
					m_data[i] = 0;
				}

				return *this;
			}

#if defined(HAS_CXX20)
			/**
			 * Copy from pointer m_data until null terminator is found or maximum size is reached (MemSize)
			 * @tparam ElemPtr Type of the pointer m_data (Default: const Elem* const)
			 * @param other Buffer to copy from
			 * @param m_data_overlaps Whether the m_data overlaps with the string's m_data
			 * @return Self reference
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
			 * @param m_data_overlaps Whether the m_data overlaps with the string's m_data
			 * @return Self reference
			 */
			template < typename ElemPtr = const Elem* const, typename = std::enable_if_t<
				std::is_pointer<ElemPtr>::value&&
				std::is_same<typename std::remove_const<typename std::remove_pointer<typename std::remove_const<ElemPtr>::type>::type>::type, Elem>::value &&
				(!std::is_array<ElemPtr>::value)>>
#endif
				constexpr string& copy(ElemPtr other, const bool m_data_overlaps) noexcept
			{
				ASSERT_ASSUME(other != nullptr);

				size_type i = 0;

				while (i < MemSize - 1 && !(m_data[i] = other[i++])) LIKELY;

				if (i < MemSize - 1) LIKELY
				{
					m_data[i] = 0;
				}

				return *this;
			}

#if defined(HAS_CXX20)
			/**
			 * Copy from pointer m_data count of characters
			 * @tparam Count Count of characters to copy
			 * @tparam ElemPtr Type of the pointer m_data (Default: const Elem* const)
			 * @param other Buffer to copy from
			 * @return Self reference
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
			 * @return Self reference
			 */
			template <size_type Count, typename ElemPtr, typename = std::enable_if_t<
				std::is_pointer<ElemPtr>::value&&
				std::is_same<typename std::remove_const<typename std::remove_pointer<typename std::remove_const<ElemPtr>::type>::type>::type, Elem>::value &&
				(!std::is_array<ElemPtr>::value)>>
#endif
				constexpr string& copy(ElemPtr other) noexcept
			{
				ASSERT_ASSUME(other != nullptr);

				if (is_constant_evaluated())
				{
					constexpr bool m_data_smaller = Count < MemSize;
					constexpr size_type size = (m_data_smaller ? Count : MemSize) * sizeof(Elem);


					for (size_type i = 0; i < size; ++i)
					{
						m_data[i] = other[i];
					}

					IF_CONSTEXPR (m_data_smaller)
					{
						m_data[Count] = 0;
					}
				}
				else
				{
					IF_CONSTEXPR(Count < MemSize)
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

			/**
			 * Copy from pointer m_data count of characters
			 * @tparam ElemPtr Type of the pointer m_data (Default: const Elem* const)
			 * @param other Buffer to copy from
			 * @param count MemSize of the m_data to copy from
			 * @return Self reference
			 */
#if defined(HAS_CXX20)
			template <typename ElemPtr = const Elem* const>
				requires std::is_pointer<ElemPtr>::value &&
						 std::is_same<typename std::remove_const<typename std::remove_pointer<typename std::remove_const<ElemPtr>::type>::type>::type, Elem>::value &&
						 (!std::is_array<ElemPtr>::value)
#else
			template <typename ElemPtr = const Elem* const, typename = std::enable_if_t<
				std::is_pointer<ElemPtr>::value&&
				std::is_same<typename std::remove_const<typename std::remove_pointer<typename std::remove_const<ElemPtr>::type>::type>::type, Elem>::value &&
				(!std::is_array<ElemPtr>::value)>>
#endif
				constexpr string& copy(ElemPtr other, const size_type count) noexcept
			{
				ASSERT_ASSUME(other != nullptr);
				//[[assume(other != nullptr)]]

				if (is_constant_evaluated())
				{
					if (count < MemSize) LIKELY
					{
						for (size_type i = 0; i < count; ++i) LIKELY
						{
							m_data[i] = other[i];
						}

						m_data[count - 1] = 0;
					}
					else UNLIKELY
					{
						for (size_type i = 0; i < MemSize; ++i) LIKELY
						{
							m_data[i] = other[i];
						}
					}
				}
				else
				{
					if (count < MemSize) LIKELY
					{
						const size_type byte_size = count * sizeof(Elem);
						std::memcpy(m_data, other, byte_size);

						m_data[count] = 0;
					}
					else UNLIKELY
					{
						constexpr size_type byte_size = MemSize * sizeof(Elem);
						std::memcpy(m_data, other, byte_size);
					}
				}

				return *this;
			}

#if defined(HAS_CXX20)
			/**
			 * Copy from pointer m_data count of characters
			 * @tparam BufferOverlaps Whether the m_data overlaps with the string's m_data
			 * @tparam Count Count of characters to copy
			 * @tparam ElemPtr Type of the pointer m_data (Default: const Elem* const)
			 * @param other Buffer to copy from
			 * @return Self reference
			 */
			template <bool BufferOverlaps, size_type Count, typename ElemPtr = const Elem* const>
				requires std::is_pointer<ElemPtr>::value &&
						 std::is_same<typename std::remove_const<typename std::remove_pointer<typename std::remove_const<ElemPtr>::type>::type>::type, Elem>::value &&
						 (!std::is_array<ElemPtr>::value)
#else
			/**
			 * Copy from pointer m_data count of characters
			 * @tparam BufferOverlaps Whether the m_data overlaps with the string's m_data
			 * @tparam Count Count of characters to copy
			 * @tparam ElemPtr Type of the pointer m_data (Default: const Elem* const)
			 * @param other Buffer to copy from
			 * @return Self reference
			 */
			template <size_type Count, typename ElemPtr, typename = std::enable_if_t<
				std::is_pointer<ElemPtr>::value &&
				std::is_same<typename std::remove_const<typename std::remove_pointer<typename std::remove_const<ElemPtr>::type>::type>::type, Elem>::value &&
				(!std::is_array<ElemPtr>::value)>>
#endif
				constexpr string& copy(ElemPtr other) noexcept
			{
				ASSERT_ASSUME(other != nullptr);

				if (is_constant_evaluated())
				{
					constexpr bool m_data_smaller = Count < MemSize;
					constexpr size_type size = (m_data_smaller ? Count : MemSize) * sizeof(Elem);


					for (size_type i = 0; i < size; ++i)
					{
						m_data[i] = other[i];
					}

					IF_CONSTEXPR(m_data_smaller)
					{
						m_data[Count] = 0;
					}
				}
				else
				{
					constexpr bool m_data_smaller = Count < MemSize;
					constexpr size_type byte_size = (m_data_smaller ? Count : MemSize) * sizeof(Elem);


					IF_CONSTEXPR(BufferOverlaps)
					{
						std::memmove(m_data, other, byte_size);
					}
					else
					{
						std::memcpy(m_data, other, byte_size);
					}


					IF_CONSTEXPR(m_data_smaller)
					{
						m_data[Count] = 0;
					}
				}
				return *this;
			}

#if defined(HAS_CXX20)
			/**
			 * Copy from pointer m_data count of characters
			 * @tparam ElemPtr Type of the pointer m_data (Default: const Elem* const)
			 * @param other Buffer to copy from
			 * @param m_data_overlaps Whether the m_data overlaps with the string's m_data
			 * @param count Count of characters to copy
			 * @return Self reference
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
			 * @param m_data_overlaps Whether the m_data overlaps with the string's m_data
			 * @param count Count of characters to copy
			 * @return Self reference
			 */
			template <size_type Count, typename ElemPtr, typename = std::enable_if_t<
				std::is_pointer<ElemPtr>::value&&
				std::is_same<typename std::remove_const<typename std::remove_pointer<typename std::remove_const<ElemPtr>::type>::type>::type, Elem>::value &&
				(!std::is_array<ElemPtr>::value)>>
#endif
				constexpr string& copy(ElemPtr other, const bool m_data_overlaps, const size_type count) noexcept
			{
				ASSERT_ASSUME(other != nullptr);

				if (is_constant_evaluated())
				{
					const bool m_data_smaller = count < MemSize;
					const size_type size = (m_data_smaller ? count : MemSize) * sizeof(Elem);


					for (size_type i = 0; i < size; ++i)
					{
						m_data[i] = other[i];
					}

					IF_CONSTEXPR(m_data_smaller)
					{
						m_data[count] = 0;
					}
				}
				else
				{
					if (count < MemSize) LIKELY
					{
						const size_type byte_size = count * sizeof(Elem);
						IF_CONSTEXPR(m_data_overlaps)
						{
							std::memmove(m_data, other, byte_size);
						}
						else
						{
							std::memcpy(m_data, other, byte_size);
						}

						m_data[count - 1] = 0;
					}
					else UNLIKELY
					{
						constexpr size_type byte_size = MemSize * sizeof(Elem);
						IF_CONSTEXPR(m_data_overlaps)
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


#if defined(HAS_CXX20)
			template <char_type OtherElem, size_type OtherMemSize>
#else
			template <typename OtherElem, size_type OtherMemSize>
#endif
			constexpr string& copy(const string<OtherElem, OtherMemSize>& other)
			{
				ASSERT_ASSUME(this != &other);

				copy(other.data());

				return *this;
			}

#if defined(HAS_CXX20)
			template <char_type OtherElem, size_type OtherMemSize>
#else
			template <typename OtherElem, size_type OtherMemSize>
#endif
			constexpr string& copy(const string<OtherElem, OtherMemSize>& other, const size_type count)
			{
				ASSERT_ASSUME(this != &other);

				copy(other.data(), count);

				return *this;
			}

			/**
			 * Access the element at the index (unchecked)
			 * @param index Index of the element to access
			 * @return Reference to the element at the index
			 */
			NODISCARD constexpr Elem& at(const size_type index) noexcept
			{
				ASSERT_ASSUME(index < MemSize);

				return m_data[index];
			}

			/**
			 * Returns a const reference to the element at the index (unchecked)
			 * @param index Index of the element to access
			 * @return Const reference to the element at the index
			 */
			NODISCARD constexpr const Elem& at(const size_type index) const noexcept
			{
				ASSERT_ASSUME(index < MemSize);

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
				IF_CONSTEXPR (std::is_same<Elem, char>::value)
				{
					std::memset(m_data, val, MemSize);
				}
				else IF_CONSTEXPR (std::is_same<Elem, wchar_t>::value)
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
				ASSERT_ASSUME(index1 >= 0 && index1 < MemSize);
				ASSERT_ASSUME(index2 >= 0 && index2 < MemSize);

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
				ASSERT_ASSUME(this != &other);

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
			NODISCARD constexpr const string& as_const() const noexcept
			{
				return *this;
			}

			/**
			 * @return Array representing string data
			 */
			NODISCARD constexpr Elem(&data() noexcept)[MemSize]
			{
				return m_data;
			}

			/**
			 * @return Const array representing string data
			 */
			NODISCARD constexpr const Elem(&data() const noexcept)[MemSize]
			{
				return m_data;
			}

			/**
			 * @return C-String representation of the string (not necessarily null-terminated)
			 */
			NODISCARD constexpr const Elem(&c_str() const noexcept)[MemSize]
			{
				return m_data;
			}


			/**
			 * @return Size of the string (until null terminator)
			 */
			NODISCARD constexpr size_type str_size() const noexcept
			{
				IF_CONSTEXPR (!MemSize)
					return 0;

				IF_CONSTEXPR (MemSize == 1)
					return static_cast<bool>(m_data[0]);

				if (is_constant_evaluated())
				{
					size_type len{ 0 };

					for (; len < mem_size() && m_data[len]; ++len);

					return len;
				}

				IF_CONSTEXPR (std::is_same<Elem, char>::value)
				{
#if !defined(HAS_CXX17) // C++14 fails to recognize type restriction
					return strnlen(reinterpret_cast<const char*>(m_data), MemSize);
#else
					return strnlen(m_data, MemSize);
#endif
				}

				IF_CONSTEXPR (std::is_same<Elem, wchar_t>::value)
				{
#if !defined(HAS_CXX17) // C++14 fails to recognize type restriction
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
			NODISCARD constexpr size_type size() const noexcept
			{
				return str_size();
			}

			/**
			 * @return Size of the string memory m_data
			 */
			NODISCARD static
#if defined(HAS_CXX20)
			CONSTEVAL20
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
			NODISCARD static
#if defined(HAS_CXX20)
				CONSTEVAL20
#else
				constexpr
#endif
			size_type max_size() noexcept
			{
				return mem_size();
			}
		};

		// ----- Deduction guides -----
#if defined(HAS_CXX17)
		template <typename Elem, size_t Size>
		explicit string(const Elem(&)[Size]) -> string<Elem, Size - 1>;

		template <typename Elem, size_t Size>
		explicit string(const Elem(&)[Size], size_t) -> string<Elem, Size - 1>;
#endif
	}
}