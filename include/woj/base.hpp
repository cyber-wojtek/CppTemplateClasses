#pragma once

#pragma once

#ifndef WOJ_BASE_HPP
#define	WOJ_BASE_HPP
#endif

// Define version detection for MSVC (_MSVC_LANG) and GCC/Clang (__cplusplus)
#if defined(_MSC_VER)  &&defined(_MSVC_LANG)
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


#if 1 || WOJ_HAS_CXX23
#define WOJ_CONSTEXPR23 constexpr
#else
#define WOJ_CONSTEXPR23 inline
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
#include <cstdio>
#include <cstdint>
#include <compare>

namespace woj
{
	class noinit_t;

	template <typename Type>
	class is_noinit_t : std::false_type {};

	template <>
	class is_noinit_t<noinit_t> : std::true_type {};

	template <typename Type>
	constexpr bool is_noinit_t_v = is_noinit_t<Type>::value;

	/**
	 * Represents a type that is used to prevent the initialization of a variable
	 */
	class noinit_t
	{
	public:
		explicit
#if WOJ_HAS_CXX20
			consteval
#else
			constexpr
#endif
			noinit_t()
			noexcept = default;

#if WOJ_HAS_CXX20
		consteval
#else
		constexpr
#endif
			noinit_t(const noinit_t &other)
			noexcept = default;

#if WOJ_HAS_CXX20
		consteval
#else
		constexpr
#endif
			noinit_t(noinit_t &&other)
			noexcept = default;

#if WOJ_HAS_CXX20
		consteval
#else
		constexpr
#endif
			noinit_t &operator=(const noinit_t &other)
			noexcept = default;

#if WOJ_HAS_CXX20
		consteval
#else
		constexpr
#endif
			noinit_t &operator=(noinit_t &&other)
			noexcept = default;

#if WOJ_HAS_CXX20
		constexpr
#endif
			~noinit_t()
			noexcept = default;

#if WOJ_HAS_CXX20
		consteval
#else
		constexpr
#endif
			bool operator==(const noinit_t &other) const
			noexcept
		{
			return true;
		}

#if WOJ_HAS_CXX20
		consteval
#else
		constexpr
#endif
			std::strong_ordering operator<=>(const noinit_t &other) const
			noexcept
		{
			return std::strong_ordering::equal;
		}

#if WOJ_HAS_CXX20
		consteval
#else
		constexpr
#endif
			operator bool() const
			noexcept
		{
			return false;
		}
	};

	/**
	 * Represents a constant that is used to prevent the initialization of a class
	 */
	constexpr noinit_t noinit{};

	class none_t;

	template <typename Type>
	class is_none_t : std::false_type {};

	template <>
	class is_none_t<none_t> : std::true_type {};

	template <typename Type>
	constexpr bool is_none_t_v = is_none_t<Type>::value;

	/**
	 * Represents a type that is used to construct class without any value
	 */
	class none_t
	{
	public:
		explicit 
#if WOJ_HAS_CXX20
		consteval
#else
		constexpr
#endif
			none_t() 
			noexcept = default;

#if WOJ_HAS_CXX20
		consteval
#else
		constexpr
#endif
			none_t(const none_t &other) 
			noexcept = default;

#if WOJ_HAS_CXX20
		consteval
#else
		constexpr
#endif
			none_t(none_t &&other) 
			noexcept = default;

#if WOJ_HAS_CXX20
		consteval
#else
		constexpr
#endif
			none_t &operator=(const none_t &other) 
			noexcept = default;

#if WOJ_HAS_CXX20
		consteval
#else
		constexpr
#endif
			none_t &operator=(none_t &&other)
			noexcept = default;

#if WOJ_HAS_CXX20
		constexpr
#endif
			~none_t() 
			noexcept = default;

#if WOJ_HAS_CXX20
		consteval
#else
		constexpr
#endif
			bool operator==(const none_t &other) const 
			noexcept 
		{ 
			return true; 
		}

#if WOJ_HAS_CXX20
		consteval
#else
		constexpr
#endif
			std::strong_ordering operator<=>(const none_t &other) const 
			noexcept 
		{
			return std::strong_ordering::equal; 
		}

#if WOJ_HAS_CXX20
		consteval
#else
		constexpr
#endif
			operator bool() const 
			noexcept 
		{ 
			return false; 
		}
	};

	/**
	 * Represents a constant that is used to construct an empty/unset value.
	 */
	constexpr none_t none{};

	class empty_t;

	template <typename Type>
	class is_empty_t : std::false_type {};

	template <>
	class is_empty_t<empty_t> : std::true_type {};

	template <typename Type>
	constexpr bool is_empty_t_v = is_empty_t<Type>::value;

	/**
	 * Represents a type that is to be used as a placeholder for when empty constructor like '{}' may be desired (e.g. 'std::initializer_list' - like with no elements)
	 */
	class empty_t
	{
	public:
#if WOJ_HAS_CXX20
		consteval
#else
		constexpr
#endif
			empty_t() 
			noexcept = default;

#if WOJ_HAS_CXX20
		consteval
#else
		constexpr
#endif
			empty_t(const empty_t &other)
			noexcept = default;

#if WOJ_HAS_CXX20
		consteval
#else
		constexpr
#endif
			empty_t(empty_t &&other)
			noexcept = default;

#if WOJ_HAS_CXX20
		consteval
#else
		constexpr
#endif
			empty_t &operator=(const empty_t &other)
			noexcept = default;

#if WOJ_HAS_CXX20
		consteval
#else
		constexpr
#endif
			empty_t &operator=(empty_t &&other)
			noexcept = default;

#if WOJ_HAS_CXX20
		constexpr
#endif
			~empty_t()
			noexcept = default;

#if WOJ_HAS_CXX20
		consteval
#else
		constexpr
#endif
			bool operator==(const empty_t &other) const
			noexcept
		{
			return true;
		}

#if WOJ_HAS_CXX20
		consteval
#else
		constexpr
#endif
			std::strong_ordering operator<=>(const empty_t &other) const
			noexcept
		{
			return std::strong_ordering::equal;
		}

#if WOJ_HAS_CXX20
		consteval
#else
		constexpr
#endif
			operator bool() const
			noexcept
		{
			return false;
		}
	};

	class in_place_t;

	template <typename Type>
	class is_in_place : std::false_type {};

	template <>
	class is_in_place<in_place_t> : std::true_type {};

	template <typename Type>
	constexpr bool is_in_place_v = is_in_place<Type>::value;

	class in_place_t
	{
	public:
		explicit
#if WOJ_HAS_CXX20
		consteval
#else
		constexpr
#endif
			in_place_t()
			noexcept = default;

#if WOJ_HAS_CXX20
		consteval
#else
		constexpr
#endif
			in_place_t(const in_place_t &other)
			noexcept = default;

#if WOJ_HAS_CXX20
		consteval
#else
		constexpr
#endif
			in_place_t(in_place_t &&other)
			noexcept = default;

#if WOJ_HAS_CXX20
		consteval
#else
		constexpr
#endif
			in_place_t &operator=(const in_place_t &other)
			noexcept = default;

#if WOJ_HAS_CXX20
		consteval
#else
		constexpr
#endif
			in_place_t &operator=(in_place_t &&other)
			noexcept = default;

#if WOJ_HAS_CXX20
		constexpr
#endif
			~in_place_t()
			noexcept = default;

#if WOJ_HAS_CXX20
		consteval
#else
		constexpr
#endif
			bool operator==(const in_place_t &other) const
			noexcept
		{
			return true;
		}

#if WOJ_HAS_CXX20
		consteval
#else
		constexpr
#endif
			std::strong_ordering operator<=>(const in_place_t &other) const
			noexcept
		{
			return std::strong_ordering::equal;
		}

#if WOJ_HAS_CXX20
		consteval
#else
		constexpr
#endif
			operator bool() const
			noexcept
		{
			return false;
		}
	};

	constexpr in_place_t in_place{};

	class invalid_t;

	template <typename Type>
	class is_invalid_t : std::false_type {};

	template <>
	class is_invalid_t<invalid_t> : std::true_type {};

	template <typename Type>
	constexpr bool is_invalid_t_v = is_invalid_t<Type>::value;

	class invalid_t
	{
	public:
		explicit
#if WOJ_HAS_CXX20
			consteval
#else
			constexpr
#endif
			invalid_t()
			noexcept = default;

#if WOJ_HAS_CXX20
		consteval
#else
		constexpr
#endif
			invalid_t(const invalid_t &other)
			noexcept = default;

#if WOJ_HAS_CXX20
		consteval
#else
		constexpr
#endif
			invalid_t(invalid_t &&other)
			noexcept = default;

#if WOJ_HAS_CXX20
		consteval
#else
		constexpr
#endif
			invalid_t &operator=(const invalid_t &other)
			noexcept = default;

#if WOJ_HAS_CXX20
		consteval
#else
		constexpr
#endif
			invalid_t &operator=(invalid_t &&other)
			noexcept = default;

#if WOJ_HAS_CXX20
		constexpr
#endif
			~invalid_t()
			noexcept = default;

#if WOJ_HAS_CXX20
		consteval
#else
		constexpr
#endif
			bool operator==(const invalid_t &other) const
			noexcept
		{
			return true;
		}

#if WOJ_HAS_CXX20
		consteval
#else
		constexpr
#endif
			std::strong_ordering operator<=>(const invalid_t &other) const
			noexcept
		{
			return std::strong_ordering::equal;
		}

#if WOJ_HAS_CXX20
		consteval
#else
		constexpr
#endif
			operator bool() const
			noexcept
		{
			return false;
		}
	};

	constexpr invalid_t invalid{};

	class dynamic_states_t
	{
	public:
		explicit
#if WOJ_HAS_CXX20
			consteval
#else
			constexpr
#endif
			dynamic_states_t()
			noexcept = default;

#if WOJ_HAS_CXX20
		consteval
#else
		constexpr
#endif
			dynamic_states_t(const dynamic_states_t &other)
			noexcept = default;

#if WOJ_HAS_CXX20
		consteval
#else
		constexpr
#endif
			dynamic_states_t(dynamic_states_t &&other)
			noexcept = default;

#if WOJ_HAS_CXX20
		consteval
#else
		constexpr
#endif
			dynamic_states_t &operator=(const dynamic_states_t &other)
			noexcept = default;

#if WOJ_HAS_CXX20
		consteval
#else
		constexpr
#endif
			dynamic_states_t &operator=(dynamic_states_t &&other)
			noexcept = default;

#if WOJ_HAS_CXX20
		constexpr
#endif
			~dynamic_states_t()
			noexcept = default;

#if WOJ_HAS_CXX20
		consteval
#else
		constexpr
#endif
			bool operator==(const dynamic_states_t &other) const
			noexcept
		{
			return true;
		}

#if WOJ_HAS_CXX20
		consteval
#else
		constexpr
#endif
			std::strong_ordering operator<=>(const dynamic_states_t &other) const
			noexcept
		{
			return std::strong_ordering::equal;
		}

#if WOJ_HAS_CXX20
		consteval
#else
		constexpr
#endif
			operator bool() const
			noexcept
		{
			return false;
		}
	};

	inline constexpr dynamic_states_t dynamic_states{};

	class delimiter_t;

	template <typename Type>
	class is_delimiter_t : std::false_type {};

	template <>
	class is_delimiter_t<delimiter_t> : std::true_type {};

	template <typename Type>
	constexpr bool is_delimiter_t_v = is_delimiter_t<Type>::value;

	class delimiter_t
	{
	public:
#if WOJ_HAS_CXX20
			consteval
#else
			constexpr
#endif
			delimiter_t()
			noexcept = default;

#if WOJ_HAS_CXX20
		consteval
#else
		constexpr
#endif
			delimiter_t(const delimiter_t &other)
			noexcept = default;

#if WOJ_HAS_CXX20
		consteval
#else
		constexpr
#endif
			delimiter_t(delimiter_t &&other)
			noexcept = default;

#if WOJ_HAS_CXX20
		consteval
#else
		constexpr
#endif
			delimiter_t &operator=(const delimiter_t &other)
			noexcept = default;

#if WOJ_HAS_CXX20
		consteval
#else
		constexpr
#endif
			delimiter_t &operator=(delimiter_t &&other)
			noexcept = default;

#if WOJ_HAS_CXX20
		constexpr
#endif
			~delimiter_t()
			noexcept = default;

#if WOJ_HAS_CXX20
		consteval
#else
		constexpr
#endif
			bool operator==(const delimiter_t &other) const
			noexcept
		{
			return true;
		}

#if WOJ_HAS_CXX20
		consteval
#else
		constexpr
#endif
			std::strong_ordering operator<=>(const delimiter_t &other) const
			noexcept
		{
			return std::strong_ordering::equal;
		}

#if WOJ_HAS_CXX20
		consteval
#else
		constexpr
#endif
			operator bool() const
			noexcept
		{
			return false;
		}
	};

	constexpr delimiter_t delimiter{};

	/**
	 * Function that checks if the m_function is being evaluated at compile-time.
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
#elif (defined(__clang__)  &&|| __clang_major__ >= 10) || (defined(__GNUC__)  &&__GNUC__ >= 10) || (defined(__INTEL_COMPILER)  &&__INTEL_COMPILER >= 2005)
		return __builtin_is_constant_evaluated();
#else
		return false;
#endif
	}

	class exception {
	public:
		char* m_message;
		char* m_file;
		char* m_function;
		size_t m_line;
		bool m_manage;
		mutable char* m_what_buffer;

		constexpr exception() noexcept
			: m_message(nullptr), m_file(nullptr), m_function(nullptr), m_line(0), m_manage(false), m_what_buffer(nullptr) {}

		constexpr exception(const size_t line, const char* const msg, const char* const file, const char* const function) noexcept
			: m_message(msg ? copy_string(msg) : nullptr), m_file(file ? copy_string(file) : nullptr), m_function(function ? copy_string(function) : nullptr), m_line(line), m_manage(true), m_what_buffer(nullptr) {}

		constexpr exception(const exception &other) noexcept
			: m_message(other.m_message ? copy_string(other.m_message) : nullptr), m_file(other.m_file ? copy_string(other.m_file) : nullptr), m_function(other.m_function ? copy_string(other.m_function) : nullptr), m_line(other.m_line), m_manage(true), m_what_buffer(nullptr) {}

		constexpr exception(exception &&other) noexcept
			: m_message(other.m_message), m_file(other.m_file), m_function(other.m_function), m_line(other.m_line), m_manage(other.m_manage), m_what_buffer(other.m_what_buffer) {
			other.m_message = other.m_file = other.m_function = nullptr;
			other.m_manage = false;
			other.m_what_buffer = nullptr;
		}

		virtual ~exception() noexcept {
			clear();
			delete[] m_what_buffer;
		}

		constexpr exception &operator=(const exception &other) noexcept {
			if (this != &other) {
				clear();
				m_message = copy_string(other.m_message);
				m_file = copy_string(other.m_file);
				m_function = copy_string(other.m_function);
				m_line = other.m_line;
				m_manage = true;
			}
			return *this;
		}

		constexpr exception &operator=(exception &&other) noexcept {
			if (this != &other) {
				clear();
				m_message = other.m_message;
				m_file = other.m_file;
				m_function = other.m_function;
				m_line = other.m_line;
				m_manage = other.m_manage;
				m_what_buffer = other.m_what_buffer;

				other.m_message = other.m_file = other.m_function = nullptr;
				other.m_manage = false;
				other.m_what_buffer = nullptr;
			}
			return *this;
		}

		WOJ_NODISCARD const char* message() const noexcept { return m_message; }
		WOJ_NODISCARD size_t line() const noexcept { return m_line; }
		WOJ_NODISCARD const char* file() const noexcept { return m_file; }
		WOJ_NODISCARD const char* function() const noexcept { return m_function; }

		WOJ_NODISCARD const char* what() const noexcept {
			if (!m_what_buffer) {
				const size_t size = std::strlen(file()) + std::strlen(function()) + std::strlen(message()) + 32;
				m_what_buffer = new char[size];
				std::sprintf(m_what_buffer, "%s:%zu: %s: %s", file(), line(), function(), message());
			}
			return m_what_buffer;
		}

	private:
		constexpr void clear() noexcept {
			if (m_manage) {
				delete[] m_message;
				delete[] m_file;
				delete[] m_function;
			}
			m_message = m_file = m_function = nullptr;
			m_manage = false;
			m_line = 0;
		}

		static constexpr char* copy_string(const char* source) noexcept {
			if (!source) return nullptr;
			size_t length = std::strlen(source);
			char* copy = new char[length + 1];
			std::memcpy(copy, source, length);
			copy[length] = '\0';
			return copy;
		}
	};
}
