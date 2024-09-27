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

#if __cpp_if_constexpr	>= 201606L
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