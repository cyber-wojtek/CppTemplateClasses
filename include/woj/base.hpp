#pragma once

#pragma once

#ifndef WOJ_BASE_HPP
#define	WOJ_BASE_HPP
#endif

// Define version detection for MSVC (_MSVC_LANG) and GCC/Clang (__cplusplus)
#if defined(_MSC_VER) && defined(_MSVC_LANG)
#define WOJ_CPP_VERSION _MSVC_LANG
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)
#else
#define WOJ_CPP_VERSION __cplusplus
#endif

// Check for C++ version and define corresponding macros
#if WOJ_CPP_VERSION >= 202602L
#define WOJ_HAS_CXX26 1
#endif

#if WOJ_CPP_VERSION >= 202302L
#define WOJ_HAS_CXX23 1
#endif

#if WOJ_CPP_VERSION >= 202002L
#define WOJ_HAS_CXX20 1
#endif

#if 1 || defined(WOJ_HAS_CXX23)
#define WOJ_CONSTEXPR23 constexpr
#else
#define WOJ_CONSTEXPR23 inline
#endif

#if defined(WOJ_HAS_CXX20)
#define WOJ_CONSTEXPR20 constexpr
#define WOJ_CONSTEVAL20 consteval
#define WOJ_CONSTEVAL consteval
#else
#define WOJ_CONSTEXPR20 inline
#define WOJ_CONSTEVAL20 inline
#define WOJ_CONSTEVAL constexpr
#endif


#if __has_cpp_attribute(likely) >= 201803L
#define WOJ_LIKELY [[likely]]
#else
#define WOJ_LIKELY
#endif

#if __has_cpp_attribute(unlikely) >= 201803L
#define WOJ_UNLIKELY [[unlikely]]
#else
#define WOJ_UNLIKELY
#endif

#if __has_cpp_attribute(nodiscard) >= 201603L
#define WOJ_NODISCARD [[nodiscard]]
#else
#define WOJ_NODISCARD
#endif

#if __has_cpp_attribute(nodiscard) >= 201907L
#define WOJ_NODISCARD_MSG(msg) [[nodiscard(msg)]]
#else
#define WOJ_NODISCARD_MSG(msg) WOJ_NODISCARD
#endif

#if __has_cpp_attribute(maybe_unused) >= 201603L
#define WOJ_MAYBE_UNUSED [[maybe_unused]]
#else
#define WOJ_MAYBE_UNUSED
#endif

#if __has_cpp_attribute(deprecated) >= 201309L
#define WOJ_DEPRECATED [[deprecated]]
#define WOJ_DEPRECATED_MSG(msg) [[deprecated(msg)]]
#else
#define WOJ_DEPRECATED
#define WOJ_DEPRECATED_MSG(msg)
#endif

#if __has_cpp_attribute(fallthrough) >= 201603L
#define WOJ_FALLTHROUGH [[fallthrough]]
#else
#define WOJ_FALLTHROUGH
#endif

#if __has_cpp_attribute(noreturn) >= 200809L
#define WOJ_NORETURN [[noreturn]]
#else
#define WOJ_NORETURN
#endif

#if __has_cpp_attribute(carries_dependency) >= 200809L
#define WOJ_CARRIES_DEPENDENCY [[carries_dependency]]
#else
#define WOJ_CARRIES_DEPENDENCY
#endif

#if __has_cpp_attribute(indeterminate) >= 202106L
#define WOJ_INDETERMINATE [[indeterminate]]
#else
#define WOJ_INDETERMINATE
#endif

#if __has_cpp_attribute(assume) >= 202207L
#define WOJ_ASSUME(...) [[assume(__VA_ARGS__)]]
#elif defined(_MSC_VER) // Microsoft Visual C++
#define WOJ_ASSUME(...) __assume(__VA_ARGS__)
#elif defined(__clang__) || defined(__INTEL_COMPILER) // LLVMs
#define WOJ_ASSUME(...) __builtin_assume(__VA_ARGS__)
#elif defined(__GNUC__)
#if __GNUC__ >= 13
#define WOJ_ASSUME(...) __attribute__((__assume__(__VA_ARGS__)))
#else
#define WOJ_ASSUME(...) do { if (!(__VA_ARGS__)) __builtin_unreachable(); } while (false);
#endif
#else
#define WOJ_ASSUME(...) void(0);
#endif

#ifdef _MSC_VER
#define WOJ_ALWAYS_INLINE __forceinline
#elif defined(__clang__) || defined(__INTEL_COMPILER) || defined(__GNUC__)
#define WOJ_ALWAYS_INLINE __attribute__((always_inline))
#else
#define WOJ_ALWAYS_INLINE inline
#endif

#define WOJ_ASSERT_ASSUME(...) assert(__VA_ARGS__); WOJ_ASSUME(__VA_ARGS__);

#include <cstring>
#include <string>
#include <type_traits>

namespace woj
{
	/**
	 * Represents a type that is used to prevent the initialization of a variable
	 */
	struct noinit_t
	{
		explicit constexpr noinit_t() noexcept = default;
	};

	/**
	 * Represents a constant that is used to prevent the initialization of a variable
	 */
	constexpr noinit_t noinit{};

	/**
	 * Represents a type that is used to construct class without any value
	 */
	struct none_t
	{
		explicit constexpr none_t() noexcept = default;
	};

	/**
	 * Represents a constant that is used to construct an empty value.
	 */
	constexpr none_t none{};

	/**
	 * Represents a type that is to be used as a placeholder for when empty constructor like '{}' may be problematic.
	 */
	struct empty_t
	{
		constexpr empty_t() noexcept = default;
	};

	struct in_place_t
	{
		explicit constexpr in_place_t() noexcept = default;
	};

	constexpr in_place_t in_place{};

	class dynamic_states_t
	{
	public:
		explicit constexpr dynamic_states_t() noexcept = default;
	};

	inline constexpr dynamic_states_t dynamic_states{};

	/**
	 * Function that checks if the function is being evaluated at compile-time.
	 * @return True if the function is being evaluated at compile-time, false otherwise.
	 */
	constexpr bool is_constant_evaluated()
	{
#if __cpp_if_consteval >= 202106L
		if consteval
		{
			return true;
		}
		return false;
#elif __cpp_lib_is_constant_evaluated >= 201811L
		return std::is_constant_evaluated();
#elif defined(_MSC_VER)
		return std::_Is_constant_evaluated();
#elif (defined(__clang__) && || __clang_major__ >= 10) || (defined(__GNUC__) && __GNUC__ >= 10) || (defined(__INTEL_COMPILER) && __INTEL_COMPILER >= 2005)
		return __builtin_is_constant_evaluated();
#else
		return false;
#endif
	}

	class exception
	{
	public:
		char* message;
		bool manage;

		constexpr exception() noexcept : message{ nullptr }, manage{ false } {}

		constexpr exception(const exception& other) noexcept
			: message{ new char[std::char_traits<char>::length(other.message) + 1] }, manage{ true } // Allocate space for null terminator
		{
			// Ensure proper copying depending on whether we're in a constant evaluation context
			if (is_constant_evaluated()) {
				// Manually copy characters to ensure null termination
				size_t i;
				for (i = 0; other.message[i] != '\0'; ++i) {
					message[i] = other.message[i];
				}
				message[i] = '\0'; // Ensure null termination
			}
			else {
				std::strcpy(message, other.message); // Copy using std::strcpy which handles null termination
			}
		}

		constexpr exception(exception&& other) noexcept : message{ other.message }, manage{ true }
		{
			other.message = nullptr;
			other.manage = false;
		}

		explicit constexpr exception(const char* const msg) noexcept : message{ new char[std::char_traits<char>::length(msg) + 1] }, manage{ true }
		{
			// Ensure proper copying depending on whether we're in a constant evaluation context
			if (is_constant_evaluated()) {
				// Manually copy characters to ensure null termination
				size_t i;
				for (i = 0; msg[i] != '\0'; ++i) {
					message[i] = msg[i];
				}
				message[i] = '\0'; // Ensure null termination
			}
			else {
				std::strcpy(message, msg); // Copy using std::strcpy which handles null termination
			}
		}

		constexpr exception(const char* const msg, const size_t size) noexcept : message{ new char[size] }, manage{ true }
		{
			if (is_constant_evaluated())
			{
				for (size_t i = 0; i < size; ++i)
				{
					message[i] = msg[i];
				}
			}
			else
			{
				memcpy(message, msg, size * sizeof(char));
			}
		}

		explicit constexpr exception(char*&& msg) noexcept : message{ msg }, manage{ true }
		{
			msg = nullptr;
		}

		constexpr exception(char*&& msg, const size_t) noexcept : message{ msg }, manage{ true }
		{
			msg = nullptr;
		}

		virtual WOJ_CONSTEXPR20 ~exception() noexcept
		{
			if (manage)
			{
				delete[] message;
			}
		}

		constexpr exception& operator=(const exception& other) noexcept
		{
			if (this == &other)
			{
				return *this;
			}

			if (manage)
			{
				delete[] message;
			}

			manage = true;

			size_t size;

			if (is_constant_evaluated())
			{
				for (size = 0; other.message[size]; ++size);
			}
			else
			{
				size = strlen(other.message);
			}
			message = new char[size];
			if (is_constant_evaluated())
			{
				for (size_t i = 0; i < size; ++i)
				{
					message[i] = other.message[i];
				}
			}
			else
			{
				memcpy(message, other.message, size * sizeof(char));
			}

			return *this;
		}
		constexpr exception& operator=(exception&& other) noexcept
		{
			message = other.message;
			other.message = nullptr;

			manage = true;
			other.manage = false;

			return *this;
		}

	    WOJ_NODISCARD virtual const char* what() const noexcept
		{
			return message ? message : "Unknown exception.";
		}
	};
}
