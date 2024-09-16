#include <iostream>
#include <Windows.h>
#include <cstdio>
#include <cstdlib>
#define __STDC_WANT_LIB_EXT1__ 1
#include <cstring>
#include <algorithm>
#include <type_traits>

#include "../include/woj/defs.hpp"
#include "../include/woj/string.hpp"

#include <cassert>

namespace woj
{
	namespace stack
	{
		template <char_t TElem, size_t Size> 
		class string
		{
		public:
			using value_type = TElem;
			using size_type = size_t;
			using difference_type = std::ptrdiff_t;
			using pointer = TElem*;
			using const_pointer = TElem*;
			using reference = TElem&;
			using const_reference = const TElem&;

			alignas(TElem) TElem buffer[Size]{};

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
			CONSTEXPR20 string(const TElem (&other)[Size]) noexcept
			{
				copy(other);
			}

			/**
			 * Copy constructor from array buffer count of characters
			 * @param other Buffer to copy from
			 * @param count Size of the buffer to copy from
			 */
			CONSTEXPR20 string(const TElem (&other)[Size], const size_type count) noexcept
			{
				copy(other, count);
			}

			/**
			 * Copy constructor from array buffer whose size is different from the string size
			 * @tparam OtherSize Size of the buffer to copy from
			 * @param other Buffer to copy from
			 */
			template <size_type OtherSize> requires (OtherSize != Size)
			CONSTEXPR20 string(const TElem (&other)[OtherSize]) noexcept
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
			CONSTEXPR20 string(const TElem (&other)[OtherSize], const size_type count) noexcept
			{
				copy(other, count);
			}


			/**
			 * Copy constructor from pointer buffer until null terminator is found or maximum size is reached (Size)
			 * @tparam TElemPtr Type of the pointer buffer (Default: const TElem* const)
			 * @param other Buffer to copy from
			 */
			template <typename TElemPtr = const TElem* const>
			requires std::is_pointer_v<TElemPtr>&&
				std::is_same_v<std::remove_const_t<std::remove_pointer_t<std::remove_const_t<std::remove_pointer_t<TElemPtr>>>>, TElem> &&
				(!std::is_array_v<TElemPtr>)
			CONSTEXPR20 string(TElemPtr other) noexcept
			{
				copy(other);
			}

			/**
			 * Copy constructor from pointer buffer count of characters
			 * @tparam TElemPtr Type of the pointer buffer (Default: const TElem* const)
			 * @param other Buffer to copy from
			 * @param count Size of the buffer to copy from
			 */
			template <typename TElemPtr = const TElem* const>
			requires std::is_pointer_v<TElemPtr> &&
				std::is_same_v<std::remove_const_t<std::remove_pointer_t<std::remove_const_t<std::remove_pointer_t<TElemPtr>>>>, TElem> &&
				(!std::is_array_v<TElemPtr>)
			CONSTEXPR20 string(TElemPtr other, const size_type count) noexcept
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
			CONSTEXPR20 string& operator=(const TElem other[Size]) noexcept
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
				CONSTEXPR20 string& operator=(const TElem other[OtherSize]) noexcept
			{
				return copy(other);
			}

			/**
			 * Copy from pointer buffer
			 * @tparam TElemPtr Type of the pointer buffer (Default: const TElem* const)
			 * @param other Buffer to copy from
			 * @return Self reference
			 */
			template <typename TElemPtr = const TElem* const>
			requires std::is_pointer_v<TElemPtr>&&
				std::is_same_v<std::remove_const_t<std::remove_pointer_t<std::remove_const_t<std::remove_pointer_t<TElemPtr>>>>, TElem> &&
				(!std::is_array_v<TElemPtr>)
			CONSTEXPR20 string& operator=(TElemPtr other) noexcept
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

			CONSTEXPR20 TElem& operator[](const size_type index) noexcept
			{
				return at(index);
			}

			CONSTEXPR20 const TElem& operator[](const size_type index) const noexcept
			{
				return at(index);
			}

			// ----- Iteration functions -----
			CONSTEXPR20 pointer begin() noexcept
			{
				return buffer;
			}

			CONSTEXPR20 const_pointer begin() const noexcept
			{
				return begin();
			}

			CONSTEXPR20 const_pointer cbegin() const noexcept
			{
				return begin();
			}

			CONSTEXPR20 pointer end() noexcept
			{
				return buffer + Size;
			}

			CONSTEXPR20 const_pointer end() const noexcept
			{
				return end();
			}

			CONSTEXPR20 const_pointer cend() const noexcept
			{
				return end();
			}

			CONSTEXPR20 pointer rbegin() noexcept
			{
				return buffer + Size - 1;
			}

			CONSTEXPR20 const_pointer rbegin() const noexcept
			{
				return rbegin();
			}

			CONSTEXPR20 const_pointer crbegin() const noexcept
			{
				return rbegin();
			}

			CONSTEXPR20 pointer rend() noexcept
			{
				return buffer - 1;
			}

			CONSTEXPR20 const_pointer rend() const noexcept
			{
				return rend();
			}

			CONSTEXPR20 const_pointer crend() const noexcept
			{
				return rend();
			}

			// ----- Copy functions from buffers -----

			/**
			 * Copy from array buffer
			 * @param other Buffer to copy from
			 * @return Self reference
			 */
			CONSTEXPR20 string& copy(const TElem(&other)[Size]) noexcept
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
					CONSTEXPR20 size_type byte_size = Size * sizeof(TElem);
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
			CONSTEXPR20 string& copy(const TElem(&other)[Size], const size_type count) noexcept
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
					const size_type byte_size = min_count * sizeof(TElem);
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
			CONSTEXPR20 string& copy(const TElem(&other)[OtherSize]) noexcept
			{
				ASSERT_ASSUME(other != nullptr);
				//[[assume(other != nullptr)]]

				CONSTEXPR20 size_type min_count = (std::min)(OtherSize, Size - 1);

				IF_CONSTEVAL
				{
					for (size_type i = 0; i < min_count; ++i) [[likely]]
					{
						buffer[i] = other[i];
					}
				}
				else
				{
					CONSTEXPR20 size_type byte_size = min_count * sizeof(TElem);
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
			CONSTEXPR20 string& copy(const TElem(&other)[OtherSize], const size_type count) noexcept
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
					const size_type byte_size = min_count * sizeof(TElem);
					std::memcpy(buffer, other, byte_size);
				}

				buffer[min_count] = '\0';

				return *this;
			}

			/**
			 * Copy from pointer buffer until null terminator is found or maximum size is reached (Size)
			 * @tparam TElemPtr Type of the pointer buffer (Default: const TElem* const)
			 * @param other Buffer to copy from
			 * @return Self reference
			 */
			template <typename TElemPtr = const TElem* const>
				requires std::is_pointer_v<TElemPtr> &&
					std::is_same_v<std::remove_const_t<std::remove_pointer_t<std::remove_const_t<std::remove_pointer_t<TElemPtr>>>>, TElem> &&
					(!std::is_array_v<TElemPtr>)
				CONSTEXPR20 string& copy(TElemPtr other) noexcept
			{
				ASSERT_ASSUME(other != nullptr);

				//[[assume(other != nullptr)]]

				IF_CONSTEVAL
				{
					size_type i = 0;

					while (i < Size - 1 && !(buffer[i] = other[i++])) [[likely]] {}

					if (i >= Size - 1)
					{
						buffer[Size - 1] = TElem{ 0 };
					}
				}
				else if CONSTEXPR17 (std::is_same_v<TElem, char>)
				{
					strcpy_s(buffer, other);
				}
				else if CONSTEXPR17 (std::is_same_v<TElem, wchar_t>)
				{
					wcscpy_s(buffer, other);
				}
				else
				{
					size_type i = 0;

					while (i < Size - 1 && !(buffer[i] = other[i++])) [[likely]] {}

					if (i >= Size - 1)
					{
						buffer[Size - 1] = TElem{ 0 };
					}
				}
				return *this;
			}

			/**
			 * Copy from pointer buffer count of characters
			 * @tparam TElemPtr Type of the pointer buffer (Default: const TElem* const)
			 * @param other Buffer to copy from
			 * @param count Size of the buffer to copy from
			 * @return Self reference
			 */
			template <typename TElemPtr = const TElem* const>
				requires std::is_pointer_v<TElemPtr>&&
			std::is_same_v<std::remove_const_t<std::remove_pointer_t<std::remove_const_t<std::remove_pointer_t<TElemPtr>>>>, TElem> &&
				(!std::is_array_v<TElemPtr>)
				CONSTEXPR20 string& copy(TElemPtr other, const size_type count) noexcept
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
				else if CONSTEXPR17(std::is_same_v<TElem, char>)
				{
					strcpy_s(buffer, other);
					}
				else if CONSTEXPR17(std::is_same_v<TElem, wchar_t>)
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

			CONSTEXPR20 TElem& at(const size_type index) noexcept
			{
				ASSERT_ASSUME(index >= 0 && index < Size);

				return buffer[index];
			}

			CONSTEXPR20 const TElem& at(const size_type index) const noexcept
			{
				ASSERT_ASSUME(index >= 0 && index < Size);

				return buffer[index];
			}

			CONSTEXPR20 string& fill(const TElem val) noexcept
			{
				IF_CONSTEVAL
				{
					for (size_type i = 0; i < Size; ++i)
					{
						buffer[i] = val;
					}
					return *this;
				}
				if CONSTEXPR17 (std::is_same_v<TElem, char>)
				{
					std::memset(buffer, val, Size);
				}
				else if CONSTEXPR17 (std::is_same_v<TElem, wchar_t>)
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

int main()
{

	constexpr woj::stack::string<char, 100> str1{ "Hello, World!" };

	constexpr  woj::stack::string<char, 100> str2{ "Hello, World!", 5 };

	constexpr  woj::stack::string<char, 100> str3{ str2.data() };

	woj::stack::string str{ "34" };

	std::cout.write(str.buffer, str.size());

	std::cout << str.size() << typeid(str.data()).name();

	//char* buffer = (char*)malloc(100);

	//strcpy(buffer, "Hello, World!");

	//woj::stack::string<char, 100> str3(buffer), str4(buffer, 5);

	return 0;
}