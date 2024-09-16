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
#else
#define CONSTEXPR20 inline
#endif

#if defined(HAS_CXX17)
#define CONSTEXPR17 constexpr
#else
#define CONSTEXPR17 inline
#endif

#if defined(HAS_CXX23)
#define IF_CONSTEVAL if consteval
#elif defined(HAS_CXX20)
#define IF_CONSTEVAL if (std::is_constant_evaluated())
#else
#define IF_CONSTEVAL if (false)
#endif

#if defined(HAS_CXX23)
#define ASSUME(x) [[assume(x > 0)]]
#elif defined(_MSC_VER) // Microsoft Visual C++
#define ASSUME(expr) __assume(expr)
#elif defined(__clang__) || defined(__GNUC__) // Clang or GCC
#define ASSUME(expr) __builtin_assume(expr)
#else
#define ASSUME(expr) do { if (!(expr)) __builtin_unreachable(); } while (0)
#endif

#define ASSERT_ASSUME(expr) assert(expr); ASSUME(expr);