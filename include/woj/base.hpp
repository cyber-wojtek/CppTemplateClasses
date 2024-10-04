#pragma once

#pragma once

#ifndef WOJ_BASE_HPP
#define	WOJ_BASE_HPP
#endif

// Define version detection for MSVC (_MSVC_LANG) and GCC/Clang (__cplusplus)
#if defined(_MSC_VER) && defined(_MSVC_LANG)
#define CPP_VERSION _MSVC_LANG
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)
#else
#define CPP_VERSION __cplusplus
#endif

// Check for C++ version and define corresponding macros
#if CPP_VERSION >= 202602L
#define HAS_CXX26 1
#endif

#if CPP_VERSION >= 202302L
#define HAS_CXX23 1
#endif

#if CPP_VERSION >= 202002L
#define HAS_CXX20 1
#endif

#if CPP_VERSION >= 201703L
#define HAS_CXX17 1
#endif

#ifdef HAS_CXX17
#define INLINE_VAR17 inline
#else
#define INLINE_VAR17
#endif

// Define CONSTEXPR macros based on detected C++ version
#if defined(HAS_CXX26)
#define CONSTEXPR26 constexpr
#define IF_HAS_CXX26_(...) if constexpr (true && __VA_ARGS__)
#define IF_HAS_CXX26 if constexpr (true)
#else
#define CONSTEXPR26 inline
#endif

#if defined(HAS_CXX23)
#define CONSTEXPR23 constexpr
#define IF_HAS_CXX23_(...) if constexpr (true && __VA_ARGS__)
#define IF_HAS_CXX23 if constexpr (true)
#else
#define CONSTEXPR23 inline
#endif

#if defined(HAS_CXX20)
#define CONSTEXPR20 constexpr
#define CONSTEVAL20 consteval
#define IF_HAS_CXX20_(...) if constexpr (true __VA_ARGS__)
#define IF_HAS_CXX20 if constexpr (true)
#else
#define CONSTEXPR20 inline
#define CONSTEVAL20 inline
#endif

#if defined(HAS_CXX17)
#define CONSTEXPR17  constexpr
#define IF_HAS_CXX17_(...) if constexpr (true __VA_ARGS__)
#define IF_HAS_CXX17 if constexpr (true)
#else
#define CONSTEXPR17 inline
#define IF_HAS_CXX17_(...) if (false __VA_ARGS__)
#define IF_HAS_CXX17 if (false)
#endif

#if __has_cpp_attribute(likely) >= 201803L
#define LIKELY [[likely]]
#else
#define LIKELY
#endif

#if __has_cpp_attribute(unlikely) >= 201803L
#define UNLIKELY [[unlikely]]
#else
#define UNLIKELY
#endif

#if __has_cpp_attribute(nodiscard) >= 201603L
#define NODISCARD [[nodiscard]]
#else
#define NODISCARD
#endif

#if __has_cpp_attribute(nodiscard) >= 201907L
#define NODISCARD_(msg) [[nodiscard(msg)]]
#else
#define NODISCARD_(msg) NODISCARD
#endif

#if __has_cpp_attribute(maybe_unused) >= 201603L
#define MAYBE_UNUSED [[maybe_unused]]
#else
#define MAYBE_UNUSED
#endif

#if __has_cpp_attribute(deprecated) >= 201309L
#define DEPRECATED [[deprecated]]
#define DEPRECATED_(msg) [[deprecated(msg)]]
#else
#define DEPRECATED
#define DEPRECATED_(msg)
#endif

#if __has_cpp_attribute(fallthrough) >= 201603L
#define FALLTHROUGH [[fallthrough]]
#else
#define FALLTHROUGH
#endif

#if __has_cpp_attribute(noreturn) >= 200809L
#define NORETURN [[noreturn]]
#else
#define NORETURN
#endif

#if __has_cpp_attribute(carries_dependency) >= 200809L
#define CARRIES_DEPENDENCY [[carries_dependency]]
#else
#define CARRIES_DEPENDENCY
#endif

#if __has_cpp_attribute(indeterminate) >= 202106L
#define INDETERMINATE [[indeterminate]]
#else
#define INDETERMINATE
#endif

#if __has_cpp_attribute(assume) >= 202207L
#define ASSUME(...) [[assume(__VA_ARGS__)]]
#elif defined(_MSC_VER) // Microsoft Visual C++
#define ASSUME(...) __assume(__VA_ARGS__)
#elif defined(__clang__) || defined(__INTEL_COMPILER) // LLVMs
#define ASSUME(...) __builtin_assume(__VA_ARGS__)
#elif defined(__GNUC__)
#if __GNUC__ >= 13
#define ASSUME(...) __attribute__((__assume__(__VA_ARGS__)))
#else
#define ASSUME(...) do { if (!(__VA_ARGS__)) __builtin_unreachable(); } while (false);
#endif
#endif

#if __cpp_if_constexpr >= 201606L
#define IF_CONSTEXPR(...) if constexpr (__VA_ARGS__)
#else
#define IF_CONSTEXPR(...) if (__VA_ARGS__)
#endif

#if !defined(HAS_CXX26)
#define IF_HAS_CXX26_(...) IF_CONSTEXPR (false __VA_ARGS__)
#define IF_HAS_CXX26 IF_CONSTEXPR (false)
#endif

#if !defined(HAS_CXX23)
#define IF_HAS_CXX23_(...) IF_CONSTEXPR (false __VA_ARGS__)
#define IF_HAS_CXX23 IF_CONSTEXPR (false)
#endif

#if !defined(HAS_CXX20)
#define IF_HAS_CXX20_(...) IF_CONSTEXPR (false __VA_ARGS__)
#define IF_HAS_CXX20 IF_CONSTEXPR (false)
#endif

#define ASSERT_ASSUME(...) assert(__VA_ARGS__); ASSUME(__VA_ARGS__);

#include <cstring>
#include <type_traits>

namespace woj
{
	/**
	 * Represents a type that is used to prevent the initialization of a variable
	 */
	struct noinit_t
	{
		explicit constexpr noinit_t() noexcept {}
	};

	/**
	 * Represents a constant that is used to prevent the initialization of a variable
	 */
	constexpr noinit_t noinit{};

	/**
	 * Represents a type that is used to construct class without any value or construct builtin types with 0
	 */
	struct null_t
	{
		explicit constexpr null_t() noexcept {}
	};

	/**
	 * Represents a constant that is used to construct an empty value.
	 */
	constexpr null_t null{};

	struct in_place_t
	{
		explicit constexpr in_place_t() noexcept {}
	};

	constexpr in_place_t in_place{};

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
		char* const message;

		constexpr exception() noexcept : message{ nullptr } {}

		exception(const exception& other) noexcept : message{ new char[strlen(other.message)] }
		{
			strcpy(message, other.message);
		}

		constexpr exception(exception&& other) noexcept : message{ other.message } {}

		explicit exception(const char* const msg) noexcept : message{ new char[strlen(msg)] }
		{
			strcpy(message, msg);
		}

		constexpr exception(const char* const msg, const size_t size) noexcept : message{ new char[size] }
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

		explicit constexpr exception(char* const&& msg) noexcept : message{ msg } {}

		constexpr exception(char* const&& msg, const size_t) noexcept : message{ msg } {}

		virtual CONSTEXPR20 ~exception() noexcept
		{
			delete[] message;
		}

	    NODISCARD virtual const char* what() const noexcept
		{
			return message ? message : "Unknown exception.";
		}
	};
}
