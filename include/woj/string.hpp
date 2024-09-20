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
	namespace impl
	{
		template <typename Elem, typename Traits = std::char_traits<Elem>>
		class basic_streambuf_publicized : public std::basic_streambuf<Elem, Traits>
		{
		public:
			using base_type = std::basic_streambuf<Elem, Traits>;

			// Private
			using base_type::base_type;
			using base_type::operator=;
			using base_type::swap;

			// Public
			using base_type::~basic_streambuf;
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
#endif // _HAS_OLD_IOSTREAMS_MEMBERS
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
	concept char_type = std::is_same_v<T, char> || std::is_same_v<T, char8_t> || std::is_same_v<T, wchar_t> || std::is_same_v<T, char16_t> || std::is_same_v<T, char32_t>;
	#else
	template <typename T>
	struct is_char
	{
		static constexpr bool value = std::is_same_v<T, char> || std::is_same_v<T, wchar_t> || std::is_same_v<T, char16_t> || std::is_same_v<T, char32_t>;
	};

	template <typename T>
	using is_char_v = typename is_char<T>::value;
	#endif

	namespace stack
	{
#if defined(HAS_CXX20)
		template <char_type Elem, size_t Size, bool EnableIndexWrapAround = false>
#else
		template <typename Elem, size_t Size, bool EnableIndexWrapAround = false> requires is_char_v<Elem>
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

			template <typename IStrElem, typename IStrTraits = std::char_traits<IStrElem>>
			CONSTEXPR20 friend std::ostream& operator<<(std::basic_ostream<IStrElem, IStrTraits>& ostr, const string& str)
			{
				using ostr_type = std::basic_ostream<IStrElem, IStrTraits>;
				typename ostr_type::iostate state{ ostr_type::goodbit };

				std::string s;
				std::cout << s;

				if (typename ostr_type::sentry{ ostr }) LIKELY
				{
					size_type pad = (ostr.width() <= 0) ? 0 : static_cast<size_type>(ostr.width());

					if ((ostr.flags() & ostr_type::adjustfield) != ostr_type::left)
					{
						for ()
					}
				}
				else
					state |= ostr_type::badbit;

				auto obj = static_cast<std::basic_streambuf<char>*>(nullptr);
				obj->xsputn

				ostr.rdbuf()->in_avail();
				return ostr;
			}

			template <typename IStrElem, typename IStrTraits = std::char_traits<IStrElem>>
			CONSTEXPR20 friend std::istream& operator>>(std::basic_istream<IStrElem, IStrTraits>& istr, string& str)
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

					for (; i < istr.width() > 0 ? (std::min)(str.max_size(), istr.width()) : str.max_size(); ++i, chr = istr.rdbuf()->snextc()) LIKELY
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

			NODISCARD17 CONSTEXPR20 Elem& operator[](const size_type index) noexcept
			{
				return at(index);
			}

			NODISCARD17 CONSTEXPR20 const Elem& operator[](const size_type index) const noexcept
			{
				return at(index);
			}

			// ----- Iteration functions -----
			NODISCARD17 CONSTEXPR20 iterator begin() noexcept
			{
				return buffer;
			}

			NODISCARD17 CONSTEXPR20 const_iterator begin() const noexcept
			{
				return buffer;
			}

			NODISCARD17 CONSTEXPR20 const_iterator cbegin() const noexcept
			{
				return begin();
			}

			NODISCARD17 CONSTEXPR20 iterator end() noexcept
			{
				return buffer + Size;
			}

			NODISCARD17 CONSTEXPR20 const_iterator end() const noexcept
			{
				return buffer + Size;
			}

			NODISCARD17 CONSTEXPR20 const_iterator cend() const noexcept
			{
				return end();
			}

			NODISCARD17 CONSTEXPR20 reverse_iterator rbegin() noexcept
			{
				return buffer + Size - 1;
			}

			NODISCARD17 CONSTEXPR20 const_reverse_iterator rbegin() const noexcept
			{
				return buffer + Size - 1;
			}

			NODISCARD17 CONSTEXPR20 const_reverse_iterator crbegin() const noexcept
			{
				return rbegin();
			}

			NODISCARD17 CONSTEXPR20 pointer rend() noexcept
			{
				return buffer - 1;
			}

			NODISCARD17 CONSTEXPR20 const_reverse_iterator rend() const noexcept
			{
				return buffer - 1;
			}

			NODISCARD17 CONSTEXPR20 const_reverse_iterator crend() const noexcept
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

			NODISCARD17 CONSTEXPR20 const string& as_const() const noexcept
			{
				return *this;
			}

			NODISCARD17 CONSTEXPR20 const decltype(buffer)& data() const noexcept
			{
				return buffer;
			}

			NODISCARD17 CONSTEXPR20 decltype(buffer)& data() noexcept
			{
				return buffer;
			}

			NODISCARD17 CONSTEXPR20 const decltype(buffer)& c_str() const noexcept
			{
				return buffer;
			}

			NODISCARD17 CONSTEXPR20 size_type str_size() const noexcept
			{
				size_type len{ mem_size() };

				for (; len > 0 && buffer[len]; --len) [[likely]] {}

				return len;

			}

			NODISCARD17 CONSTEXPR20 size_type size() const noexcept
			{
				return str_size();
			}

			NODISCARD17 static CONSTEVAL20 size_type mem_size() noexcept
			{
				return Size;
			}

			NODISCARD17 static CONSTEVAL20 size_type max_size() noexcept
			{
				return mem_size();
			}
		};
	}
}