#pragma once

#ifndef WOJ_STRING_HPP
#define WOJ_STRING_HPP
#include <cassert>
#endif

#ifndef WOJ_DEFS_HPP
#include "defs.hpp"
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
	#if defined(HAS_CXX20)
	template <typename T>
	concept char_type = std::is_same_v<T, char> || std::is_same_v<T, char8_t> || std::is_same_v<T, wchar_t> || std::is_same_v<T, char16_t> || std::is_same_v<T, char32_t>;
	#else
	template <typename T>
	constexpr bool is_char_v = std::is_same_v<T, char> || std::is_same_v<T, wchar_t> || std::is_same_v<T, char16_t> || std::is_same_v<T, char32_t>;

	template <typename T>
	struct is_char
	{
		static constexpr bool value = std::is_same_v<T, char> || std::is_same_v<T, wchar_t> || std::is_same_v<T, char16_t> || std::is_same_v<T, char32_t>;
	};

	template <typename T>
	using is_char_v = is_char<T>::value;
	#endif

	template <typename T>
	class reversed_iterators : public T
	{
		using iterator = typename T::iterator;
		using const_iterator = typename T::const_iterator;
		using reverse_iterator = typename T::reverse_iterator;
		using const_reverse_iterator = typename T::const_reverse_iterator;

		// ----- Iteration functions -----
		CONSTEXPR20 iterator begin() noexcept
		{
			return this->rbegin();
		}

		CONSTEXPR20 const_iterator begin() const noexcept
		{
			return this->rbegin();
		}

		CONSTEXPR20 const_iterator cbegin() const noexcept
		{
			return this->crbegin();
		}

		CONSTEXPR20 iterator end() noexcept
		{
			return this->rend();
		}

		CONSTEXPR20 const_iterator end() const noexcept
		{
			return this->rend();
		}

		CONSTEXPR20 const_iterator cend() const noexcept
		{
			return this->crend();
		}

		CONSTEXPR20 iterator rbegin() noexcept
		{
			return this->begin();
		}

		CONSTEXPR20 const_iterator rbegin() const noexcept
		{
			return this->begin();
		}

		CONSTEXPR20 const_iterator crbegin() const noexcept
		{
			return this->cbegin();
		}

		CONSTEXPR20 iterator rend() noexcept
		{
			return this->end();
		}

		CONSTEXPR20 const_iterator rend() const noexcept
		{
			return this->end();
		}

		CONSTEXPR20 const_iterator crend() const noexcept
		{
			return this->cend();
		}
	};

	namespace stack
	{
#if defined(HAS_CXX20)
		template <char_type Elem, size_t Size>
#else
		template <typename Elem, size_t Size> requires is_char_v<Elem>
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

			alignas(Elem) Elem buffer[Size]{};

			template <typename Elem, typename Traits = std::char_traits<Elem>>
			CONSTEXPR20 friend std::ostream& operator<<(std::basic_ostream<Elem, Traits>& ostr, const string& str)
			{
				ostr.write(str.data(), str.size());
				return ostr;
			}

			template <typename Elem, typename Traits = std::char_traits<Elem>>
			CONSTEXPR20 friend std::istream& operator>>(std::basic_istream<Elem, Traits>& istr, string& str)
			{
				using istr_type = std::basic_istream<Elem, Traits>;
				using ctype = std::ctype<Elem>;

				typename istr_type::iostate state{ istr_type::goodbit };

				if (typename istr_type::sentry{ istr }) LIKELY
				{
					const ctype& ctype_facet = std::use_facet<ctype>(istr.getloc());

					typename Traits::int_type chr = istr.rdbuf()->sgetc();
					bool changed{ false };

					for (size_type i = 0; i < (std::min)(str.size(), istr.width()); ++i, chr = istr.rdbuf()->snextc()) LIKELY
					{
						if (Traits::eq_int_type(chr, Traits::eof)) UNLIKELY
						{
							state |= istr_type::eofbit;
							break;
						}
						if (ctype_facet.is(ctype::space, Traits::to_char_type(chr))) UNLIKELY
						{
							break;
						}
						str[i] = Traits::to_char_type(chr);

						if (!changed) UNLIKELY
						{
							changed = true;
						}
					}

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
			CONSTEXPR20 string() = default;

			// ----- Copy constructors from buffers -----

			/**
			 * Copy constructor from array buffer
			 * @param other Buffer to copy from
			 */
			CONSTEXPR20 string(const Elem(&other)[Size]) noexcept
			{
				copy(other);
			}

			/**
			 * Copy constructor from array buffer count of characters
			 * @param other Buffer to copy from
			 * @param count Size of the buffer to copy from
			 */
			CONSTEXPR20 string(const Elem(&other)[Size], const size_type count) noexcept
			{
				copy(other, count);
			}

			/**
			 * Copy constructor from array buffer whose size is different from the string size
			 * @tparam OtherSize Size of the buffer to copy from
			 * @param other Buffer to copy from
			 */
			template <size_type OtherSize> requires (OtherSize != Size)
				CONSTEXPR20 string(const Elem(&other)[OtherSize]) noexcept
			{
				copy(other);
			}

			/**
			 * Copy constructor from array buffer whose size is different from the string size
			 * @tparam OtherSize Size of the buffer to copy from
			 * @param other Buffer to copy from
			 * @param count Size of the buffer to copy from
			 */
			template <size_type OtherSize> requires (OtherSize != Size)
				CONSTEXPR20 string(const Elem(&other)[OtherSize], const size_type count) noexcept
			{
				copy(other, count);
			}


			/**
			 * Copy constructor from pointer buffer until null terminator is found or maximum size is reached (Size)
			 * @tparam ElemPtr Type of the pointer buffer (Default: const Elem* const)
			 * @param other Buffer to copy from
			 */
			template <typename ElemPtr = const Elem* const>
				requires std::is_pointer_v<ElemPtr>&&
			std::is_same_v<std::remove_const_t<std::remove_pointer_t<std::remove_const_t<std::remove_pointer_t<ElemPtr>>>>, Elem> &&
				(!std::is_array_v<ElemPtr>)
				CONSTEXPR20 string(ElemPtr other) noexcept
			{
				copy(other);
			}

			/**
			 * Copy constructor from pointer buffer count of characters
			 * @tparam ElemPtr Type of the pointer buffer (Default: const Elem* const)
			 * @param other Buffer to copy from
			 * @param count Size of the buffer to copy from
			 */
			template <typename ElemPtr = const Elem* const>
				requires std::is_pointer_v<ElemPtr>&&
			std::is_same_v<std::remove_const_t<std::remove_pointer_t<std::remove_const_t<std::remove_pointer_t<ElemPtr>>>>, Elem> &&
				(!std::is_array_v<ElemPtr>)
				CONSTEXPR20 string(ElemPtr other, const size_type count) noexcept
			{
				copy(other, count);
			}


			/**
			 * Copy constructor from another string
			 * @param other String to copy from
			 */
			CONSTEXPR20 string(const string& other) noexcept
			{
				copy(other);
			}

			/**
			 * Copy constructor from another string count of characters
			 * @param other String to copy from
			 * @param count Size of the buffer to copy from
			 */
			CONSTEXPR20 string(const string& other, const size_type count) noexcept
			{
				copy(other, count);
			}

			/**
			 * Move constructor is deleted
			 */
			CONSTEXPR20 string(string&&) = delete;

			/**
			 * Destructs the string
			 */
			CONSTEXPR20 ~string() = default;

			// ----- Assignment operators -----

			/**
			 * Copy from array buffer
			 * @param other Buffer to copy from
			 * @return Self reference
			 */
			CONSTEXPR20 string& operator=(const Elem other[Size]) noexcept
			{
				return copy(other);
			}

			/**
			 * Copy from array buffer
			 * @tparam OtherSize Size of the buffer to copy from
			 * @param other Buffer to copy from
			 * @return Self reference
			 */
			template <size_type OtherSize> requires (OtherSize != Size)
				CONSTEXPR20 string& operator=(const Elem other[OtherSize]) noexcept
			{
				return copy(other);
			}

			/**
			 * Copy from pointer buffer
			 * @tparam ElemPtr Type of the pointer buffer (Default: const Elem* const)
			 * @param other Buffer to copy from
			 * @return Self reference
			 */
			template <typename ElemPtr = const Elem* const>
				requires std::is_pointer_v<ElemPtr>&&
			std::is_same_v<std::remove_const_t<std::remove_pointer_t<std::remove_const_t<std::remove_pointer_t<ElemPtr>>>>, Elem> &&
				(!std::is_array_v<ElemPtr>)
				CONSTEXPR20 string& operator=(ElemPtr other) noexcept
			{
				return copy(other);
			}

			/**
			 * Copy from another string
			 * @param other String to copy from
			 * @return Self reference
			 */
			CONSTEXPR20 string& operator=(const string& other) noexcept
			{
				return copy(other);
			}

			/**
			 * Move from another string is deleted
			 */
			CONSTEXPR20 string& operator=(string&&) = delete;

			CONSTEXPR20 Elem& operator[](const size_type index) noexcept
			{
				return at(index);
			}

			CONSTEXPR20 const Elem& operator[](const size_type index) const noexcept
			{
				return at(index);
			}

			// ----- Iteration functions -----
			CONSTEXPR20 iterator begin() noexcept
			{
				return buffer;
			}

			CONSTEXPR20 const_iterator begin() const noexcept
			{
				return buffer;
			}

			CONSTEXPR20 const_iterator cbegin() const noexcept
			{
				return begin();
			}

			CONSTEXPR20 iterator end() noexcept
			{
				return buffer + Size;
			}

			CONSTEXPR20 const_iterator end() const noexcept
			{
				return buffer + Size;
			}

			CONSTEXPR20 const_iterator cend() const noexcept
			{
				return end();
			}

			CONSTEXPR20 reverse_iterator rbegin() noexcept
			{
				return buffer + Size - 1;
			}

			CONSTEXPR20 const_reverse_iterator rbegin() const noexcept
			{
				return buffer + Size - 1;
			}

			CONSTEXPR20 const_reverse_iterator crbegin() const noexcept
			{
				return rbegin();
			}

			CONSTEXPR20 pointer rend() noexcept
			{
				return buffer - 1;
			}

			CONSTEXPR20 const_reverse_iterator rend() const noexcept
			{
				return buffer - 1;
			}

			CONSTEXPR20 const_reverse_iterator crend() const noexcept
			{
				return rend();
			}

			// ----- Copy functions from buffers -----

			/**
			 * Copy from array buffer
			 * @param other Buffer to copy from
			 * @return Self reference
			 */
			CONSTEXPR20 string& copy(const Elem(&other)[Size]) noexcept
			{
				ASSERT_ASSUME(other != nullptr);

				IF_CONSTEVAL
				{
					for (size_type i = 0; i < Size - 1; ++i) [[likely]]
					{
						buffer[i] = other[i];
					}
				}
				else
				{
					constexpr size_type byte_size = Size * sizeof(Elem);
					std::memcpy(buffer, other, byte_size);
				}

				buffer[Size - 1] = '\0';

				return *this;
			}

			/**
			 * Copy from array buffer with count of characters
			 * @param other Buffer to copy from
			 * @param count Count of characters to copy
			 * @return Self reference
			 */
			CONSTEXPR20 string& copy(const Elem(&other)[Size], const size_type count) noexcept
			{
				//std::unreachable();
				ASSERT_ASSUME(other != nullptr);

				const size_type min_count = (std::min)(count, Size - 1);

				IF_CONSTEVAL
				{
					for (size_type i = 0; i < min_count; ++i) [[likely]]
					{
						buffer[i] = other[i];
					}
				}
				else
				{
					const size_type byte_size = min_count * sizeof(Elem);
					std::memcpy(buffer, other, byte_size);
				}


				buffer[min_count] = '\0';

				return *this;
			}

			/**
			 * Copy from array buffer whose size is different from the string size
			 * @tparam OtherSize Size of the buffer to copy from
			 * @param other Buffer to copy from
			 * @return Self reference
			 */
			template <size_type OtherSize>
			CONSTEXPR20 string& copy(const Elem(&other)[OtherSize]) noexcept
			{
				ASSERT_ASSUME(other != nullptr);
				//[[assume(other != nullptr)]]

				constexpr size_type min_count = (std::min)(OtherSize, Size - 1);

				IF_CONSTEVAL
				{
					for (size_type i = 0; i < min_count; ++i) [[likely]]
					{
						buffer[i] = other[i];
					}
				}
				else
				{
					constexpr size_type byte_size = min_count * sizeof(Elem);
					std::memcpy(buffer, other, byte_size);
				}

				buffer[min_count] = '\0';

				return *this;
			}

			/**
			 * Copy from array buffer whose size is different from the string size
			 * @tparam OtherSize Size of the buffer to copy from
			 * @param other Buffer to copy from
			 * @param count Count of characters to copy
			 * @return Self reference
			 */
			template <size_type OtherSize>
			CONSTEXPR20 string& copy(const Elem(&other)[OtherSize], const size_type count) noexcept
			{
				ASSERT_ASSUME(other != nullptr);
				//[[assume(other != nullptr)]]

				const size_type min_count = (std::min)(count, Size - 1);

				IF_CONSTEVAL
				{
					for (size_type i = 0; i < min_count; ++i) [[likely]]
					{
						buffer[i] = other[i];
					}
				}
				else
				{
					const size_type byte_size = min_count * sizeof(Elem);
					std::memcpy(buffer, other, byte_size);
				}

					buffer[min_count] = '\0';

					return *this;
			}

			/**
			 * Copy from pointer buffer until null terminator is found or maximum size is reached (Size)
			 * @tparam ElemPtr Type of the pointer buffer (Default: const Elem* const)
			 * @param other Buffer to copy from
			 * @return Self reference
			 */
			template <typename ElemPtr = const Elem* const>
				requires std::is_pointer_v<ElemPtr>&&
			std::is_same_v<std::remove_const_t<std::remove_pointer_t<std::remove_const_t<std::remove_pointer_t<ElemPtr>>>>, Elem> &&
				(!std::is_array_v<ElemPtr>)
				CONSTEXPR20 string& copy(ElemPtr other) noexcept
			{
				ASSERT_ASSUME(other != nullptr);

				//[[assume(other != nullptr)]]

				IF_CONSTEVAL
				{
					size_type i = 0;

					while (i < Size - 1 && !(buffer[i] = other[i++])) [[likely]] {}

					if (i >= Size - 1)
					{
						buffer[Size - 1] = Elem{ 0 };
					}
				}
				else IF_CONSTEXPR17(std::is_same_v<Elem, char>)
				{
					strcpy_s(buffer, other);
				}
				else IF_CONSTEXPR17(std::is_same_v<Elem, wchar_t>)
				{
					wcscpy_s(buffer, other);
				}
				else
				{
					size_type i = 0;

					while (i < Size - 1 && !(buffer[i] = other[i++])) [[likely]] {}

					if (i >= Size - 1)
					{
						buffer[Size - 1] = Elem{ 0 };
					}
				}
				return *this;
			}

			/**
			 * Copy from pointer buffer count of characters
			 * @tparam ElemPtr Type of the pointer buffer (Default: const Elem* const)
			 * @param other Buffer to copy from
			 * @param count Size of the buffer to copy from
			 * @return Self reference
			 */
			template <typename ElemPtr = const Elem* const>
				requires std::is_pointer_v<ElemPtr>&&
			std::is_same_v<std::remove_const_t<std::remove_pointer_t<std::remove_const_t<std::remove_pointer_t<ElemPtr>>>>, Elem> &&
				(!std::is_array_v<ElemPtr>)
				CONSTEXPR20 string& copy(ElemPtr other, const size_type count) noexcept
			{
				ASSERT_ASSUME(other != nullptr);
				//[[assume(other != nullptr)]]

				IF_CONSTEVAL
				{
					const size_type min_count = (std::min)(count, Size - 1);

					for (size_type i = 0; i < min_count; ++i) [[likely]]
					{
						buffer[i] = other[i];
					}

					buffer[min_count] = '\0';
				}
				else IF_CONSTEXPR17(std::is_same_v<Elem, char>)
				{
					strcpy_s(buffer, other);
				}
				else IF_CONSTEXPR17(std::is_same_v<Elem, wchar_t>)
				{
					wcscpy_s(buffer, other);
				}
				else
				{
					const size_type min_count = (std::min)(count, Size - 1);

					for (size_type i = 0; i < min_count; ++i) [[likely]]
					{
						buffer[i] = other[i];
					}

					buffer[min_count] = '\0';
				}

				return *this;
			}

			CONSTEXPR20 string& copy(const string& other)
			{
				ASSERT_ASSUME(this != &other);

				copy(other.buffer);

				return *this;
			}

			CONSTEXPR20 string& copy(const string& other, const size_type count)
			{
				ASSERT_ASSUME(this != &other);

				copy(other.buffer, count);

				return *this;
			}

			CONSTEXPR20 Elem& at(const size_type index) noexcept
			{
				ASSERT_ASSUME(index >= 0 && index < Size);

				return buffer[index];
			}

			CONSTEXPR20 const Elem& at(const size_type index) const noexcept
			{
				ASSERT_ASSUME(index >= 0 && index < Size);

				return buffer[index];
			}

			CONSTEXPR20 string& fill(const Elem val) noexcept
			{
				IF_CONSTEVAL
				{
					for (size_type i = 0; i < Size; ++i)
					{
						buffer[i] = val;
					}
					return *this;
				}
				IF_CONSTEXPR17(std::is_same_v<Elem, char>)
				{
					std::memset(buffer, val, Size);
				}
				else IF_CONSTEXPR17(std::is_same_v<Elem, wchar_t>)
				{
					std::wmemset(buffer, val, Size);
					}
				else
				{
					std::fill(buffer, buffer + Size, val);
				}

				return *this;
			}

			CONSTEXPR20 string& swap(const size_type index1, const size_type index2) noexcept
			{
				ASSERT_ASSUME(index1 >= 0 && index1 < Size);
				ASSERT_ASSUME(index2 >= 0 && index2 < Size);

				buffer[index1] ^= buffer[index2];
				buffer[index2] ^= buffer[index1];
				buffer[index1] ^= buffer[index2];
				return *this;
			}

			CONSTEXPR20 string& swap(string& other) noexcept
			{
				ASSERT_ASSUME(this != &other);

				for (size_type i = 0; i < Size; ++i)
				{
					buffer[i] ^= other.buffer[i];
					other.buffer[i] ^= buffer[i];
					buffer[i] ^= other.buffer[i];
				}

				return *this;
			}

			CONSTEXPR20 const string& as_const() const noexcept
			{
				return *this;
			}

			[[nodiscard]] CONSTEXPR20 const decltype(buffer)& data() const noexcept
			{
				return buffer;
			}

			[[nodiscard]] CONSTEXPR20 decltype(buffer)& data() noexcept
			{
				return buffer;
			}

			[[nodiscard]] CONSTEXPR20 const decltype(buffer)& c_str() const noexcept
			{
				return buffer;
			}

			static consteval size_type size() noexcept
			{
				return Size;
			}
		};
	}
}