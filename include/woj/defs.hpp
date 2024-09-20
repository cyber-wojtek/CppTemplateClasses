#pragma once

#ifndef WOJ_DEFS_HPP
#define	WOJ_DEFS_HPP
#endif

// Define version detection for MSVC (_MSVC_LANG) and GCC/Clang (__cplusplus)
#if defined(_MSC_VER) && defined(_MSVC_LANG)
	#define CPP_VERSION _MSVC_LANG
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
#else
	#define CONSTEXPR26 inline
#endif

#if defined(HAS_CXX23)
	#define CONSTEXPR23 constexpr
#else
	#define CONSTEXPR23 inline
#endif

#if defined(HAS_CXX20)
	#define CONSTEXPR20 constexpr
	#define CONSTEVAL20 consteval
	#define LIKELY [[likely]]
	#define UNLIKELY [[unlikely]]
#else
	#define CONSTEXPR20 inline
	#define CONSTEVAL20 inline
	#define LIKELY
	#define UNLIKELY
#endif

#if defined(HAS_CXX17)
	#define CONSTEXPR17    constexpr
	#define IF_CONSTEXPR17 if constexpr
	#define NODISCARD17 [[nodiscard]]
#else
	#define CONSTEXPR17 inline
	#define IF_CONSTEXPR17 if (false)
	#define NODISCARD17
#endif

#if defined(HAS_CXX23)
	#define IF_CONSTEVAL if consteval
#elif defined(HAS_CXX20)
	#define IF_CONSTEVAL if (std::is_constant_evaluated())
#else
	#define IF_CONSTEVAL if (false)
#endif

#if defined(HAS_CXX23)
	#define ASSUME(...) [[assume(__VA_ARGS__)]]
#elif defined(_MSC_VER) // Microsoft Visual C++
	#define ASSUME(...) __assume(__VA_ARGS__)
#elif defined(__clang__) // Clang
	#define ASSUME(...) __builtin_assume(__VA_ARGS__)
#elif defined(__GNUC__)
	#if __GNUC__ >= 13
		#define ASSUME(...) __attribute__((__assume__(__VA_ARGS__)))
	#else
		#define ASSUME(...) do { if (!(__VA_ARGS__)) __builtin_unreachable(); } while (false);
	#endif
#endif
#define ASSERT_ASSUME(...) assert(__VA_ARGS__); ASSUME(__VA_ARGS__);