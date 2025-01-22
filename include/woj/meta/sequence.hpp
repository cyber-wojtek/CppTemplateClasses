#pragma once

#include <type_traits>
#include <algorithm>
#include <utility>
#include "../base.hpp"
#include "../vector.hpp"

namespace woj::meta
{
	class out_of_sequence_range final : public exception
	{
	public:
		constexpr out_of_sequence_range() noexcept : exception{ static_cast<uint64_t>(-1), "Out of sequence range", nullptr, nullptr } {}

		constexpr out_of_sequence_range(const size_t line, const char* const file, const char* const function) noexcept : exception{ line, "Out of sequence range", file, function } {}
	};

	template <typename... Types>
	class type_sequence
	{
	public:
		constexpr type_sequence() noexcept = default;

		explicit constexpr type_sequence(none_t) noexcept {}

		explicit constexpr type_sequence(noinit_t) noexcept {}

		constexpr type_sequence(const type_sequence&) noexcept = default;

		constexpr type_sequence(type_sequence&&) noexcept = delete;

		explicit constexpr operator bool() const noexcept
		{
			return static_cast<bool>(sizeof...(Types));
		}

		constexpr type_sequence& operator=(const type_sequence&) = delete;

		constexpr type_sequence& operator=(type_sequence&&) = delete;

		WOJ_CONSTEXPR20 ~type_sequence() noexcept = default;

#if WOJ_HAS_CXX20
		WOJ_CONSTEVAL20
#else
		constexpr
#endif
			static size_t size() noexcept
		{
			return sizeof...(Types);
		}

#if WOJ_HAS_CXX20
		WOJ_CONSTEVAL20
#else
		constexpr
#endif
			static size_t max_size() noexcept
		{
			return sizeof...(Types);
		}

		template <size_t Index>
		using at = std::tuple_element_t<Index, std::tuple<Types...>>;
	};

	template <>
	class type_sequence<>
	{
	public:
		constexpr type_sequence() noexcept = default;

		explicit constexpr type_sequence(none_t) noexcept {}

		explicit constexpr type_sequence(noinit_t) noexcept {}

		constexpr type_sequence(const type_sequence&) noexcept = default;

		constexpr type_sequence(type_sequence&&) noexcept = delete;

		explicit constexpr operator bool() const noexcept
		{
			return false;
		} 

		constexpr type_sequence& operator=(const type_sequence&) = delete;

		constexpr type_sequence& operator=(type_sequence&&) = delete;

		WOJ_CONSTEXPR20 ~type_sequence() noexcept = default;

#if WOJ_HAS_CXX20
		WOJ_CONSTEVAL20
#else
		constexpr
#endif
			static size_t size() noexcept
		{
			return 0;
		}

#if WOJ_HAS_CXX20
		WOJ_CONSTEVAL20
#else
		constexpr
#endif
			static size_t max_size() noexcept
		{
			return 0;
		}

		template <size_t Index>
		using at = none_t;
	};

	template <size_t Index, typename... Types>
	class type_sequence_at_impl
	{
	public:
		using type = std::tuple_element_t<Index, std::tuple<Types...>>;

		constexpr type_sequence_at_impl() noexcept = default;

		explicit constexpr type_sequence_at_impl(const type_sequence<Types...>&) noexcept {}
	};

	template <size_t Index, typename TypeSequence>
	class type_sequence_at
	{
	public:
		using type = type_sequence_at_impl<Index>::type;

#if WOJ_HAS_CXX20
		WOJ_CONSTEVAL20
#else
		constexpr
#endif
			type_sequence_at() noexcept = default;
	};

	template <auto... Values>
	class value_sequence
	{
	public:
		constexpr value_sequence() noexcept = default;

		explicit constexpr value_sequence(none_t) noexcept {}

		explicit constexpr value_sequence(noinit_t) noexcept {}

		constexpr value_sequence(const value_sequence&) noexcept = default;

		constexpr value_sequence(value_sequence&&) noexcept = delete;

		explicit constexpr operator bool() const noexcept
		{
			return static_cast<bool>(sizeof...(Values));
		}

		constexpr value_sequence& operator=(const value_sequence&) = delete;

		constexpr value_sequence& operator=(value_sequence&&) = delete;

		WOJ_CONSTEXPR20 ~value_sequence() noexcept = default;

		template <size_t Index>
#ifdef HAS_CXX20
		WOJ_CONSTEVAL20
#else
		constexpr
#endif
			static auto at() noexcept
#ifndef NDEBUG
			(Index < sizeof...(Values))
#endif
		{
			if constexpr (Index < sizeof...(Values))
			{
				return std::get<Index>(std::make_tuple(Values...));
			}
			else
			{
#ifndef NDEBUG
				throw out_of_sequence_range(116, "value_sequence.hpp", "woj::meta::value_sequence<Values...>::at_impl<Index, Indexes, OtherValueTypes...>()");
#else
				return none;
#endif
			}
		}

		template <size_t Index>
#ifdef HAS_CXX20
		WOJ_CONSTEVAL20
#else
		constexpr
#endif
			static auto get() noexcept
#ifndef NDEBUG
			(Index < sizeof...(Values))
#endif
		{
			return at<Index>();
		}

#if WOJ_HAS_CXX20
		WOJ_CONSTEVAL20
#else
		constexpr
#endif
			static size_t size() noexcept
		{
			return sizeof...(Values);
		}

#if WOJ_HAS_CXX20
		WOJ_CONSTEVAL20
#else
		constexpr
#endif
			static size_t max_size() noexcept
		{
			return sizeof...(Values);
		}
	};

	template <>
	class value_sequence<>
	{
	public:
		constexpr value_sequence() noexcept = default;

		explicit constexpr value_sequence(none_t) noexcept {}

		explicit constexpr value_sequence(noinit_t) noexcept {}

		constexpr value_sequence(const value_sequence&) noexcept = default;

		constexpr value_sequence(value_sequence&&) noexcept = delete;

		explicit constexpr operator bool() const noexcept
		{
			return false;
		}

		constexpr value_sequence& operator=(const value_sequence&) = delete;

		constexpr value_sequence& operator=(value_sequence&&) = delete;

		template <size_t Index>
#ifdef HAS_CXX20
		WOJ_CONSTEVAL20
#else
		constexpr
#endif
			static auto at() noexcept
#ifndef NDEBUG
			(false)
#endif
		{
#ifndef NDEBUG
			throw out_of_sequence_range(193, "value_sequence.hpp", "woj::meta::value_sequence<Values...>::at_impl<Index, Indexes, OtherValueTypes...>()");
#else
			return none;
#endif
		}

		template <size_t Index>
#ifdef HAS_CXX20
		WOJ_CONSTEVAL20
#else
		constexpr
#endif
			static auto get() noexcept
#ifndef NDEBUG
			(false)
#endif
		{
			return at<Index>();
		}

#if WOJ_HAS_CXX20
		WOJ_CONSTEVAL20
#else
		constexpr
#endif
			static size_t size() noexcept
		{
			return 0;
		}

#if WOJ_HAS_CXX20
		WOJ_CONSTEVAL20
#else
		constexpr
#endif
			static size_t max_size() noexcept
		{
			return 0;
		}
	};
}