#pragma once

#include <cassert>
#include <type_traits>
#include <limits>
#include <cstdint>
#include <optional>
#include <iostream>

#include "base.hpp"

#include <boost/optional.hpp>

namespace woj
{
	class bad_optional_access : std::exception
	{
		NODISCARD const char* what() const noexcept override
		{
			return "Bad optional access";
		}
	};

	/**
	 * Represents states of the optional.
	 */
	enum class optional_state : uint8_t
	{
		/**
		 * The optional has a value.
		 */
		has_value = 0u,
		/**
		 * The optional does not have a value.
		 */
		no_value = 1u,
		/**
		 * The state of the optional is unknown.
		 */
		unknown = 2u
	};

	template <typename ValueType>
	class optional
	{
	public:

		using value_type = ValueType;

		bool m_has_value;

		union
		{
			null_t m_empty;
			ValueType m_value;
		};
		
		/**
		 * Constructs an empty optional.
		 */
		constexpr optional() noexcept : m_has_value{ false }, m_empty{}
		{
			if (is_constant_evaluated())
			{
				std::construct_at(&m_value);
			}
		}

		/**
		 * Constructs an optional from another optional by copying it.
		 * @param other The optional to copy.
		 * @param other_state State of the other optional.
		 */
		constexpr optional(const optional& other, const optional_state& other_state = optional_state::unknown) noexcept(std::is_nothrow_copy_constructible<ValueType>::value)
			requires(std::is_copy_constructible<ValueType>::value)
		: m_has_value{ other.m_has_value }, m_empty{}
		{
			if (other_state == optional_state::has_value || other)
			{
				std::construct_at(&m_value, other.m_value);
			}
		}

		/**
		 * Constructs an optional from another optional by moving it.
		 * @param other The optional to move.
		 * @param other_state State of the other optional.
		 */
		constexpr optional(optional&& other, const optional_state& other_state = optional_state::unknown) noexcept(std::is_nothrow_move_constructible<ValueType>::value)
			requires(std::is_move_constructible<ValueType>::value)
			: m_has_value{ other.m_has_value }, m_empty{}
		{
			if (other_state == optional_state::has_value || other)
			{
				std::construct_at(&m_value, std::move(other.m_value));
				other.m_has_value = false;
			}
		}

		/**
		 * Constructs an optional from a value by copying it.
		 * @tparam OtherValueType The type of the value to copy.
		 * @param value The value to copy.
		 */
		template <typename OtherValueType> requires (std::is_constructible<ValueType, const OtherValueType&>::value && !std::is_same_v<std::remove_cvref_t<OtherValueType>, optional>)
		constexpr optional(const OtherValueType& value) noexcept(std::is_nothrow_constructible<ValueType, const OtherValueType&>::value)
			: m_has_value{ true }, m_value{ value } {}

		/**
		 * Constructs an optional from a value by moving it.
		 * @tparam OtherValueType The type of the value to move.
		 * @param value Value to move.
		 */
		template <typename OtherValueType> requires (std::is_constructible<ValueType, OtherValueType&&>::value && !std::is_same_v<std::remove_cvref_t<ValueType>, optional>)
		constexpr optional(OtherValueType&& value) noexcept(std::is_nothrow_constructible<ValueType, OtherValueType&&>::value)
			: m_has_value{ true }, m_value{ std::move(value) } {}

		/**
		 * Constructs the value of the optional by forwarding the arguments.
		 * @tparam OtherValueTypes The types of the arguments to forward.
		 * @param values The values to forward.
		 */
		template <typename... OtherValueTypes>
		constexpr optional(in_place_t, OtherValueTypes&&... values) noexcept(std::is_nothrow_constructible<ValueType, OtherValueTypes...>::value)
			requires(std::is_constructible<ValueType, OtherValueTypes...>::value)
			: m_has_value{ true }, m_value{ std::forward<OtherValueTypes>(values)... } {}

		/**
		 * Constructs an empty optional.
		 */
		constexpr optional(const null_t) noexcept : m_has_value{ false }, m_empty{}
		{
			if (is_constant_evaluated())
			{
				std::construct_at(&m_value);
			}
		}

		/**
		 * Constructs an uninitialized optional.
		 * State of the optional is undefined until value construction.
		 */
		constexpr optional(const noinit_t) noexcept : m_empty{} {}

		/**
		 * Destructs the optional.
		 */
		CONSTEXPR20 ~optional() = default;

		/**
		 * Assigns the optional by copying another optional.
		 * @param other The optional to copy.
		 * @return The reference to the assigned optional.
		 */
		constexpr optional& operator=(const optional& other) noexcept(std::is_nothrow_copy_constructible<ValueType>::value)
			requires(std::is_copy_constructible<ValueType>::value)
		{
			return copy_construct(other);
		}

		/**
		 * Assigns the optional by moving another optional.
		 * @param other The optional to move.
		 * @return The reference to the assigned optional.
		 */
		constexpr optional& operator=(optional&& other) noexcept(std::is_nothrow_move_constructible<ValueType>::value)
			requires(std::is_move_constructible<ValueType>::value)
		{
			return move_construct(other);
		}

		/**
		 * Assigns the optional by copying a value.
		 * @tparam OtherValueType The type of the value to copy.
		 * @param value The value to copy.
		 * @return The reference to the assigned optional.
		 */
		template <typename OtherValueType> requires (std::is_constructible<ValueType, const OtherValueType&>::value && !std::is_same_v<std::remove_cvref_t<OtherValueType>, optional>)
		constexpr optional& operator=(const OtherValueType& value) noexcept(std::is_nothrow_constructible<ValueType, const OtherValueType&>::value)
		{
			return copy_construct(value);
		}

		/**
		 * Assigns the optional by moving a value.
		 * @tparam OtherValueType The type of the value to move.
		 * @param value The value to move.
		 * @return The reference to the assigned optional.
		 */
		template <typename OtherValueType> requires (std::is_constructible<ValueType, OtherValueType&&>::value && !std::is_same_v<std::remove_cvref_t<ValueType>, optional>)
		constexpr optional& operator=(OtherValueType&& value) noexcept(std::is_nothrow_constructible<ValueType, OtherValueType&&>::value)
		{
			return move_construct(value);
		}

		/**
		 * Assigns the optional to be empty.
		 * @return The reference to the assigned optional.
		 */
		constexpr optional& operator=(const null_t) noexcept
		{
			m_has_value = false;

			return *this;
		}

		/**
		 * Converts the optional to an lvalue reference.
		 * @return Lvalue reference to the value.
		 */
		constexpr operator ValueType&() volatile
#if defined(NDEBUG)
			noexcept
#endif
		{
#if !defined(NDEBUG)
			if (!m_has_value)
				throw bad_optional_access{};
#endif

			return m_value;
		}

		/**
		 * Converts the optional to a const lvalue reference.
		 * @return Const lvalue reference to the value.
		 */
		constexpr operator const ValueType&() const
#if defined(NDEBUG)
			noexcept
#endif
		{
#if !defined(NDEBUG)
			if (!m_has_value)
				throw bad_optional_access{};
#endif

			return m_value;
		}

		/**
		 * Converts the optional to a boolean value.
		 * @return True if the optional has a value, false otherwise.
		 */
		constexpr operator bool() const noexcept
		{
			return has_value();
		}

		/**
		 * Returns a pointer to the value.
		 * @return The pointer to the value.
		 */
		NODISCARD constexpr ValueType* operator->() noexcept
		{
#if !defined(NDEBUG)
			if (!m_has_value)
				throw bad_optional_access{};
#endif

			return std::addressof(m_value);
		}

		/**
		 * Returns a const pointer to the value.
		 * @return The const pointer to the value.
		 */
		NODISCARD constexpr const ValueType* operator->() const noexcept
		{
#if !defined(NDEBUG)
			if (!m_has_value)
				throw bad_optional_access{};
#endif

			return std::addressof(m_value);
		}

		/**
		 * Returns an lvalue reference to the value.
		 * @return The lvalue reference to the value.
		 */
		NODISCARD constexpr ValueType& operator*() noexcept
		{
#if !defined(NDEBUG)
			if (!m_has_value)
				throw bad_optional_access{};
#endif

			return m_value;
		}

		/**
		 * Returns a const lvalue reference to the value.
		 * @return The const lvalue reference to the value.
		 */
		NODISCARD constexpr const ValueType& operator*() const noexcept
		{
#if !defined(NDEBUG)
			if (!m_has_value)
				throw bad_optional_access{};
#endif

			return m_value;
		}

		/**
		 * Constructs the optional to be empty.
		 * @tparam State State of the optional.
		 * @return The lvalue reference to optional.
		 */
		template <optional_state State = optional_state::unknown>
		constexpr optional& empty_construct() noexcept
		{
			IF_CONSTEXPR (State != optional_state::no_value)
			{
				m_has_value = false;
			}
			return *this;
		}

		/**
		 * Constructs the optional from another optional by copying it.
		 * @tparam State State of the optional.
		 * @tparam OtherState State of the other optional.
		 * @param other The optional to copy.
		 * @return The lvalue reference to optional.
		 */
		template <optional_state State = optional_state::unknown, optional_state OtherState = optional_state::unknown> requires(std::is_copy_constructible<ValueType>::value)
		constexpr optional& copy_construct(const optional& other) noexcept(std::is_nothrow_copy_constructible<ValueType>::value)
		{
			IF_CONSTEXPR (OtherState == optional_state::has_value)
			{
				IF_CONSTEXPR (State != optional_state::has_value)
				{
					m_has_value = true;
				}
				m_value = other.m_value;
			}
			else IF_CONSTEXPR (OtherState == optional_state::no_value)
			{
				IF_CONSTEXPR (State != optional_state::no_value)
				{
					m_has_value = false;
				}
			}
			else // OtherState == unknown
			{
				if (other)
				{
					m_has_value = true;
					m_value = other.m_value;
				}
			}

			return *this;
		}

		/**
		 * Constructs an optional from another optional by moving it.
		 * @tparam State State of the optional.
		 * @tparam OtherState State of the other optional.
		 * @param other The optional to move.
		 * @return The lvalue reference to optional.
		 */
		template <optional_state State = optional_state::unknown, optional_state OtherState = optional_state::unknown> requires(std::is_move_constructible<ValueType>::value)
		constexpr optional& move_construct(optional&& other) noexcept(std::is_nothrow_move_constructible<ValueType>::value)
		{
			IF_CONSTEXPR (OtherState == optional_state::has_value)
			{
				IF_CONSTEXPR (State != optional_state::has_value)
				{
					m_has_value = true;
				}
				m_value = std::move(other.m_value);
				other.m_has_value = false;
			}
			else IF_CONSTEXPR (OtherState == optional_state::no_value)
			{
				IF_CONSTEXPR(State != optional_state::no_value)
				{
					m_has_value = false;
				}
			}
			else // OtherState == unknown
			{
				if (other)
				{
					m_has_value = true;
					m_value = other.m_value;
					other.m_has_value = false;
				}
			}

			return *this;
		}

		/**
		 * Constructs an optional from a value by copying it.
		 * @tparam State State of the optional.
		 * @tparam OtherValueType The type of the value to copy.
		 * @param value The value to copy.
		 * @return The lvalue reference to optional.
		 */
		template <optional_state State = optional_state::unknown, typename OtherValueType> requires (std::is_constructible<ValueType, const OtherValueType&>::value && !std::is_same_v<std::remove_cvref_t<OtherValueType>, optional>)
		constexpr optional& copy_construct(const OtherValueType& value) noexcept(std::is_nothrow_constructible<ValueType, const OtherValueType&>::value)
		{
			IF_CONSTEXPR (State != optional_state::has_value)
			{
				m_has_value = true;
			}
			m_value = value;

			return *this;
		}

		/**
		 * Constructs an optional from a value by moving it.
		 * @tparam State State of the optional.
		 * @tparam OtherValueType The type of the value to move.
		 * @param value Value to move.
		 * @return The rvalue reference to optional.
		 */
		template <optional_state State = optional_state::unknown, typename OtherValueType> requires (std::is_constructible<ValueType, OtherValueType&&>::value && !std::is_same_v<std::remove_cvref_t<ValueType>, optional>)
		constexpr optional& move_construct(OtherValueType&& value) noexcept(std::is_nothrow_constructible<ValueType, OtherValueType&&>::value)
		{
			IF_CONSTEXPR (State != optional_state::has_value)
			{
				m_has_value = true;
			}
			m_value = std::move(value);

			return *this;
		}

		/**
		 * Constructs an empty optional.
		 * @tparam State State of the optional.
		 * @return The lvalue reference to the constructed optional.
		 */
		template <optional_state State = optional_state::unknown>
		constexpr optional& null_construct(const null_t) noexcept
		{
			IF_CONSTEXPR (State != optional_state::no_value)
			{
				m_has_value = false;
			}

			if (is_constant_evaluated())
			{
				m_value = ValueType{};
			}

			return *this;
		}

		/**
		 * Returns a const lvalue reference to the value.
		 * @tparam State State of the optional.
		 * @return The const lvalue reference to the value.
		 */
		template <optional_state State = optional_state::unknown>
		NODISCARD constexpr ValueType& value() noexcept(State == optional_state::has_value)
		{
			IF_CONSTEXPR(State == optional_state::has_value)
			{
				return m_value;
			}
			IF_CONSTEXPR (State == optional_state::no_value)
			{
				throw bad_optional_access{};
			}
			if (m_value)
				return m_value;

			throw bad_optional_access{};
		}

		/**
		 * Returns a const rvalue reference to the value.
		 * @tparam State State of the optional.
		 * @return The const rvalue reference to the value.
		 */
		template <optional_state State = optional_state::unknown>
		NODISCARD constexpr const ValueType& value() const noexcept(State == optional_state::has_value)
		{
			IF_CONSTEXPR(State == optional_state::has_value)
			{
				return m_value;
			}
			IF_CONSTEXPR(State == optional_state::no_value)
			{
				throw bad_optional_access{};
			}
			if (m_value)
				return m_value;

			throw bad_optional_access{};
		}


		/**
		 * Checks if the optional has a value.
		 * @tparam State State of the optional.
		 * @return True if the optional has a value, false otherwise.
		 */
		template <optional_state State = optional_state::unknown>
		NODISCARD constexpr bool has_value() const noexcept(State == optional_state::has_value)
		{
			IF_CONSTEXPR (State == optional_state::has_value)
			{
				return true;
			}
			IF_CONSTEXPR (State == optional_state::no_value)
			{
				return false;
			}

			return m_has_value;
		}

		/**
		 * Resets the optional to be empty.
		 * @tparam State State of the optional.
		 * @return The lvalue reference to the optional.
		 */
		template <optional_state State = optional_state::unknown>
		constexpr optional& reset() noexcept
		{
			IF_CONSTEXPR (State != optional_state::no_value)
			{
				m_has_value = false;
			}

			return *this;
		}

		/**
		 * Emplaces the value of the optional by forwarding the arguments.
		 * @tparam State State of the optional.
		 * @tparam OtherValueTypes The types of the arguments to forward.
		 * @param values The values to forward.
		 * @return The lvalue reference to the optional.
		 */
		template <optional_state State = optional_state::unknown, typename... OtherValueTypes> requires(std::is_constructible<ValueType, OtherValueTypes...>::value)
		constexpr optional& emplace(OtherValueTypes&&... values) noexcept(std::is_nothrow_constructible<ValueType, OtherValueTypes...>::value)
		{
			IF_CONSTEXPR(State != optional_state::no_value)
			{
				m_has_value = true;
			}

			std::construct_at(&m_value, std::forward<OtherValueTypes>(values)...);

			return *this;
		}

		/**
		 * Applies the function to the value of the optional.
		 * @tparam State State of the optional.
		 * @tparam FuncType The type of the function to apply.
		 * @tparam ArgTypes The types of the arguments to pass to the function.
		 * @param func The function to apply.
		 * @param args The arguments to pass to the function.
		 * @return The reference to the optional.
		 */
		template <optional_state State = optional_state::unknown, typename FuncType, typename... ArgTypes> requires (std::is_invocable_v<FuncType, ValueType&, ArgTypes...>)
		constexpr optional& apply(FuncType&& func, ArgTypes&&... args) noexcept(std::is_nothrow_invocable_v<FuncType, ValueType, ArgTypes...> && State == optional_state::has_value)
		{
			IF_CONSTEXPR (State == optional_state::has_value)
			{
				func(m_value, args...);
			}
			IF_CONSTEXPR (State == optional_state::no_value)
			{
				throw bad_optional_access{};
			}
			IF_CONSTEXPR(State == optional_state::unknown)
			{
				if (m_has_value)
				{
					func(m_value, args...);
				}
				else
				{
					throw bad_optional_access{};
				}
			}

			return *this;
		}

		/**
		 * Returns the optional as a const reference.
		 * @return The const reference to the optional.
		 */
		NODISCARD constexpr const optional& as_const() const noexcept
		{
			return *this;
		}

		/**
		 * Returns the state of the optional.
		 * @tparam State State of the optional.
		 * @return The state of the optional. The state returned is not unknown.
		 */
		template <optional_state State = optional_state::unknown>
		NODISCARD constexpr optional_state state() const noexcept
		{
			IF_CONSTEXPR (State != optional_state::unknown)
			{
				return State;
			}

			return m_has_value ? optional_state::has_value : optional_state::no_value;
		}

		/**
		 * Swaps the values of two optionals.
		 * @param other The optional to swap with.
		 * @return The reference to the swapped optional.
		 */
		template <optional_state State = optional_state::unknown, optional_state OtherState = optional_state::unknown>
		constexpr optional& swap(optional& other) noexcept((std::is_move_constructible<ValueType>::value && std::is_nothrow_move_constructible<ValueType>::value) || (std::is_swappable<ValueType>::value && std::is_nothrow_swappable<ValueType>::value))
												  requires(std::is_move_constructible<ValueType>::value || std::is_swappable<ValueType>::value)
		{
			// ---------- SELF: 1 (CEVAL) ----------
			IF_CONSTEXPR (State == optional_state::has_value)
			{
				// -----> SELF: 1 (CEVAL), OTHER: 1 (CEVAL) <---------
				IF_CONSTEXPR (OtherState == optional_state::has_value)
				{
					std::swap(m_value, other.m_value);
				}
				// -----> SELF: 1 (CEVAL), OTHER: 0 (CEVAL) <---------
				else IF_CONSTEXPR (OtherState == optional_state::no_value)
				{
					std::construct_at(std::addressof(other.m_value), std::move(m_value));
					other.m_has_value = true;
					m_has_value = false;
				}
				// -----> SELF: 1 (CEVAL), OTHER: 1 (REVAL) <---------
				else if (other.m_has_value)
				{
					std::swap(m_value, other.m_value);
				}
				// -----> SELF: 1 (CEVAL), OTHER: 0 (REVAL) <---------
				else
				{
					std::construct_at(std::addressof(other.m_value), std::move(m_value));
					other.m_has_value = true;
					m_has_value = false;
				}
			}
			// ---------- SELF: 0 (CEVAL) ----------
			else IF_CONSTEXPR (State == optional_state::no_value)
			{
				// -----> SELF: 0 (CEVAL), OTHER: 1 (CEVAL) <---------
				IF_CONSTEXPR (OtherState == optional_state::has_value)
				{
					std::construct_at(std::addressof(m_value), std::move(other.m_value));
					other.m_has_value = false;
					m_has_value = true;
				}
				// -----> SELF: 0 (CEVAL), OTHER: 0 (CEVAL) <--------- OMITTED

				// -----> SELF: 0 (CEVAL), OTHER: ? (CEVAL) <---------
				else IF_CONSTEXPR (OtherState == optional_state::unknown)
				{
					// >> SELF: 0 (CEVAL), OTHER: 1 (REVAL) <<--------
					if (other.m_has_value)
					{
						std::construct_at(std::addressof(m_value), std::move(other.m_value));
						other.m_has_value = false;
						m_has_value = true;
					}
					// >> SELF: 0 (CEVAL), OTHER: 1 (REVAL) <<-------- OMITTED
				}
			}
			// ---------- SELF: ? (CEVAL) ----------
			else
			{
				// -----> SELF: ? (CEVAL), OTHER: 1 (CEVAL) <---------
				IF_CONSTEXPR (OtherState == optional_state::has_value)
				{
					// >> SELF: 1 (REVAL), OTHER: 1 (CEVAL) <<--------
					if (m_has_value)
					{
						std::swap(m_value, other.m_value);
					}
					// >> SELF: 0 (REVAL), OTHER: 1 (CEVAL) <<--------
					else
					{
						std::construct_at(std::addressof(m_value), std::move(other.m_value));
						other.m_has_value = false;
						m_has_value = true;
					}
				}
				// -----> SELF: ?, OTHER: 0 (CEVAL) <---------
				else IF_CONSTEXPR (OtherState == optional_state::no_value)
				{
					// >> SELF: 1 (REVAL), OTHER: 0 (CEVAL) <<--------
					if (m_has_value)
					{
						std::construct_at(std::addressof(other.m_value), std::move(m_value));
						other.m_has_value = true;
						m_has_value = false;
					}
					// >> SELF: 0 (REVAL), OTHER: 0 (CEVAL) <<-------- OMITTED
				}
				// -----> SELF: 1 (REVAL), OTHER: 1 (REVAL) <---------
				else if (m_has_value && other.m_has_value)
				{
					std::swap(m_value, other.m_value);
				}
				// -----> SELF: 1 (REVAL), OTHER: 0 (REVAL) <---------
				else if (m_has_value)
				{
					std::construct_at(std::addressof(other.m_value), std::move(m_value));
					other.m_has_value = true;
					m_has_value = false;
				}
				// -----> SELF: 0 (REVAL), OTHER: 1 (REVAL) <---------
				else if (other.m_has_value)
				{
					std::construct_at(std::addressof(m_value), std::move(other.m_value));
					other.m_has_value = false;
					m_has_value = true;
				}
				// -----> SELF: 0 (REVAL), OTHER: 0 (REVAL) <--------- OMITTED
			}
			return *this;
		}

		constexpr optional& swap2(optional& other, optional_state state, optional_state other_state) noexcept((std::is_move_constructible<ValueType>::value&& std::is_nothrow_move_constructible<ValueType>::value) || (std::is_swappable<ValueType>::value && std::is_nothrow_swappable<ValueType>::value))
		{
			if (state == optional_state::has_value)
			{
				if (other_state == optional_state::has_value)
				{
					std::swap(m_value, other.m_value);
				}
				else if (other_state == optional_state::no_value)
				{
					std::construct_at(std::addressof(other.m_value), std::move(m_value));
					other.m_has_value = true;
					m_has_value = false;
				}
				else // other_state == optional_state::unknown
				{
					if (other.m_has_value)
					{
						std::swap(m_value, other.m_value);
					}
					else
					{
						std::construct_at(std::addressof(other.m_value), std::move(m_value));
						other.m_has_value = true;
						m_has_value = false;
					}
				}
			}
			else if (state == optional_state::no_value)
			{
				if (other_state == optional_state::has_value)
				{
					std::construct_at(std::addressof(m_value), std::move(other.m_value));
					other.m_has_value = false;
					m_has_value = true;
				}
				else if (other_state == optional_state::unknown)
				{
					if (other.m_has_value)
					{
						std::construct_at(std::addressof(m_value), std::move(other.m_value));
						other.m_has_value = false;
						m_has_value = true;
					}
				}
				// Omitted case: state == no_value and other_state == no_value, no need to do anything
			}
			else // state == optional_state::unknown
			{
				if (other_state == optional_state::has_value)
				{
					if (m_has_value)
					{
						std::swap(m_value, other.m_value);
					}
					else
					{
						std::construct_at(std::addressof(m_value), std::move(other.m_value));
						other.m_has_value = false;
						m_has_value = true;
					}
				}
				else if (other_state == optional_state::no_value)
				{
					if (m_has_value)
					{
						std::construct_at(std::addressof(other.m_value), std::move(m_value));
						other.m_has_value = true;
						m_has_value = false;
					}
				}
				else // other_state == optional_state::unknown
				{
					if (m_has_value && other.m_has_value)
					{
						std::swap(m_value, other.m_value);
					}
					else if (m_has_value)
					{
						std::construct_at(std::addressof(other.m_value), std::move(m_value));
						other.m_has_value = true;
						m_has_value = false;
					}
					else if (other.m_has_value)
					{
						std::construct_at(std::addressof(m_value), std::move(other.m_value));
						other.m_has_value = false;
						m_has_value = true;
					}
					// Omitted case: Both do not have values, nothing to do.
				}
			}

			return *this;
		}
	};
}
