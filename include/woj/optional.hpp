#pragma once

#include <cassert>
#include <type_traits>
#include <limits>
#include <cstdint>
#include <optional>
#include <iostream>

#include "defs.hpp"

namespace woj
{
	struct nullopt_t
	{
		constexpr nullopt_t(const int) {}
	};

	constexpr nullopt_t nullopt{ 0 };

	template <typename ValueType>
	class optional
	{
	public:
		using value_type = ValueType;

		bool m_has_value;
		ValueType m_value;
				
		constexpr optional() noexcept : m_has_value{ false } {}

		constexpr optional(const optional& other) noexcept(std::is_nothrow_constructible<ValueType, ValueType&>::value) requires(std::is_constructible<ValueType, ValueType&>::value) : m_has_value{other.m_has_value}, m_value{other.m_value} {}
		constexpr optional(optional&& other) noexcept(std::is_nothrow_move_constructible<ValueType>::value) requires(std::is_constructible<ValueType, ValueType&&>::value) : m_has_value{ other.m_has_value }, m_value{ std::move(other.m_value) }
		{
			other.m_has_value = false;
		}

		template <typename OtherValueType> requires (std::is_constructible<ValueType, OtherValueType&>::value)
		constexpr optional(const OtherValueType& value) noexcept(std::is_nothrow_constructible<ValueType, OtherValueType&>::value) : m_has_value{ true }, m_value{ value } {}

		template <typename OtherValueType> requires (std::is_constructible<ValueType, OtherValueType&&>::value)
		constexpr optional(OtherValueType&& value) noexcept(std::is_nothrow_constructible<ValueType, OtherValueType&&>::value) : m_has_value{ true }, m_value{ std::move(value) } {}

		constexpr optional(const nullopt_t) noexcept : m_has_value{ false } {}

		constexpr optional& operator=(const optional& other) noexcept(std::is_nothrow_constructible<ValueType, ValueType&>::value) requires(std::is_constructible<ValueType, ValueType&>::value)
		{
			m_has_value = other.has_value();
			m_value = other.value();

			return *this;
		}

		constexpr optional& operator=(optional&& other) noexcept(std::is_nothrow_constructible<ValueType, ValueType&&>::value) requires(std::is_constructible<ValueType, ValueType&&>::value)
		{
			m_has_value = other.has_value();
			m_value = std::move(other.value());

			return *this;
		}

		NODISCARD constexpr bool has_value() const noexcept
		{
			return m_has_value;
		}

		NODISCARD constexpr ValueType& value() noexcept
		{
			std::optional<int>::
			assert(has_value());

			return m_value;
		}

		NODISCARD constexpr const ValueType& value() const
		{
			assert(has_value());

			return m_value;
		}
	};
}
