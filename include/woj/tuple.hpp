#pragma once

#include <type_traits>

#include "string.hpp"
#include "vector.hpp"
#include "meta/base.hpp"
#include "meta/sequence.hpp"
#include "woj/base.hpp"

#define __WOJ_EMPTY_FUNCTION_BODY {}
#define __WOJ_EMPTY_FUNCTION_NOEXCEPT_BODY noexcept __WOJ_EMPTY_FUNCTION_BODY
#define __WOJ_RETURN_THIS_FUNCTION_METHOD_BODY { return *this; }
#define __WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY noexcept __WOJ_RETURN_THIS_FUNCTION_METHOD_BODY
#define __WOJ_RETURN_FORWARD_THIS_FUNCTION_METHOD_BODY { return std::forward<decltype(*this)>(*this); }
#define __WOJ_RETURN_FORWARD_THIS_FUNCTION_METHOD_NOEXCEPT_BODY noexcept __WOJ_RETURN_FORWARD_THIS_FUNCTION_METHOD_BODY
/*
#define __WOJ_RETURN_FORWARD_THIS_FUNCTION_METHOD_BODY { return std::forward<nulluple>(*this); }
#define __WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY noexcept __WOJ_RETURN_FORWARD_THIS_FUNCTION_METHOD_BODY
#define __WOJ_RETURN_FORWARD_CONST_THIS_FUNCTION_METHOD_BODY { return std::forward<const nulluple>(*this); }
#define __WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY noexcept __WOJ_RETURN_FORWARD_CONST_THIS_FUNCTION_METHOD_BODY
*/

namespace woj
{
	class bad_nulluple_access final : public exception
	{
	public:
		constexpr bad_nulluple_access(const size_t line, const char* const message, const char* const file, const char* const function)
			: exception{ line, message, file, function } {
		}
		constexpr bad_nulluple_access(const bad_nulluple_access&) = default;
		constexpr bad_nulluple_access(bad_nulluple_access&&) = default;
		constexpr bad_nulluple_access& operator =(const bad_nulluple_access&) = default;
		constexpr bad_nulluple_access& operator =(bad_nulluple_access&&) = default;
	};

	/**
	 * Class representing a null tuple (0-tuple)
	 */
	class nulluple
	{
	public:


		/**
		 * Enum representing the state of the nulluple
		 */
		enum class state_t : uint8_t
		{
			initialized /* The nulluple is initialized */,
			uninitialized /* The nulluple is uninitialized */,
			unknown /* The state of the nulluple is unknown */
		};

		using this_type = nulluple;

		/**
		 * Constructs a nulluple
		 */
		constexpr nulluple()
			noexcept = default;

		/**
		 * Constructs an uninitialized nulluple
		 * @param noinit No initialization tag
		 */
		constexpr nulluple(const noinit_t noinit)
		__WOJ_EMPTY_FUNCTION_NOEXCEPT_BODY

		/**
		 * Constructs a nulluple from another nulluple
		 * @param other Other nulluple
		 */
		constexpr nulluple(const nulluple &other)
			noexcept = default;

		/**
		 * Constructs a nulluple from another nulluple
		 * @param other_state State of the other nulluple
		 * @param other	Other nulluple
		 */
		constexpr nulluple(const state_t other_state, const nulluple &other)
		__WOJ_EMPTY_FUNCTION_NOEXCEPT_BODY

		/**
		 * Constructs a nulluple in place
		 * @param in_place In place tag
		 */
		constexpr nulluple(const in_place_t in_place)
		__WOJ_EMPTY_FUNCTION_NOEXCEPT_BODY

		/**
		 * Destroys the nulluple
		 */
		constexpr
			~nulluple()
			noexcept = default;

		constexpr nulluple &operator =(const nulluple other)
			__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Converts the nulluple to a boolean (always false since the nulluple is empty)
		 */
		[[nodiscard]] explicit constexpr operator bool() const
			noexcept
		{
			return false;
		}

		/**
		 * Equality operator (always true since all nulluples are equal to each other)
		 * @param other Other nulluple
		 * @return True
		 */
		[[nodiscard]]
		constexpr bool operator ==(const nulluple other) const
			noexcept
		{
			return true;
		}

		/**
		 * Three-way comparison operator (always equal since all nulluples are equal to each other)
		 * @param other Other nulluple
		 * @return Equal
		 */
		[[nodiscard]]
		constexpr std::strong_ordering operator <=>(const nulluple other) const
			noexcept
		{
			return std::strong_ordering::equal;
		}

		/**
		 * Constructs current nulluple from a noinit tag (does nothing)
		 * @tparam State State of the current nulluple
		 * @tparam OtherState UNUSED. State of the other nulluple
		 * @param noinit No initialization tag
		 * @return const lvalue reference to the current nulluple
		 */
		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown>
		constexpr const nulluple &construct_from(const noinit_t noinit) const &
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Constructs current nulluple from a noinit tag (does nothing)
		 * @tparam State State of the current nulluple
		 * @tparam OtherState UNUSED. State of the other nulluple
		 * @param noinit No initialization tag
		 * @return lvalue reference to the current nulluple
		 */
		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown>
		constexpr nulluple &construct_from(const noinit_t noinit) & 
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Constructs current nulluple from a noinit tag (does nothing)
		 * @tparam State State of the current nulluple
		 * @tparam OtherState UNUSED. State of the other nulluple
		 * @param noinit No initialization tag
		 * @return const rvalue reference to the current nulluple
		 */
		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown>
		constexpr const nulluple &&construct_from(const noinit_t noinit) const &&
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Constructs current nulluple from a noinit tag (does nothing)
		 * @tparam State State of the current nulluple
		 * @tparam OtherState UNUSED. State of the other nulluple
		 * @param noinit No initialization tag
		 * @return rvalue reference to the current nulluple
		 */
		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown>
		constexpr nulluple &&construct_from(const noinit_t noinit) && 
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Constructs current nulluple from another nulluple (does nothing)
		 * @tparam DynamicStates Dynamic states tag
		 * @param state State of the current nulluple
		 * @param other_state UNUSED. State of the other nulluple
		 * @param noinit No initialization tag
		 * @return const lvalue reference to the current nulluple
		 */
		template <dynamic_states_t DynamicStates>
		constexpr const nulluple &construct_from(const state_t state, const state_t other_state, const noinit_t noinit) const &
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Constructs current nulluple from another nulluple (does nothing)
		 * @tparam DynamicStates Dynamic states tag
		 * @param state State of the current nulluple
		 * @param other_state UNUSED. State of the other nulluple
		 * @param noinit No initialization tag
		 * @return lvalue reference to the current nulluple
		 */
		template <dynamic_states_t DynamicStates>
		constexpr nulluple &construct_from(const state_t state, const state_t other_state, const noinit_t noinit) & 
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Constructs current nulluple from another nulluple (does nothing)
		 * @tparam DynamicStates Dynamic states tag
		 * @param state State of the current nulluple
		 * @param other_state UNUSED. State of the other nulluple
		 * @param noinit No initialization tag
		 * @return const rvalue reference to the current nulluple
		 */
		template <dynamic_states_t DynamicStates>
		constexpr const nulluple &&construct_from(const state_t state, const state_t other_state, const noinit_t noinit) const &&
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Constructs current nulluple from another nulluple (does nothing)
		 * @tparam DynamicStates Dynamic states tag
		 * @param state State of the current nulluple
		 * @param other_state UNUSED. State of the other nulluple
		 * @param noinit No initialization tag
		 * @return rvalue reference to the current nulluple
		 */
		template <dynamic_states_t DynamicStates>
		constexpr nulluple &&construct_from(const state_t state, const state_t other_state, const noinit_t noinit) && 
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Constructs current nulluple from another nulluple (does nothing)
		 * @tparam State State of the current nulluple
		 * @tparam OtherState State of the other nulluple
		 * @param other Other nulluple
		 * @return const lvalue reference to the current nulluple
		 */
		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown>
		constexpr const nulluple &construct_from(const nulluple other) const &
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Constructs current nulluple from another nulluple (does nothing)
		 * @tparam State State of the current nulluple
		 * @tparam OtherState State of the other nulluple
		 * @param other Other nulluple
		 * @return lvalue reference to the current nulluple
		 */
		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown>
		constexpr nulluple &construct_from(const nulluple other) & 
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Constructs current nulluple from another nulluple (does nothing)
		 * @tparam State State of the current nulluple
		 * @tparam OtherState State of the other nulluple
		 * @param other Other nulluple
		 * @return const rvalue reference to the current nulluple
		 */
		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown>
		constexpr const nulluple &&construct_from(const nulluple other) const &&
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Constructs current nulluple from another nulluple (does nothing)
		 * @tparam State State of the current nulluple
		 * @tparam OtherState State of the other nulluple
		 * @param other Other nulluple
		 * @return rvalue reference to the current nulluple
		 */
		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown>
		constexpr nulluple &&construct_from(const nulluple other) && 
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Constructs current nulluple from another nulluple (does nothing)
		 * @tparam DynamicStates Dynamic states tag
		 * @param state State of the current nulluple
		 * @param other_state State of the other nulluple
		 * @param other Other nulluple
		 * @return const lvalue reference to the current nulluple
		 */
		template <dynamic_states_t DynamicStates>
		constexpr const nulluple &construct_from(const state_t state, const state_t other_state, const nulluple other) const &
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Constructs current nulluple from another nulluple (does nothing)
		 * @tparam DynamicStates Dynamic states tag
		 * @param state State of the current nulluple
		 * @param other_state State of the other nulluple
		 * @param other Other nulluple
		 * @return lvalue reference to the current nulluple
		 */
		template <dynamic_states_t DynamicStates>
		constexpr nulluple &construct_from(const state_t state, const state_t other_state, const nulluple other) & 
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Constructs current nulluple from another nulluple (does nothing)
		 * @tparam DynamicStates Dynamic states tag
		 * @param state State of the current nulluple
		 * @param other_state State of the other nulluple
		 * @param other Other nulluple
		 * @return const rvalue reference to the current nulluple
		 */
		template <dynamic_states_t DynamicStates>
		constexpr const nulluple &&construct_from(const state_t state, const state_t other_state, const nulluple other) const &&
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Constructs current nulluple from another nulluple (does nothing)
		 * @tparam DynamicStates Dynamic states tag
		 * @param state State of the current nulluple
		 * @param other_state State of the other nulluple
		 * @param other Other nulluple
		 * @return rvalue reference to the current nulluple
		 */
		template <dynamic_states_t DynamicStates>
		constexpr nulluple &&construct_from(const state_t state, const state_t other_state, const nulluple other) && 
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Constructs a new nulluple from a noinit tag
		 * @tparam OtherState UNUSED. State of the other nulluple
		 * @param noinit No initialization tag
		 * @return The new nulluple
		 */
		template <state_t OtherState = state_t::unknown>
		[[nodiscard]] static consteval nulluple constructed_from(const noinit_t noinit)
			noexcept
		{
			return nulluple{};
		}

		/**
		 * Constructs a new nulluple from a noinit tag
		 * @tparam DynamicStates Dynamic states tag
		 * @param other_state UNUSED. State of the other nulluple
		 * @param noinit No initialization tag
		 * @return The new nulluple
		 */
		template <dynamic_states_t DynamicStates>
		[[nodiscard]] static consteval nulluple constructed_from(const state_t other_state, const noinit_t noinit)
			noexcept
		{
			return nulluple{};
		}

		/**
		 * Constructs a new nulluple from another nulluple
		 * @tparam OtherState State of the other nulluple
		 * @param other Other nulluple
		 * @return The new nulluple
		 */
		template <state_t OtherState = state_t::unknown>
		[[nodiscard]] static consteval nulluple constructed_from(const nulluple other)
			noexcept
		{
			return nulluple{};
		}

		/**
		 * Constructs a new nulluple from another nulluple
		 * @tparam DynamicStates Dynamic states tag
		 * @param other_state State of the other nulluple
		 * @param other Other nulluple
		 * @return The new nulluple
		 */
		template <dynamic_states_t DynamicStates>
		[[nodiscard]] static consteval nulluple constructed_from(const state_t other_state, const nulluple other)
			noexcept
		{
			return nulluple{};
		}

		/**
		 * Constructs to many other nulluples from current nulluple (does nothing)
		 * @tparam State State of the current nulluple
		 * @tparam OtherNulluplesStates States of the other nulluples
		 * @tparam OtherValuesTypes Types of the other nulluples
		 * @param other_values Other nulluples
		 * @return const lvalue reference to the current nulluple
		 */
		template <state_t State = state_t::unknown, state_t ...OtherNulluplesStates, typename ...OtherValuesTypes>
			requires
			(
				(
					true && 
					... && 
					std::is_same_v<nulluple, std::remove_cvref_t<OtherValuesTypes>>
				)
			)
		constexpr const nulluple &construct_to(const OtherValuesTypes ...other_values) const &
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Constructs to many other nulluples from current nulluple (does nothing)
		 * @tparam State State of the current nulluple
		 * @tparam OtherNulluplesStates States of the other nulluples
		 * @tparam OtherValuesTypes Types of the other nulluples
		 * @param other_values Other nulluples
		 * @return lvalue reference to the current nulluple
		 */
		template <state_t State = state_t::unknown, state_t ...OtherNulluplesStates, typename ...OtherValuesTypes>
			requires
			(
				(
					true&& 
					...&& 
					std::is_same_v<nulluple, std::remove_cvref_t<OtherValuesTypes>>
				)
			)
		constexpr nulluple &construct_to(const OtherValuesTypes ...other_values) & 
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY


		/**
		 * Constructs to many other nulluples from current nulluple (does nothing)
		 * @tparam State State of the current nulluple
		 * @tparam OtherNulluplesStates States of the other nulluples
		 * @tparam OtherValuesTypes Types of the other nulluples
		 * @param other_values Other nulluples
		 * @return const rvalue reference to the current nulluple
		 */
		template <state_t State = state_t::unknown, state_t ...OtherNulluplesStates, typename ...OtherValuesTypes>
			requires
			(
				(
					true&& 
					...&& 
					std::is_same_v<nulluple, std::remove_cvref_t<OtherValuesTypes>>
				)
			)
		constexpr const nulluple &&construct_to(const OtherValuesTypes ...other_values) const &&
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Constructs to many other nulluples from current nulluple (does nothing)
		 * @tparam State State of the current nulluple
		 * @tparam OtherNulluplesStates States of the other nulluples
		 * @tparam OtherValuesTypes Types of the other nulluples
		 * @param other_values Other nulluples
		 * @return rvalue reference to the current nulluple
		 */
		template <state_t State = state_t::unknown, state_t ...OtherNulluplesStates, typename ...OtherValuesTypes>
			requires
			(
				(
					true&& 
					...&& 
					std::is_same_v<nulluple, std::remove_cvref_t<OtherValuesTypes>>
				)
			)
		constexpr nulluple &&construct_to(const OtherValuesTypes ...other_values) && 
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Constructs to many other nulluples from current nulluple (does nothing)
		 * @tparam DynamicStates Dynamic states tag
		 * @tparam OtherNulluplesStatesSize Size of the states of the other nulluples
		 * @tparam OtherValuesTypes Types of the other nulluples
		 * @param state State of the current nulluple
		 * @param other_nulluple_states States of the other nulluples
		 * @param other_values Other nulluples
		 * @return const lvalue reference to the current nulluple
		 */
		template <dynamic_states_t DynamicStates, size_t OtherNulluplesStatesSize, typename ...OtherValuesTypes>
			requires
			(
				(
					true&& 
					...&& 
					std::is_same_v<nulluple, std::remove_cvref_t<OtherValuesTypes>>
				)
			)
		constexpr const nulluple &construct_to(const state_t state, const state_t (& other_nulluple_states)[OtherNulluplesStatesSize], const OtherValuesTypes ...other_values) const &
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Constructs to many other nulluples from current nulluple (does nothing)
		 * @tparam DynamicStates Dynamic states tag
		 * @tparam OtherNulluplesStatesSize Size of the states of the other nulluples
		 * @tparam OtherValuesTypes Types of the other nulluples
		 * @param state State of the current nulluple
		 * @param other_nulluple_states States of the other nulluples
		 * @param other_values Other nulluples
		 * @return const lvalue reference to the current nulluple
		 */
		template <dynamic_states_t DynamicStates, size_t OtherNulluplesStatesSize, typename ...OtherValuesTypes>
		requires
		(
			(
				true&& 
				...&& 
				std::is_same_v<nulluple, std::remove_cvref_t<OtherValuesTypes>>
			)
		)
		constexpr nulluple &construct_to(const state_t state, const state_t (& other_nulluple_states)[OtherNulluplesStatesSize], const OtherValuesTypes ...other_values) & 
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Constructs to many other nulluples from current nulluple (does nothing)
		 * @tparam DynamicStates Dynamic states tag
		 * @tparam OtherNulluplesStatesSize Size of the states of the other nulluples
		 * @tparam OtherValuesTypes Types of the other nulluples
		 * @param state State of the current nulluple
		 * @param other_nulluple_states States of the other nulluples
		 * @param other_values Other nulluples
		 * @return const lvalue reference to the current nulluple
		 */
		template <dynamic_states_t DynamicStates, size_t OtherNulluplesStatesSize, typename ...OtherValuesTypes>
		requires
		(
			(
				true&& 
				...&& 
				std::is_same_v<nulluple, std::remove_cvref_t<OtherValuesTypes>>
			)
		)
		constexpr const nulluple &&construct_to(const state_t state, const state_t (& other_nulluple_states)[OtherNulluplesStatesSize], const OtherValuesTypes ...other_values) const &&
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Constructs to many other nulluples from current nulluple (does nothing)
		 * @tparam DynamicStates Dynamic states tag
		 * @tparam OtherNulluplesStatesSize Size of the states of the other nulluples
		 * @tparam OtherValuesTypes Types of the other nulluples
		 * @param state State of the current nulluple
		 * @param other_nulluple_states States of the other nulluples
		 * @param other_values Other nulluples
		 * @return const lvalue reference to the current nulluple
		 */
		template <dynamic_states_t DynamicStates, size_t OtherNulluplesStatesSize, typename ...OtherValuesTypes>
		requires
		(
			(
				true&& 
				...&& 
				std::is_same_v<nulluple, std::remove_cvref_t<OtherValuesTypes>>
			)
		)
		constexpr nulluple &&construct_to(const state_t state, const state_t (& other_nulluple_states)[OtherNulluplesStatesSize], const OtherValuesTypes ...other_values) && 
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Constructs to many other nulluples from current nulluple (does nothing)
		 * @tparam DynamicStates Dynamic states tag
		 * @tparam OtherValuesTypes Types of the other nulluples
		 * @param state State of the current nulluple
		 * @param other_nulluple_states States of the other nulluples
		 * @param other_values Other nulluples
		 * @return const lvalue reference to the current nulluple
		 */
		template <dynamic_states_t DynamicStates, size_t OtherNulluplesStatesSize, typename ...OtherValuesTypes>
			requires
			(
				(
					true&& 
					...&& 
					std::is_same_v<nulluple, std::remove_cvref_t<OtherValuesTypes>>
				)
			)
		constexpr const nulluple &construct_to(const state_t state, const stack::vector<state_t, OtherNulluplesStatesSize>& other_nulluple_states, const OtherValuesTypes ...other_values) const &
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Constructs to many other nulluples from current nulluple (does nothing)
		 * @tparam DynamicStates Dynamic states tag
		 * @tparam OtherValuesTypes Types of the other nulluples
		 * @param state State of the current nulluple
		 * @param other_nulluple_states States of the other nulluples
		 * @param other_values Other nulluples
		 * @return lvalue reference to the current nulluple
		 */
		template <dynamic_states_t DynamicStates, size_t OtherNulluplesStatesSize, typename ...OtherValuesTypes>
			requires
			(
				(
					true&& 
					...&& 
					std::is_same_v<nulluple, std::remove_cvref_t<OtherValuesTypes>>
				)
			)
		constexpr nulluple &construct_to(const state_t state, const stack::vector<state_t, OtherNulluplesStatesSize>& other_nulluple_states, const OtherValuesTypes ...other_values) & 
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Constructs to many other nulluples from current nulluple (does nothing)
		 * @tparam DynamicStates Dynamic states tag
		 * @tparam OtherValuesTypes Types of the other nulluples
		 * @param state State of the current nulluple
		 * @param other_nulluple_states States of the other nulluples
		 * @param other_values Other nulluples
		 * @return const rvalue reference to the current nulluple
		 */
		template <dynamic_states_t DynamicStates, size_t OtherNulluplesStatesSize, typename ...OtherValuesTypes>
			requires
			(
				(
					true&& 
					...&& 
					std::is_same_v<nulluple, std::remove_cvref_t<OtherValuesTypes>>
				)
			)
		constexpr const nulluple &&construct_to(const state_t state, const stack::vector<state_t, OtherNulluplesStatesSize>& other_nulluple_states, const OtherValuesTypes ...other_values) const &&
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Constructs to many other nulluples from current nulluple (does nothing)
		 * @tparam DynamicStates Dynamic states tag
		 * @tparam OtherValuesTypes Types of the other nulluples
		 * @param state State of the current nulluple
		 * @param other_nulluple_states States of the other nulluples
		 * @param other_values Other nulluples
		 * @return rvalue reference to the current nulluple
		 */
		template <dynamic_states_t DynamicStates, size_t OtherNulluplesStatesSize, typename ...OtherValuesTypes>
			requires
			(
				(
					true&& 
					...&& 
					std::is_same_v<nulluple, std::remove_cvref_t<OtherValuesTypes>>
				)
			)
		constexpr nulluple &&construct_to(const state_t state, const stack::vector<state_t, OtherNulluplesStatesSize>& other_nulluple_states, const OtherValuesTypes ...other_values) && 
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Constructs to many other nulluples from current nulluple (does nothing)
		 * @tparam DynamicStates Dynamic states tag
		 * @tparam OtherValuesTypes Types of the other nulluples
		 * @param state State of the current nulluple
		 * @param other_nulluple_states States of the other nulluples
		 * @param other_values Other nulluples
		 * @return const lvalue reference to the current nulluple
		 */
		template <dynamic_states_t DynamicStates, typename ...OtherValuesTypes>
			requires
			(
				(
					true&& 
					...&& 
					std::is_same_v<nulluple, std::remove_cvref_t<OtherValuesTypes>>
				)
			)
		constexpr const nulluple &construct_to(const state_t state, const empty_t other_nulluple_states, const OtherValuesTypes ...other_values) const &
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Constructs to many other nulluples from current nulluple (does nothing)
		 * @tparam DynamicStates Dynamic states tag
		 * @tparam OtherValuesTypes Types of the other nulluples
		 * @param state State of the current nulluple
		 * @param other_nulluple_states States of the other nulluples
		 * @param other_values Other nulluples
		 * @return lvalue reference to the current nulluple
		 */
		template <dynamic_states_t DynamicStates, typename ...OtherValuesTypes>
			requires
			(
				(
					true&& 
					...&& 
					std::is_same_v<nulluple, std::remove_cvref_t<OtherValuesTypes>>
				)
			)
		constexpr nulluple &construct_to(const state_t state, const empty_t other_nulluple_states, const OtherValuesTypes ...other_values) & 
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
	 	 * Constructs to many other nulluples from current nulluple (does nothing)
	 	 * @tparam DynamicStates Dynamic states tag
		 * @tparam OtherValuesTypes Types of the other nulluples
		 * @param state State of the current nulluple
		 * @param other_nulluple_states States of the other nulluples
		 * @param other_values Other nulluples
		 * @return const lvalue reference to the current nulluple
		 */
		template <dynamic_states_t DynamicStates, typename ...OtherValuesTypes>
			requires
			(
				(
					true&& 
					...&& 
				std::is_same_v<nulluple, std::remove_cvref_t<OtherValuesTypes>>
				)
			)
		constexpr const nulluple &&construct_to(const state_t state, const empty_t other_nulluple_states, const OtherValuesTypes ...other_values) const &&
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Constructs to many other nulluples from current nulluple (does nothing)
		 * @tparam DynamicStates Dynamic states tag
		 * @tparam OtherValuesTypes Types of the other nulluples
		 * @param state State of the current nulluple
		 * @param other_nulluple_states States of the other nulluples
		 * @param other_values Other nulluples
		 * @return const lvalue reference to the current nulluple
		 */
		template <dynamic_states_t DynamicStates, typename ...OtherValuesTypes>
			requires
			(
				(
					true&& 
					...&& 
					std::is_same_v<nulluple, std::remove_cvref_t<OtherValuesTypes>>
				)
			)
		constexpr nulluple &&construct_to(const state_t state, const empty_t other_nulluple_states, const OtherValuesTypes ...other_values) && 
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Constructs to many other nulluples from current nulluple (does nothing)
		 * @tparam DynamicStates Dynamic states tag
		 * @tparam OtherNulluplesStatesType Type of the other nulluples' states
		 * @tparam OtherValuesTypes Types of the other nulluples
		 * @param state State of the current nulluple
		 * @param other_nulluple_states States of the other nulluples
		 * @param other_values Other nulluples
		 * @return const lvalue reference to the current nulluple
		 */
		template <dynamic_states_t DynamicStates, typename OtherNulluplesStatesType, typename ...OtherValuesTypes>
			requires
			(
				(
					requires (OtherNulluplesStatesType other_nulluple_states)
					{
						{
							other_nulluple_states.size()
						} -> std::convertible_to<size_t>;
						{
							other_nulluple_states[0]
						} -> std::same_as<state_t>;
					} ||
					requires (OtherNulluplesStatesType other_nulluple_states)
					{
						{
							*++other_nulluple_states.begin()
						} -> std::same_as<state_t>;
						other_nulluple_states.end();
					}
				) &&
				(
					true &&
					... &&
					std::is_same_v<nulluple, std::remove_cvref_t<OtherValuesTypes>>
				)
			)
		constexpr const nulluple &construct_to(const state_t state, const OtherNulluplesStatesType &other_nulluple_states, const OtherValuesTypes ...other_values) const &
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Constructs to many other nulluples from current nulluple (does nothing)
		 * @tparam DynamicStates Dynamic states tag
		 * @tparam OtherNulluplesStatesType Type of the other nulluples states
		 * @tparam OtherValuesTypes Types of the other nulluples
		 * @param state State of the current nulluple
		 * @param other_nulluple_states States of the other nulluples
		 * @param other_values Other nulluples
		 * @return const lvalue reference to the current nulluple
		 */
		template <dynamic_states_t DynamicStates, typename OtherNulluplesStatesType, typename ...OtherValuesTypes>
			requires
			(
				(
					requires (OtherNulluplesStatesType other_nulluple_states)
					{
						{
							other_nulluple_states.size()
						} -> std::convertible_to<size_t>;
						{
							other_nulluple_states[0]
						} -> std::same_as<state_t>;
					} ||
					requires (OtherNulluplesStatesType other_nulluple_states)
					{
						{
							*++other_nulluple_states.begin()
						} -> std::same_as<state_t>;
						other_nulluple_states.end();
					}
				) && 
				(
					true && 
					... && 
					std::is_same_v<nulluple, std::remove_cvref_t<OtherValuesTypes>>
				)
			)
		constexpr nulluple &construct_to(const state_t state, const OtherNulluplesStatesType& other_nulluple_states, const OtherValuesTypes ...other_values) &
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Constructs to many other nulluples from current nulluple (does nothing)
		 * @tparam DynamicStates Dynamic states tag
		 * @tparam OtherNulluplesStatesType Type of the other nulluples' states
		 * @tparam OtherValuesTypes Types of the other nulluples
		 * @param state State of the current nulluple
		 * @param other_nulluple_states States of the other nulluples
		 * @param other_values Other nulluples
		 * @return const lvalue reference to the current nulluple
		 */
		template <dynamic_states_t DynamicStates, typename OtherNulluplesStatesType, typename ...OtherValuesTypes>
			requires
			(
				(
					requires (OtherNulluplesStatesType other_nulluple_states)
					{
						{
							other_nulluple_states.size()
						} -> std::convertible_to<size_t>;
						{
							other_nulluple_states[0]
						} -> std::same_as<state_t>;
					} ||
					requires (OtherNulluplesStatesType other_nulluple_states)
					{
						{
							*++other_nulluple_states.begin()
						} -> std::same_as<state_t>;
						other_nulluple_states.end();
					}
				) &&
				(
					true &&
					... &&
					std::is_same_v<nulluple, std::remove_cvref_t<OtherValuesTypes>>
				)
			)
		constexpr const nulluple &&construct_to(const state_t state, const OtherNulluplesStatesType& other_nulluple_states, const OtherValuesTypes ...other_values) const &&
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Constructs to many other nulluples from current nulluple (does nothing)
		 * @tparam DynamicStates Dynamic states tag
		 * @tparam OtherNulluplesStatesType Type of the other nulluples' states
		 * @tparam OtherValuesTypes Types of the other nulluples
		 * @param state State of the current nulluple
		 * @param other_nulluple_states States of the other nulluples
		 * @param other_values Other nulluples
		 * @return const lvalue reference to the current nulluple
		 */
		template <dynamic_states_t DynamicStates, typename OtherNulluplesStatesType, typename ...OtherValuesTypes>
			requires
			(
				(
					requires (OtherNulluplesStatesType other_nulluple_states)
					{
						{
							other_nulluple_states.size()
						} -> std::convertible_to<size_t>;
						{
							other_nulluple_states[0]
						} -> std::same_as<state_t>;
					} ||
					requires (OtherNulluplesStatesType other_nulluple_states)
					{
						{
							*++other_nulluple_states.begin()
						} -> std::same_as<state_t>;
						other_nulluple_states.end();
					}
				) &&
				(
					true &&
					... &&
					std::is_same_v<nulluple, std::remove_cvref_t<OtherValuesTypes>>
				)
			)
		constexpr const nulluple &construct_to(const state_t state, const OtherNulluplesStatesType& other_nulluple_states, const OtherValuesTypes ...other_values) &&
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Assigns current nulluple from another nulluple (does nothing)
		 * @tparam State State of the current nulluple
		 * @tparam OtherState State of the other nulluple
		 * @param other Other nulluple
		 * @return const lvalue reference to the current nulluple
		 */
		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown>
		constexpr const nulluple &assign_from(const nulluple other) const &
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Assigns current nulluple from another nulluple (does nothing)
		 * @tparam State State of the current nulluple
		 * @tparam OtherState State of the other nulluple
		 * @param other Other nulluple
		 * @return lvalue reference to the current nulluple
		 */
		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown>
		constexpr nulluple &assign_from(const nulluple other) & 
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Assigns current nulluple from another nulluple (does nothing)
		 * @tparam State State of the current nulluple
		 * @tparam OtherState State of the other nulluple
		 * @param other Other nulluple
		 * @return const rvalue reference to the current nulluple
		 */
		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown>
		constexpr const nulluple &&assign_from(const nulluple other) const &&
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Assigns current nulluple from another nulluple (does nothing)
		 * @tparam State State of the current nulluple
		 * @tparam OtherState State of the other nulluple
		 * @param other Other nulluple
		 * @return rvalue reference to the current nulluple
		 */
		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown>
		constexpr nulluple &&assign_from(const nulluple other) && 
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY


		/**
		 * Assigns current nulluple from another nulluple (does nothing)
		 * @tparam DynamicStates Dynamic states tag
		 * @param state State of the current nulluple
		 * @param other_state State of the other nulluple
		 * @param other Other nulluple
		 * @return const lvalue reference to the current nulluple
		 */
		template <dynamic_states_t DynamicStates>
		constexpr const nulluple &assign_from(const state_t state, const state_t other_state, const nulluple other) const &
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Assigns current nulluple from another nulluple (does nothing)
		 * @tparam DynamicStates Dynamic states tag
		 * @param state State of the current nulluple
		 * @param other_state State of the other nulluple
		 * @param other Other nulluple
		 * @return lvalue reference to the current nulluple
		 */
		template <dynamic_states_t DynamicStates>
		constexpr nulluple &assign_from(const state_t state, const state_t other_state, const nulluple other) & 
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Assigns current nulluple from another nulluple (does nothing)
		 * @tparam DynamicStates Dynamic states tag
		 * @param state State of the current nulluple
		 * @param other_state State of the other nulluple
		 * @param other Other nulluple
		 * @return const rvalue reference to the current nulluple
		 */
		template <dynamic_states_t DynamicStates>
		constexpr const nulluple &&assign_from(const state_t state, const state_t other_state, const nulluple other) const &&
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Assigns current nulluple from another nulluple (does nothing)
		 * @tparam DynamicStates Dynamic states tag
		 * @param state State of the current nulluple
		 * @param other_state State of the other nulluple
		 * @param other Other nulluple
		 * @return rvalue reference to the current nulluple
		 */
		template <dynamic_states_t DynamicStates>
		constexpr nulluple &&assign_from(const state_t state, const state_t other_state, const nulluple other) && 
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Assigns from current nulluple to many other nulluples (does nothing)
		 * @tparam State State of the current nulluple
		 * @tparam OtherNulluplesStates States of the other nulluples
		 * @tparam OtherValuesTypes Types of the other nulluples
		 * @param other_values Other nulluples
		 * @return const lvalue reference to the current nulluple
		 */
		template <state_t State = state_t::unknown, state_t ...OtherNulluplesStates, typename ...OtherValuesTypes>
			requires
			(
				(
					true&& 
					...&& 
					std::is_same_v<nulluple, std::remove_cvref_t<OtherValuesTypes>>
				)
			)
		constexpr const nulluple &assign_to(const OtherValuesTypes ...other_values) const &
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Assigns from current nulluple to many other nulluples (does nothing)
		 * @tparam State State of the current nulluple
		 * @tparam OtherNulluplesStates States of the other nulluples
		 * @tparam OtherValuesTypes Types of the other nulluples
		 * @param other_values Other nulluples
		 * @return lvalue reference to the current nulluple
		 */
		template <state_t State = state_t::unknown, state_t ...OtherNulluplesStates, typename ...OtherValuesTypes>
			requires
			(
				(
					true&& 
					...&& 
					std::is_same_v<nulluple, std::remove_cvref_t<OtherValuesTypes>>
				)
			)
		constexpr nulluple &assign_to(const OtherValuesTypes ...other_values) & 
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Assigns from current nulluple to many other nulluples (does nothing)
		 * @tparam State State of the current nulluple
		 * @tparam OtherNulluplesStates States of the other nulluples
		 * @tparam OtherValuesTypes Types of the other nulluples
		 * @param other_values Other nulluples
		 * @return const rvalue reference to the current nulluple
		 */
		template <state_t State = state_t::unknown, state_t ...OtherNulluplesStates, typename ...OtherValuesTypes>
			requires
			(
				(
					true&& 
					...&& 
					std::is_same_v<nulluple, std::remove_cvref_t<OtherValuesTypes>>
				)
			)
		constexpr const nulluple &&assign_to(const OtherValuesTypes ...other_values) const &&
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Assigns from current nulluple to many other nulluples (does nothing)
		 * @tparam State State of the current nulluple
		 * @tparam OtherNulluplesStates States of the other nulluples
		 * @tparam OtherValuesTypes Types of the other nulluples
		 * @param other_values Other nulluples
		 * @return rvalue reference to the current nulluple
		 */
		template <state_t State = state_t::unknown, state_t ...OtherNulluplesStates, typename ...OtherValuesTypes>
			requires
			(
				(
					true&& 
					...&& 
					std::is_same_v<nulluple, std::remove_cvref_t<OtherValuesTypes>>
				)
			)
		constexpr nulluple &&assign_to(const OtherValuesTypes ...other_values) && 
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Assigns from current nulluple to many other nulluples (does nothing)
		 * @tparam DynamicStates Dynamic states tag
		 * @tparam OtherValuesTypes Types of the other nulluples
		 * @param state State of the current nulluple
		 * @param other_nulluple_states States of the other nulluples
		 * @param other_values Other nulluples
		 * @return const lvalue reference to the current nulluple
		 */
		template <dynamic_states_t DynamicStates, size_t OtherNulluplesStatesSize, typename ...OtherValuesTypes>
			requires
			(
				(
					true&& 
					...&& 
					std::is_same_v<nulluple, std::remove_cvref_t<OtherValuesTypes>>
				)
			)
		constexpr const nulluple &assign_to(const state_t state, const state_t (& other_nulluple_states)[OtherNulluplesStatesSize], const OtherValuesTypes ...other_values) const &
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Assigns from current nulluple to many other nulluples (does nothing)
		 * @tparam DynamicStates Dynamic states tag
		 * @tparam OtherValuesTypes Types of the other nulluples
		 * @param state State of the current nulluple
		 * @param other_nulluple_states States of the other nulluples
		 * @param other_values Other nulluples
		 * @return lvalue reference to the current nulluple
		 */
		template <dynamic_states_t DynamicStates, size_t OtherNulluplesStatesSize, typename ...OtherValuesTypes>
			requires
			(
				(
					true&& 
					...&& 
					std::is_same_v<nulluple, std::remove_cvref_t<OtherValuesTypes>>
				)
			)
		constexpr nulluple &assign_to(const state_t state, const state_t (& other_nulluple_states)[OtherNulluplesStatesSize], const OtherValuesTypes ...other_values) & 
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Assigns from current nulluple to many other nulluples (does nothing)
		 * @tparam DynamicStates Dynamic states tag
		 * @tparam OtherValuesTypes Types of the other nulluples
		 * @param state State of the current nulluple
		 * @param other_nulluple_states States of the other nulluples
		 * @param other_values Other nulluples
		 * @return const rvalue reference to the current nulluple
		 */
		template <dynamic_states_t DynamicStates, size_t OtherNulluplesStatesSize, typename ...OtherValuesTypes>
			requires
			(
				(
					true&& 
					...&& 
					std::is_same_v<nulluple, std::remove_cvref_t<OtherValuesTypes>>
				)
			)
		constexpr const nulluple &&assign_to(const state_t state, const state_t (& other_nulluple_states)[OtherNulluplesStatesSize], const OtherValuesTypes ...other_values) const &&
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Assigns from current nulluple to many other nulluples (does nothing)
		 * @tparam DynamicStates Dynamic states tag
		 * @tparam OtherValuesTypes Types of the other nulluples
		 * @param state State of the current nulluple
		 * @param other_nulluple_states States of the other nulluples
		 * @param other_values Other nulluples
		 * @return rvalue reference to the current nulluple
		 */
		template <dynamic_states_t DynamicStates, size_t OtherNulluplesStatesSize, typename ...OtherValuesTypes>
			requires
			(
				(
					true&& 
					...&& 
					std::is_same_v<nulluple, std::remove_cvref_t<OtherValuesTypes>>
				)
			)
		constexpr nulluple &&assign_to(const state_t state, const state_t (& other_nulluple_states)[OtherNulluplesStatesSize], const OtherValuesTypes ...other_values) && 
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Assigns from current nulluple to many other nulluples (does nothing)
		 * @tparam DynamicStates Dynamic states tag
		 * @tparam OtherValuesTypes Types of the other nulluples
		 * @param state State of the current nulluple
		 * @param other_nulluple_states States of the other nulluples
		 * @param other_values Other nulluples
		 * @return const lvalue reference to the current nulluple
		 */
		template <dynamic_states_t DynamicStates, size_t OtherNulluplesStatesSize, typename ...OtherValuesTypes>
			requires
			(
				(
					true&& 
					...&& 
					std::is_same_v<nulluple, std::remove_cvref_t<OtherValuesTypes>>
				)
			)
		constexpr const nulluple &assign_to(const state_t state, const stack::vector<state_t, OtherNulluplesStatesSize>& other_nulluple_states, const OtherValuesTypes ...other_values) const &
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Assigns from current nulluple to many other nulluples (does nothing)
		 * @tparam DynamicStates Dynamic states tag
		 * @tparam OtherValuesTypes Types of the other nulluples
		 * @param state State of the current nulluple
		 * @param other_nulluple_states States of the other nulluples
		 * @param other_values Other nulluples
		 * @return lvalue reference to the current nulluple
		 */
		template <dynamic_states_t DynamicStates, size_t OtherNulluplesStatesSize, typename ...OtherValuesTypes>
			requires
			(
				(
					true&& 
					...&& 
					std::is_same_v<nulluple, std::remove_cvref_t<OtherValuesTypes>>
				)
			)
		constexpr nulluple &assign_to(const state_t state, const stack::vector<state_t, OtherNulluplesStatesSize>& other_nulluple_states, const OtherValuesTypes ...other_values) & 
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Assigns from current nulluple to many other nulluples (does nothing)
		 * @tparam DynamicStates Dynamic states tag
		 * @tparam OtherValuesTypes Types of the other nulluples
		 * @param state State of the current nulluple
		 * @param other_nulluple_states States of the other nulluples
		 * @param other_values Other nulluples
		 * @return const rvalue reference to the current nulluple
		 */
		template <dynamic_states_t DynamicStates, size_t OtherNulluplesStatesSize, typename ...OtherValuesTypes>
			requires
			(
				(
					true&& 
					...&& 
					std::is_same_v<nulluple, std::remove_cvref_t<OtherValuesTypes>>
				)
			)
		constexpr const nulluple &&assign_to(const state_t state, const stack::vector<state_t, OtherNulluplesStatesSize>& other_nulluple_states, const OtherValuesTypes ...other_values) const &&
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Assigns from current nulluple to many other nulluples (does nothing)
		 * @tparam DynamicStates Dynamic states tag
		 * @tparam OtherValuesTypes Types of the other nulluples
		 * @param state State of the current nulluple
		 * @param other_nulluple_states States of the other nulluples
		 * @param other_values Other nulluples
		 * @return rvalue reference to the current nulluple
		 */
		template <dynamic_states_t DynamicStates, size_t OtherNulluplesStatesSize, typename ...OtherValuesTypes>
			requires
			(
				(
					true&& 
					...&& 
					std::is_same_v<nulluple, std::remove_cvref_t<OtherValuesTypes>>
				)
			)
		constexpr nulluple &&assign_to(const state_t state, const stack::vector<state_t, OtherNulluplesStatesSize>& other_nulluple_states, const OtherValuesTypes ...other_values) && 
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Assigns from current nulluple to many other nulluples (does nothing)
		 * @tparam DynamicStates Dynamic states tag
		 * @tparam OtherValuesTypes Types of the other nulluples
		 * @param state State of the current nulluple
		 * @param other_nulluple_states States of the other nulluples
		 * @param other_values Other nulluples
		 * @return const lvalue reference to the current nulluple
		 */
		template <dynamic_states_t DynamicStates, typename ...OtherValuesTypes>
			requires
			(
				(
					true&& 
					...&& 
					std::is_same_v<nulluple, std::remove_cvref_t<OtherValuesTypes>>
				)
			)
		constexpr const nulluple &assign_to(const state_t state, const empty_t other_nulluple_states, const OtherValuesTypes ...other_values) const &
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Assigns from current nulluple to many other nulluples (does nothing)
		 * @tparam DynamicStates Dynamic states tag
		 * @tparam OtherValuesTypes Types of the other nulluples
		 * @param state State of the current nulluple
		 * @param other_nulluple_states States of the other nulluples
		 * @param other_values Other nulluples
		 * @return lvalue reference to the current nulluple
		 */
		template <dynamic_states_t DynamicStates, size_t OtherNulluplesStatesSize, typename ...OtherValuesTypes>
			requires
			(
				(
					true&& 
					...&& 
					std::is_same_v<nulluple, std::remove_cvref_t<OtherValuesTypes>>
				)
			)
		constexpr nulluple &assign_to(const state_t state, const empty_t other_nulluple_states, const OtherValuesTypes ...other_values) & 
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Assigns from current nulluple to many other nulluples (does nothing)
		 * @tparam DynamicStates Dynamic states tag
		 * @tparam OtherValuesTypes Types of the other nulluples
		 * @param state State of the current nulluple
		 * @param other_nulluple_states States of the other nulluples
		 * @param other_values Other nulluples
		 * @return const rvalue reference to the current nulluple
		 */
		template <dynamic_states_t DynamicStates, size_t OtherNulluplesStatesSize, typename ...OtherValuesTypes>
			requires
			(
				(
					true&& 
					...&& 
					std::is_same_v<nulluple, std::remove_cvref_t<OtherValuesTypes>>
				)
			)
		constexpr const nulluple &&assign_to(const state_t state, const empty_t other_nulluple_states, const OtherValuesTypes ...other_values) const &&
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Assigns from current nulluple to many other nulluples (does nothing)
		 * @tparam DynamicStates Dynamic states tag
		 * @tparam OtherValuesTypes Types of the other nulluples
		 * @param state State of the current nulluple
		 * @param other_nulluple_states States of the other nulluples
		 * @param other_values Other nulluples
		 * @return rvalue reference to the current nulluple
		 */
		template <dynamic_states_t DynamicStates, size_t OtherNulluplesStatesSize, typename ...OtherValuesTypes>
			requires
			(
				(
					true&& 
					...&& 
					std::is_same_v<nulluple, std::remove_cvref_t<OtherValuesTypes>>
				)
			)
		constexpr nulluple &&assign_to(const state_t state, const empty_t other_nulluple_states, const OtherValuesTypes ...other_values) && 
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Constructs to many other nulluples from current nulluple (does nothing)
		 * @tparam DynamicStates Dynamic states tag
		 * @tparam OtherNulluplesStatesType Type of the other nulluples' states
		 * @tparam OtherValuesTypes Types of the other nulluples
		 * @param state State of the current nulluple
		 * @param other_nulluple_states States of the other nulluples
		 * @param other_values Other nulluples
		 * @return const lvalue reference to the current nulluple
		 */
		template <dynamic_states_t DynamicStates, typename OtherNulluplesStatesType, typename ...OtherValuesTypes>
			requires
			(
				(
					requires (OtherNulluplesStatesType other_nulluple_states)
					{
						{
							other_nulluple_states.size()
						} -> std::convertible_to<size_t>;
						{
							other_nulluple_states[0]
						} -> std::same_as<state_t>;
					} ||
					requires (OtherNulluplesStatesType other_nulluple_states)
					{
						{
							*++other_nulluple_states.begin()
						} -> std::same_as<state_t>;
						other_nulluple_states.end();
					}
				) &&
				(
					true &&
					... &&
					std::is_same_v<nulluple, std::remove_cvref_t<OtherValuesTypes>>
				)
			)
		constexpr const nulluple &assign_to(const state_t state, const OtherNulluplesStatesType& other_nulluple_states, const OtherValuesTypes ...other_values) const &
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Constructs to many other nulluples from current nulluple (does nothing)
		 * @tparam DynamicStates Dynamic states tag
		 * @tparam OtherNulluplesStatesType Type of the other nulluples' states
		 * @tparam OtherValuesTypes Types of the other nulluples
		 * @param state State of the current nulluple
		 * @param other_nulluple_states States of the other nulluples
		 * @param other_values Other nulluples
		 * @return const lvalue reference to the current nulluple
		 */
		template <dynamic_states_t DynamicStates, typename OtherNulluplesStatesType, typename ...OtherValuesTypes>
			requires
			(
				(
					requires (OtherNulluplesStatesType other_nulluple_states)
					{
						{
							other_nulluple_states.size()
						} -> std::convertible_to<size_t>;
						{
							other_nulluple_states[0]
						} -> std::same_as<state_t>;
					} ||
					requires (OtherNulluplesStatesType other_nulluple_states)
					{
						{
							*++other_nulluple_states.begin()
						} -> std::same_as<state_t>;
						other_nulluple_states.end();
					}
				) &&
				(
					true &&
					... &&
					std::is_same_v<nulluple, std::remove_cvref_t<OtherValuesTypes>>
				)
			)
		constexpr nulluple &assign_to(const state_t state, const OtherNulluplesStatesType& other_nulluple_states, const OtherValuesTypes ...other_values)&
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Constructs to many other nulluples from current nulluple (does nothing)
		 * @tparam DynamicStates Dynamic states tag
		 * @tparam OtherNulluplesStatesType Type of the other nulluples' states
		 * @tparam OtherValuesTypes Types of the other nulluples
		 * @param state State of the current nulluple
		 * @param other_nulluple_states States of the other nulluples
		 * @param other_values Other nulluples
		 * @return const lvalue reference to the current nulluple
		 */
		template <dynamic_states_t DynamicStates, typename OtherNulluplesStatesType, typename ...OtherValuesTypes>
			requires
			(
				(
					requires (OtherNulluplesStatesType other_nulluple_states)
					{
						{
							other_nulluple_states.size()
						} -> std::convertible_to<size_t>;
						{
							other_nulluple_states[0]
						} -> std::same_as<state_t>;
					} ||
					requires (OtherNulluplesStatesType other_nulluple_states)
					{
						{
							*++other_nulluple_states.begin()
						} -> std::same_as<state_t>;
						other_nulluple_states.end();
					}
				) &&
				(
					true &&
					... &&
					std::is_same_v<nulluple, std::remove_cvref_t<OtherValuesTypes>>
				)
			)
		constexpr const nulluple &&assign_to(const state_t state, const OtherNulluplesStatesType& other_nulluple_states, const OtherValuesTypes ...other_values) const &&
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Constructs to many other nulluples from current nulluple (does nothing)
		 * @tparam DynamicStates Dynamic states tag
		 * @tparam OtherNulluplesStatesType Type of the other nulluples' states
		 * @tparam OtherValuesTypes Types of the other nulluples
		 * @param state State of the current nulluple
		 * @param other_nulluple_states States of the other nulluples
		 * @param other_values Other nulluples
		 * @return const lvalue reference to the current nulluple
		 */
		template <dynamic_states_t DynamicStates, typename OtherNulluplesStatesType, typename ...OtherValuesTypes>
			requires
			(
				(
					requires (OtherNulluplesStatesType other_nulluple_states)
					{
						{
							other_nulluple_states.size()
						} -> std::convertible_to<size_t>;
						{
							other_nulluple_states[0]
						} -> std::same_as<state_t>;
					} ||
					requires (OtherNulluplesStatesType other_nulluple_states)
					{
						{
							*++other_nulluple_states.begin()
						} -> std::same_as<state_t>;
						other_nulluple_states.end();
					}
				) &&
				(
					true &&
					... &&
					std::is_same_v<nulluple, std::remove_cvref_t<OtherValuesTypes>>
				)
			)
		constexpr const nulluple &assign_to(const state_t state, const OtherNulluplesStatesType& other_nulluple_states, const OtherValuesTypes ...other_values) &&
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Emplaces fields from provided arguments, each field has its arguments separated by delimiter tag (does nothing)
		 * @tparam State State of the current nulluple
		 * @return const lvalue reference to the current nulluple
		 */
		template <state_t State = state_t::unknown>
		constexpr const nulluple &emplace_from() const &
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Emplaces fields from provided arguments, each field has its arguments separated by delimiter tag (does nothing)
		 * @tparam State State of the current nulluple
		 * @return lvalue reference to the current nulluple
		 */
		template <state_t State = state_t::unknown>
		constexpr nulluple &emplace_from() & 
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Emplaces from provided arguments (does nothing)
		 * @tparam State State of the current nulluple
		 * @return const rvalue reference to the current nulluple
		 */
		template <state_t State = state_t::unknown>
		constexpr const nulluple &&emplace_from() const &&
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Emplaces from provided arguments (does nothing)
		 * @tparam State State of the current nulluple
		 * @return rvalue reference to the current nulluple
		 */
		template <state_t State = state_t::unknown>
		constexpr nulluple &&emplace_from() && 
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Emplaces fields from provided arguments, each field has its arguments separated by delimiter tag (does nothing)
		 * @tparam DynamicStates Dynamic states tag
		 * @return const lvalue reference to the current nulluple
		 */
		template <dynamic_states_t DynamicStates>
		constexpr const nulluple &emplace_from(const state_t state) const &
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Emplaces fields from provided arguments, each field has its arguments separated by delimiter tag (does nothing)
		 * @tparam DynamicStates Dynamic states tag
		 * @param state State of the current nulluple
		 * @return lvalue reference to the current nulluple
		 */
		template <dynamic_states_t DynamicStates>
		constexpr nulluple &emplace_from(const state_t state) & 
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Emplaces from provided arguments (does nothing)
		 * @tparam DynamicStates Dynamic states tag
		 * @param state State of the current nulluple
		 * @return const rvalue reference to the current nulluple
		 */
		template <dynamic_states_t DynamicStates>
		constexpr const nulluple &&emplace_from(const state_t state, const state_t other_state) const &&
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Emplaces from provided arguments (does nothing)
		 * @tparam DynamicStates Dynamic states tag
		 * @param state State of the current nulluple
		 * @return rvalue reference to the current nulluple
		 */
		template <dynamic_states_t DynamicStates>
		constexpr nulluple &&emplace_from(const state_t state) && 
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY


		/**
		 * Emplaces from provided arguments into new nulluple (does nothing)
		 * @return new nulluple
		 */
		[[nodiscard]] static consteval nulluple emplaced_from()
			noexcept
		{
			return nulluple{};
		}

		/**
		 * Copies into current nulluple from another nulluple (does nothing)
		 * @tparam State State of the current nulluple
		 * @tparam OtherState State of the other nulluple
		 * @param other Other nulluple
		 * @return const lvalue reference to the current nulluple
		 */
		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown>
		constexpr const nulluple &copy_from(const nulluple other) const &
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Copies into current nulluple from another nulluple (does nothing)
		 * @tparam State State of the current nulluple
		 * @tparam OtherState State of the other nulluple
		 * @param other Other nulluple
		 * @return lvalue reference to the current nulluple
		 */
		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown>
		constexpr nulluple &copy_from(const nulluple other) & 
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Copies into current nulluple from another nulluple (does nothing)
		 * @tparam State State of the current nulluple
		 * @tparam OtherState State of the other nulluple
		 * @param other Other nulluple
		 * @return const rvalue reference to the current nulluple
		 */
		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown>
		constexpr const nulluple &&copy_from(const nulluple other) const &&
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Copies into current nulluple from another nulluple (does nothing)
		 * @tparam State State of the current nulluple
		 * @tparam OtherState State of the other nulluple
		 * @param other Other nulluple
		 * @return rvalue reference to the current nulluple
		 */
		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown>
		constexpr nulluple &&copy_from(const nulluple other) && 
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Copies into current nulluple from another nulluple (does nothing)
		 * @tparam DynamicStates Dynamic states tag
		 * @param state State of the current nulluple
		 * @param other_state State of the other nulluple
		 * @param other Other nulluple
		 * @return const lvalue reference to the current nulluple
		 */
		template <dynamic_states_t DynamicStates>
		constexpr const nulluple &copy_from(const state_t state, const state_t other_state, const nulluple other) const &
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Copies into current nulluple from another nulluple (does nothing)
		 * @tparam DynamicStates Dynamic states tag
		 * @param state State of the current nulluple
		 * @param other_state State of the other nulluple
		 * @param other Other nulluple
		 * @return lvalue reference to the current nulluple
		 */
		template <dynamic_states_t DynamicStates>
		constexpr nulluple &copy_from(const state_t state, const state_t other_state, const nulluple other) & 
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Copies into current nulluple from another nulluple (does nothing)
		 * @tparam DynamicStates Dynamic states tag
		 * @param state State of the current nulluple
		 * @param other_state State of the other nulluple
		 * @param other Other nulluple
		 * @return const rvalue reference to the current nulluple
		 */
		template <dynamic_states_t DynamicStates>
		constexpr const nulluple &&copy_from(const state_t state, const state_t other_state, const nulluple other) const &&
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Copies into current nulluple from another nulluple (does nothing)
		 * @tparam DynamicStates Dynamic states tag
		 * @param state State of the current nulluple
		 * @param other_state State of the other nulluple
		 * @param other Other nulluple
		 * @return rvalue reference to the current nulluple
		 */
		template <dynamic_states_t DynamicStates>
		constexpr nulluple &&copy_from(const state_t state, const state_t other_state, const nulluple other) && 
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Copies into new nulluple from another nulluple (does nothing)
		 * @tparam OtherState State of the other nulluple
		 * @param other Other nulluple
		 * @return new nulluple
		*/
		template <state_t OtherState = state_t::unknown>
		[[nodiscard]] static
#if WOJ_HAS_CXX20
			consteval
#else
			constexpr
#endif
			nulluple copied_from(const nulluple other)
			noexcept
		{
			return nulluple{ other };
		}

		/**
		 * Copies into new nulluple from another nulluple (does nothing)
		 * @tparam DynamicStates Dynamic states tag
		 * @param state State of the current nulluple
		 * @param other_state State of the other nulluple
		 * @param other Other nulluple
		 * @return new nulluple
		*/
		template <dynamic_states_t DynamicStates>
		[[nodiscard]] static
#if WOJ_HAS_CXX20
			consteval
#else
			constexpr
#endif
			nulluple copied_from(const state_t other_state, const nulluple other)
			noexcept
		{
			return nulluple{ other };
		}

		/**
		 * Copies into new nulluple from another nulluple (does nothing)
		 * @tparam DynamicStates Dynamic states tag
		 * @param state State of the current nulluple
		 * @param other_state State of the other nulluple
		 * @param other Other nulluple
		 * @return new nulluple
		*/
		template <state_t State = state_t::unknown, state_t ...OtherNulluplesStates, typename ...OtherValuesTypes>
			requires
			(
				(
					true&& 
					...&& 
					std::is_same_v<nulluple, std::remove_cvref_t<OtherValuesTypes>>
				)
			)
		constexpr const nulluple &copy_to(const OtherValuesTypes ...other_values) const &
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Copies to many other nulluples from current nulluple (does nothing)
		 * @tparam State State of the current nulluple
		 * @tparam OtherNulluplesStates States of the other nulluples
		 * @tparam OtherValuesTypes Types of the other nulluples
		 * @param other_values Other nulluples
		 * @return lvalue reference to the current nulluple
		 */
		template <state_t State = state_t::unknown, state_t ...OtherNulluplesStates, typename ...OtherValuesTypes>
			requires
			(
				(
					true&& 
					...&& 
					std::is_same_v<nulluple, std::remove_cvref_t<OtherValuesTypes>>
				)
			)
		constexpr nulluple &copy_to(const OtherValuesTypes ...other_values) & 
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Copies to many other nulluples from current nulluple (does nothing)
		 * @tparam State State of the current nulluple
		 * @tparam OtherNulluplesStates States of the other nulluples
		 * @tparam OtherValuesTypes Types of the other nulluples
		 * @param other_values Other nulluples
		 * @return const rvalue reference to the current nulluple
		 */
		template <state_t State = state_t::unknown, state_t ...OtherNulluplesStates, typename ...OtherValuesTypes>
			requires
			(
				(
					true&& 
					...&& 
					std::is_same_v<nulluple, std::remove_cvref_t<OtherValuesTypes>>
				)
			)
		constexpr const nulluple &&copy_to(const OtherValuesTypes ...other_values) const &&
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Copies to many other nulluples from current nulluple (does nothing)
		 * @tparam State State of the current nulluple
		 * @tparam OtherNulluplesStates States of the other nulluples
		 * @tparam OtherValuesTypes Types of the other nulluples
		 * @param other_values Other nulluples
		 * @return rvalue reference to the current nulluple
		 */
		template <state_t State = state_t::unknown, state_t ...OtherNulluplesStates, typename ...OtherValuesTypes>
			requires
			(
				(
					true&& 
					...&& 
					std::is_same_v<nulluple, std::remove_cvref_t<OtherValuesTypes>>
				)
			)
		constexpr nulluple &&copy_to(const OtherValuesTypes ...other_values) && 
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Copies to many other nulluples from current nulluple (does nothing)
		 * @tparam DynamicStates Dynamic states tag
		 * @tparam OtherValuesTypes Types of the other nulluples
		 * @param state State of the current nulluple
		 * @param other_nulluple_states States of the other nulluples
		 * @param other_values Other nulluples
		 * @return const lvalue reference to the current nulluple
		 */
		template <dynamic_states_t DynamicStates, size_t OtherNulluplesStatesSize, typename ...OtherValuesTypes>
			requires
			(
				(
					true&& 
					...&& 
					std::is_same_v<nulluple, std::remove_cvref_t<OtherValuesTypes>>
				)
			)
		constexpr const nulluple &copy_to(const state_t state, const state_t (& other_nulluple_states)[OtherNulluplesStatesSize], const OtherValuesTypes ...other_values) const &
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		template <dynamic_states_t DynamicStates, size_t OtherNulluplesStatesSize, typename ...OtherValuesTypes>
			requires
			(
				(
					true&& 
					...&& 
					std::is_same_v<nulluple, std::remove_cvref_t<OtherValuesTypes>>
				)
			)
		constexpr nulluple &copy_to(const state_t state, const state_t (& other_nulluple_states)[OtherNulluplesStatesSize], const OtherValuesTypes ...other_values) & 
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		template <dynamic_states_t DynamicStates, size_t OtherNulluplesStatesSize, typename ...OtherValuesTypes>
			requires
			(
				(
					true&& 
					...&& 
					std::is_same_v<nulluple, std::remove_cvref_t<OtherValuesTypes>>
				)
			)
		constexpr const nulluple &&copy_to(const state_t state, const state_t (& other_nulluple_states)[OtherNulluplesStatesSize], const OtherValuesTypes ...other_values) const &&
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		template <dynamic_states_t DynamicStates, size_t OtherNulluplesStatesSize, typename ...OtherValuesTypes>
			requires
			(
				(
					true&& 
					...&& 
					std::is_same_v<nulluple, std::remove_cvref_t<OtherValuesTypes>>
				)
			)
		constexpr nulluple &&copy_to(const state_t state, const state_t (& other_nulluple_states)[OtherNulluplesStatesSize], const OtherValuesTypes ...other_values) && 
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		template <dynamic_states_t DynamicStates, size_t OtherNulluplesStatesSize, typename ...OtherValuesTypes>
			requires
			(
				(
					true&& 
					...&& 
					std::is_same_v<nulluple, std::remove_cvref_t<OtherValuesTypes>>
				)
			)
		constexpr const nulluple &copy_to(const state_t state, const stack::vector<state_t, OtherNulluplesStatesSize>& other_nulluple_states, const OtherValuesTypes ...other_values) const &
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		template <dynamic_states_t DynamicStates, size_t OtherNulluplesStatesSize, typename ...OtherValuesTypes>
			requires
			(
				(
					true&& 
					...&& 
					std::is_same_v<nulluple, std::remove_cvref_t<OtherValuesTypes>>
				)
			)
		constexpr nulluple &copy_to(const state_t state, const stack::vector<state_t, OtherNulluplesStatesSize>& other_nulluple_states, const OtherValuesTypes ...other_values) & 
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		template <dynamic_states_t DynamicStates, size_t OtherNulluplesStatesSize, typename ...OtherValuesTypes>
			requires
			(
				(
					true&& 
					...&& 
					std::is_same_v<nulluple, std::remove_cvref_t<OtherValuesTypes>>
				)
			)
		constexpr const nulluple &&copy_to(const state_t state, const stack::vector<state_t, OtherNulluplesStatesSize>& other_nulluple_states, const OtherValuesTypes ...other_values) const &&
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		template <dynamic_states_t DynamicStates, size_t OtherNulluplesStatesSize, typename ...OtherValuesTypes>
			requires
			(
				(
					true&& 
					...&& 
					std::is_same_v<nulluple, std::remove_cvref_t<OtherValuesTypes>>
					)
			)
		constexpr nulluple &&copy_to(const state_t state, const stack::vector<state_t, OtherNulluplesStatesSize>& other_nulluple_states, const OtherValuesTypes ...other_values) && 
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		template <dynamic_states_t DynamicStates, typename ...OtherValuesTypes>
			requires
			(
				(
					true&& 
					...&& 
					std::is_same_v<nulluple, std::remove_cvref_t<OtherValuesTypes>>
				)
			)
		constexpr const nulluple &copy_to(const state_t state, const empty_t empty, const OtherValuesTypes ...other_values) const &
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		template <dynamic_states_t DynamicStates, size_t OtherNulluplesStatesSize, typename ...OtherValuesTypes>
			requires
			(
				(
					true&& 
					...&& 
					std::is_same_v<nulluple, std::remove_cvref_t<OtherValuesTypes>>
				)
			)
		constexpr nulluple &copy_to(const state_t state, const empty_t empty, const OtherValuesTypes ...other_values) & 
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		template <dynamic_states_t DynamicStates, size_t OtherNulluplesStatesSize, typename ...OtherValuesTypes>
			requires
			(
				(
					true&& 
					...&& 
					std::is_same_v<nulluple, std::remove_cvref_t<OtherValuesTypes>>
				)
			)
		constexpr const nulluple &&copy_to(const state_t state, const empty_t empty, const OtherValuesTypes ...other_values) const &&
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		template <dynamic_states_t DynamicStates, size_t OtherNulluplesStatesSize, typename ...OtherValuesTypes>
			requires
			(
				(
					true&& 
					...&& 
					std::is_same_v<nulluple, std::remove_cvref_t<OtherValuesTypes>>
				)
			)
		constexpr nulluple &&copy_to(const state_t state, const empty_t empty, const OtherValuesTypes ...other_values) && 
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Constructs to many other nulluples from current nulluple (does nothing)
		 * @tparam DynamicStates Dynamic states tag
		 * @tparam OtherNulluplesStatesType Type of the other nulluples' states
		 * @tparam OtherValuesTypes Types of the other nulluples
		 * @param state State of the current nulluple
		 * @param other_nulluple_states States of the other nulluples
		 * @param other_values Other nulluples
		 * @return const lvalue reference to the current nulluple
		 */
		template <dynamic_states_t DynamicStates, typename OtherNulluplesStatesType, typename ...OtherValuesTypes>
			requires
			(
				(
					requires (OtherNulluplesStatesType other_nulluple_states)
					{
						{
							other_nulluple_states.size()
						} -> std::convertible_to<size_t>;
						{
							other_nulluple_states[0]
						} -> std::same_as<state_t>;
					} ||
					requires (OtherNulluplesStatesType other_nulluple_states)
					{
						{
							*++other_nulluple_states.begin()
						} -> std::same_as<state_t>;
						other_nulluple_states.end();
					}
				) &&
				(
					true &&
					... &&
					std::is_same_v<nulluple, std::remove_cvref_t<OtherValuesTypes>>
				)
			)
		constexpr const nulluple &copy_to(const state_t state, const OtherNulluplesStatesType& other_nulluple_states, const OtherValuesTypes ...other_values) const &
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Constructs to many other nulluples from current nulluple (does nothing)
		 * @tparam DynamicStates Dynamic states tag
		 * @tparam OtherNulluplesStatesType Type of the other nulluples' states
		 * @tparam OtherValuesTypes Types of the other nulluples
		 * @param state State of the current nulluple
		 * @param other_nulluple_states States of the other nulluples
		 * @param other_values Other nulluples
		 * @return const lvalue reference to the current nulluple
		 */
		template <dynamic_states_t DynamicStates, typename OtherNulluplesStatesType, typename ...OtherValuesTypes>
			requires
			(
				(
					requires (OtherNulluplesStatesType other_nulluple_states)
					{
						{
							other_nulluple_states.size()
						} -> std::convertible_to<size_t>;
						{
							other_nulluple_states[0]
						} -> std::same_as<state_t>;
					} ||
					requires (OtherNulluplesStatesType other_nulluple_states)
					{
						{
							*++other_nulluple_states.begin()
						} -> std::same_as<state_t>;
						other_nulluple_states.end();
					}
				) &&
				(
					true &&
					... &&
					std::is_same_v<nulluple, std::remove_cvref_t<OtherValuesTypes>>
				)
			)
		constexpr nulluple &copy_to(const state_t state, const OtherNulluplesStatesType& other_nulluple_states, const OtherValuesTypes ...other_values)&
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Constructs to many other nulluples from current nulluple (does nothing)
		 * @tparam DynamicStates Dynamic states tag
		 * @tparam OtherNulluplesStatesType Type of the other nulluples' states
		 * @tparam OtherValuesTypes Types of the other nulluples
		 * @param state State of the current nulluple
		 * @param other_nulluple_states States of the other nulluples
		 * @param other_values Other nulluples
		 * @return const lvalue reference to the current nulluple
		 */
		template <dynamic_states_t DynamicStates, typename OtherNulluplesStatesType, typename ...OtherValuesTypes>
			requires
			(
				(
					requires (OtherNulluplesStatesType other_nulluple_states)
					{
						{
							other_nulluple_states.size()
						} -> std::convertible_to<size_t>;
						{
							other_nulluple_states[0]
						} -> std::same_as<state_t>;
					} ||
						requires (OtherNulluplesStatesType other_nulluple_states)
					{
						{
							*++other_nulluple_states.begin()
						} -> std::same_as<state_t>;
						other_nulluple_states.end();
					}
				) &&
				(
					true &&
					... &&
					std::is_same_v<nulluple, std::remove_cvref_t<OtherValuesTypes>>
				)
			)
		constexpr const nulluple &&copy_to(const state_t state, const OtherNulluplesStatesType& other_nulluple_states, const OtherValuesTypes ...other_values) const &&
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Constructs to many other nulluples from current nulluple (does nothing)
		 * @tparam DynamicStates Dynamic states tag
		 * @tparam OtherNulluplesStatesType Type of the other nulluples' states
		 * @tparam OtherValuesTypes Types of the other nulluples
		 * @param state State of the current nulluple
		 * @param other_nulluple_states States of the other nulluples
		 * @param other_values Other nulluples
		 * @return const lvalue reference to the current nulluple
		 */
		template <dynamic_states_t DynamicStates, typename OtherNulluplesStatesType, typename ...OtherValuesTypes>
			requires
			(
				(
					requires (OtherNulluplesStatesType other_nulluple_states)
					{
						{
							other_nulluple_states.size()
						} -> std::convertible_to<size_t>;
						{
							other_nulluple_states[0]
						} -> std::same_as<state_t>;
					} ||
					requires (OtherNulluplesStatesType other_nulluple_states)
					{
						{
							*++other_nulluple_states.begin()
						} -> std::same_as<state_t>;
						other_nulluple_states.end();
					}
				) &&
				(
					true &&
					... &&
					std::is_same_v<nulluple, std::remove_cvref_t<OtherValuesTypes>>
				)
			)
		constexpr const nulluple &copy_to(const state_t state, const OtherNulluplesStatesType& other_nulluple_states, const OtherValuesTypes ...other_values) &&
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown>
		constexpr const nulluple &move_from(const nulluple other) const &
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown>
		constexpr nulluple &move_from(const nulluple other) & 
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown>
		constexpr const nulluple &&move_from(const nulluple other) const &&
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown>
		constexpr nulluple &&move_from(const nulluple other) && 
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		template <dynamic_states_t DynamicStates>
		constexpr const nulluple &move_from(const state_t state, const state_t other_state, const nulluple other) const &
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		template <dynamic_states_t DynamicStates>
		constexpr nulluple &move_from(const state_t state, const state_t other_state, const nulluple other) & 
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		template <dynamic_states_t DynamicStates>
		constexpr const nulluple &&move_from(const state_t state, const state_t other_state, const nulluple other) const &&
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY;

		template <dynamic_states_t DynamicStates>
		constexpr nulluple &&move_from(const state_t state, const state_t other_state, const nulluple other) && 
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		template <state_t OtherState = state_t::unknown>
		[[nodiscard]] static consteval nulluple moved_from(const nulluple other)
			noexcept
		{
			return nulluple{};
		}

		template <dynamic_states_t DynamicStates>
		[[nodiscard]] static consteval nulluple moved_from(const state_t state, const state_t other_state, const nulluple other)
			noexcept
		{
			return nulluple{};
		}

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown>
		consteval const nulluple &move_to(const nulluple &other) const &
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY


		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown>
		constexpr nulluple &move_to(const nulluple &other) & 
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY


		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown>
		constexpr const nulluple &&move_to(const nulluple &other) const &&
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown>
		constexpr nulluple &&move_to(const nulluple &other) && 
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		template <dynamic_states_t DynamicStates>
		constexpr const nulluple &move_to(const state_t state, const state_t other_state, const nulluple &other) const &
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		template <dynamic_states_t DynamicStates>
		constexpr nulluple &move_to(const state_t state, const state_t other_state, const nulluple &other) & 
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		template <dynamic_states_t DynamicStates>
		constexpr const nulluple &&move_to(const state_t state, const state_t other_state, const nulluple &other) const &&
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		template <dynamic_states_t DynamicStates>
		constexpr nulluple &&move_to(const state_t state, const state_t other_state, const nulluple &other) && 
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		template <state_t State = state_t::unknown>
		constexpr const nulluple &reset() const &
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		template <state_t State = state_t::unknown>
		constexpr nulluple &reset() & 
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		template <state_t State = state_t::unknown>
		constexpr const nulluple &&reset() const &&
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		template <state_t State = state_t::unknown>
		constexpr nulluple &&reset() && 
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		template <dynamic_states_t DynamicStates>
		constexpr const nulluple &reset(const state_t state) const &
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		template <dynamic_states_t DynamicStates>
		constexpr nulluple &reset(const state_t state) & 
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		template <dynamic_states_t DynamicStates>
		constexpr const nulluple &&reset(const state_t state) const &&
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		template <dynamic_states_t DynamicStates>
		constexpr nulluple &&reset(const state_t state) && 
			__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		[[nodiscard]] static consteval nulluple resetted()
			noexcept
		{
			return nulluple{};
		}

		template <size_t Index>
		[[nodiscard]] static
#if defined(NDEBUG)
			consteval
#else
			constexpr
#endif
			invalid_t get
#ifndef NDEBUG
			[[noreturn]]
#endif
			()
			noexcept
#ifndef NDEBUG
			(
				false
			)
#endif
		{
#ifndef NDEBUG
			throw bad_nulluple_access{ __LINE__, "Nulluple access out of bounds.", __FILE__, __func__ };
#endif
			return invalid;
		}

		template <size_t Index>
		[[nodiscard]] static
#if defined(NDEBUG)
			consteval
#else
			constexpr
#endif
			invalid_t at
#ifndef NDEBUG
			[[noreturn]]
#endif
			()
			noexcept
#ifndef NDEBUG
			(
				false
			)
#endif
		{
#ifndef NDEBUG
			throw bad_nulluple_access{ __LINE__, "Nulluple access out of bounds.", __FILE__, __func__ };
#endif
			return invalid;
		}

		[[nodiscard]] static consteval size_t size()
			noexcept
		{
			return 0;
		}

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown>
		constexpr const nulluple &swap_with(const nulluple other) const &
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown>
		constexpr nulluple &swap_with(const nulluple other) & 
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown>
		constexpr const nulluple &&swap_with(const nulluple other) const &&
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown>
		constexpr nulluple &&swap_with(const nulluple other) && 
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		template <dynamic_states_t DynamicStates>
		constexpr const nulluple &swap_with(const state_t state, const state_t other_state, const nulluple other) const &
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		template <dynamic_states_t DynamicStates>
		constexpr nulluple &swap_with(const state_t state, const state_t other_state, const nulluple other) & 
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		template <dynamic_states_t DynamicStates>
		constexpr const nulluple &&swap_with(const state_t state, const state_t other_state, const nulluple other) const &&
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		template <dynamic_states_t DynamicStates>
		constexpr nulluple &&swap_with(const state_t state, const state_t other_state, const nulluple other) && 
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		template <state_t State = state_t::unknown, typename VisitFunctionType, typename ...VisitArgumentsTypes>
		constexpr const nulluple &visit
#ifndef NDEBUG
			[[noreturn]]
#endif
			(VisitFunctionType &&visit_function, VisitArgumentsTypes &&...visit_arguments) const &
			noexcept
#ifndef NDEBUG
			(
				false
			)
#else
			(
				std::is_nothrow_invocable_v<VisitFunctionType, VisitArgumentsTypes &&...>
			)
#endif
		{
#ifndef NDEBUG
			throw bad_nulluple_access{ __LINE__, "Nulluple access out of bounds.", __FILE__, __func__ };
#endif
			visit_function(std::forward<VisitArgumentsTypes>(visit_arguments) ...);
			return *this; 
		}

		template <state_t State = state_t::unknown, typename VisitFunctionType, typename ...VisitArgumentsTypes>
		constexpr nulluple &visit
#ifndef NDEBUG
			[[noreturn]]
#endif
			(VisitFunctionType &&visit_function, VisitArgumentsTypes &&...visit_arguments) &
			noexcept
#ifndef NDEBUG
			(
				false
			)
#else
			(
				std::is_nothrow_invocable_v<VisitFunctionType, VisitArgumentsTypes &&...>
			)
#endif
		{
#ifndef NDEBUG
			throw bad_nulluple_access{ __LINE__, "Nulluple access out of bounds.", __FILE__, __func__ };
#endif
			visit_function(std::forward<VisitArgumentsTypes>(visit_arguments) ...);
			return *this;
		}

		template <state_t State = state_t::unknown, typename VisitFunctionType, typename ...VisitArgumentsTypes>
		constexpr const nulluple &&visit
#ifndef NDEBUG
			[[noreturn]]
#endif
			(VisitFunctionType &&visit_function, VisitArgumentsTypes &&...visit_arguments) const &&
			noexcept
#ifndef NDEBUG
			(
				false
			)
#else
			(
				std::is_nothrow_invocable_v<VisitFunctionType, VisitArgumentsTypes &&...>
			)
#endif
		{
#ifndef NDEBUG
			throw bad_nulluple_access{ __LINE__, "Nulluple access out of bounds.", __FILE__, __func__ };
#endif
			visit_function(std::forward<VisitArgumentsTypes>(visit_arguments) ...);
			return *this;
		}

		template <state_t State = state_t::unknown, typename VisitFunctionType, typename ...VisitArgumentsTypes>
		constexpr nulluple &&visit
#ifndef NDEBUG
			[[noreturn]]
#endif
			(VisitFunctionType &&visit_function, VisitArgumentsTypes &&...visit_arguments) &&
			noexcept
#ifndef NDEBUG
			(
				false
			)
#else
			(
				std::is_nothrow_invocable_v<VisitFunctionType, VisitArgumentsTypes &&...>
			)
#endif
		{
#ifndef NDEBUG
			throw bad_nulluple_access{ __LINE__, "Nulluple access out of bounds.", __FILE__, __func__ };
#endif
			visit_function(std::forward<VisitArgumentsTypes>(visit_arguments) ...);
			return *this;
		}

		template <state_t State = state_t::unknown, typename VisitFunctionType, typename ...VisitArgumentsTypes>
		static
#ifndef NDEBUG
			constexpr
#else
			consteval
#endif
			nulluple visited
#ifndef NDEBUG
			[[noreturn]]
#endif
			(VisitFunctionType &&visit_function, VisitArgumentsTypes &&...visit_arguments)
			noexcept
#ifndef NDEBUG
			(
				false
			)
#endif
		{
#ifndef NDEBUG
			throw bad_nulluple_access{ __LINE__, "Nulluple access out of bounds.", __FILE__, __func__ };
#endif
			visit_function(std::forward<VisitArgumentsTypes>(visit_arguments) ...);
			return nulluple{};
		}
	};

	class bad_single_access final : public exception
	{
	public:
		bad_single_access(const size_t line, const char* const message, const char* const file, const char* const function)
			: exception{ line, message, file, function } {
		}
		bad_single_access(const bad_single_access&) = default;
		bad_single_access(bad_single_access&&) = default;
		bad_single_access& operator=(const bad_single_access&) = default;
		bad_single_access& operator=(bad_single_access&&) = default;
		~bad_single_access() = default;
	};

	template <typename FirstValueType>
	class single
	{
	public:
		enum class state_t : uint8_t
		{
			initialized,
			uninitialized,
			unknown
		};

		union
		{
			FirstValueType first;
		};

		using this_type = single;
		using first_value_type = FirstValueType;
		using value_type = FirstValueType;
		using reference = FirstValueType&;
		using const_reference = const FirstValueType&;
		using rvalue_reference = FirstValueType&&;
		using const_rvalue_reference = const FirstValueType&&;
		using pointer = FirstValueType*;
		using const_pointer = const FirstValueType*;

		constexpr single()
			noexcept
			(
				std::is_nothrow_default_constructible_v<FirstValueType>
			)
			requires
			(
				std::is_default_constructible_v<FirstValueType>
			)
			: first{} {}

		constexpr single()
			noexcept
			requires
			(
				!std::is_default_constructible_v<FirstValueType>
			) {}

		explicit constexpr single(const noinit_t noinit)
			noexcept {}

		template <typename OtherFirstValueType>
			requires
			(
				!std::is_same_v<std::remove_cvref_t<OtherFirstValueType>, single>
			)
			constexpr single(OtherFirstValueType &&first)
			noexcept
			(
				std::is_nothrow_constructible_v<FirstValueType, OtherFirstValueType &&>
			)
			: first{ std::forward<OtherFirstValueType>(first) } {}

		template <typename OtherFirstValueType>
			requires
			(
				!std::is_same_v<std::remove_cvref_t<OtherFirstValueType>, single>
			)
			constexpr single(const state_t other_state, OtherFirstValueType &&first)
			noexcept
			(
				std::is_nothrow_constructible_v<FirstValueType, OtherFirstValueType&&>
			)
			: first{ std::forward<OtherFirstValueType>(first) } {
		}

		constexpr single(const single &other)
			noexcept
			(
				std::is_nothrow_copy_constructible_v<FirstValueType>
			)
			: first{ other.first } {}

		constexpr single(single &&other)
			noexcept
			(
				std::is_nothrow_move_constructible_v<FirstValueType>
			)
			: first{ std::move(other.first) } {}

		constexpr single(const state_t other_state, const single &other)
		{
			if (other_state == state_t::initialized || other_state == state_t::unknown)
			{
				std::construct_at(std::addressof(first), other.first);
			}
			else
			{
				throw bad_single_access{ __LINE__, "Single access out of bounds.", __FILE__, __func__ };
			}
		}

		constexpr single(const state_t other_state, single &&other)
		{
			if (other_state == state_t::initialized || other_state == state_t::unknown)
			{
				std::construct_at(std::addressof(first), std::move(other.first));
			}
			else
			{
				throw bad_single_access{ __LINE__, "Single access out of bounds.", __FILE__, __func__ };
			}
		}

		template <typename ...FirstValueArgsValueTypes>
			requires
			(
				sizeof...(FirstValueArgsValueTypes) != 0
			)
		constexpr single(const in_place_t in_place, FirstValueArgsValueTypes &&...first_value_args)
			noexcept
			(
				std::is_nothrow_constructible_v<FirstValueType, FirstValueArgsValueTypes &&...>
			)
			: first{ std::forward<FirstValueArgsValueTypes>(first_value_args) ... } {
		}


		constexpr ~single()
			noexcept
			(
				std::is_nothrow_destructible_v<FirstValueType>
			)
		{
			std::destroy_at(std::addressof(first));
		}

		template <typename OtherFirstValueType>
			requires
			(
				!std::is_same_v<std::remove_cvref_t<OtherFirstValueType>, single>
			)
			constexpr single &operator=(OtherFirstValueType &&other)
			noexcept
			(
				std::is_nothrow_assignable_v<FirstValueType, OtherFirstValueType &&> ||
				(
					!std::is_assignable_v<FirstValueType, OtherFirstValueType &&> &&
					std::is_nothrow_destructible_v<FirstValueType> &&
					std::is_nothrow_constructible_v<FirstValueType, OtherFirstValueType &&>
				)
			)
		{
			if constexpr (std::is_assignable_v<FirstValueType, OtherFirstValueType &&>)
			{
				first = std::forward<OtherFirstValueType>(other);
			}
			else
			{
				std::destroy_at(std::addressof(first));
				std::construct_at(std::addressof(first), std::forward<OtherFirstValueType>(other));
			}
			return *this;
		}

		constexpr single &operator=(const single &other) & 
			noexcept
			(
				std::is_nothrow_copy_assignable_v<FirstValueType> ||
				(
					!std::is_copy_assignable_v<FirstValueType>&& 
					std::is_nothrow_copy_constructible_v<FirstValueType>&& 
					std::is_nothrow_destructible_v<FirstValueType>
				)
			)
		{
			if constexpr (std::is_copy_assignable_v<FirstValueType>)
			{
				first = other.first;
			}
			else
			{
				std::destroy_at(std::addressof(first));
				std::construct_at(std::addressof(first), other.first);
			}
			return *this;
		}

		constexpr single &&operator=(const single &other) && 
			noexcept
			(
				std::is_nothrow_copy_assignable_v<FirstValueType> ||
				(
					!std::is_copy_assignable_v<FirstValueType>&& 
					std::is_nothrow_copy_constructible_v<FirstValueType>&& 
					std::is_nothrow_destructible_v<FirstValueType>
				)
			)
		{
			if constexpr (std::is_copy_assignable_v<FirstValueType>)
			{
				first = other.first;
			}
			else
			{
				std::destroy_at(std::addressof(first));
				std::construct_at(std::addressof(first), other.first);
			}
			return *this;
		}

		constexpr single &operator=(single &&other) & 
			noexcept
			(
				std::is_nothrow_copy_assignable_v<FirstValueType> ||
				(
					!std::is_copy_assignable_v<FirstValueType>&& 
					std::is_nothrow_copy_constructible_v<FirstValueType>&& 
					std::is_nothrow_destructible_v<FirstValueType>
				)
			)
		{
			if constexpr (std::is_copy_assignable_v<FirstValueType>)
			{
				first = other.first;
			}
			else
			{
				std::destroy_at(std::addressof(first));
				std::construct_at(std::addressof(first), other.first);
			}
			return *this;
		}

		constexpr single &&operator=(single &&other) && 
			noexcept
			(
				std::is_nothrow_copy_assignable_v<FirstValueType> ||
				(
					!std::is_copy_assignable_v<FirstValueType>&& 
					std::is_nothrow_copy_constructible_v<FirstValueType>&& 
					std::is_nothrow_destructible_v<FirstValueType>
				)
			)
		{
			if constexpr (std::is_copy_assignable_v<FirstValueType>)
			{
				first = other.first;
			}
			else
			{
				std::destroy_at(std::addressof(first));
				std::construct_at(std::addressof(first), other.first);
			}
			return *this;
		}

		[[nodiscard]] explicit constexpr operator bool() const
			noexcept
		{
			return true;
		}

		[[nodiscard]] constexpr bool operator ==(const single &other) const
			noexcept
			(
				std::is_arithmetic_v<FirstValueType> ||
				std::is_pointer_v<FirstValueType>
			)
		{
			return first == other.first;
		}

		[[nodiscard]] constexpr std::strong_ordering operator <=>(const single &other) const
			noexcept
			(
				std::is_arithmetic_v<FirstValueType> ||
				std::is_pointer_v<FirstValueType>
			)
		{
			if (first < other.first)
			{
				return std::strong_ordering::less;
			}
			if (first > other.first)
			{
				return std::strong_ordering::greater;
			}
			return std::strong_ordering::equal;
		}

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown>
		constexpr const single &construct_from(const noinit_t noinit) const &
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY


		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown>
		constexpr single &construct_from(const noinit_t noinit) & 
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown>
		constexpr const single &&construct_from(const noinit_t noinit) const &&
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY


		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown>
		constexpr single &&construct_from(const noinit_t noinit) && 
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		template <dynamic_states_t DynamicStates>
		constexpr const single &construct_from(const state_t state, const state_t other_state, const noinit_t noinit) const &
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		template <dynamic_states_t DynamicStates>
		constexpr single &construct_from(const state_t state, const state_t other_state, const noinit_t noinit) & 
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		template <dynamic_states_t DynamicStates>
		constexpr const single &&construct_from(const state_t state, const state_t other_state, const noinit_t noinit) const &&
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		template <dynamic_states_t DynamicStates>
		constexpr single &&construct_from(const state_t state, const state_t other_state, const noinit_t noinit) && 
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

	private:
		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown>
		constexpr void construct_from_helper(const single &other)
#ifndef NDEBUG
			noexcept
			(
				(
					(
						State == state_t::initialized ||
						State == state_t::unknown
					) && 
					(
						OtherState == state_t::initialized ||
						OtherState == state_t::unknown
					) &&
					std::is_nothrow_destructible_v<FirstValueType> &&
					std::is_nothrow_copy_constructible_v<FirstValueType>
				) ||
				(
					State == state_t::uninitialized && 
					(
						OtherState == state_t::initialized ||
						OtherState == state_t::unknown
					) &&
					std::is_nothrow_copy_constructible_v<FirstValueType>
				)
			)
#else
			noexcept
			(
				(
					(
						State == state_t::initialized ||
						State == state_t::unknown
					)
					std::is_nothrow_destructible_v<FirstValueType> &&
					std::is_nothrow_copy_constructible_v<FirstValueType>
				) ||
				(
					State == state_t::uninitialized &&
					std::is_nothrow_copy_constructible_v<FirstValueType>
				)
			)
#endif
		{
			if constexpr
				(
					(
						State == state_t::initialized ||
						State == state_t::unknown
					) && 
					(
						OtherState == state_t::initialized ||
						OtherState == state_t::unknown
					)
				)
			{
				std::destroy_at(std::addressof(first));
				std::construct_at(std::addressof(first), other.first);
			}
			else if constexpr
				(
					State == state_t::uninitialized &&
					(
						OtherState == state_t::initialized ||
						OtherState == state_t::unknown
					)
				)
			{
				std::construct_at(std::addressof(first), other.first);
			}
#ifndef NDEBUG
			else
			{
				throw bad_single_access{ __LINE__, "Single access out of bounds.", __FILE__, __func__ };
			}
#endif
		}
	public:

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown>
		constexpr single &construct_from(const single &other) & 
#ifndef NDEBUG
			noexcept
			(
				(
					(
						State == state_t::initialized ||
						State == state_t::unknown
					) &&
					(
						OtherState == state_t::initialized ||
						OtherState == state_t::unknown
					) &&
					std::is_nothrow_destructible_v<FirstValueType>&&
					std::is_nothrow_copy_constructible_v<FirstValueType>
				) ||
				(
					State == state_t::uninitialized &&
					(
						OtherState == state_t::initialized ||
						OtherState == state_t::unknown
					) &&
					std::is_nothrow_copy_constructible_v<FirstValueType>
				)
			)
#else
			noexcept
			(
				(
					(
						State == state_t::initialized ||
						State == state_t::unknown
					)
					std::is_nothrow_destructible_v<FirstValueType>&&
					std::is_nothrow_copy_constructible_v<FirstValueType>
				) ||
				(
					State == state_t::uninitialized &&
					std::is_nothrow_copy_constructible_v<FirstValueType>
				)
			)
#endif
		{
			this->construct_from_helper<State, OtherState>(other);
			return *this;
		}

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown>
		constexpr single &&construct_from(const single &other) &&
#ifndef NDEBUG
			noexcept
			(
				(
					(
						State == state_t::initialized ||
						State == state_t::unknown
					) &&
					(
						OtherState == state_t::initialized ||
						OtherState == state_t::unknown
					) &&
					std::is_nothrow_destructible_v<FirstValueType>&&
					std::is_nothrow_copy_constructible_v<FirstValueType>
				) ||
				(
					State == state_t::uninitialized &&
					(
						OtherState == state_t::initialized ||
						OtherState == state_t::unknown
					) &&
					std::is_nothrow_copy_constructible_v<FirstValueType>
				)
			)
#else
			noexcept
			(
				(
					(
						State == state_t::initialized ||
						State == state_t::unknown
					)
					std::is_nothrow_destructible_v<FirstValueType>&&
					std::is_nothrow_copy_constructible_v<FirstValueType>
				) ||
				(
					State == state_t::uninitialized &&
					std::is_nothrow_copy_constructible_v<FirstValueType>
				)
			)
#endif
		{
			this->construct_from_helper<State, OtherState>(other);
			return *this;
		}

		private:
			template <dynamic_states_t DynamicStates>
			constexpr void construct_from_helper(const state_t state, const state_t other_state, const single &other)
				noexcept
#ifndef NDEBUG
				(
					false	
				)
#else
				(
					std::is_nothrow_destructible_v<FirstValueType> &&
					std::is_nothrow_constructible_v<FirstValueType>
				)
#endif
			{
				if
					(
						(
							state == state_t::initialized ||
							state == state_t::unknown
						) &&
						(
							other_state == state_t::initialized ||
							other_state == state_t::unknown
						)
					)
				{
					std::destroy_at(std::addressof(first));
					std::construct_at(std::addressof(first), other.first);
				}
				else if
					(
						state == state_t::uninitialized &&
						(
							other_state == state_t::initialized ||
							other_state == state_t::unknown
						)
					)
				{
					std::construct_at(std::addressof(first), other.first);
				}
#ifndef NDEBUG
				else
				{
					throw bad_single_access{ __LINE__, "Single access out of bounds.", __FILE__, __func__ };
				}
#endif
			}
	public:

		template <dynamic_states_t DynamicStates>
		constexpr single &construct_from(const state_t state, const state_t other_state, const single &other) &
			noexcept
#ifndef NDEBUG
			(
				false
			)
#else
			(
				std::is_nothrow_destructible_v<FirstValueType>&&
				std::is_nothrow_constructible_v<FirstValueType>
			)
#endif
		{
			this->construct_from_helper<dynamic_states>(state, other_state, other);
			return *this;
		}

		template <dynamic_states_t DynamicStates>
		constexpr single &&construct_from(const state_t state, const state_t other_state, const single &other) &&
			noexcept
#ifndef NDEBUG
			(
				false
			)
#else
			(
				std::is_nothrow_destructible_v<FirstValueType>&&
				std::is_nothrow_constructible_v<FirstValueType>
			)
#endif
		{
			this->construct_from_helper<dynamic_states>(state, other_state, other);
			return *this;
		}

	private:
		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown>
		constexpr void construct_from_helper(single &&other)
			noexcept
#ifndef NDEBUG
			(
				(
					(
						State == state_t::initialized ||
						State == state_t::unknown
					) &&
					(
						OtherState == state_t::initialized ||
						OtherState == state_t::unknown
					) &&
					std::is_nothrow_destructible_v<FirstValueType>&&
					std::is_nothrow_move_constructible_v<FirstValueType>
				) ||
				(
					State == state_t::uninitialized &&
					(
						OtherState == state_t::initialized ||
						OtherState == state_t::unknown
					) &&
					std::is_nothrow_move_constructible_v<FirstValueType>
				)
			)
#else
			(
				(
					(
						State == state_t::initialized ||
						State == state_t::unknown
					) &&
					std::is_nothrow_destructible_v<FirstValueType> &&
					std::is_nothrow_move_constructible_v<FirstValueType>
				) ||
				(
					State == state_t::uninitialized &&
					std::is_nothrow_move_constructible_v<FirstValueType>
				)
			)
#endif

		{
			if constexpr
				(
					(
						State == state_t::initialized ||
						State == state_t::unknown
					) &&
					(
						OtherState == state_t::initialized ||
						OtherState == state_t::unknown
					)
				)
			{
				std::destroy_at(std::addressof(first));
				std::construct_at(std::addressof(first), other.first);
			}
			else if constexpr
				(
					State == state_t::uninitialized &&
					(
						OtherState == state_t::initialized ||
						OtherState == state_t::unknown
					)
				)
			{
				std::construct_at(std::addressof(first), std::move(other.first));
			}
#ifndef NDEBUG
			else
			{
				throw bad_single_access{ __LINE__, "Single access out of bounds.", __FILE__, __func__ };
			}
#endif
		}
	public:

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown>
		constexpr single &construct_from(single &&other) &
			noexcept
#ifndef NDEBUG
			(
				(
					(
						State == state_t::initialized ||
						State == state_t::unknown
					) &&
					(
						OtherState == state_t::initialized ||
						OtherState == state_t::unknown
					) &&
					std::is_nothrow_destructible_v<FirstValueType>&&
					std::is_nothrow_move_constructible_v<FirstValueType>
				) ||
				(
					State == state_t::uninitialized &&
					(
						OtherState == state_t::initialized ||
						OtherState == state_t::unknown
					) &&
					std::is_nothrow_move_constructible_v<FirstValueType>
				)
			)
#else
			(
				(
					(
						State == state_t::initialized ||
						State == state_t::unknown
					) &&
					std::is_nothrow_destructible_v<FirstValueType>&&
					std::is_nothrow_move_constructible_v<FirstValueType>
				) ||
				(
					State == state_t::uninitialized &&
					std::is_nothrow_move_constructible_v<FirstValueType>
				)
			)
#endif
		{
			this->construct_from_helper<State, OtherState>(other);
			return *this;
		}

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown>
		constexpr single &&construct_from(single &&other) &&
			noexcept
#ifndef NDEBUG
			(
				(
					(
						State == state_t::initialized ||
						State == state_t::unknown
					) &&
					(
						OtherState == state_t::initialized ||
						OtherState == state_t::unknown
					) &&
					std::is_nothrow_destructible_v<FirstValueType>&&
					std::is_nothrow_move_constructible_v<FirstValueType>
				) ||
				(
					State == state_t::uninitialized &&
					(
						OtherState == state_t::initialized ||
						OtherState == state_t::unknown
					) &&
					std::is_nothrow_move_constructible_v<FirstValueType>
				)
			)
#else
			(
				(
					(
						State == state_t::initialized ||
						State == state_t::unknown
					) &&
					std::is_nothrow_destructible_v<FirstValueType>&&
					std::is_nothrow_move_constructible_v<FirstValueType>
				) ||
				(
					State == state_t::uninitialized &&
					std::is_nothrow_move_constructible_v<FirstValueType>
				)
			)
#endif
		{
			this->construct_from_helper<State, OtherState>(other);
			return *this;
		}

	private:
		template <dynamic_states_t DynamicStates>
		constexpr void construct_from_helper(const state_t state, const state_t other_state, single &&other)
			noexcept
#ifndef NDEBUG
			(
				false
			)
#else
			(
				std::is_nothrow_destructible_v<FirstValueType>&&
				std::is_nothrow_move_constructible_v<FirstValueType>
			)
#endif
		{
			if
				(
					(
						state == state_t::initialized ||
						state == state_t::unknown
					) &&
					(
						other_state == state_t::initialized ||
						other_state == state_t::unknown
					)
				)
			{
				std::destroy_at(std::addressof(first));
				std::construct_at(std::addressof(first), other.first);
			}
			else if
				(
					state == state_t::uninitialized &&
					(
						other_state == state_t::initialized ||
						other_state == state_t::unknown
					)
				)
			{
				std::construct_at(std::addressof(first), std::move(other.first));
			}
#ifndef NDEBUG
			else
			{
				throw bad_single_access{ __LINE__, "Single access out of bounds.", __FILE__, __func__ };
			}
#endif
		}
	public:

		template <dynamic_states_t DynamicStates>
		constexpr single &construct_from(const state_t state, const state_t other_state, single &&other) &
			noexcept
#ifndef NDEBUG
			(
				false
			)
#else
			(
				std::is_nothrow_destructible_v<FirstValueType> &&
				std::is_nothrow_move_constructible_v<FirstValueType>
			)
#endif
		{
			this->construct_from_helper<DynamicStates>(state, other_state, other);
			return *this;
		}

		template <dynamic_states_t DynamicStates>
		constexpr single &&construct_from(const state_t state, const state_t other_state, single &&other) &&
			noexcept
#ifndef NDEBUG
			(
				false
			)
#else
			(
				std::is_nothrow_destructible_v<FirstValueType>&&
				std::is_nothrow_move_constructible_v<FirstValueType>
			)
#endif
		{
			this->construct_from_helper<DynamicStates>(state, other_state, other);
			return *this;
		}

	private:
		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown, typename OtherFirstValueType>
			requires
			(
				!std::is_same_v<std::remove_cvref_t<OtherFirstValueType>, single>
			)
		constexpr void construct_from_helper(OtherFirstValueType &&other)
			noexcept
			(
				(
					(
						State == state_t::initialized ||
						State == state_t::unknown
					) &&
					std::is_nothrow_destructible_v<FirstValueType> &&
					std::is_nothrow_constructible_v<FirstValueType, OtherFirstValueType &&>
				) ||
				(
					State == state_t::uninitialized && 
					std::is_nothrow_constructible_v<FirstValueType, OtherFirstValueType &&>
				)
			)
		{
			if constexpr (State == state_t::initialized || State == state_t::unknown)
			{
				std::destroy_at(std::addressof(first));
				std::construct_at(std::addressof(first), std::forward<OtherFirstValueType>(other));
			}
			else
			{
				std::construct_at(std::addressof(first), std::forward<OtherFirstValueType>(other));
			}
		}
	public:

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown, typename OtherFirstValueType>
			requires
			(
				!std::is_same_v<std::remove_cvref_t<OtherFirstValueType>, single>
			)
		constexpr single &construct_from(OtherFirstValueType &&other) & 
			noexcept
			(
				(
					(
						State == state_t::initialized ||
						State == state_t::unknown
					) &&
					std::is_nothrow_destructible_v<FirstValueType> &&
					std::is_nothrow_constructible_v<FirstValueType, OtherFirstValueType &&>
				) ||
				(
					State == state_t::uninitialized&& 
					std::is_nothrow_constructible_v<FirstValueType, OtherFirstValueType &&>
				)
			)
		{
			this->construct_from_helper<State, OtherState>(std::forward<OtherFirstValueType>(other));

			return *this;
		}

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown, typename OtherFirstValueType>
			requires
			(
				!std::is_same_v<std::remove_cvref_t<OtherFirstValueType>, single>
			)
		constexpr single &&construct_from(OtherFirstValueType &&other) && 
			noexcept
			(
				(
					(
						State == state_t::initialized ||
						State == state_t::unknown
					) &&
					std::is_nothrow_destructible_v<FirstValueType> &&
					std::is_nothrow_constructible_v<FirstValueType, OtherFirstValueType &&>
				) ||
				(
					State == state_t::uninitialized && 
					std::is_nothrow_constructible_v<FirstValueType, OtherFirstValueType &&>
				)
			)
		{
			this->construct_from_helper<State, OtherState>(std::forward<OtherFirstValueType>(other));

			return *this;
		}

	private:

		template <dynamic_states_t DynamicStates, typename OtherFirstValueType>
			requires
			(
				!std::is_same_v<std::remove_cvref_t<OtherFirstValueType>, single>
			)
		constexpr void construct_from_helper(const state_t state, const state_t other_state, OtherFirstValueType &&other)
			noexcept
			(
				std::is_nothrow_destructible_v<FirstValueType> &&
				std::is_nothrow_constructible_v<FirstValueType, OtherFirstValueType &&>
			)
		{
			if (state == state_t::initialized || state == state_t::unknown)
			{
				std::destroy_at(std::addressof(first));
				std::construct_at(std::addressof(first), std::forward<OtherFirstValueType>(other));
			}
			else
			{
				std::construct_at(std::addressof(first), std::forward<OtherFirstValueType>(other));
			}
		}

	public:

		template <dynamic_states_t DynamicStates, typename OtherFirstValueType>
			requires
			(
				!std::is_same_v<std::remove_cvref_t<OtherFirstValueType>, single>
			)
		constexpr single &construct_from(const state_t state, const state_t other_state, OtherFirstValueType &&other) & 
			noexcept
			(
				std::is_nothrow_destructible_v<FirstValueType> &&
				std::is_nothrow_constructible_v<FirstValueType, OtherFirstValueType &&>
			)
		{
			this->construct_from_helper(state, other_state, std::forward<OtherFirstValueType>(other));
			return *this;
		}

		template <dynamic_states_t DynamicStates, typename OtherFirstValueType>
			requires
			(
				!std::is_same_v<std::remove_cvref_t<OtherFirstValueType>, single>
			)
		constexpr single &&construct_from(const state_t state, const state_t other_state, OtherFirstValueType &&other) && 
			noexcept
			(
				std::is_nothrow_destructible_v<FirstValueType> &&
				std::is_nothrow_constructible_v<FirstValueType, OtherFirstValueType &&>
			)
		{
			this->construct_from_helper(state, other_state, std::forward<OtherFirstValueType>(other));
			return *this;
		}

		template <state_t OtherState = state_t::unknown>
		[[nodiscard]] static constexpr single constructed_from(const noinit_t noinit)
			noexcept
		{
			return single{ noinit };
		}

		template <dynamic_states_t DynamicStates>
		[[nodiscard]] static constexpr single constructed_from(const state_t other_state, const noinit_t noinit)
			noexcept
		{
			return single{ noinit };
		}

		template <state_t OtherState = state_t::unknown>
		[[nodiscard]] static constexpr single constructed_from(const single &other)
			noexcept
#ifndef NDEBUG
			(
				(
					OtherState == state_t::initialized ||
					OtherState == state_t::unknown
				) &&
				std::is_nothrow_copy_constructible_v<FirstValueType>
			)
#else
			(
				std::is_nothrow_move_constructible_v<FirstValueType>
			)
#endif
		{
			single temp{ noinit };
			temp.construct_from<state_t::uninitialized, OtherState>(other);
			return std::move(temp);
		}

		template <dynamic_states_t DynamicStates>
		[[nodiscard]] static constexpr single constructed_from(const state_t other_state, const single &other)
			noexcept
#ifndef NDEBUG
			(
				false
			)
#else
			(
				std::is_nothrow_copy_constructible_v<FirstValueType>
			)
#endif
		{
			single temp{ noinit };
			temp.construct_from(state_t::uninitialized, other_state, other);
			return std::move(temp);
		}

		template <state_t OtherState = state_t::unknown>
		[[nodiscard]] static constexpr single constructed_from(single &&other)
			noexcept
#ifndef NDEBUG
			(
				(
					OtherState == state_t::initialized ||
					OtherState == state_t::unknown
				) &&
				std::is_nothrow_move_constructible_v<FirstValueType>
			)
#else
			(
				std::is_nothrow_move_constructible_v<FirstValueType>
			)
#endif
			
		{
			single temp{ noinit };
			temp.template construct_from<state_t::uninitialized, OtherState>(std::forward<single>(other));
			return std::move(temp);
		}

		template <dynamic_states_t DynamicStates>
		[[nodiscard]] static constexpr single constructed_from(const state_t other_state, single &&other)
			noexcept
#ifndef NDEBUG
			(
				false
			)
#else
			(
				std::is_nothrow_copy_constructible_v<FirstValueType>
			)
#endif
		{
			single temp{ noinit };
			temp.template construct_from<dynamic_states>(state_t::uninitialized, other_state, std::forward<single>(other));
			return std::move(temp);
		}

		template <state_t OtherState = state_t::unknown, typename OtherFirstValueType>
			requires
			(
				!std::is_same_v<std::remove_cvref_t<OtherFirstValueType>, single>
			)
		[[nodiscard]] static constexpr single constructed_from(OtherFirstValueType &&other)
			noexcept
			(
				std::is_nothrow_constructible_v<FirstValueType, OtherFirstValueType &&>
			)
		{
			single temp{ noinit };
			temp.template construct_from<state_t::uninitialized, OtherState>(std::forward<OtherFirstValueType>(other));
			return std::move(temp);
		}

		template <dynamic_states_t DynamicStates, typename OtherFirstValueType>
		[[nodiscard]] static constexpr single constructed_from(const state_t other_state, OtherFirstValueType &&other)
			noexcept
			(
				std::is_nothrow_constructible_v<FirstValueType, OtherFirstValueType &&>
			)
		{
			single temp{ noinit };
			temp.template construct_from<dynamic_states>(state_t::uninitialized, other_state, std::forward<OtherFirstValueType>(other));
			return std::move(temp);
		}

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown>
		constexpr const single &construct_to(single &other) const &
			noexcept
#ifndef NDEBUG
		(
			(
				(
					State == state_t::initialized ||
					State == state_t::unknown
				) &&
				(
					OtherState == state_t::initialized ||
					OtherState == state_t::unknown
				) &&
				std::is_nothrow_destructible_v<FirstValueType>&&
				std::is_nothrow_copy_constructible_v<FirstValueType>
			) ||
			(
				State == state_t::uninitialized &&
				OtherState == state_t::initialized &&
				std::is_nothrow_copy_constructible_v<FirstValueType>
			)
		)
#else
			(
				(
					(
						State == state_t::initialized ||
						State == state_t::unknown
					) &&
					std::is_nothrow_destructible_v<FirstValueType>&&
					std::is_nothrow_copy_constructible_v<FirstValueType>
				) ||
				(
					State == state_t::uninitialized &&
					std::is_nothrow_copy_constructible_v<FirstValueType>
				)
			)
#endif
		{
			if constexpr (State == state_t::initialized || State == state_t::unknown)
			{
				if constexpr (OtherState == state_t::initialized || OtherState == state_t::unknown)
				{
					std::destroy_at(std::addressof(other.first));
					std::construct_at(std::addressof(other.first), first);
				}
				else
				{
					std::construct_at(std::addressof(other.first), first);
				}
			}
#ifndef NDEBUG
			else
			{
				throw bad_single_access{ __LINE__, "Single access out of bounds.", __FILE__, __func__ };
			}
#endif
			return *this;
		}

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown>
		constexpr single &construct_to(single &other) &
			noexcept
#ifndef NDEBUG
			(
				(
					(
						State == state_t::initialized ||
						State == state_t::unknown
					) &&
					(
						OtherState == state_t::initialized ||
						OtherState == state_t::unknown
					) &&
					std::is_nothrow_destructible_v<FirstValueType>&&
					std::is_nothrow_copy_constructible_v<FirstValueType>
				) ||
				(
					State == state_t::uninitialized &&
					OtherState == state_t::initialized &&
					std::is_nothrow_copy_constructible_v<FirstValueType>
				)
			)
#else
			(
				(
					(
						State == state_t::initialized ||
						State == state_t::unknown
					) &&
					std::is_nothrow_destructible_v<FirstValueType>&&
					std::is_nothrow_copy_constructible_v<FirstValueType>
				) ||
				(
					State == state_t::uninitialized &&
					std::is_nothrow_copy_constructible_v<FirstValueType>
				)
			)
#endif
		{
			if constexpr (State == state_t::initialized || State == state_t::unknown)
			{
				if constexpr (OtherState == state_t::initialized || OtherState == state_t::unknown)
				{
					std::destroy_at(std::addressof(other.first));
					std::construct_at(std::addressof(other.first), first);
				}
				else
				{
					std::construct_at(std::addressof(other.first), first);
				}
			}
#ifndef NDEBUG
			else
			{
				throw bad_single_access{ __LINE__, "Single access out of bounds.", __FILE__, __func__ };
			}
#endif
			return *this;
		}

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown>
		constexpr single &&construct_to(single &other) &&
			noexcept
#ifndef NDEBUG
			(
				(
					(
						State == state_t::initialized ||
						State == state_t::unknown
					) &&
					(
						OtherState == state_t::initialized ||
						OtherState == state_t::unknown
					) &&
					std::is_nothrow_destructible_v<FirstValueType>&&
					std::is_nothrow_move_constructible_v<FirstValueType>
				) ||
				(
					State == state_t::uninitialized &&
					OtherState == state_t::initialized &&
					std::is_nothrow_move_constructible_v<FirstValueType>
				)
			)
#else
			(
				(
					(
						State == state_t::initialized ||
						State == state_t::unknown
					) &&
					std::is_nothrow_destructible_v<FirstValueType>&&
					std::is_nothrow_move_constructible_v<FirstValueType>
				) ||
				(
					State == state_t::uninitialized &&
					std::is_nothrow_move_constructible_v<FirstValueType>
				)
			)
#endif
		{
			if constexpr (State == state_t::initialized || State == state_t::unknown)
			{
				if constexpr (OtherState == state_t::initialized || OtherState == state_t::unknown)
				{
					std::destroy_at(std::addressof(other.first));
					std::construct_at(std::addressof(other.first), std::move(first));
				}
				else
				{
					std::construct_at(std::addressof(other.first), std::move(first));
				}
			}
#ifndef NDEBUG
			else
			{
				throw bad_single_access{ __LINE__, "Single access out of bounds.", __FILE__, __func__ };
			}
#endif
			return *this;
		}

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown>
		constexpr const single &&construct_to(single &other) const &&
			noexcept
#ifndef NDEBUG
			(
				(
					(
						State == state_t::initialized ||
						State == state_t::unknown
					) &&
					(
						OtherState == state_t::initialized ||
						OtherState == state_t::unknown
					) &&
					std::is_nothrow_destructible_v<FirstValueType>&&
					std::is_nothrow_copy_constructible_v<FirstValueType>
				) ||
				(
					State == state_t::uninitialized &&
					OtherState == state_t::initialized &&
					std::is_nothrow_copy_constructible_v<FirstValueType>
				)
			)
#else
			(
				(
					(
						State == state_t::initialized ||
						State == state_t::unknown
					) &&
					std::is_nothrow_destructible_v<FirstValueType>&&
					std::is_nothrow_copy_constructible_v<FirstValueType>
				) ||
				(
					State == state_t::uninitialized &&
					std::is_nothrow_copy_constructible_v<FirstValueType>
				)
			)
#endif
		{
			if constexpr (State == state_t::initialized || State == state_t::unknown)
			{
				if constexpr (OtherState == state_t::initialized || OtherState == state_t::unknown)
				{
					std::destroy_at(std::addressof(other.first));
					std::construct_at(std::addressof(other.first), first);
				}
				else
				{
					std::construct_at(std::addressof(other.first), first);
				}
			}
#ifndef NDEBUG
			else
			{
				throw bad_single_access{ __LINE__, "Single access out of bounds.", __FILE__, __func__ };
			}
#endif
			return *this;
		}

		template <dynamic_states_t DynamicStates>
		constexpr const single &construct_to(const state_t state, const state_t other_state, single &other) const &
			noexcept
#ifndef NDEBUG
			(
				false
			)
#else
			(
				std::is_nothrow_destructible_v<FirstValueType> &&
				std::is_nothrow_copy_constructible_v<FirstValueType>
			)
#endif
		{
			if (state == state_t::initialized || other_state == state_t::unknown)
			{
				if (state == state_t::initialized || other_state == state_t::unknown)
				{
					std::destroy_at(std::addressof(other.first));
					std::construct_at(std::addressof(other.first), first);
				}
				else
				{
					std::construct_at(std::addressof(other.first), first);
				}
			}
#ifndef NDEBUG
			else
			{
				throw bad_single_access{ __LINE__, "Single access out of bounds.", __FILE__, __func__ };
			}
#endif
			return *this;
		}

		template <dynamic_states_t DynamicStates>
		constexpr single &construct_to(const state_t state, const state_t other_state, single &other) &
			noexcept
#ifndef NDEBUG
			(
				false
			)
#else
			(
				std::is_nothrow_destructible_v<FirstValueType> &&
				std::is_nothrow_copy_constructible_v<FirstValueType>
			)
#endif
		{
			if (state == state_t::initialized || state == state_t::unknown)
			{
				if (other_state == state_t::initialized || other_state == state_t::unknown)
				{
					std::destroy_at(std::addressof(other.first));
					std::construct_at(std::addressof(other.first), first);
				}
				else
				{
					std::construct_at(std::addressof(other.first), first);
				}
			}
#ifndef NDEBUG
			else
			{
				throw bad_single_access{ __LINE__, "Single access out of bounds.", __FILE__, __func__ };
			}
#endif
			return *this;
		}

		template <dynamic_states_t DynamicStates>
		constexpr const single &&construct_to(const state_t state, const state_t other_state, single &other) const &&
			noexcept
#ifndef NDEBUG
			(
				false
			)
#else
			(
				std::is_nothrow_destructible_v<FirstValueType> &&
				std::is_nothrow_copy_constructible_v<FirstValueType>
			)
#endif
		{
			if (state == state_t::initialized || state == state_t::unknown)
			{
				if (other_state == state_t::initialized || other_state == state_t::unknown)
				{
					std::destroy_at(std::addressof(other.first));
					std::construct_at(std::addressof(other.first), first);
				}
				else
				{
					std::construct_at(std::addressof(other.first), first);
				}
			}
#ifndef NDEBUG
			else
			{
				throw bad_single_access{ __LINE__, "Single access out of bounds.", __FILE__, __func__ };
			}
#endif
			return *this;
		}

		template <dynamic_states_t DynamicStates>
		constexpr single &&construct_to(const state_t state, const state_t other_state, single &other) &&
			noexcept
#ifndef NDEBUG
			(
				false
			)
#else
			(
				std::is_nothrow_destructible_v<FirstValueType> &&
				std::is_nothrow_move_constructible_v<FirstValueType>
			)
#endif
		{
			if (state == state_t::initialized || other_state == state_t::unknown)
			{
				if (state == state_t::initialized || other_state == state_t::unknown)
				{
					std::destroy_at(std::addressof(other.first));
					std::construct_at(std::addressof(other.first), std::move(first));
				}
				else
				{
					std::construct_at(std::addressof(other.first), std::move(first));
				}
			}
#ifndef NDEBUG
			else
			{
				throw bad_single_access{ __LINE__, "Single access out of bounds.", __FILE__, __func__ };
			}
#endif
			return *this;
		}

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown>
		constexpr const single &construct_to(single &&other) const &
			noexcept
#ifndef NDEBUG
			(
				(
					(
						State == state_t::initialized ||
						State == state_t::unknown
					) &&
					(
						OtherState == state_t::initialized ||
						OtherState == state_t::unknown
					) &&
					std::is_nothrow_destructible_v<FirstValueType>&&
					std::is_nothrow_copy_constructible_v<FirstValueType>
				) ||
				(
					State == state_t::uninitialized &&
					OtherState == state_t::initialized &&
					std::is_nothrow_copy_constructible_v<FirstValueType>
				)
			)
#else
			(
				(
					(
						State == state_t::initialized ||
						State == state_t::unknown
					) &&
					std::is_nothrow_destructible_v<FirstValueType>&&
					std::is_nothrow_copy_constructible_v<FirstValueType>
				) ||
				(
					State == state_t::uninitialized &&
					std::is_nothrow_copy_constructible_v<FirstValueType>
				)
			)
#endif
		{
			if constexpr (State == state_t::initialized || State == state_t::unknown)
			{
				if constexpr (OtherState == state_t::initialized || OtherState == state_t::unknown)
				{
					std::destroy_at(std::addressof(other.first));
					std::construct_at(std::addressof(other.first), first);
				}
				else
				{
					std::construct_at(std::addressof(other.first), first);
				}
			}
#ifndef NDEBUG
			else
			{
				throw bad_single_access{ __LINE__, "Single access out of bounds.", __FILE__, __func__ };
			}
#endif
			return *this;
		}

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown>
		constexpr single &construct_to(single &&other) &
			noexcept
#ifndef NDEBUG
			(
				(
					(
						State == state_t::initialized ||
						State == state_t::unknown
					) &&
					(
						OtherState == state_t::initialized ||
						OtherState == state_t::unknown
					) &&
					std::is_nothrow_destructible_v<FirstValueType>&&
					std::is_nothrow_copy_constructible_v<FirstValueType>
				) ||
				(
					State == state_t::uninitialized &&
					OtherState == state_t::initialized &&
					std::is_nothrow_copy_constructible_v<FirstValueType>
				)
			)
#else
			(
				(
					(
						State == state_t::initialized ||
						State == state_t::unknown
					) &&
					std::is_nothrow_destructible_v<FirstValueType>&&
					std::is_nothrow_copy_constructible_v<FirstValueType>
				) ||
				(
					State == state_t::uninitialized &&
					std::is_nothrow_copy_constructible_v<FirstValueType>
				)
			)
#endif
		{
			if constexpr (State == state_t::initialized || State == state_t::unknown)
			{
				if constexpr (OtherState == state_t::initialized || OtherState == state_t::unknown)
				{
					std::destroy_at(std::addressof(other.first));
					std::construct_at(std::addressof(other.first), first);
				}
				else
				{
					std::construct_at(std::addressof(other.first), first);
				}
			}
#ifndef NDEBUG
			else
			{
				throw bad_single_access{ __LINE__, "Single access out of bounds.", __FILE__, __func__ };
			}
#endif
			return *this;
		}

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown>
		constexpr single &&construct_to(single &&other) &&
			noexcept
#ifndef NDEBUG
			(
				(
					(
						State == state_t::initialized ||
						State == state_t::unknown
					) &&
					(
						OtherState == state_t::initialized ||
						OtherState == state_t::unknown
					) &&
					std::is_nothrow_destructible_v<FirstValueType>&&
					std::is_nothrow_move_constructible_v<FirstValueType>
				) ||
				(
					State == state_t::uninitialized &&
					OtherState == state_t::initialized &&
					std::is_nothrow_move_constructible_v<FirstValueType>
				)
			)
#else
			(
				(
					(
						State == state_t::initialized ||
						State == state_t::unknown
					) &&
					std::is_nothrow_destructible_v<FirstValueType>&&
					std::is_nothrow_move_constructible_v<FirstValueType>
				) ||
				(
					State == state_t::uninitialized &&
					std::is_nothrow_move_constructible_v<FirstValueType>
				)
			)
#endif
		{
			if constexpr (State == state_t::initialized || State == state_t::unknown)
			{
				if constexpr (OtherState == state_t::initialized || OtherState == state_t::unknown)
				{
					std::destroy_at(std::addressof(other.first));
					std::construct_at(std::addressof(other.first), std::move(first));
				}
				else
				{
					std::construct_at(std::addressof(other.first), std::move(first));
				}
			}
#ifndef NDEBUG
			else
			{
				throw bad_single_access{ __LINE__, "Single access out of bounds.", __FILE__, __func__ };
			}
#endif
			return *this;
		}

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown>
		constexpr const single &&construct_to(single &&other) const &&
			noexcept
#ifndef NDEBUG
			(
				(
					(
						State == state_t::initialized ||
						State == state_t::unknown
					) &&
					(
						OtherState == state_t::initialized ||
						OtherState == state_t::unknown
					) &&
					std::is_nothrow_destructible_v<FirstValueType>&&
					std::is_nothrow_copy_constructible_v<FirstValueType>
				) ||
				(
					State == state_t::uninitialized &&
					OtherState == state_t::initialized &&
					std::is_nothrow_copy_constructible_v<FirstValueType>
				)
			)
#else
			(
				(
					(
						State == state_t::initialized ||
						State == state_t::unknown
					) &&
					std::is_nothrow_destructible_v<FirstValueType>&&
					std::is_nothrow_copy_constructible_v<FirstValueType>
				) ||
				(
					State == state_t::uninitialized &&
					std::is_nothrow_copy_constructible_v<FirstValueType>
				)
			)
#endif
		{
			if constexpr (State == state_t::initialized || State == state_t::unknown)
			{
				if constexpr (OtherState == state_t::initialized || OtherState == state_t::unknown)
				{
					std::destroy_at(std::addressof(other.first));
					std::construct_at(std::addressof(other.first), first);
				}
				else
				{
					std::construct_at(std::addressof(other.first), first);
				}
			}
#ifndef NDEBUG
			else
			{
				throw bad_single_access{ __LINE__, "Single access out of bounds.", __FILE__, __func__ };
			}
#endif
			return *this;
		}

		template <dynamic_states_t DynamicStates>
		constexpr const single &construct_to(const state_t state, const state_t other_state, single &&other) const &
			noexcept
#ifndef NDEBUG
			(
				false
			)
#else
			(
				std::is_nothrow_destructible_v<FirstValueType>&&
				std::is_nothrow_copy_constructible_v<FirstValueType>
			)
#endif
		{
			if (state == state_t::initialized || other_state == state_t::unknown)
			{
				std::destroy_at(std::addressof(other.first));
				std::construct_at(std::addressof(other.first), first);
			}
#ifndef NDEBUG
			else
			{
				throw bad_single_access{ __LINE__, "Single access out of bounds.", __FILE__, __func__ };
			}
#endif
			return *this;
		}

		template <dynamic_states_t DynamicStates>
		constexpr single &construct_to(const state_t state, const state_t other_state, single &&other) &
			noexcept
#ifndef NDEBUG
			(
				false
			)
#else
			(
				std::is_nothrow_destructible_v<FirstValueType>&&
				std::is_nothrow_copy_constructible_v<FirstValueType>
			)
#endif
		{
			if (state == state_t::initialized || other_state == state_t::unknown)
			{
				if (state == state_t::initialized || other_state == state_t::unknown)
				{
					std::destroy_at(std::addressof(other.first));
					std::construct_at(std::addressof(other.first), first);
				}
				else
				{
					std::construct_at(std::addressof(other.first), first);
				}
			}
#ifndef NDEBUG
			else
			{
				throw bad_single_access{ __LINE__, "Single access out of bounds.", __FILE__, __func__ };
			}
#endif
			return *this;
		}

		template <dynamic_states_t DynamicStates>
		constexpr const single &&construct_to(const state_t state, const state_t other_state, single &&other) const &&
			noexcept
#ifndef NDEBUG
			(
				false
			)
#else
			(
				std::is_nothrow_destructible_v<FirstValueType>&&
				std::is_nothrow_copy_constructible_v<FirstValueType>
			)
#endif
		{
			this->construct_to_helper<dynamic_states>(state, other_state, other);
			return *this;
		}

		template <dynamic_states_t DynamicStates>
		constexpr single &&construct_to(const state_t state, const state_t other_state, single &&other) &&
			noexcept
#ifndef NDEBUG
			(
				false
			)
#else
			(
				std::is_nothrow_destructible_v<FirstValueType>&&
				std::is_nothrow_move_constructible_v<FirstValueType>
			)
#endif
		{
			if (state == state_t::initialized || other_state == state_t::unknown)
			{
				if (state == state_t::initialized || other_state == state_t::unknown)
				{
					std::destroy_at(std::addressof(other.first));
					std::construct_at(std::addressof(other.first), std::move(first));
				}
				else
				{
					std::construct_at(std::addressof(other.first), std::move(first));
				}
			}
#ifndef NDEBUG
			else
			{
				throw bad_single_access{ __LINE__, "Single access out of bounds.", __FILE__, __func__ };
			}
#endif
			return *this;
		}

	private:

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown, typename OtherFirstValueType>
			requires
			(
				!std::is_same_v<std::remove_cvref_t<OtherFirstValueType>, single>
			)
		constexpr void construct_to_helper(OtherFirstValueType &&other) const
			noexcept
#ifndef NDEBUG
			(
				std::is_nothrow_destructible_v<FirstValueType> &&
				std::is_nothrow_constructible_v<FirstValueType, OtherFirstValueType &&>
			)
#endif
		{
			if constexpr (State == state_t::initialized || State == state_t::unknown)
			{
				std::destroy_at(std::addressof(other));
				std::construct_at(std::addressof(other), first);
			}
#ifndef NDEBUG
			else
			{
				throw bad_single_access{ __LINE__, "Single access out of bounds.", __FILE__, __func__ };
			}
#endif
		}

	public:

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown, typename OtherFirstValueType>
			requires
			(
				!std::is_same_v<std::remove_cvref_t<OtherFirstValueType>, single>
			)
		constexpr const single &construct_to(OtherFirstValueType && other) const &
			noexcept
#ifndef NDEBUG
			(
				std::is_nothrow_destructible_v<FirstValueType> &&
				std::is_nothrow_constructible_v<FirstValueType, OtherFirstValueType &&>
			)
#endif
		{
			this->template construct_to_helper<State, OtherState>(other);
			return *this;
		}

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown, typename OtherFirstValueType>
			requires
			(
				!std::is_same_v<std::remove_cvref_t<OtherFirstValueType>, single>
			)
		constexpr single &construct_to(OtherFirstValueType &&other) &
			noexcept
#ifndef NDEBUG
			(
				std::is_nothrow_destructible_v<FirstValueType> &&
				std::is_nothrow_constructible_v<FirstValueType, OtherFirstValueType &&>
			)
#endif
		{
			this->template construct_to_helper<State, OtherState>(other);
			return *this;
		}

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown, typename OtherFirstValueType>
			requires
			(
				!std::is_same_v<std::remove_cvref_t<OtherFirstValueType>, single>
			)
		constexpr const single &&construct_to(OtherFirstValueType &&other) const &&
			noexcept
#ifndef NDEBUG
			(
				std::is_nothrow_destructible_v<FirstValueType> &&
				std::is_nothrow_constructible_v<FirstValueType, OtherFirstValueType &&>
			)
#endif
		{
			this->template construct_to_helper<State, OtherState>(other);
			return *this;
		}

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown, typename OtherFirstValueType>
			requires
			(
				!std::is_same_v<std::remove_cvref_t<OtherFirstValueType>, single>
			)
		constexpr single &&construct_to(OtherFirstValueType &&other) &&
			noexcept
#ifndef NDEBUG
			(
				std::is_nothrow_destructible_v<FirstValueType> &&
				std::is_nothrow_constructible_v<FirstValueType, OtherFirstValueType &&>
			)
#endif
		{
			if (State == state_t::initialized || State == state_t::unknown)
			{
				std::destroy_at(std::addressof(other));
				std::construct_at(std::addressof(other), std::move(first));
			}
#ifndef NDEBUG
			else
			{
				throw bad_single_access{ __LINE__, "Single access out of bounds.", __FILE__, __func__ };
			}
#endif
			return *this;
		}

	private:

		template <dynamic_states_t DynamicStates, typename OtherFirstValueType>
			requires
			(
				!std::is_same_v<std::remove_cvref_t<OtherFirstValueType>, single>
			)
		constexpr void construct_to_helper(const state_t state, const state_t other_state, OtherFirstValueType &&other) const
			noexcept
#ifndef NDEBUG
			(
				false
			)
#else
			(
				std::is_nothrow_destructible_v<FirstValueType> &&
				std::is_nothrow_constructible_v<FirstValueType, OtherFirstValueType &&>
			)
#endif
		{
			if (state == state_t::initialized || state == state_t::unknown)
			{
				std::destroy_at(std::addressof(other));
				std::construct_at(std::addressof(other), first);
			}
#ifndef NDEBUG
			else
			{
				throw bad_single_access{ __LINE__, "Single access out of bounds.", __FILE__, __func__ };
			}
#endif
		}

	public:

		template <dynamic_states_t DynamicStates, typename OtherFirstValueType>
			requires
			(
				!std::is_same_v<std::remove_cvref_t<OtherFirstValueType>, single>
			)
		constexpr const single &construct_to(const state_t state, const state_t other_state, OtherFirstValueType &&other) const &
			noexcept
#ifndef NDEBUG
			(
				false
			)
#else
			(
				std::is_nothrow_destructible_v<FirstValueType> &&
				std::is_nothrow_constructible_v<FirstValueType, OtherFirstValueType &&>
			)
#endif
		{
			this->template construct_to_helper<dynamic_states>(state, other_state, other);
			return *this;
		}

		template <dynamic_states_t DynamicStates, typename OtherFirstValueType>
			requires
			(
				!std::is_same_v<std::remove_cvref_t<OtherFirstValueType>, single>
			)
		constexpr single &construct_to(const state_t state, const state_t other_state, OtherFirstValueType &&other) & 
		{
			this->template construct_to_helper<dynamic_states>(state, other_state, other);
			return *this;
		}

		template <dynamic_states_t DynamicStates, typename OtherFirstValueType>
			requires
			(
				!std::is_same_v<std::remove_cvref_t<OtherFirstValueType>, single>
			)
		constexpr const single &&construct_to(const state_t state, const state_t other_state, OtherFirstValueType &&other) const &&
		{
			this->template construct_to_helper<dynamic_states>(state, other_state, other);
			return *this;
		}

		template <dynamic_states_t DynamicStates, typename OtherFirstValueType>
			requires
			(
				!std::is_same_v<std::remove_cvref_t<OtherFirstValueType>, single>
			)
		constexpr single &&construct_to(const state_t state, const state_t other_state, OtherFirstValueType &&other) && 
		{
			if (state == state_t::initialized || state == state_t::unknown)
			{
				std::destroy_at(std::addressof(other));
				std::construct_at(std::addressof(other), first);
			}
#ifndef NDEBUG
			else
			{
				throw bad_single_access{ __LINE__, "Single access out of bounds.", __FILE__, __func__ };
			}
#endif
			return *this;
		}


	private:
		template <typename ...OthersTypes, size_t ...OthersTypesIndexes>
		static consteval
		size_t helper_count_singles(std::index_sequence<OthersTypesIndexes ...>) noexcept
		{
			using tuple_type = std::tuple<std::remove_cvref_t<OthersTypes> ...>;

			constexpr size_t res = (0 + ... + std::is_same_v<std::tuple_element_t<OthersTypesIndexes, tuple_type>, this_type>);
			return res;
		}

		template <state_t State = state_t::unknown, typename OtherValueType, size_t Index, typename ...OtherValuesTypes, state_t ...OtherSinglesStates>
		constexpr void construct_to_impl(const meta::value_sequence<OtherSinglesStates ...> other_singles_states, OtherValueType &&other_value) const &
		{
			constexpr size_t number_singles = helper_count_singles<OtherValuesTypes ...>(std::make_index_sequence<Index>());

			if constexpr (std::is_same_v<std::remove_cvref_t<OtherValueType>, this_type>)
			{
				if constexpr (number_singles < sizeof...(OtherSinglesStates))
				{
					constexpr stack::vector<state_t, sizeof...(OtherSinglesStates)> other_singles_states{ std::forward<decltype(OtherSinglesStates)>(OtherSinglesStates) ... };
					constexpr state_t other_single_state = other_singles_states[number_singles];
					this->construct_to<State, other_single_state>(std::forward<decltype(other_value)>(other_value));
				}
				else
				{
					this->construct_to<State>(std::forward<decltype(other_value)>(other_value));
				}
			}
			else
			{
				this->construct_to<State>(std::forward<decltype(other_value)>(other_value));
			}
		}

		template <state_t State = state_t::unknown, typename OtherValueType, size_t Index, typename ...OtherValuesTypes, state_t ...OtherSinglesStates>
		constexpr void construct_to_impl(const meta::value_sequence<OtherSinglesStates ...> other_singles_states, OtherValueType &&other_value) &
		{
			constexpr size_t number_singles = helper_count_singles<OtherValuesTypes ...>(std::make_index_sequence<Index>());

			if constexpr (std::is_same_v<std::remove_cvref_t<OtherValueType>, this_type>)
			{
				if constexpr (number_singles < sizeof...(OtherSinglesStates))
				{
					constexpr stack::vector<state_t, sizeof...(OtherSinglesStates)> other_singles_states{ std::forward<decltype(OtherSinglesStates)>(OtherSinglesStates) ... };
					constexpr state_t other_single_state = other_singles_states[number_singles];
					this->construct_to<State, other_single_state>(std::forward<decltype(other_value)>(other_value));
				}
				else
				{
					this->construct_to<State>(std::forward<decltype(other_value)>(other_value));
				}
			}
			else
			{
				this->construct_to<State>(std::forward<decltype(other_value)>(other_value));
			}
		}

		template <state_t State = state_t::unknown, typename OtherValueType, size_t Index, typename ...OtherValuesTypes, state_t ...OtherSinglesStates>
		constexpr void construct_to_impl(const meta::value_sequence<OtherSinglesStates ...> other_singles_states, OtherValueType &&other_value) const &&
		{
			constexpr size_t number_singles = helper_count_singles<OtherValuesTypes ...>(std::make_index_sequence<Index>());

			if constexpr (std::is_same_v<std::remove_cvref_t<OtherValueType>, this_type>)
			{
				if constexpr (number_singles < sizeof...(OtherSinglesStates))
				{
					constexpr stack::vector<state_t, sizeof...(OtherSinglesStates)> other_singles_states{ std::forward<decltype(OtherSinglesStates)>(OtherSinglesStates) ... };
					constexpr state_t other_single_state = other_singles_states[number_singles];
					this->construct_to<State, other_single_state>(std::forward<decltype(other_value)>(other_value));
				}
				else
				{
					this->construct_to<State>(std::forward<decltype(other_value)>(other_value));
				}
			}
			else
			{
				this->construct_to<State>(std::forward<decltype(other_value)>(other_value));
			}
		}

		template <state_t State = state_t::unknown, typename OtherValueType, size_t Index, typename ...OtherValuesTypes, state_t ...OtherSinglesStates>
		constexpr void construct_to_impl(const meta::value_sequence<OtherSinglesStates ...> other_singles_states, OtherValueType &&other_value) &&
		{
			constexpr size_t number_singles = helper_count_singles<OtherValuesTypes ...>(std::make_index_sequence<Index>());

			if constexpr (std::is_same_v<std::remove_cvref_t<OtherValueType>, this_type>)
			{
				if constexpr (number_singles < sizeof...(OtherSinglesStates))
				{
					constexpr stack::vector<state_t, sizeof...(OtherSinglesStates)> other_singles_states{ std::forward<decltype(OtherSinglesStates)>(OtherSinglesStates) ... };
					constexpr state_t other_single_state = other_singles_states[number_singles];
					this->construct_to<State, other_single_state>(std::forward<decltype(other_value)>(other_value));
				}
				else
				{
					this->construct_to<State>(std::forward<decltype(other_value)>(other_value));
				}
			}
			else
			{
				this->construct_to<State>(std::forward<decltype(other_value)>(other_value));
			}
		}

		template <state_t State = state_t::unknown, state_t ...OtherSinglesStates, typename ...OtherValuesTypes, size_t ...OthersTypesIndexes>
		constexpr void construct_to_helper(OtherValuesTypes &&...other_values, std::index_sequence<OthersTypesIndexes ...>) const &
		{
			(
				this->template construct_to_impl<State, OtherValuesTypes, OthersTypesIndexes, OtherValuesTypes ...>(woj::meta::value_sequence<OtherSinglesStates...>{}, std::forward<OtherValuesTypes>(other_values)), 
				...
			);
		}

		template <state_t State = state_t::unknown, state_t ...OtherSinglesStates, typename ...OtherValuesTypes, size_t ...OthersTypesIndexes>
		constexpr void construct_to_helper(OtherValuesTypes &&...other_values, std::index_sequence<OthersTypesIndexes ...>) &
		{
			(
				this->template construct_to_impl<State, OtherValuesTypes, OthersTypesIndexes, OtherValuesTypes ...>(woj::meta::value_sequence<OtherSinglesStates...>{}, std::forward<OtherValuesTypes>(other_values)),
				...
			);
		}

		template <state_t State = state_t::unknown, state_t ...OtherSinglesStates, typename ...OtherValuesTypes, size_t ...OthersTypesIndexes>
		constexpr void construct_to_helper(OtherValuesTypes &&...other_values, std::index_sequence<OthersTypesIndexes ...>) const &&
		{
			(
				this->template construct_to_impl<State, OtherValuesTypes, OthersTypesIndexes, OtherValuesTypes ...>(woj::meta::value_sequence<OtherSinglesStates...>{}, std::forward<OtherValuesTypes>(other_values)),
				...
			);
		}

		template <state_t State = state_t::unknown, state_t ...OtherSinglesStates, typename ...OtherValuesTypes, size_t ...OthersTypesIndexes>
		constexpr void construct_to_helper(OtherValuesTypes &&...other_values, std::index_sequence<OthersTypesIndexes ...>) &&
		{
			(
				this->template construct_to_impl<State, OtherValuesTypes, OthersTypesIndexes, OtherValuesTypes ...>(woj::meta::value_sequence<OtherSinglesStates...>{}, std::forward<OtherValuesTypes>(other_values)),
				...
			);
		}

	public:

		template <state_t State = state_t::unknown, state_t ...OthersSingleStates, typename ...OtherValuesTypes>
		constexpr const single &construct_to(OtherValuesTypes &&...other_values) const &
		{
			this->template construct_to_helper<State, OthersSingleStates..., OtherValuesTypes...>(std::forward<OtherValuesTypes>(other_values)..., std::make_index_sequence < sizeof...(OtherValuesTypes) > {});
			return *this;
		}

		template <state_t State = state_t::unknown, state_t ...OthersSingleStates, typename ...OtherValuesTypes>
		constexpr single &construct_to(OtherValuesTypes &&...other_values) &
		{
			this->template construct_to_helper<State, OthersSingleStates..., OtherValuesTypes...>(std::forward<OtherValuesTypes>(other_values)..., std::make_index_sequence < sizeof...(OtherValuesTypes) > {});
			return *this;
		}

		template <state_t State = state_t::unknown, state_t ...OthersSingleStates, typename ...OtherValuesTypes>
		constexpr const single &&construct_to(OtherValuesTypes &&...other_values) const &&
		{
			this->template construct_to_helper<State, OthersSingleStates..., OtherValuesTypes...>(std::forward<OtherValuesTypes>(other_values)..., std::make_index_sequence < sizeof...(OtherValuesTypes) > {});
			return *this;
		}

		template <state_t State = state_t::unknown, state_t ...OthersSingleStates, typename ...OtherValuesTypes>
		constexpr single &&construct_to(OtherValuesTypes &&...other_values) &&
		{
			this->template construct_to_helper<State, OthersSingleStates..., OtherValuesTypes...>(std::forward<OtherValuesTypes>(other_values)..., std::make_index_sequence < sizeof...(OtherValuesTypes) > {});
			return *this;
		}

	private:

		template <dynamic_states_t DynamicStates, typename OtherValueType, size_t Index, typename ...OtherValuesTypes, size_t OtherSinglesStatesSize>
		constexpr void construct_to_impl(const state_t state, const state_t (& other_singles_states)[OtherSinglesStatesSize], OtherValueType &&other_value) const &
		{
			constexpr size_t number_singles = helper_count_singles<OtherValuesTypes ...>(std::make_index_sequence<Index>());

			if constexpr (std::is_same_v<std::remove_cvref_t<OtherValueType>, this_type>)
			{
				if constexpr (number_singles < OtherSinglesStatesSize)
				{
					const state_t other_single_state = other_singles_states[number_singles];
					this->construct_to<dynamic_states>(state, other_single_state, std::forward<decltype(other_value)>(other_value));
				}
				else
				{
					this->construct_to<dynamic_states>(state, state_t::unknown, std::forward<decltype(other_value)>(other_value));
				}
			}
			else
			{
				this->construct_to<dynamic_states>(state, state_t::unknown, std::forward<decltype(other_value)>(other_value));
			}
		}

		template <dynamic_states_t DynamicStates, typename OtherValueType, size_t Index, typename ...OtherValuesTypes, size_t OtherSinglesStatesSize>
		constexpr void construct_to_impl(const state_t state, const state_t (& other_singles_states)[OtherSinglesStatesSize], OtherValueType &&other_value) &
		{
			constexpr size_t number_singles = helper_count_singles<OtherValuesTypes ...>(std::make_index_sequence<Index>());

			if constexpr (std::is_same_v<std::remove_cvref_t<OtherValueType>, this_type>)
			{
				if constexpr (number_singles < OtherSinglesStatesSize)
				{
					const state_t other_single_state = other_singles_states[number_singles];
					this->construct_to<dynamic_states>(state, other_single_state, std::forward<decltype(other_value)>(other_value));
				}
				else
				{
					this->construct_to<dynamic_states>(state, state_t::unknown, std::forward<decltype(other_value)>(other_value));
				}
			}
			else
			{
				this->construct_to<dynamic_states>(state, state_t::unknown, std::forward<decltype(other_value)>(other_value));
			}
		}

		template <dynamic_states_t DynamicStates, typename OtherValueType, size_t Index, typename ...OtherValuesTypes, size_t OtherSinglesStatesSize>
		constexpr void construct_to_impl(const state_t state, const state_t (& other_singles_states)[OtherSinglesStatesSize], OtherValueType &&other_value) const &&
		{
			constexpr size_t number_singles = helper_count_singles<OtherValuesTypes ...>(std::make_index_sequence<Index>());

			if constexpr (std::is_same_v<std::remove_cvref_t<OtherValueType>, this_type>)
			{
				if constexpr (number_singles < OtherSinglesStatesSize)
				{
					const state_t other_single_state = other_singles_states[number_singles];
					this->construct_to<dynamic_states>(state, other_single_state, std::forward<decltype(other_value)>(other_value));
				}
				else
				{
					this->construct_to<dynamic_states>(state, state_t::unknown, std::forward<decltype(other_value)>(other_value));
				}
			}
			else
			{
				this->construct_to<dynamic_states>(state, state_t::unknown, std::forward<decltype(other_value)>(other_value));
			}
		}

		template <dynamic_states_t DynamicStates, typename OtherValueType, size_t Index, typename ...OtherValuesTypes, size_t OtherSinglesStatesSize>
		constexpr void construct_to_impl(const state_t state, const state_t (& other_singles_states)[OtherSinglesStatesSize], OtherValueType &&other_value) &&
		{
			constexpr size_t number_singles = helper_count_singles<OtherValuesTypes ...>(std::make_index_sequence<Index>());

			if constexpr (std::is_same_v<std::remove_cvref_t<OtherValueType>, this_type>)
			{
				if constexpr (number_singles < OtherSinglesStatesSize)
				{
					const state_t other_single_state = other_singles_states[number_singles];
					this->construct_to<dynamic_states>(state, other_single_state, std::forward<decltype(other_value)>(other_value));
				}
				else
				{
					this->construct_to<dynamic_states>(state, state_t::unknown, std::forward<decltype(other_value)>(other_value));
				}
			}
			else
			{
				this->construct_to<dynamic_states>(state, state_t::unknown, std::forward<decltype(other_value)>(other_value));
			}
		}

		template <dynamic_states_t DynamicStates, typename ...OtherValuesTypes, size_t OtherSinglesStatesSize, size_t ...OthersTypesIndexes>
		constexpr void construct_to_helper(const state_t state, const state_t (& other_singles_states)[OtherSinglesStatesSize], OtherValuesTypes &&...other_values, std::index_sequence<OthersTypesIndexes ...>) const &
		{
			(
				this->template construct_to_impl<dynamic_states, OtherValuesTypes, OthersTypesIndexes, OtherValuesTypes ...>(state, other_singles_states, std::forward<OtherValuesTypes>(other_values)),
				...
			);
		}

		template <dynamic_states_t DynamicStates, typename ...OtherValuesTypes, size_t OtherSinglesStatesSize, size_t ...OthersTypesIndexes>
		constexpr void construct_to_helper(const state_t state, const state_t (& other_singles_states)[OtherSinglesStatesSize], OtherValuesTypes &&...other_values, std::index_sequence<OthersTypesIndexes ...>) &
		{
			(
				this->template construct_to_impl<dynamic_states, OtherValuesTypes, OthersTypesIndexes, OtherValuesTypes ...>(state, other_singles_states, std::forward<OtherValuesTypes>(other_values)),
				...
			);
		}

		template <dynamic_states_t DynamicStates, typename ...OtherValuesTypes, size_t OtherSinglesStatesSize, size_t ...OthersTypesIndexes>
		constexpr void construct_to_helper(const state_t state, const state_t (& other_singles_states)[OtherSinglesStatesSize], OtherValuesTypes &&...other_values, std::index_sequence<OthersTypesIndexes ...>) const &&
		{
			(
				this->template construct_to_impl<dynamic_states, OtherValuesTypes, OthersTypesIndexes, OtherValuesTypes ...>(state, other_singles_states, std::forward<OtherValuesTypes>(other_values)),
				...
			);
		}

		template <dynamic_states_t DynamicStates, typename ...OtherValuesTypes, size_t OtherSinglesStatesSize, size_t ...OthersTypesIndexes>
		constexpr void construct_to_helper(const state_t state, const state_t (& other_singles_states)[OtherSinglesStatesSize], OtherValuesTypes &&...other_values, std::index_sequence<OthersTypesIndexes ...>) &&
		{
			(
				this->template construct_to_impl<dynamic_states, OtherValuesTypes, OthersTypesIndexes, OtherValuesTypes ...>(state, other_singles_states, std::forward<OtherValuesTypes>(other_values)),
				...
			);
		}

	public:

		template <dynamic_states_t DynamicStates, size_t OtherSinglesStatesSize, typename ...OtherValuesTypes>
		constexpr const single &construct_to(const state_t state, const state_t (& other_singles_states)[OtherSinglesStatesSize], OtherValuesTypes &&...other_values) const &
		{
			this->template construct_to_helper<dynamic_states, OtherValuesTypes ...>(state, other_singles_states, std::forward<OtherValuesTypes>(other_values) ..., std::make_index_sequence < sizeof...(OtherValuesTypes) > {});
			return *this;
		}

		template <dynamic_states_t DynamicStates, size_t OtherSinglesStatesSize, typename ...OtherValuesTypes>
		constexpr single &construct_to(const state_t state, const state_t (& other_singles_states)[OtherSinglesStatesSize], OtherValuesTypes &&...other_values) &
		{
			this->template construct_to_helper<dynamic_states, OtherValuesTypes ...>(state, other_singles_states, std::forward<OtherValuesTypes>(other_values) ..., std::make_index_sequence < sizeof...(OtherValuesTypes) > {});
			return *this;
		}

		template <dynamic_states_t DynamicStates, size_t OtherSinglesStatesSize, typename ...OtherValuesTypes>
		constexpr const single &&construct_to(const state_t state, const state_t (& other_singles_states)[OtherSinglesStatesSize], OtherValuesTypes &&...other_values) const &&
		{
			this->template construct_to_helper<dynamic_states, OtherValuesTypes ...>(state, other_singles_states, std::forward<OtherValuesTypes>(other_values) ..., std::make_index_sequence < sizeof...(OtherValuesTypes) > {});
			return *this;
		}

		template <dynamic_states_t DynamicStates, size_t OtherSinglesStatesSize, typename ...OtherValuesTypes>
		constexpr single &&construct_to(const state_t state, const state_t (& other_singles_states)[OtherSinglesStatesSize], OtherValuesTypes &&...other_values)&
		{
			this->template construct_to_helper<dynamic_states, OtherValuesTypes ...>(state, other_singles_states, std::forward<OtherValuesTypes>(other_values) ..., std::make_index_sequence < sizeof...(OtherValuesTypes) > {});
			return *this;
		}

	private:

		template <dynamic_states_t DynamicStates, typename OtherValueType, size_t Index, typename ...OtherValuesTypes, size_t OtherSinglesStatesSize>
		constexpr void construct_to_impl(const state_t state, const stack::vector<state_t, OtherSinglesStatesSize> other_singles_states, OtherValueType &&other_value) const&
		{
			constexpr size_t number_singles = helper_count_singles<OtherValuesTypes ...>(std::make_index_sequence<Index>());

			if constexpr (std::is_same_v<std::remove_cvref_t<OtherValueType>, this_type>)
			{
				if constexpr (number_singles < OtherSinglesStatesSize)
				{
					const state_t other_single_state = other_singles_states[number_singles];
					this->construct_to<dynamic_states>(state, other_single_state, std::forward<decltype(other_value)>(other_value));
				}
				else
				{
					this->construct_to<dynamic_states>(state, state_t::unknown, std::forward<decltype(other_value)>(other_value));
				}
			}
			else
			{
				this->construct_to<dynamic_states>(state, state_t::unknown, std::forward<decltype(other_value)>(other_value));
			}
		}

		template <dynamic_states_t DynamicStates, typename OtherValueType, size_t Index, typename ...OtherValuesTypes, size_t OtherSinglesStatesSize>
		constexpr void construct_to_impl(const state_t state, const stack::vector<state_t, OtherSinglesStatesSize> other_singles_states, OtherValueType &&other_value)&
		{
			constexpr size_t number_singles = helper_count_singles<OtherValuesTypes ...>(std::make_index_sequence<Index>());

			if constexpr (std::is_same_v<std::remove_cvref_t<OtherValueType>, this_type>)
			{
				if constexpr (number_singles < OtherSinglesStatesSize)
				{
					const state_t other_single_state = other_singles_states[number_singles];
					this->construct_to<dynamic_states>(state, other_single_state, std::forward<decltype(other_value)>(other_value));
				}
				else
				{
					this->construct_to<dynamic_states>(state, state_t::unknown, std::forward<decltype(other_value)>(other_value));
				}
			}
			else
			{
				this->construct_to<dynamic_states>(state, state_t::unknown, std::forward<decltype(other_value)>(other_value));
			}
		}

		template <dynamic_states_t DynamicStates, typename OtherValueType, size_t Index, typename ...OtherValuesTypes, size_t OtherSinglesStatesSize>
		constexpr void construct_to_impl(const state_t state, const stack::vector<state_t, OtherSinglesStatesSize> other_singles_states, OtherValueType &&other_value) const&&
		{
			constexpr size_t number_singles = helper_count_singles<OtherValuesTypes ...>(std::make_index_sequence<Index>());

			if constexpr (std::is_same_v<std::remove_cvref_t<OtherValueType>, this_type>)
			{
				if constexpr (number_singles < OtherSinglesStatesSize)
				{
					const state_t other_single_state = other_singles_states[number_singles];
					this->construct_to<dynamic_states>(state, other_single_state, std::forward<decltype(other_value)>(other_value));
				}
				else
				{
					this->construct_to<dynamic_states>(state, state_t::unknown, std::forward<decltype(other_value)>(other_value));
				}
			}
			else
			{
				this->construct_to<dynamic_states>(state, state_t::unknown, std::forward<decltype(other_value)>(other_value));
			}
		}

		template <dynamic_states_t DynamicStates, typename OtherValueType, size_t Index, typename ...OtherValuesTypes, size_t OtherSinglesStatesSize>
		constexpr void construct_to_impl(const state_t state, const stack::vector<state_t, OtherSinglesStatesSize> other_singles_states, OtherValueType &&other_value)&&
		{
			constexpr size_t number_singles = helper_count_singles<OtherValuesTypes ...>(std::make_index_sequence<Index>());

			if constexpr (std::is_same_v<std::remove_cvref_t<OtherValueType>, this_type>)
			{
				if constexpr (number_singles < OtherSinglesStatesSize)
				{
					const state_t other_single_state = other_singles_states[number_singles];
					this->construct_to<dynamic_states>(state, other_single_state, std::forward<decltype(other_value)>(other_value));
				}
				else
				{
					this->construct_to<dynamic_states>(state, state_t::unknown, std::forward<decltype(other_value)>(other_value));
				}
			}
			else
			{
				this->construct_to<dynamic_states>(state, state_t::unknown, std::forward<decltype(other_value)>(other_value));
			}
		}

		template <dynamic_states_t DynamicStates, typename ...OtherValuesTypes, size_t OtherSinglesStatesSize, size_t ...OthersTypesIndexes>
		constexpr void construct_to_helper(const state_t state, const stack::vector<state_t, OtherSinglesStatesSize> other_singles_states, OtherValuesTypes &&...other_values, std::index_sequence<OthersTypesIndexes ...>) const&
		{
			(
				this->template construct_to_impl<dynamic_states, OtherValuesTypes, OthersTypesIndexes, OtherValuesTypes ...>(state, other_singles_states, std::forward<OtherValuesTypes>(other_values)),
				...
			);
		}

		template <dynamic_states_t DynamicStates, typename ...OtherValuesTypes, size_t OtherSinglesStatesSize, size_t ...OthersTypesIndexes>
		constexpr void construct_to_helper(const state_t state, const stack::vector<state_t, OtherSinglesStatesSize> other_singles_states, OtherValuesTypes &&...other_values, std::index_sequence<OthersTypesIndexes ...>)&
		{
			(
				this->template construct_to_impl<dynamic_states, OtherValuesTypes, OthersTypesIndexes, OtherValuesTypes ...>(state, other_singles_states, std::forward<OtherValuesTypes>(other_values)),
				...
			);
		}

		template <dynamic_states_t DynamicStates, typename ...OtherValuesTypes, size_t OtherSinglesStatesSize, size_t ...OthersTypesIndexes>
		constexpr void construct_to_helper(const state_t state, const stack::vector<state_t, OtherSinglesStatesSize> other_singles_states, OtherValuesTypes &&...other_values, std::index_sequence<OthersTypesIndexes ...>) const&&
		{
			(
				this->template construct_to_impl<dynamic_states, OtherValuesTypes, OthersTypesIndexes, OtherValuesTypes ...>(state, other_singles_states, std::forward<OtherValuesTypes>(other_values)),
				...
			);
		}

		template <dynamic_states_t DynamicStates, typename ...OtherValuesTypes, size_t OtherSinglesStatesSize, size_t ...OthersTypesIndexes>
		constexpr void construct_to_helper(const state_t state, const stack::vector<state_t, OtherSinglesStatesSize> other_singles_states, OtherValuesTypes &&...other_values, std::index_sequence<OthersTypesIndexes ...>)&&
		{
			(
				this->template construct_to_impl<dynamic_states, OtherValuesTypes, OthersTypesIndexes, OtherValuesTypes ...>(state, other_singles_states, std::forward<OtherValuesTypes>(other_values)),
				...
			);
		}

	public:

		template <dynamic_states_t DynamicStates, size_t OtherSinglesStatesSize, typename ...OtherValuesTypes>
		constexpr const single &construct_to(const state_t state, const stack::vector<state_t, OtherSinglesStatesSize> other_singles_states, OtherValuesTypes &&...other_values) const&
		{
			this->template construct_to_helper<dynamic_states, OtherValuesTypes ...>(state, other_singles_states, std::forward<OtherValuesTypes>(other_values) ..., std::make_index_sequence < sizeof...(OtherValuesTypes) > {});
			return *this;
		}

		template <dynamic_states_t DynamicStates, size_t OtherSinglesStatesSize, typename ...OtherValuesTypes>
		constexpr single &construct_to(const state_t state, const stack::vector<state_t, OtherSinglesStatesSize> other_singles_states, OtherValuesTypes &&...other_values)&
		{
			this->template construct_to_helper<dynamic_states, OtherValuesTypes ...>(state, other_singles_states, std::forward<OtherValuesTypes>(other_values) ..., std::make_index_sequence < sizeof...(OtherValuesTypes) > {});
			return *this;
		}

		template <dynamic_states_t DynamicStates, size_t OtherSinglesStatesSize, typename ...OtherValuesTypes>
		constexpr const single&& construct_to(const state_t state, const stack::vector<state_t, OtherSinglesStatesSize> other_singles_states, OtherValuesTypes &&...other_values) const&&
		{
			this->template construct_to_helper<dynamic_states, OtherValuesTypes ...>(state, other_singles_states, std::forward<OtherValuesTypes>(other_values) ..., std::make_index_sequence < sizeof...(OtherValuesTypes) > {});
			return *this;
		}

		template <dynamic_states_t DynamicStates, size_t OtherSinglesStatesSize, typename ...OtherValuesTypes>
		constexpr single&& construct_to(const state_t state, const stack::vector<state_t, OtherSinglesStatesSize> other_singles_states, OtherValuesTypes &&...other_values)&
		{
			this->template construct_to_helper<dynamic_states, OtherValuesTypes ...>(state, other_singles_states, std::forward<OtherValuesTypes>(other_values) ..., std::make_index_sequence < sizeof...(OtherValuesTypes) > {});
			return *this;
		}

	private:

		template <dynamic_states_t DynamicStates, typename OtherValueType, size_t Index, typename ...OtherValuesTypes>
		constexpr void construct_to_impl(const state_t state, const empty_t other_singles_states, OtherValueType &&other_value) const&
		{
			this->construct_to<dynamic_states>(state, state_t::unknown, std::forward<decltype(other_value)>(other_value));
		}

		template <dynamic_states_t DynamicStates, typename OtherValueType, size_t Index, typename ...OtherValuesTypes, size_t OtherSinglesStatesSize>
		constexpr void construct_to_impl(const state_t state, const empty_t other_singles_states, OtherValueType &&other_value)&
		{
			this->construct_to<dynamic_states>(state, state_t::unknown, std::forward<decltype(other_value)>(other_value));
		}

		template <dynamic_states_t DynamicStates, typename OtherValueType, size_t Index, typename ...OtherValuesTypes, size_t OtherSinglesStatesSize>
		constexpr void construct_to_impl(const state_t state, const empty_t other_singles_states, OtherValueType &&other_value) const&&
		{
			this->construct_to<dynamic_states>(state, state_t::unknown, std::forward<decltype(other_value)>(other_value));
		}

		template <dynamic_states_t DynamicStates, typename OtherValueType, size_t Index, typename ...OtherValuesTypes, size_t OtherSinglesStatesSize>
		constexpr void construct_to_impl(const state_t state, const empty_t other_singles_states, OtherValueType &&other_value)&&
		{
			this->construct_to<dynamic_states>(state, state_t::unknown, std::forward<decltype(other_value)>(other_value));
		}

		template <dynamic_states_t DynamicStates, typename ...OtherValuesTypes, size_t OtherSinglesStatesSize, size_t ...OthersTypesIndexes>
		constexpr void construct_to_helper(const state_t state, const empty_t other_singles_states, OtherValuesTypes &&...other_values, std::index_sequence<OthersTypesIndexes ...>) const&
		{
			(
				this->construct_to_impl<dynamic_states, OtherValuesTypes, OthersTypesIndexes, OtherValuesTypes ...>(state, other_singles_states, std::forward<OtherValuesTypes>(other_values)),
				...
			);
		}

		template <dynamic_states_t DynamicStates, typename ...OtherValuesTypes, size_t OtherSinglesStatesSize, size_t ...OthersTypesIndexes>
		constexpr void construct_to_helper(const state_t state, const empty_t other_singles_states, OtherValuesTypes &&...other_values, std::index_sequence<OthersTypesIndexes ...>)&
		{
			(
				this->construct_to_impl<dynamic_states, OtherValuesTypes, OthersTypesIndexes, OtherValuesTypes ...>(state, other_singles_states, std::forward<OtherValuesTypes>(other_values)),
				...
			);
		}

		template <dynamic_states_t DynamicStates, typename ...OtherValuesTypes, size_t OtherSinglesStatesSize, size_t ...OthersTypesIndexes>
		constexpr void construct_to_helper(const state_t state, const empty_t other_singles_states, OtherValuesTypes &&...other_values, std::index_sequence<OthersTypesIndexes ...>) const&&
		{
			(
				this->construct_to_impl<dynamic_states, OtherValuesTypes, OthersTypesIndexes, OtherValuesTypes ...>(state, other_singles_states, std::forward<OtherValuesTypes>(other_values)),
				...
			);
		}

		template <dynamic_states_t DynamicStates, typename ...OtherValuesTypes, size_t OtherSinglesStatesSize, size_t ...OthersTypesIndexes>
		constexpr void construct_to_helper(const state_t state, const empty_t other_singles_states, OtherValuesTypes &&...other_values, std::index_sequence<OthersTypesIndexes ...>)&&
		{
			(
				this->construct_to_impl<dynamic_states, OtherValuesTypes, OthersTypesIndexes, OtherValuesTypes ...>(state, other_singles_states, std::forward<OtherValuesTypes>(other_values)),
				...
			);
		}

	public:

		template <dynamic_states_t DynamicStates, size_t OtherSinglesStatesSize, typename ...OtherValuesTypes>
		constexpr const single &construct_to(const state_t state, const empty_t other_singles_states, OtherValuesTypes &&...other_values) const&
		{
			this->template construct_to_helper<dynamic_states, OtherValuesTypes ...>(state, other_singles_states, std::forward<OtherValuesTypes>(other_values) ..., std::make_index_sequence < sizeof...(OtherValuesTypes) > {});
			return *this;
		}

		template <dynamic_states_t DynamicStates, size_t OtherSinglesStatesSize, typename ...OtherValuesTypes>
		constexpr single &construct_to(const state_t state, const empty_t other_singles_states, OtherValuesTypes &&...other_values)&
		{
			this->template construct_to_helper<dynamic_states, OtherValuesTypes ...>(state, other_singles_states, std::forward<OtherValuesTypes>(other_values) ..., std::make_index_sequence < sizeof...(OtherValuesTypes) > {});
			return *this;
		}

		template <dynamic_states_t DynamicStates, size_t OtherSinglesStatesSize, typename ...OtherValuesTypes>
		constexpr const single&& construct_to(const state_t state, const empty_t other_singles_states, OtherValuesTypes &&...other_values) const&&
		{
			this->template construct_to_helper<dynamic_states, OtherValuesTypes ...>(state, other_singles_states, std::forward<OtherValuesTypes>(other_values) ..., std::make_index_sequence < sizeof...(OtherValuesTypes) > {});
			return *this;
		}

		template <dynamic_states_t DynamicStates, size_t OtherSinglesStatesSize, typename ...OtherValuesTypes>
		constexpr single&& construct_to(const state_t state, const empty_t other_singles_states, OtherValuesTypes &&...other_values)&
		{
			this->template construct_to_helper<dynamic_states, OtherValuesTypes ...>(state, other_singles_states, std::forward<OtherValuesTypes>(other_values) ..., std::make_index_sequence < sizeof...(OtherValuesTypes) > {});
			return *this;
		}

	private:

		template <dynamic_states_t DynamicStates, typename OtherSinglesStatesType, typename OtherValueType, size_t Index, typename ...OtherValuesTypes>
			requires
			(
				requires (OtherSinglesStatesType other_single_states)
				{
					{
						other_single_states.size()
					} -> std::convertible_to<size_t>;
					{
						other_single_states[0]
					} -> std::same_as<state_t>;
				} &&
				(
					true &&
					... &&
					std::is_same_v<nulluple, std::remove_cvref_t<OtherValuesTypes>>
				)
			)
		constexpr void construct_to_impl(const state_t state, const OtherSinglesStatesType &other_singles_states, OtherValueType&& other_value) const &
		{
			constexpr size_t number_singles = helper_count_singles<OtherValuesTypes ...>(std::make_index_sequence<Index>());

			if constexpr (std::is_same_v<std::remove_cvref_t<OtherValueType>, this_type>)
			{
				if (number_singles < other_singles_states.size())
				{
					const state_t other_single_state = other_singles_states[number_singles];
					this->construct_to<dynamic_states>(state, other_single_state, std::forward<decltype(other_value)>(other_value));
				}
				else
				{
					this->construct_to<dynamic_states>(state, state_t::unknown, std::forward<decltype(other_value)>(other_value));
				}
			}
			else
			{
				this->construct_to<dynamic_states>(state, state_t::unknown, std::forward<decltype(other_value)>(other_value));
			}
		}

		template <dynamic_states_t DynamicStates, typename OtherSinglesStatesType, typename OtherValueType, size_t Index, typename ...OtherValuesTypes>
			requires
			(
				requires (OtherSinglesStatesType other_single_states)
				{
					{
						other_single_states.size()
					} -> std::convertible_to<size_t>;
					{
						other_single_states[0]
					} -> std::same_as<state_t>;
				} &&
				(
					true &&
					... &&
					std::is_same_v<nulluple, std::remove_cvref_t<OtherValuesTypes>>
				)
			)
		constexpr void construct_to_impl(const state_t state, const OtherSinglesStatesType &other_singles_states, OtherValueType&& other_value) &
		{
			constexpr size_t number_singles = helper_count_singles<OtherValuesTypes ...>(std::make_index_sequence<Index>());

			if constexpr (std::is_same_v<std::remove_cvref_t<OtherValueType>, this_type>)
			{
				if (number_singles < other_singles_states.size())
				{
					const state_t other_single_state = other_singles_states[number_singles];
					this->construct_to<dynamic_states>(state, other_single_state, std::forward<decltype(other_value)>(other_value));
				}
				else
				{
					this->construct_to<dynamic_states>(state, state_t::unknown, std::forward<decltype(other_value)>(other_value));
				}
			}
			else
			{
				this->construct_to<dynamic_states>(state, state_t::unknown, std::forward<decltype(other_value)>(other_value));
			}
		}

		template <dynamic_states_t DynamicStates, typename OtherSinglesStatesType, typename OtherValueType, size_t Index, typename ...OtherValuesTypes>
			requires
			(
				requires (OtherSinglesStatesType other_single_states)
				{
					{
						other_single_states.size()
					} -> std::convertible_to<size_t>;
					{
						other_single_states[0]
					} -> std::same_as<state_t>;
				} &&
				(
					true &&
					... &&
					std::is_same_v<nulluple, std::remove_cvref_t<OtherValuesTypes>>
				)
			)
			constexpr void construct_to_impl(const state_t state, const OtherSinglesStatesType &other_singles_states, OtherValueType&& other_value) const &&
		{
			constexpr size_t number_singles = helper_count_singles<OtherValuesTypes ...>(std::make_index_sequence<Index>());

			if constexpr (std::is_same_v<std::remove_cvref_t<OtherValueType>, this_type>)
			{
				if (number_singles < other_singles_states.size())
				{
					const state_t other_single_state = other_singles_states[number_singles];
					this->construct_to<dynamic_states>(state, other_single_state, std::forward<decltype(other_value)>(other_value));
				}
				else
				{
					this->construct_to<dynamic_states>(state, state_t::unknown, std::forward<decltype(other_value)>(other_value));
				}
			}
			else
			{
				this->construct_to<dynamic_states>(state, state_t::unknown, std::forward<decltype(other_value)>(other_value));
			}
		}

		template <dynamic_states_t DynamicStates, typename OtherSinglesStatesType, typename OtherValueType, size_t Index, typename ...OtherValuesTypes>
			requires
			(
				requires (OtherSinglesStatesType other_single_states)
				{
					{
						other_single_states.size()
					} -> std::convertible_to<size_t>;
					{
						other_single_states[0]
					} -> std::same_as<state_t>;
				} &&
				(
					true &&
					... &&
					std::is_same_v<nulluple, std::remove_cvref_t<OtherValuesTypes>>
				)
			)
		constexpr void construct_to_impl(const state_t state, const OtherSinglesStatesType &other_singles_states, OtherValueType &&other_value) &&
		{
			constexpr size_t number_singles = helper_count_singles<OtherValuesTypes ...>(std::make_index_sequence<Index>());

			if constexpr (std::is_same_v<std::remove_cvref_t<OtherValueType>, this_type>)
			{
				if (number_singles < other_singles_states.size())
				{
					const state_t other_single_state = other_singles_states[number_singles];
					this->construct_to<dynamic_states>(state, other_single_state, std::forward<decltype(other_value)>(other_value));
				}
				else
				{
					this->construct_to<dynamic_states>(state, state_t::unknown, std::forward<decltype(other_value)>(other_value));
				}
			}
			else
			{
				this->construct_to<dynamic_states>(state, state_t::unknown, std::forward<decltype(other_value)>(other_value));
			}
		}

		template <dynamic_states_t DynamicStates, typename ...OtherValuesTypes, typename OtherSinglesStatesType, size_t ...OthersTypesIndexes>
			requires
			(
				requires (OtherSinglesStatesType other_single_states)
				{
					{
						other_single_states.size()
					} -> std::convertible_to<size_t>;
					{
						other_single_states[0]
					} -> std::same_as<state_t>;
				} &&
				(
					true &&
					... &&
					std::is_same_v<nulluple, std::remove_cvref_t<OtherValuesTypes>>
				)
			)
		constexpr void construct_to_helper(const state_t state, const OtherSinglesStatesType &other_singles_states, OtherValuesTypes &&...other_values, std::index_sequence<OthersTypesIndexes ...>) const &
		{
			(
				this->template construct_to_impl<OtherValuesTypes, OthersTypesIndexes, OtherValuesTypes ...>(state, other_singles_states, std::forward<OtherValuesTypes>(other_values)),
				...
			);
		}

		template <dynamic_states_t DynamicStates, typename ...OtherValuesTypes, typename OtherSinglesStatesType, size_t ...OthersTypesIndexes>
			requires
			(
				requires (OtherSinglesStatesType other_single_states)
				{
					{
						other_single_states.size()
					} -> std::convertible_to<size_t>;
					{
						other_single_states[0]
					} -> std::same_as<state_t>;
				} &&
				(
					true &&
					... &&
					std::is_same_v<nulluple, std::remove_cvref_t<OtherValuesTypes>>
				)
			)
		constexpr void construct_to_helper(const state_t state, const OtherSinglesStatesType &other_singles_states, OtherValuesTypes &&...other_values, std::index_sequence<OthersTypesIndexes ...>) &
		{
			(
				this->template construct_to_impl<OtherValuesTypes, OthersTypesIndexes, OtherValuesTypes ...>(state, other_singles_states, std::forward<OtherValuesTypes>(other_values)),
				...
			);
		}

		template <dynamic_states_t DynamicStates, typename ...OtherValuesTypes, typename OtherSinglesStatesType, size_t ...OthersTypesIndexes>
			requires
			(
				requires (OtherSinglesStatesType other_single_states)
				{
					{
						other_single_states.size()
					} -> std::convertible_to<size_t>;
					{
						other_single_states[0]
					} -> std::same_as<state_t>;
				} &&
				(
					true &&
					... &&
					std::is_same_v<nulluple, std::remove_cvref_t<OtherValuesTypes>>
				)
			)
		constexpr void construct_to_helper(const state_t state, const OtherSinglesStatesType &other_singles_states, OtherValuesTypes &&...other_values, std::index_sequence<OthersTypesIndexes ...>) const &&
		{
			(
				this->template construct_to_impl<OtherValuesTypes, OthersTypesIndexes, OtherValuesTypes ...>(state, other_singles_states, std::forward<OtherValuesTypes>(other_values)),
				...
			);
		}

		template <dynamic_states_t DynamicStates, typename ...OtherValuesTypes, typename OtherSinglesStatesType, size_t ...OthersTypesIndexes>
			requires
			(
				requires (OtherSinglesStatesType other_single_states)
				{
					{
						other_single_states.size()
					} -> std::convertible_to<size_t>;
					{
						other_single_states[0]
					} -> std::same_as<state_t>;
				} &&
				(
					true &&
					... &&
					std::is_same_v<nulluple, std::remove_cvref_t<OtherValuesTypes>>
				)
			)
		constexpr void construct_to_helper(const state_t state, const OtherSinglesStatesType &other_singles_states, OtherValuesTypes &&...other_values, std::index_sequence<OthersTypesIndexes ...>) &&
		{
			(
				this->template construct_to_impl<OtherValuesTypes, OthersTypesIndexes, OtherValuesTypes ...>(state, other_singles_states, std::forward<OtherValuesTypes>(other_values)),
				...
			);
		}

	public:

		template <dynamic_states_t DynamicStates, typename OtherSinglesStatesType, typename ...OtherValuesTypes>
			requires
			(
				requires (OtherSinglesStatesType other_single_states)
				{
					{
						other_single_states.size()
					} -> std::convertible_to<size_t>;
					{
						other_single_states[0]
					} -> std::same_as<state_t>;
				} &&
				(
					true &&
					... &&
					std::is_same_v<nulluple, std::remove_cvref_t<OtherValuesTypes>>
				)
			)
		constexpr const single &construct_to(const state_t state, const OtherSinglesStatesType &other_singles_states, OtherValuesTypes &&...other_values) const &
		{
			this->template construct_to_helper<OtherValuesTypes ...>(state, other_singles_states, std::forward<OtherValuesTypes>(other_values) ..., std::make_index_sequence < sizeof...(OtherValuesTypes) > {});
			return *this;
		}

		template <dynamic_states_t DynamicStates, typename OtherSinglesStatesType, typename ...OtherValuesTypes>
			requires
			(
				requires (OtherSinglesStatesType other_single_states)
				{
					{
						other_single_states.size()
					} -> std::convertible_to<size_t>;
					{
						other_single_states[0]
					} -> std::same_as<state_t>;
				} &&
				(
					true &&
					... &&
					std::is_same_v<nulluple, std::remove_cvref_t<OtherValuesTypes>>
				)
			)
		constexpr single &construct_to(const state_t state, const OtherSinglesStatesType &other_singles_states, OtherValuesTypes &&...other_values) &
		{
			this->template construct_to_helper<OtherValuesTypes ...>(state, other_singles_states, std::forward<OtherValuesTypes>(other_values) ..., std::make_index_sequence < sizeof...(OtherValuesTypes) > {});
			return *this;
		}

		template <dynamic_states_t DynamicStates, typename OtherSinglesStatesType, typename ...OtherValuesTypes>
			requires
			(
				requires (OtherSinglesStatesType other_single_states)
				{
					{
						other_single_states.size()
					} -> std::convertible_to<size_t>;
					{
						other_single_states[0]
					} -> std::same_as<state_t>;
				} &&
				(
					true &&
					... &&
					std::is_same_v<nulluple, std::remove_cvref_t<OtherValuesTypes>>
				)
			)
		constexpr const single &&construct_to(const state_t state, const OtherSinglesStatesType &other_singles_states, OtherValuesTypes &&...other_values) const &&
		{
			this->template construct_to_helper<OtherValuesTypes ...>(state, other_singles_states, std::forward<OtherValuesTypes>(other_values) ..., std::make_index_sequence < sizeof...(OtherValuesTypes) > {});
			return *this;
		}

		template <dynamic_states_t DynamicStates, typename OtherSinglesStatesType, typename ...OtherValuesTypes>
			requires
			(
				requires (OtherSinglesStatesType other_single_states)
				{
					{
						other_single_states.size()
					} -> std::convertible_to<size_t>;
					{
						other_single_states[0]
					} -> std::same_as<state_t>;
				} &&
				(
					true &&
					... &&
					std::is_same_v<nulluple, std::remove_cvref_t<OtherValuesTypes>>
				)
			)
		constexpr single&& construct_to(const state_t state, const OtherSinglesStatesType &other_singles_states, OtherValuesTypes &&...other_values) &&
		{
			this->template construct_to_helper<OtherValuesTypes ...>(state, other_singles_states, std::forward<OtherValuesTypes>(other_values) ..., std::make_index_sequence < sizeof...(OtherValuesTypes) > {});
			return *this;
		}

	private:

		template <dynamic_states_t DynamicStates, typename OtherSinglesStatesType, typename OtherValueType, size_t Index, typename ...OtherValuesTypes>
			requires
			(
				requires (OtherSinglesStatesType other_single_states)
				{
					{
						*(other_single_states + 2).begin()
					} -> std::same_as<state_t>;
					other_single_states.end();
				} &&
				(
					true &&
					... &&
					std::is_same_v<nulluple, std::remove_cvref_t<OtherValuesTypes>>
				)
			)
		constexpr void construct_to_impl(const state_t state, const OtherSinglesStatesType &other_singles_states, OtherValueType&& other_value) const &
		{
			constexpr size_t number_singles = helper_count_singles<OtherValuesTypes ...>(std::make_index_sequence<Index>());

			if constexpr (std::is_same_v<std::remove_cvref_t<OtherValueType>, this_type>)
			{
				if (other_singles_states.begin() + number_singles < other_singles_states.end())
				{
					const state_t other_single_state = *(other_singles_states.begin() + number_singles);
					this->construct_to<dynamic_states>(state, other_single_state, std::forward<decltype(other_value)>(other_value));
				}
				else
				{
					this->construct_to<dynamic_states>(state, state_t::unknown, std::forward<decltype(other_value)>(other_value));
				}
			}
			else
			{
				this->construct_to<dynamic_states>(state, state_t::unknown, std::forward<decltype(other_value)>(other_value));
			}
		}

		template <dynamic_states_t DynamicStates, typename OtherSinglesStatesType, typename OtherValueType, size_t Index, typename ...OtherValuesTypes>
			requires
			(
				requires (OtherSinglesStatesType other_single_states)
				{
					{
						*(other_single_states + 2).begin()
					} -> std::same_as<state_t>;
					other_single_states.end();
				} &&
				(
					true &&
					... &&
					std::is_same_v<nulluple, std::remove_cvref_t<OtherValuesTypes>>
				)
			)
		constexpr void construct_to_impl(const state_t state, const OtherSinglesStatesType &other_singles_states, OtherValueType&& other_value) &
		{
			constexpr size_t number_singles = helper_count_singles<OtherValuesTypes ...>(std::make_index_sequence<Index>());

			if constexpr (std::is_same_v<std::remove_cvref_t<OtherValueType>, this_type>)
			{
				if (other_singles_states.begin() + number_singles < other_singles_states.end())
				{
					const state_t other_single_state = *(other_singles_states.begin() + number_singles);
					this->construct_to<dynamic_states>(state, other_single_state, std::forward<decltype(other_value)>(other_value));
				}
				else
				{
					this->construct_to<dynamic_states>(state, state_t::unknown, std::forward<decltype(other_value)>(other_value));
				}
			}
			else
			{
				this->construct_to<dynamic_states>(state, state_t::unknown, std::forward<decltype(other_value)>(other_value));
			}
		}

		template <dynamic_states_t DynamicStates, typename OtherSinglesStatesType, typename OtherValueType, size_t Index, typename ...OtherValuesTypes>
			requires
			(
				requires (OtherSinglesStatesType other_single_states)
				{
					{
						*(other_single_states + 2).begin()
					} -> std::same_as<state_t>;
					other_single_states.end();
				} &&
				(
					true &&
					... &&
					std::is_same_v<nulluple, std::remove_cvref_t<OtherValuesTypes>>
				)
			)
		constexpr void construct_to_impl(const state_t state, const OtherSinglesStatesType &other_singles_states, OtherValueType&& other_value) const &&
		{
			constexpr size_t number_singles = helper_count_singles<OtherValuesTypes ...>(std::make_index_sequence<Index>());

			if constexpr (std::is_same_v<std::remove_cvref_t<OtherValueType>, this_type>)
			{
				if (other_singles_states.begin() + number_singles < other_singles_states.end())
				{
					const state_t other_single_state = *(other_singles_states.begin() + number_singles);
					this->construct_to<dynamic_states>(state, other_single_state, std::forward<decltype(other_value)>(other_value));
				}
				else
				{
					this->construct_to<dynamic_states>(state, state_t::unknown, std::forward<decltype(other_value)>(other_value));
				}
			}
			else
			{
				this->construct_to<dynamic_states>(state, state_t::unknown, std::forward<decltype(other_value)>(other_value));
			}
		}

		template <dynamic_states_t DynamicStates, typename OtherSinglesStatesType, typename OtherValueType, size_t Index, typename ...OtherValuesTypes>
			requires
			(
				requires (OtherSinglesStatesType other_single_states)
				{
					{
						*(other_single_states + 2).begin()
					} -> std::same_as<state_t>;
					other_single_states.end();
				} &&
				(
					true &&
					... &&
					std::is_same_v<nulluple, std::remove_cvref_t<OtherValuesTypes>>
				)
			)
		constexpr void construct_to_impl(const state_t state, const OtherSinglesStatesType &other_singles_states, OtherValueType&& other_value) &&
		{
			constexpr size_t number_singles = helper_count_singles<OtherValuesTypes ...>(std::make_index_sequence<Index>());

			if constexpr (std::is_same_v<std::remove_cvref_t<OtherValueType>, this_type>)
			{
				if (other_singles_states.begin() + number_singles < other_singles_states.end())
				{
					const state_t other_single_state = *(other_singles_states.begin() + number_singles);
					this->construct_to<dynamic_states>(state, other_single_state, std::forward<decltype(other_value)>(other_value));
				}
				else
				{
					this->construct_to<dynamic_states>(state, state_t::unknown, std::forward<decltype(other_value)>(other_value));
				}
			}
			else
			{
				this->construct_to<dynamic_states>(state, state_t::unknown, std::forward<decltype(other_value)>(other_value));
			}
		}

		template <dynamic_states_t DynamicStates, typename ...OtherValuesTypes, typename OtherSinglesStatesType, size_t ...OthersTypesIndexes>
			requires
			(
				requires (OtherSinglesStatesType other_single_states)
				{
					{
						*(other_single_states + 2).begin()
					} -> std::same_as<state_t>;
					other_single_states.end();
				} &&
				(
					true &&
					... &&
					std::is_same_v<nulluple, std::remove_cvref_t<OtherValuesTypes>>
				)
			)
		constexpr void construct_to_helper(const state_t state, const OtherSinglesStatesType &other_singles_states, OtherValuesTypes &&...other_values, std::index_sequence<OthersTypesIndexes ...>) const &
		{
			(
				this->template construct_to_impl<OtherValuesTypes, OthersTypesIndexes, OtherValuesTypes ...>(state, other_singles_states, std::forward<OtherValuesTypes>(other_values)),
				...
			);
		}

		template <dynamic_states_t DynamicStates, typename ...OtherValuesTypes, typename OtherSinglesStatesType, size_t ...OthersTypesIndexes>
			requires
			(
				requires (OtherSinglesStatesType other_single_states)
				{
					{
						*(other_single_states + 2).begin()
					} -> std::same_as<state_t>;
					other_single_states.end();
				} &&
				(
					true &&
					... &&
					std::is_same_v<nulluple, std::remove_cvref_t<OtherValuesTypes>>
				)
			)
		constexpr void construct_to_helper(const state_t state, const OtherSinglesStatesType &other_singles_states, OtherValuesTypes &&...other_values, std::index_sequence<OthersTypesIndexes ...>) &
		{
			(
				this->template construct_to_impl<OtherValuesTypes, OthersTypesIndexes, OtherValuesTypes ...>(state, other_singles_states, std::forward<OtherValuesTypes>(other_values)),
				...
			);
		}

		template <dynamic_states_t DynamicStates, typename ...OtherValuesTypes, typename OtherSinglesStatesType, size_t ...OthersTypesIndexes>
			requires
			(
				requires (OtherSinglesStatesType other_single_states)
				{
					{
						*(other_single_states + 2).begin()
					} -> std::same_as<state_t>;
					other_single_states.end();
				} &&
				(
					true &&
					... &&
					std::is_same_v<nulluple, std::remove_cvref_t<OtherValuesTypes>>
				)
			)
		constexpr void construct_to_helper(const state_t state, const OtherSinglesStatesType &other_singles_states, OtherValuesTypes &&...other_values, std::index_sequence<OthersTypesIndexes ...>) const &&
		{
			(
				this->template construct_to_impl<OtherValuesTypes, OthersTypesIndexes, OtherValuesTypes ...>(state, other_singles_states, std::forward<OtherValuesTypes>(other_values)),
				...
			);
		}

		template <dynamic_states_t DynamicStates, typename ...OtherValuesTypes, typename OtherSinglesStatesType, size_t ...OthersTypesIndexes>
			requires
			(
				requires (OtherSinglesStatesType other_single_states)
				{
					{
						*(other_single_states + 2).begin()
					} -> std::same_as<state_t>;
					other_single_states.end();
				} &&
				(
					true &&
					... &&
					std::is_same_v<nulluple, std::remove_cvref_t<OtherValuesTypes>>
				)
			)
		constexpr void construct_to_helper(const state_t state, const OtherSinglesStatesType &other_singles_states, OtherValuesTypes &&...other_values, std::index_sequence<OthersTypesIndexes ...>) &&
		{
			(
				this->template construct_to_impl<OtherValuesTypes, OthersTypesIndexes, OtherValuesTypes ...>(state, other_singles_states, std::forward<OtherValuesTypes>(other_values)),
				...
			);
		}

	public:

		template <dynamic_states_t DynamicStates, typename OtherSinglesStatesType, typename ...OtherValuesTypes>
			requires
			(
				requires (OtherSinglesStatesType other_single_states)
				{
					{
						*(other_single_states + 2).begin()
					} -> std::same_as<state_t>;
					other_single_states.end();
				} &&
				(
					true &&
					... &&
					std::is_same_v<nulluple, std::remove_cvref_t<OtherValuesTypes>>
				)
			)
		constexpr const single &construct_to(const state_t state, const OtherSinglesStatesType &other_singles_states, OtherValuesTypes &&...other_values) const &
		{
			this->template construct_to_helper<OtherValuesTypes ...>(state, other_singles_states, std::forward<OtherValuesTypes>(other_values) ..., std::make_index_sequence < sizeof...(OtherValuesTypes) > {});
			return *this;
		}

		template <dynamic_states_t DynamicStates, typename OtherSinglesStatesType, typename ...OtherValuesTypes>
			requires
				(
					requires (OtherSinglesStatesType other_single_states)
				{
					{
						*(other_single_states + 2).begin()
					} -> std::same_as<state_t>;
					other_single_states.end();
				} &&
				(
					true &&
					... &&
					std::is_same_v<nulluple, std::remove_cvref_t<OtherValuesTypes>>
				)
			)
		constexpr single& construct_to(const state_t state, const OtherSinglesStatesType& other_singles_states, OtherValuesTypes &&...other_values)&
		{
			this->template construct_to_helper<OtherValuesTypes ...>(state, other_singles_states, std::forward<OtherValuesTypes>(other_values) ..., std::make_index_sequence < sizeof...(OtherValuesTypes) > {});
			return *this;
		}

		template <dynamic_states_t DynamicStates, typename OtherSinglesStatesType, typename ...OtherValuesTypes>
			requires
				(
					requires (OtherSinglesStatesType other_single_states)
				{
					{
						*(other_single_states + 2).begin()
					} -> std::same_as<state_t>;
					other_single_states.end();
				} &&
				(
					true &&
					... &&
					std::is_same_v<nulluple, std::remove_cvref_t<OtherValuesTypes>>
				)
			)
			constexpr const single &&construct_to(const state_t state, const OtherSinglesStatesType& other_singles_states, OtherValuesTypes &&...other_values) const &&
		{
			this->template construct_to_helper<OtherValuesTypes ...>(state, other_singles_states, std::forward<OtherValuesTypes>(other_values) ..., std::make_index_sequence < sizeof...(OtherValuesTypes) > {});
			return *this;
		}

		template <dynamic_states_t DynamicStates, typename OtherSinglesStatesType, typename ...OtherValuesTypes>
			requires
			(
				requires (OtherSinglesStatesType other_single_states)
				{
					{
						*(other_single_states + 2).begin()
					} -> std::same_as<state_t>;
					other_single_states.end();
				} &&
				(
					true &&
					... &&
					std::is_same_v<nulluple, std::remove_cvref_t<OtherValuesTypes>>
				)
			)
		constexpr single &&construct_to(const state_t state, const OtherSinglesStatesType& other_singles_states, OtherValuesTypes &&...other_values)&&
		{
			this->template construct_to_helper<OtherValuesTypes ...>(state, other_singles_states, std::forward<OtherValuesTypes>(other_values) ..., std::make_index_sequence < sizeof...(OtherValuesTypes) > {});
			return *this;
		}

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown>
		constexpr const single& construct_to(single& other) const&
			noexcept
#ifndef NDEBUG
			(
				(
					(
						State == state_t::initialized ||
						State == state_t::unknown
					) &&
					(
						OtherState == state_t::initialized ||
						OtherState == state_t::unknown
					) &&
					std::is_nothrow_destructible_v<FirstValueType>&&
					std::is_nothrow_copy_constructible_v<FirstValueType>
				) ||
				(
					State == state_t::uninitialized &&
					OtherState == state_t::initialized &&
					std::is_nothrow_copy_constructible_v<FirstValueType>
				)
			)
#else
			(
				(
					(
						State == state_t::initialized ||
						State == state_t::unknown
						) &&
					std::is_nothrow_destructible_v<FirstValueType>&&
					std::is_nothrow_copy_constructible_v<FirstValueType>
					) ||
				(
					State == state_t::uninitialized &&
					std::is_nothrow_copy_constructible_v<FirstValueType>
					)
				)
#endif
		{
			if constexpr (State == state_t::initialized || State == state_t::unknown)
			{
				if constexpr (OtherState == state_t::initialized || OtherState == state_t::unknown)
				{
					std::destroy_at(std::addressof(other.first));
					std::construct_at(std::addressof(other.first), first);
				}
				else
				{
					std::construct_at(std::addressof(other.first), first);
				}
			}
#ifndef NDEBUG
			else
			{
				throw bad_single_access{ __LINE__, "Single access out of bounds.", __FILE__, __func__ };
			}
#endif
			return *this;
		}

			template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown>
			constexpr single& construct_to(single& other) &
				noexcept
#ifndef NDEBUG
				(
					(
						(
							State == state_t::initialized ||
							State == state_t::unknown
							) &&
						(
							OtherState == state_t::initialized ||
							OtherState == state_t::unknown
							) &&
						std::is_nothrow_destructible_v<FirstValueType>&&
						std::is_nothrow_copy_constructible_v<FirstValueType>
						) ||
					(
						State == state_t::uninitialized &&
						OtherState == state_t::initialized &&
						std::is_nothrow_copy_constructible_v<FirstValueType>
						)
				)
#else
				(
					(
						(
							State == state_t::initialized ||
							State == state_t::unknown
							) &&
						std::is_nothrow_destructible_v<FirstValueType>&&
						std::is_nothrow_copy_constructible_v<FirstValueType>
						) ||
					(
						State == state_t::uninitialized &&
						std::is_nothrow_copy_constructible_v<FirstValueType>
						)
					)
#endif
			{
				if constexpr (State == state_t::initialized || State == state_t::unknown)
				{
					if constexpr (OtherState == state_t::initialized || OtherState == state_t::unknown)
					{
						std::destroy_at(std::addressof(other.first));
						std::construct_at(std::addressof(other.first), first);
					}
					else
					{
						std::construct_at(std::addressof(other.first), first);
					}
				}
#ifndef NDEBUG
				else
				{
					throw bad_single_access{ __LINE__, "Single access out of bounds.", __FILE__, __func__ };
				}
#endif
				return *this;
			}

			template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown>
			constexpr single&& construct_to(single& other) &&
				noexcept
#ifndef NDEBUG
				(
					(
						(
							State == state_t::initialized ||
							State == state_t::unknown
							) &&
						(
							OtherState == state_t::initialized ||
							OtherState == state_t::unknown
							) &&
						std::is_nothrow_destructible_v<FirstValueType>&&
						std::is_nothrow_move_constructible_v<FirstValueType>
						) ||
					(
						State == state_t::uninitialized &&
						OtherState == state_t::initialized &&
						std::is_nothrow_move_constructible_v<FirstValueType>
						)
				)
#else
				(
					(
						(
							State == state_t::initialized ||
							State == state_t::unknown
							) &&
						std::is_nothrow_destructible_v<FirstValueType>&&
						std::is_nothrow_move_constructible_v<FirstValueType>
						) ||
					(
						State == state_t::uninitialized &&
						std::is_nothrow_move_constructible_v<FirstValueType>
						)
					)
#endif
			{
				if constexpr (State == state_t::initialized || State == state_t::unknown)
				{
					if constexpr (OtherState == state_t::initialized || OtherState == state_t::unknown)
					{
						std::destroy_at(std::addressof(other.first));
						std::construct_at(std::addressof(other.first), std::move(first));
					}
					else
					{
						std::construct_at(std::addressof(other.first), std::move(first));
					}
				}
#ifndef NDEBUG
				else
				{
					throw bad_single_access{ __LINE__, "Single access out of bounds.", __FILE__, __func__ };
				}
#endif
				return *this;
			}

			template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown>
			constexpr const single&& construct_to(single& other) const&&
				noexcept
#ifndef NDEBUG
				(
					(
						(
							State == state_t::initialized ||
							State == state_t::unknown
							) &&
						(
							OtherState == state_t::initialized ||
							OtherState == state_t::unknown
							) &&
						std::is_nothrow_destructible_v<FirstValueType>&&
						std::is_nothrow_copy_constructible_v<FirstValueType>
						) ||
					(
						State == state_t::uninitialized &&
						OtherState == state_t::initialized &&
						std::is_nothrow_copy_constructible_v<FirstValueType>
						)
				)
#else
				(
					(
						(
							State == state_t::initialized ||
							State == state_t::unknown
							) &&
						std::is_nothrow_destructible_v<FirstValueType>&&
						std::is_nothrow_copy_constructible_v<FirstValueType>
						) ||
					(
						State == state_t::uninitialized &&
						std::is_nothrow_copy_constructible_v<FirstValueType>
						)
					)
#endif
			{
				if constexpr (State == state_t::initialized || State == state_t::unknown)
				{
					if constexpr (OtherState == state_t::initialized || OtherState == state_t::unknown)
					{
						std::destroy_at(std::addressof(other.first));
						std::construct_at(std::addressof(other.first), first);
					}
					else
					{
						std::construct_at(std::addressof(other.first), first);
					}
				}
#ifndef NDEBUG
				else
				{
					throw bad_single_access{ __LINE__, "Single access out of bounds.", __FILE__, __func__ };
				}
#endif
				return *this;
			}

			template <dynamic_states_t DynamicStates>
			constexpr const single& construct_to(const state_t state, const state_t other_state, single& other) const&
				noexcept
#ifndef NDEBUG
				(
					false
				)
#else
				(
					std::is_nothrow_destructible_v<FirstValueType>&&
					std::is_nothrow_copy_constructible_v<FirstValueType>
					)
#endif
			{
				if (state == state_t::initialized || other_state == state_t::unknown)
				{
					if (state == state_t::initialized || other_state == state_t::unknown)
					{
						std::destroy_at(std::addressof(other.first));
						std::construct_at(std::addressof(other.first), first);
					}
					else
					{
						std::construct_at(std::addressof(other.first), first);
					}
				}
#ifndef NDEBUG
				else
				{
					throw bad_single_access{ __LINE__, "Single access out of bounds.", __FILE__, __func__ };
				}
#endif
				return *this;
			}

			template <dynamic_states_t DynamicStates>
			constexpr single& construct_to(const state_t state, const state_t other_state, single& other) &
				noexcept
#ifndef NDEBUG
				(
					false
				)
#else
				(
					std::is_nothrow_destructible_v<FirstValueType>&&
					std::is_nothrow_copy_constructible_v<FirstValueType>
					)
#endif
			{
				if (state == state_t::initialized || state == state_t::unknown)
				{
					if (other_state == state_t::initialized || other_state == state_t::unknown)
					{
						std::destroy_at(std::addressof(other.first));
						std::construct_at(std::addressof(other.first), first);
					}
					else
					{
						std::construct_at(std::addressof(other.first), first);
					}
				}
#ifndef NDEBUG
				else
				{
					throw bad_single_access{ __LINE__, "Single access out of bounds.", __FILE__, __func__ };
				}
#endif
				return *this;
			}

			template <dynamic_states_t DynamicStates>
			constexpr const single&& construct_to(const state_t state, const state_t other_state, single& other) const&&
				noexcept
#ifndef NDEBUG
				(
					false
				)
#else
				(
					std::is_nothrow_destructible_v<FirstValueType>&&
					std::is_nothrow_copy_constructible_v<FirstValueType>
					)
#endif
			{
				if (state == state_t::initialized || state == state_t::unknown)
				{
					if (other_state == state_t::initialized || other_state == state_t::unknown)
					{
						std::destroy_at(std::addressof(other.first));
						std::construct_at(std::addressof(other.first), first);
					}
					else
					{
						std::construct_at(std::addressof(other.first), first);
					}
				}
#ifndef NDEBUG
				else
				{
					throw bad_single_access{ __LINE__, "Single access out of bounds.", __FILE__, __func__ };
				}
#endif
				return *this;
			}

			template <dynamic_states_t DynamicStates>
			constexpr single&& construct_to(const state_t state, const state_t other_state, single& other) &&
				noexcept
#ifndef NDEBUG
				(
					false
				)
#else
				(
					std::is_nothrow_destructible_v<FirstValueType>&&
					std::is_nothrow_move_constructible_v<FirstValueType>
					)
#endif
			{
				if (state == state_t::initialized || other_state == state_t::unknown)
				{
					if (state == state_t::initialized || other_state == state_t::unknown)
					{
						std::destroy_at(std::addressof(other.first));
						std::construct_at(std::addressof(other.first), std::move(first));
					}
					else
					{
						std::construct_at(std::addressof(other.first), std::move(first));
					}
				}
#ifndef NDEBUG
				else
				{
					throw bad_single_access{ __LINE__, "Single access out of bounds.", __FILE__, __func__ };
				}
#endif
				return *this;
			}

			template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown>
			constexpr const single& construct_to(single&& other) const&
				noexcept
#ifndef NDEBUG
				(
					(
						(
							State == state_t::initialized ||
							State == state_t::unknown
							) &&
						(
							OtherState == state_t::initialized ||
							OtherState == state_t::unknown
							) &&
						std::is_nothrow_destructible_v<FirstValueType>&&
						std::is_nothrow_copy_constructible_v<FirstValueType>
						) ||
					(
						State == state_t::uninitialized &&
						OtherState == state_t::initialized &&
						std::is_nothrow_copy_constructible_v<FirstValueType>
						)
				)
#else
				(
					(
						(
							State == state_t::initialized ||
							State == state_t::unknown
							) &&
						std::is_nothrow_destructible_v<FirstValueType>&&
						std::is_nothrow_copy_constructible_v<FirstValueType>
						) ||
					(
						State == state_t::uninitialized &&
						std::is_nothrow_copy_constructible_v<FirstValueType>
						)
					)
#endif
			{
				if constexpr (State == state_t::initialized || State == state_t::unknown)
				{
					if constexpr (OtherState == state_t::initialized || OtherState == state_t::unknown)
					{
						std::destroy_at(std::addressof(other.first));
						std::construct_at(std::addressof(other.first), first);
					}
					else
					{
						std::construct_at(std::addressof(other.first), first);
					}
				}
#ifndef NDEBUG
				else
				{
					throw bad_single_access{ __LINE__, "Single access out of bounds.", __FILE__, __func__ };
				}
#endif
				return *this;
			}

			template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown>
			constexpr single& construct_to(single&& other) &
				noexcept
#ifndef NDEBUG
				(
					(
						(
							State == state_t::initialized ||
							State == state_t::unknown
							) &&
						(
							OtherState == state_t::initialized ||
							OtherState == state_t::unknown
							) &&
						std::is_nothrow_destructible_v<FirstValueType>&&
						std::is_nothrow_copy_constructible_v<FirstValueType>
						) ||
					(
						State == state_t::uninitialized &&
						OtherState == state_t::initialized &&
						std::is_nothrow_copy_constructible_v<FirstValueType>
						)
				)
#else
				(
					(
						(
							State == state_t::initialized ||
							State == state_t::unknown
							) &&
						std::is_nothrow_destructible_v<FirstValueType>&&
						std::is_nothrow_copy_constructible_v<FirstValueType>
						) ||
					(
						State == state_t::uninitialized &&
						std::is_nothrow_copy_constructible_v<FirstValueType>
						)
					)
#endif
			{
				if constexpr (State == state_t::initialized || State == state_t::unknown)
				{
					if constexpr (OtherState == state_t::initialized || OtherState == state_t::unknown)
					{
						std::destroy_at(std::addressof(other.first));
						std::construct_at(std::addressof(other.first), first);
					}
					else
					{
						std::construct_at(std::addressof(other.first), first);
					}
				}
#ifndef NDEBUG
				else
				{
					throw bad_single_access{ __LINE__, "Single access out of bounds.", __FILE__, __func__ };
				}
#endif
				return *this;
			}

			template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown>
			constexpr single&& construct_to(single&& other) &&
				noexcept
#ifndef NDEBUG
				(
					(
						(
							State == state_t::initialized ||
							State == state_t::unknown
							) &&
						(
							OtherState == state_t::initialized ||
							OtherState == state_t::unknown
							) &&
						std::is_nothrow_destructible_v<FirstValueType>&&
						std::is_nothrow_move_constructible_v<FirstValueType>
						) ||
					(
						State == state_t::uninitialized &&
						OtherState == state_t::initialized &&
						std::is_nothrow_move_constructible_v<FirstValueType>
						)
				)
#else
				(
					(
						(
							State == state_t::initialized ||
							State == state_t::unknown
							) &&
						std::is_nothrow_destructible_v<FirstValueType>&&
						std::is_nothrow_move_constructible_v<FirstValueType>
						) ||
					(
						State == state_t::uninitialized &&
						std::is_nothrow_move_constructible_v<FirstValueType>
						)
					)
#endif
			{
				if constexpr (State == state_t::initialized || State == state_t::unknown)
				{
					if constexpr (OtherState == state_t::initialized || OtherState == state_t::unknown)
					{
						std::destroy_at(std::addressof(other.first));
						std::construct_at(std::addressof(other.first), std::move(first));
					}
					else
					{
						std::construct_at(std::addressof(other.first), std::move(first));
					}
				}
#ifndef NDEBUG
				else
				{
					throw bad_single_access{ __LINE__, "Single access out of bounds.", __FILE__, __func__ };
				}
#endif
				return *this;
			}

			template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown>
			constexpr const single&& construct_to(single&& other) const&&
				noexcept
#ifndef NDEBUG
				(
					(
						(
							State == state_t::initialized ||
							State == state_t::unknown
							) &&
						(
							OtherState == state_t::initialized ||
							OtherState == state_t::unknown
							) &&
						std::is_nothrow_destructible_v<FirstValueType>&&
						std::is_nothrow_copy_constructible_v<FirstValueType>
						) ||
					(
						State == state_t::uninitialized &&
						OtherState == state_t::initialized &&
						std::is_nothrow_copy_constructible_v<FirstValueType>
						)
				)
#else
				(
					(
						(
							State == state_t::initialized ||
							State == state_t::unknown
							) &&
						std::is_nothrow_destructible_v<FirstValueType>&&
						std::is_nothrow_copy_constructible_v<FirstValueType>
						) ||
					(
						State == state_t::uninitialized &&
						std::is_nothrow_copy_constructible_v<FirstValueType>
						)
					)
#endif
			{
				if constexpr (State == state_t::initialized || State == state_t::unknown)
				{
					if constexpr (OtherState == state_t::initialized || OtherState == state_t::unknown)
					{
						std::destroy_at(std::addressof(other.first));
						std::construct_at(std::addressof(other.first), first);
					}
					else
					{
						std::construct_at(std::addressof(other.first), first);
					}
				}
#ifndef NDEBUG
				else
				{
					throw bad_single_access{ __LINE__, "Single access out of bounds.", __FILE__, __func__ };
				}
#endif
				return *this;
			}

			template <dynamic_states_t DynamicStates>
			constexpr const single& construct_to(const state_t state, const state_t other_state, single&& other) const&
				noexcept
#ifndef NDEBUG
				(
					false
				)
#else
				(
					std::is_nothrow_destructible_v<FirstValueType>&&
					std::is_nothrow_copy_constructible_v<FirstValueType>
					)
#endif
			{
				if (state == state_t::initialized || other_state == state_t::unknown)
				{
					std::destroy_at(std::addressof(other.first));
					std::construct_at(std::addressof(other.first), first);
				}
#ifndef NDEBUG
				else
				{
					throw bad_single_access{ __LINE__, "Single access out of bounds.", __FILE__, __func__ };
				}
#endif
				return *this;
			}

			template <dynamic_states_t DynamicStates>
			constexpr single& construct_to(const state_t state, const state_t other_state, single&& other) &
				noexcept
#ifndef NDEBUG
				(
					false
				)
#else
				(
					std::is_nothrow_destructible_v<FirstValueType>&&
					std::is_nothrow_copy_constructible_v<FirstValueType>
					)
#endif
			{
				if (state == state_t::initialized || other_state == state_t::unknown)
				{
					if (state == state_t::initialized || other_state == state_t::unknown)
					{
						std::destroy_at(std::addressof(other.first));
						std::construct_at(std::addressof(other.first), first);
					}
					else
					{
						std::construct_at(std::addressof(other.first), first);
					}
				}
#ifndef NDEBUG
				else
				{
					throw bad_single_access{ __LINE__, "Single access out of bounds.", __FILE__, __func__ };
				}
#endif
				return *this;
			}

			template <dynamic_states_t DynamicStates>
			constexpr const single&& construct_to(const state_t state, const state_t other_state, single&& other) const&&
				noexcept
#ifndef NDEBUG
				(
					false
				)
#else
				(
					std::is_nothrow_destructible_v<FirstValueType>&&
					std::is_nothrow_copy_constructible_v<FirstValueType>
					)
#endif
			{
				this->construct_to_helper<dynamic_states>(state, other_state, other);
				return *this;
			}

			template <dynamic_states_t DynamicStates>
			constexpr single&& construct_to(const state_t state, const state_t other_state, single&& other) &&
				noexcept
#ifndef NDEBUG
				(
					false
				)
#else
				(
					std::is_nothrow_destructible_v<FirstValueType>&&
					std::is_nothrow_move_constructible_v<FirstValueType>
					)
#endif
			{
				if (state == state_t::initialized || other_state == state_t::unknown)
				{
					if (state == state_t::initialized || other_state == state_t::unknown)
					{
						std::destroy_at(std::addressof(other.first));
						std::construct_at(std::addressof(other.first), std::move(first));
					}
					else
					{
						std::construct_at(std::addressof(other.first), std::move(first));
					}
				}
#ifndef NDEBUG
				else
				{
					throw bad_single_access{ __LINE__, "Single access out of bounds.", __FILE__, __func__ };
				}
#endif
				return *this;
			}

	private:

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown, typename OtherFirstValueType>
			requires
		(
			!std::is_same_v<std::remove_cvref_t<OtherFirstValueType>, single>
			)
			constexpr void construct_to_helper(OtherFirstValueType&& other) const
			noexcept
#ifndef NDEBUG
			(
				std::is_nothrow_destructible_v<FirstValueType>&&
				std::is_nothrow_constructible_v<FirstValueType, OtherFirstValueType&&>
			)
#endif
		{
			if constexpr (State == state_t::initialized || State == state_t::unknown)
			{
				std::destroy_at(std::addressof(other));
				std::construct_at(std::addressof(other), first);
			}
#ifndef NDEBUG
			else
			{
				throw bad_single_access{ __LINE__, "Single access out of bounds.", __FILE__, __func__ };
			}
#endif
		}

	public:

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown, typename OtherFirstValueType>
			requires
		(
			!std::is_same_v<std::remove_cvref_t<OtherFirstValueType>, single>
			)
			constexpr const single& construct_to(OtherFirstValueType&& other) const&
			noexcept
#ifndef NDEBUG
			(
				std::is_nothrow_destructible_v<FirstValueType>&&
				std::is_nothrow_constructible_v<FirstValueType, OtherFirstValueType&&>
			)
#endif
		{
			this->template construct_to_helper<State, OtherState>(other);
			return *this;
		}

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown, typename OtherFirstValueType>
			requires
		(
			!std::is_same_v<std::remove_cvref_t<OtherFirstValueType>, single>
			)
			constexpr single& construct_to(OtherFirstValueType&& other) &
			noexcept
#ifndef NDEBUG
			(
				std::is_nothrow_destructible_v<FirstValueType>&&
				std::is_nothrow_constructible_v<FirstValueType, OtherFirstValueType&&>
			)
#endif
		{
			this->template construct_to_helper<State, OtherState>(other);
			return *this;
		}

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown, typename OtherFirstValueType>
			requires
		(
			!std::is_same_v<std::remove_cvref_t<OtherFirstValueType>, single>
			)
			constexpr const single&& construct_to(OtherFirstValueType&& other) const&&
			noexcept
#ifndef NDEBUG
			(
				std::is_nothrow_destructible_v<FirstValueType>&&
				std::is_nothrow_constructible_v<FirstValueType, OtherFirstValueType&&>
			)
#endif
		{
			this->template construct_to_helper<State, OtherState>(other);
			return *this;
		}

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown, typename OtherFirstValueType>
			requires
		(
			!std::is_same_v<std::remove_cvref_t<OtherFirstValueType>, single>
			)
			constexpr single&& construct_to(OtherFirstValueType&& other) &&
			noexcept
#ifndef NDEBUG
			(
				std::is_nothrow_destructible_v<FirstValueType>&&
				std::is_nothrow_constructible_v<FirstValueType, OtherFirstValueType&&>
			)
#endif
		{
			if (State == state_t::initialized || State == state_t::unknown)
			{
				std::destroy_at(std::addressof(other));
				std::construct_at(std::addressof(other), std::move(first));
			}
#ifndef NDEBUG
			else
			{
				throw bad_single_access{ __LINE__, "Single access out of bounds.", __FILE__, __func__ };
			}
#endif
			return *this;
		}

	private:

		template <dynamic_states_t DynamicStates, typename OtherFirstValueType>
			requires
		(
			!std::is_same_v<std::remove_cvref_t<OtherFirstValueType>, single>
			)
			constexpr void construct_to_helper(const state_t state, const state_t other_state, OtherFirstValueType&& other) const
			noexcept
#ifndef NDEBUG
			(
				false
			)
#else
			(
				std::is_nothrow_destructible_v<FirstValueType>&&
				std::is_nothrow_constructible_v<FirstValueType, OtherFirstValueType&&>
				)
#endif
		{
			if (state == state_t::initialized || state == state_t::unknown)
			{
				std::destroy_at(std::addressof(other));
				std::construct_at(std::addressof(other), first);
			}
#ifndef NDEBUG
			else
			{
				throw bad_single_access{ __LINE__, "Single access out of bounds.", __FILE__, __func__ };
			}
#endif
		}

	public:

		template <dynamic_states_t DynamicStates, typename OtherFirstValueType>
			requires
		(
			!std::is_same_v<std::remove_cvref_t<OtherFirstValueType>, single>
			)
			constexpr const single& construct_to(const state_t state, const state_t other_state, OtherFirstValueType&& other) const&
			noexcept
#ifndef NDEBUG
			(
				false
			)
#else
			(
				std::is_nothrow_destructible_v<FirstValueType>&&
				std::is_nothrow_constructible_v<FirstValueType, OtherFirstValueType&&>
				)
#endif
		{
			this->template construct_to_helper<dynamic_states>(state, other_state, other);
			return *this;
		}

		template <dynamic_states_t DynamicStates, typename OtherFirstValueType>
			requires
		(
			!std::is_same_v<std::remove_cvref_t<OtherFirstValueType>, single>
			)
			constexpr single& construct_to(const state_t state, const state_t other_state, OtherFirstValueType&& other)&
		{
			this->template construct_to_helper<dynamic_states>(state, other_state, other);
			return *this;
		}

		template <dynamic_states_t DynamicStates, typename OtherFirstValueType>
			requires
		(
			!std::is_same_v<std::remove_cvref_t<OtherFirstValueType>, single>
			)
			constexpr const single&& construct_to(const state_t state, const state_t other_state, OtherFirstValueType&& other) const&&
		{
			this->template construct_to_helper<dynamic_states>(state, other_state, other);
			return *this;
		}

		template <dynamic_states_t DynamicStates, typename OtherFirstValueType>
			requires
		(
			!std::is_same_v<std::remove_cvref_t<OtherFirstValueType>, single>
			)
			constexpr single&& construct_to(const state_t state, const state_t other_state, OtherFirstValueType&& other)&&
		{
			if (state == state_t::initialized || state == state_t::unknown)
			{
				std::destroy_at(std::addressof(other));
				std::construct_at(std::addressof(other), first);
			}
#ifndef NDEBUG
			else
			{
				throw bad_single_access{ __LINE__, "Single access out of bounds.", __FILE__, __func__ };
			}
#endif
			return *this;
		}

	private:

		template <state_t State = state_t::unknown, typename OtherValueType, size_t Index, typename ...OtherValuesTypes, state_t ...OtherSinglesStates>
		constexpr void assign_to_impl(const meta::value_sequence<OtherSinglesStates ...> other_singles_states, OtherValueType&& other_value)&
		{
			constexpr size_t number_singles = helper_count_singles<OtherValuesTypes ...>(std::make_index_sequence<Index>());

			if constexpr (std::is_same_v<std::remove_cvref_t<OtherValueType>, this_type>)
			{
				if constexpr (number_singles < sizeof...(OtherSinglesStates))
				{
					constexpr stack::vector<state_t, sizeof...(OtherSinglesStates)> other_singles_states{ std::forward<decltype(OtherSinglesStates)>(OtherSinglesStates) ... };
					constexpr state_t other_single_state = other_singles_states[number_singles];
					this->assign_to<State, other_single_state>(std::forward<decltype(other_value)>(other_value));
				}
				else
				{
					this->assign_to<State>(std::forward<decltype(other_value)>(other_value));
				}
			}
			else
			{
				this->assign_to<State>(std::forward<decltype(other_value)>(other_value));
			}
		}

		template <state_t State = state_t::unknown, typename OtherValueType, size_t Index, typename ...OtherValuesTypes, state_t ...OtherSinglesStates>
		constexpr void assign_to_impl(const meta::value_sequence<OtherSinglesStates ...> other_singles_states, OtherValueType&& other_value) const&&
		{
			constexpr size_t number_singles = helper_count_singles<OtherValuesTypes ...>(std::make_index_sequence<Index>());

			if constexpr (std::is_same_v<std::remove_cvref_t<OtherValueType>, this_type>)
			{
				if constexpr (number_singles < sizeof...(OtherSinglesStates))
				{
					constexpr stack::vector<state_t, sizeof...(OtherSinglesStates)> other_singles_states{ std::forward<decltype(OtherSinglesStates)>(OtherSinglesStates) ... };
					constexpr state_t other_single_state = other_singles_states[number_singles];
					this->assign_to<State, other_single_state>(std::forward<decltype(other_value)>(other_value));
				}
				else
				{
					this->assign_to<State>(std::forward<decltype(other_value)>(other_value));
				}
			}
			else
			{
				this->assign_to<State>(std::forward<decltype(other_value)>(other_value));
			}
		}

		template <state_t State = state_t::unknown, typename OtherValueType, size_t Index, typename ...OtherValuesTypes, state_t ...OtherSinglesStates>
		constexpr void assign_to_impl(const meta::value_sequence<OtherSinglesStates ...> other_singles_states, OtherValueType&& other_value)&&
		{
			constexpr size_t number_singles = helper_count_singles<OtherValuesTypes ...>(std::make_index_sequence<Index>());

			if constexpr (std::is_same_v<std::remove_cvref_t<OtherValueType>, this_type>)
			{
				if constexpr (number_singles < sizeof...(OtherSinglesStates))
				{
					constexpr stack::vector<state_t, sizeof...(OtherSinglesStates)> other_singles_states{ std::forward<decltype(OtherSinglesStates)>(OtherSinglesStates) ... };
					constexpr state_t other_single_state = other_singles_states[number_singles];
					this->assign_to<State, other_single_state>(std::forward<decltype(other_value)>(other_value));
				}
				else
				{
					this->assign_to<State>(std::forward<decltype(other_value)>(other_value));
				}
			}
			else
			{
				this->assign_to<State>(std::forward<decltype(other_value)>(other_value));
			}
		}

		template <state_t State = state_t::unknown, state_t ...OtherSinglesStates, typename ...OtherValuesTypes, size_t ...OthersTypesIndexes>
		constexpr void assign_to_helper(OtherValuesTypes &&...other_values, std::index_sequence<OthersTypesIndexes ...>) const&
		{
			(
				this->template assign_to_impl<State, OtherValuesTypes, OthersTypesIndexes, OtherValuesTypes ...>(woj::meta::value_sequence<OtherSinglesStates...>{}, std::forward<OtherValuesTypes>(other_values)),
				...
				);
		}

		template <state_t State = state_t::unknown, state_t ...OtherSinglesStates, typename ...OtherValuesTypes, size_t ...OthersTypesIndexes>
		constexpr void assign_to_helper(OtherValuesTypes &&...other_values, std::index_sequence<OthersTypesIndexes ...>)&
		{
			(
				this->template assign_to_impl<State, OtherValuesTypes, OthersTypesIndexes, OtherValuesTypes ...>(woj::meta::value_sequence<OtherSinglesStates...>{}, std::forward<OtherValuesTypes>(other_values)),
				...
				);
		}

		template <state_t State = state_t::unknown, state_t ...OtherSinglesStates, typename ...OtherValuesTypes, size_t ...OthersTypesIndexes>
		constexpr void assign_to_helper(OtherValuesTypes &&...other_values, std::index_sequence<OthersTypesIndexes ...>) const&&
		{
			(
				this->template assign_to_impl<State, OtherValuesTypes, OthersTypesIndexes, OtherValuesTypes ...>(woj::meta::value_sequence<OtherSinglesStates...>{}, std::forward<OtherValuesTypes>(other_values)),
				...
				);
		}

		template <state_t State = state_t::unknown, state_t ...OtherSinglesStates, typename ...OtherValuesTypes, size_t ...OthersTypesIndexes>
		constexpr void assign_to_helper(OtherValuesTypes &&...other_values, std::index_sequence<OthersTypesIndexes ...>)&&
		{
			(
				this->template assign_to_impl<State, OtherValuesTypes, OthersTypesIndexes, OtherValuesTypes ...>(woj::meta::value_sequence<OtherSinglesStates...>{}, std::forward<OtherValuesTypes>(other_values)),
				...
				);
		}

	public:

		template <state_t State = state_t::unknown, state_t ...OthersSingleStates, typename ...OtherValuesTypes>
		constexpr const single& assign_to(OtherValuesTypes &&...other_values) const&
		{
			this->template assign_to_helper<State, OthersSingleStates..., OtherValuesTypes...>(std::forward<OtherValuesTypes>(other_values)..., std::make_index_sequence < sizeof...(OtherValuesTypes) > {});
			return *this;
		}

		template <state_t State = state_t::unknown, state_t ...OthersSingleStates, typename ...OtherValuesTypes>
		constexpr single& assign_to(OtherValuesTypes &&...other_values)&
		{
			this->template assign_to_helper<State, OthersSingleStates..., OtherValuesTypes...>(std::forward<OtherValuesTypes>(other_values)..., std::make_index_sequence < sizeof...(OtherValuesTypes) > {});
			return *this;
		}

		template <state_t State = state_t::unknown, state_t ...OthersSingleStates, typename ...OtherValuesTypes>
		constexpr const single&& assign_to(OtherValuesTypes &&...other_values) const&&
		{
			this->template assign_to_helper<State, OthersSingleStates..., OtherValuesTypes...>(std::forward<OtherValuesTypes>(other_values)..., std::make_index_sequence < sizeof...(OtherValuesTypes) > {});
			return *this;
		}

		template <state_t State = state_t::unknown, state_t ...OthersSingleStates, typename ...OtherValuesTypes>
		constexpr single&& assign_to(OtherValuesTypes &&...other_values)&&
		{
			this->template assign_to_helper<State, OthersSingleStates..., OtherValuesTypes...>(std::forward<OtherValuesTypes>(other_values)..., std::make_index_sequence < sizeof...(OtherValuesTypes) > {});
			return *this;
		}

	private:

		template <dynamic_states_t DynamicStates, typename OtherValueType, size_t Index, typename ...OtherValuesTypes, size_t OtherSinglesStatesSize>
		constexpr void assign_to_impl(const state_t state, const state_t(&other_singles_states)[OtherSinglesStatesSize], OtherValueType&& other_value) const&
		{
			constexpr size_t number_singles = helper_count_singles<OtherValuesTypes ...>(std::make_index_sequence<Index>());

			if constexpr (std::is_same_v<std::remove_cvref_t<OtherValueType>, this_type>)
			{
				if constexpr (number_singles < OtherSinglesStatesSize)
				{
					const state_t other_single_state = other_singles_states[number_singles];
					this->assign_to<dynamic_states>(state, other_single_state, std::forward<decltype(other_value)>(other_value));
				}
				else
				{
					this->assign_to<dynamic_states>(state, state_t::unknown, std::forward<decltype(other_value)>(other_value));
				}
			}
			else
			{
				this->assign_to<dynamic_states>(state, state_t::unknown, std::forward<decltype(other_value)>(other_value));
			}
		}

		template <dynamic_states_t DynamicStates, typename OtherValueType, size_t Index, typename ...OtherValuesTypes, size_t OtherSinglesStatesSize>
		constexpr void assign_to_impl(const state_t state, const state_t(&other_singles_states)[OtherSinglesStatesSize], OtherValueType&& other_value)&
		{
			constexpr size_t number_singles = helper_count_singles<OtherValuesTypes ...>(std::make_index_sequence<Index>());

			if constexpr (std::is_same_v<std::remove_cvref_t<OtherValueType>, this_type>)
			{
				if constexpr (number_singles < OtherSinglesStatesSize)
				{
					const state_t other_single_state = other_singles_states[number_singles];
					this->assign_to<dynamic_states>(state, other_single_state, std::forward<decltype(other_value)>(other_value));
				}
				else
				{
					this->assign_to<dynamic_states>(state, state_t::unknown, std::forward<decltype(other_value)>(other_value));
				}
			}
			else
			{
				this->assign_to<dynamic_states>(state, state_t::unknown, std::forward<decltype(other_value)>(other_value));
			}
		}

		template <dynamic_states_t DynamicStates, typename OtherValueType, size_t Index, typename ...OtherValuesTypes, size_t OtherSinglesStatesSize>
		constexpr void assign_to_impl(const state_t state, const state_t(&other_singles_states)[OtherSinglesStatesSize], OtherValueType&& other_value) const&&
		{
			constexpr size_t number_singles = helper_count_singles<OtherValuesTypes ...>(std::make_index_sequence<Index>());

			if constexpr (std::is_same_v<std::remove_cvref_t<OtherValueType>, this_type>)
			{
				if constexpr (number_singles < OtherSinglesStatesSize)
				{
					const state_t other_single_state = other_singles_states[number_singles];
					this->assign_to<dynamic_states>(state, other_single_state, std::forward<decltype(other_value)>(other_value));
				}
				else
				{
					this->assign_to<dynamic_states>(state, state_t::unknown, std::forward<decltype(other_value)>(other_value));
				}
			}
			else
			{
				this->assign_to<dynamic_states>(state, state_t::unknown, std::forward<decltype(other_value)>(other_value));
			}
		}

		template <dynamic_states_t DynamicStates, typename OtherValueType, size_t Index, typename ...OtherValuesTypes, size_t OtherSinglesStatesSize>
		constexpr void assign_to_impl(const state_t state, const state_t(&other_singles_states)[OtherSinglesStatesSize], OtherValueType&& other_value)&&
		{
			constexpr size_t number_singles = helper_count_singles<OtherValuesTypes ...>(std::make_index_sequence<Index>());

			if constexpr (std::is_same_v<std::remove_cvref_t<OtherValueType>, this_type>)
			{
				if constexpr (number_singles < OtherSinglesStatesSize)
				{
					const state_t other_single_state = other_singles_states[number_singles];
					this->assign_to<dynamic_states>(state, other_single_state, std::forward<decltype(other_value)>(other_value));
				}
				else
				{
					this->assign_to<dynamic_states>(state, state_t::unknown, std::forward<decltype(other_value)>(other_value));
				}
			}
			else
			{
				this->assign_to<dynamic_states>(state, state_t::unknown, std::forward<decltype(other_value)>(other_value));
			}
		}

		template <dynamic_states_t DynamicStates, typename ...OtherValuesTypes, size_t OtherSinglesStatesSize, size_t ...OthersTypesIndexes>
		constexpr void assign_to_helper(const state_t state, const state_t(&other_singles_states)[OtherSinglesStatesSize], OtherValuesTypes &&...other_values, std::index_sequence<OthersTypesIndexes ...>) const&
		{
			(
				this->template assign_to_impl<dynamic_states, OtherValuesTypes, OthersTypesIndexes, OtherValuesTypes ...>(state, other_singles_states, std::forward<OtherValuesTypes>(other_values)),
				...
				);
		}

		template <dynamic_states_t DynamicStates, typename ...OtherValuesTypes, size_t OtherSinglesStatesSize, size_t ...OthersTypesIndexes>
		constexpr void assign_to_helper(const state_t state, const state_t(&other_singles_states)[OtherSinglesStatesSize], OtherValuesTypes &&...other_values, std::index_sequence<OthersTypesIndexes ...>)&
		{
			(
				this->template assign_to_impl<dynamic_states, OtherValuesTypes, OthersTypesIndexes, OtherValuesTypes ...>(state, other_singles_states, std::forward<OtherValuesTypes>(other_values)),
				...
				);
		}

		template <dynamic_states_t DynamicStates, typename ...OtherValuesTypes, size_t OtherSinglesStatesSize, size_t ...OthersTypesIndexes>
		constexpr void assign_to_helper(const state_t state, const state_t(&other_singles_states)[OtherSinglesStatesSize], OtherValuesTypes &&...other_values, std::index_sequence<OthersTypesIndexes ...>) const&&
		{
			(
				this->template assign_to_impl<dynamic_states, OtherValuesTypes, OthersTypesIndexes, OtherValuesTypes ...>(state, other_singles_states, std::forward<OtherValuesTypes>(other_values)),
				...
				);
		}

		template <dynamic_states_t DynamicStates, typename ...OtherValuesTypes, size_t OtherSinglesStatesSize, size_t ...OthersTypesIndexes>
		constexpr void assign_to_helper(const state_t state, const state_t(&other_singles_states)[OtherSinglesStatesSize], OtherValuesTypes &&...other_values, std::index_sequence<OthersTypesIndexes ...>)&&
		{
			(
				this->template assign_to_impl<dynamic_states, OtherValuesTypes, OthersTypesIndexes, OtherValuesTypes ...>(state, other_singles_states, std::forward<OtherValuesTypes>(other_values)),
				...
				);
		}

	public:

		template <dynamic_states_t DynamicStates, size_t OtherSinglesStatesSize, typename ...OtherValuesTypes>
		constexpr const single& assign_to(const state_t state, const state_t(&other_singles_states)[OtherSinglesStatesSize], OtherValuesTypes &&...other_values) const&
		{
			this->template assign_to_helper<dynamic_states, OtherValuesTypes ...>(state, other_singles_states, std::forward<OtherValuesTypes>(other_values) ..., std::make_index_sequence < sizeof...(OtherValuesTypes) > {});
			return *this;
		}

		template <dynamic_states_t DynamicStates, size_t OtherSinglesStatesSize, typename ...OtherValuesTypes>
		constexpr single& assign_to(const state_t state, const state_t(&other_singles_states)[OtherSinglesStatesSize], OtherValuesTypes &&...other_values)&
		{
			this->template assign_to_helper<dynamic_states, OtherValuesTypes ...>(state, other_singles_states, std::forward<OtherValuesTypes>(other_values) ..., std::make_index_sequence < sizeof...(OtherValuesTypes) > {});
			return *this;
		}

		template <dynamic_states_t DynamicStates, size_t OtherSinglesStatesSize, typename ...OtherValuesTypes>
		constexpr const single&& assign_to(const state_t state, const state_t(&other_singles_states)[OtherSinglesStatesSize], OtherValuesTypes &&...other_values) const&&
		{
			this->template assign_to_helper<dynamic_states, OtherValuesTypes ...>(state, other_singles_states, std::forward<OtherValuesTypes>(other_values) ..., std::make_index_sequence < sizeof...(OtherValuesTypes) > {});
			return *this;
		}

		template <dynamic_states_t DynamicStates, size_t OtherSinglesStatesSize, typename ...OtherValuesTypes>
		constexpr single&& assign_to(const state_t state, const state_t(&other_singles_states)[OtherSinglesStatesSize], OtherValuesTypes &&...other_values)&
		{
			this->template assign_to_helper<dynamic_states, OtherValuesTypes ...>(state, other_singles_states, std::forward<OtherValuesTypes>(other_values) ..., std::make_index_sequence < sizeof...(OtherValuesTypes) > {});
			return *this;
		}

	private:

		template <dynamic_states_t DynamicStates, typename OtherValueType, size_t Index, typename ...OtherValuesTypes, size_t OtherSinglesStatesSize>
		constexpr void assign_to_impl(const state_t state, const stack::vector<state_t, OtherSinglesStatesSize> other_singles_states, OtherValueType&& other_value) const&
		{
			constexpr size_t number_singles = helper_count_singles<OtherValuesTypes ...>(std::make_index_sequence<Index>());

			if constexpr (std::is_same_v<std::remove_cvref_t<OtherValueType>, this_type>)
			{
				if constexpr (number_singles < OtherSinglesStatesSize)
				{
					const state_t other_single_state = other_singles_states[number_singles];
					this->assign_to<dynamic_states>(state, other_single_state, std::forward<decltype(other_value)>(other_value));
				}
				else
				{
					this->assign_to<dynamic_states>(state, state_t::unknown, std::forward<decltype(other_value)>(other_value));
				}
			}
			else
			{
				this->assign_to<dynamic_states>(state, state_t::unknown, std::forward<decltype(other_value)>(other_value));
			}
		}

		template <dynamic_states_t DynamicStates, typename OtherValueType, size_t Index, typename ...OtherValuesTypes, size_t OtherSinglesStatesSize>
		constexpr void assign_to_impl(const state_t state, const stack::vector<state_t, OtherSinglesStatesSize> other_singles_states, OtherValueType&& other_value)&
		{
			constexpr size_t number_singles = helper_count_singles<OtherValuesTypes ...>(std::make_index_sequence<Index>());

			if constexpr (std::is_same_v<std::remove_cvref_t<OtherValueType>, this_type>)
			{
				if constexpr (number_singles < OtherSinglesStatesSize)
				{
					const state_t other_single_state = other_singles_states[number_singles];
					this->assign_to<dynamic_states>(state, other_single_state, std::forward<decltype(other_value)>(other_value));
				}
				else
				{
					this->assign_to<dynamic_states>(state, state_t::unknown, std::forward<decltype(other_value)>(other_value));
				}
			}
			else
			{
				this->assign_to<dynamic_states>(state, state_t::unknown, std::forward<decltype(other_value)>(other_value));
			}
		}

		template <dynamic_states_t DynamicStates, typename OtherValueType, size_t Index, typename ...OtherValuesTypes, size_t OtherSinglesStatesSize>
		constexpr void assign_to_impl(const state_t state, const stack::vector<state_t, OtherSinglesStatesSize> other_singles_states, OtherValueType&& other_value) const&&
		{
			constexpr size_t number_singles = helper_count_singles<OtherValuesTypes ...>(std::make_index_sequence<Index>());

			if constexpr (std::is_same_v<std::remove_cvref_t<OtherValueType>, this_type>)
			{
				if constexpr (number_singles < OtherSinglesStatesSize)
				{
					const state_t other_single_state = other_singles_states[number_singles];
					this->assign_to<dynamic_states>(state, other_single_state, std::forward<decltype(other_value)>(other_value));
				}
				else
				{
					this->assign_to<dynamic_states>(state, state_t::unknown, std::forward<decltype(other_value)>(other_value));
				}
			}
			else
			{
				this->assign_to<dynamic_states>(state, state_t::unknown, std::forward<decltype(other_value)>(other_value));
			}
		}

		template <dynamic_states_t DynamicStates, typename OtherValueType, size_t Index, typename ...OtherValuesTypes, size_t OtherSinglesStatesSize>
		constexpr void assign_to_impl(const state_t state, const stack::vector<state_t, OtherSinglesStatesSize> other_singles_states, OtherValueType&& other_value)&&
		{
			constexpr size_t number_singles = helper_count_singles<OtherValuesTypes ...>(std::make_index_sequence<Index>());

			if constexpr (std::is_same_v<std::remove_cvref_t<OtherValueType>, this_type>)
			{
				if constexpr (number_singles < OtherSinglesStatesSize)
				{
					const state_t other_single_state = other_singles_states[number_singles];
					this->assign_to<dynamic_states>(state, other_single_state, std::forward<decltype(other_value)>(other_value));
				}
				else
				{
					this->assign_to<dynamic_states>(state, state_t::unknown, std::forward<decltype(other_value)>(other_value));
				}
			}
			else
			{
				this->assign_to<dynamic_states>(state, state_t::unknown, std::forward<decltype(other_value)>(other_value));
			}
		}

		template <dynamic_states_t DynamicStates, typename ...OtherValuesTypes, size_t OtherSinglesStatesSize, size_t ...OthersTypesIndexes>
		constexpr void assign_to_helper(const state_t state, const stack::vector<state_t, OtherSinglesStatesSize> other_singles_states, OtherValuesTypes &&...other_values, std::index_sequence<OthersTypesIndexes ...>) const&
		{
			(
				this->template assign_to_impl<dynamic_states, OtherValuesTypes, OthersTypesIndexes, OtherValuesTypes ...>(state, other_singles_states, std::forward<OtherValuesTypes>(other_values)),
				...
				);
		}

		template <dynamic_states_t DynamicStates, typename ...OtherValuesTypes, size_t OtherSinglesStatesSize, size_t ...OthersTypesIndexes>
		constexpr void assign_to_helper(const state_t state, const stack::vector<state_t, OtherSinglesStatesSize> other_singles_states, OtherValuesTypes &&...other_values, std::index_sequence<OthersTypesIndexes ...>)&
		{
			(
				this->template assign_to_impl<dynamic_states, OtherValuesTypes, OthersTypesIndexes, OtherValuesTypes ...>(state, other_singles_states, std::forward<OtherValuesTypes>(other_values)),
				...
				);
		}

		template <dynamic_states_t DynamicStates, typename ...OtherValuesTypes, size_t OtherSinglesStatesSize, size_t ...OthersTypesIndexes>
		constexpr void assign_to_helper(const state_t state, const stack::vector<state_t, OtherSinglesStatesSize> other_singles_states, OtherValuesTypes &&...other_values, std::index_sequence<OthersTypesIndexes ...>) const&&
		{
			(
				this->template assign_to_impl<dynamic_states, OtherValuesTypes, OthersTypesIndexes, OtherValuesTypes ...>(state, other_singles_states, std::forward<OtherValuesTypes>(other_values)),
				...
				);
		}

		template <dynamic_states_t DynamicStates, typename ...OtherValuesTypes, size_t OtherSinglesStatesSize, size_t ...OthersTypesIndexes>
		constexpr void assign_to_helper(const state_t state, const stack::vector<state_t, OtherSinglesStatesSize> other_singles_states, OtherValuesTypes &&...other_values, std::index_sequence<OthersTypesIndexes ...>)&&
		{
			(
				this->template assign_to_impl<dynamic_states, OtherValuesTypes, OthersTypesIndexes, OtherValuesTypes ...>(state, other_singles_states, std::forward<OtherValuesTypes>(other_values)),
				...
				);
		}

	public:

		template <dynamic_states_t DynamicStates, size_t OtherSinglesStatesSize, typename ...OtherValuesTypes>
		constexpr const single& assign_to(const state_t state, const stack::vector<state_t, OtherSinglesStatesSize> other_singles_states, OtherValuesTypes &&...other_values) const&
		{
			this->template assign_to_helper<dynamic_states, OtherValuesTypes ...>(state, other_singles_states, std::forward<OtherValuesTypes>(other_values) ..., std::make_index_sequence < sizeof...(OtherValuesTypes) > {});
			return *this;
		}

		template <dynamic_states_t DynamicStates, size_t OtherSinglesStatesSize, typename ...OtherValuesTypes>
		constexpr single& assign_to(const state_t state, const stack::vector<state_t, OtherSinglesStatesSize> other_singles_states, OtherValuesTypes &&...other_values)&
		{
			this->template assign_to_helper<dynamic_states, OtherValuesTypes ...>(state, other_singles_states, std::forward<OtherValuesTypes>(other_values) ..., std::make_index_sequence < sizeof...(OtherValuesTypes) > {});
			return *this;
		}

		template <dynamic_states_t DynamicStates, size_t OtherSinglesStatesSize, typename ...OtherValuesTypes>
		constexpr const single&& assign_to(const state_t state, const stack::vector<state_t, OtherSinglesStatesSize> other_singles_states, OtherValuesTypes &&...other_values) const&&
		{
			this->template assign_to_helper<dynamic_states, OtherValuesTypes ...>(state, other_singles_states, std::forward<OtherValuesTypes>(other_values) ..., std::make_index_sequence < sizeof...(OtherValuesTypes) > {});
			return *this;
		}

		template <dynamic_states_t DynamicStates, size_t OtherSinglesStatesSize, typename ...OtherValuesTypes>
		constexpr single&& assign_to(const state_t state, const stack::vector<state_t, OtherSinglesStatesSize> other_singles_states, OtherValuesTypes &&...other_values)&
		{
			this->template assign_to_helper<dynamic_states, OtherValuesTypes ...>(state, other_singles_states, std::forward<OtherValuesTypes>(other_values) ..., std::make_index_sequence < sizeof...(OtherValuesTypes) > {});
			return *this;
		}

	private:

		template <dynamic_states_t DynamicStates, typename OtherValueType, size_t Index, typename ...OtherValuesTypes>
		constexpr void assign_to_impl(const state_t state, const empty_t other_singles_states, OtherValueType&& other_value) const&
		{
			this->assign_to<dynamic_states>(state, state_t::unknown, std::forward<decltype(other_value)>(other_value));
		}

		template <dynamic_states_t DynamicStates, typename OtherValueType, size_t Index, typename ...OtherValuesTypes, size_t OtherSinglesStatesSize>
		constexpr void assign_to_impl(const state_t state, const empty_t other_singles_states, OtherValueType&& other_value)&
		{
			this->assign_to<dynamic_states>(state, state_t::unknown, std::forward<decltype(other_value)>(other_value));
		}

		template <dynamic_states_t DynamicStates, typename OtherValueType, size_t Index, typename ...OtherValuesTypes, size_t OtherSinglesStatesSize>
		constexpr void assign_to_impl(const state_t state, const empty_t other_singles_states, OtherValueType&& other_value) const&&
		{
			this->assign_to<dynamic_states>(state, state_t::unknown, std::forward<decltype(other_value)>(other_value));
		}

		template <dynamic_states_t DynamicStates, typename OtherValueType, size_t Index, typename ...OtherValuesTypes, size_t OtherSinglesStatesSize>
		constexpr void assign_to_impl(const state_t state, const empty_t other_singles_states, OtherValueType&& other_value)&&
		{
			this->assign_to<dynamic_states>(state, state_t::unknown, std::forward<decltype(other_value)>(other_value));
		}

		template <dynamic_states_t DynamicStates, typename ...OtherValuesTypes, size_t OtherSinglesStatesSize, size_t ...OthersTypesIndexes>
		constexpr void assign_to_helper(const state_t state, const empty_t other_singles_states, OtherValuesTypes &&...other_values, std::index_sequence<OthersTypesIndexes ...>) const&
		{
			(
				this->assign_to_impl<dynamic_states, OtherValuesTypes, OthersTypesIndexes, OtherValuesTypes ...>(state, other_singles_states, std::forward<OtherValuesTypes>(other_values)),
				...
				);
		}

		template <dynamic_states_t DynamicStates, typename ...OtherValuesTypes, size_t OtherSinglesStatesSize, size_t ...OthersTypesIndexes>
		constexpr void assign_to_helper(const state_t state, const empty_t other_singles_states, OtherValuesTypes &&...other_values, std::index_sequence<OthersTypesIndexes ...>)&
		{
			(
				this->assign_to_impl<dynamic_states, OtherValuesTypes, OthersTypesIndexes, OtherValuesTypes ...>(state, other_singles_states, std::forward<OtherValuesTypes>(other_values)),
				...
				);
		}

		template <dynamic_states_t DynamicStates, typename ...OtherValuesTypes, size_t OtherSinglesStatesSize, size_t ...OthersTypesIndexes>
		constexpr void assign_to_helper(const state_t state, const empty_t other_singles_states, OtherValuesTypes &&...other_values, std::index_sequence<OthersTypesIndexes ...>) const&&
		{
			(
				this->assign_to_impl<dynamic_states, OtherValuesTypes, OthersTypesIndexes, OtherValuesTypes ...>(state, other_singles_states, std::forward<OtherValuesTypes>(other_values)),
				...
				);
		}

		template <dynamic_states_t DynamicStates, typename ...OtherValuesTypes, size_t OtherSinglesStatesSize, size_t ...OthersTypesIndexes>
		constexpr void assign_to_helper(const state_t state, const empty_t other_singles_states, OtherValuesTypes &&...other_values, std::index_sequence<OthersTypesIndexes ...>)&&
		{
			(
				this->assign_to_impl<dynamic_states, OtherValuesTypes, OthersTypesIndexes, OtherValuesTypes ...>(state, other_singles_states, std::forward<OtherValuesTypes>(other_values)),
				...
				);
		}

	public:

		template <dynamic_states_t DynamicStates, size_t OtherSinglesStatesSize, typename ...OtherValuesTypes>
		constexpr const single& assign_to(const state_t state, const empty_t other_singles_states, OtherValuesTypes &&...other_values) const&
		{
			this->template assign_to_helper<dynamic_states, OtherValuesTypes ...>(state, other_singles_states, std::forward<OtherValuesTypes>(other_values) ..., std::make_index_sequence < sizeof...(OtherValuesTypes) > {});
			return *this;
		}

		template <dynamic_states_t DynamicStates, size_t OtherSinglesStatesSize, typename ...OtherValuesTypes>
		constexpr single& assign_to(const state_t state, const empty_t other_singles_states, OtherValuesTypes &&...other_values)&
		{
			this->template assign_to_helper<dynamic_states, OtherValuesTypes ...>(state, other_singles_states, std::forward<OtherValuesTypes>(other_values) ..., std::make_index_sequence < sizeof...(OtherValuesTypes) > {});
			return *this;
		}

		template <dynamic_states_t DynamicStates, size_t OtherSinglesStatesSize, typename ...OtherValuesTypes>
		constexpr const single&& assign_to(const state_t state, const empty_t other_singles_states, OtherValuesTypes &&...other_values) const&&
		{
			this->template assign_to_helper<dynamic_states, OtherValuesTypes ...>(state, other_singles_states, std::forward<OtherValuesTypes>(other_values) ..., std::make_index_sequence < sizeof...(OtherValuesTypes) > {});
			return *this;
		}

		template <dynamic_states_t DynamicStates, size_t OtherSinglesStatesSize, typename ...OtherValuesTypes>
		constexpr single&& assign_to(const state_t state, const empty_t other_singles_states, OtherValuesTypes &&...other_values)&
		{
			this->template assign_to_helper<dynamic_states, OtherValuesTypes ...>(state, other_singles_states, std::forward<OtherValuesTypes>(other_values) ..., std::make_index_sequence < sizeof...(OtherValuesTypes) > {});
			return *this;
		}

	private:

		template <dynamic_states_t DynamicStates, typename OtherSinglesStatesType, typename OtherValueType, size_t Index, typename ...OtherValuesTypes>
			requires
		(
			requires (OtherSinglesStatesType other_single_states)
		{
			{
				other_single_states.size()
			} -> std::convertible_to<size_t>;
			{
				other_single_states[0]
			} -> std::same_as<state_t>;
		} &&
			(
				true &&
				... &&
				std::is_same_v<nulluple, std::remove_cvref_t<OtherValuesTypes>>
				)
			)
			constexpr void assign_to_impl(const state_t state, const OtherSinglesStatesType& other_singles_states, OtherValueType&& other_value) const&
		{
			constexpr size_t number_singles = helper_count_singles<OtherValuesTypes ...>(std::make_index_sequence<Index>());

			if constexpr (std::is_same_v<std::remove_cvref_t<OtherValueType>, this_type>)
			{
				if (number_singles < other_singles_states.size())
				{
					const state_t other_single_state = other_singles_states[number_singles];
					this->assign_to<dynamic_states>(state, other_single_state, std::forward<decltype(other_value)>(other_value));
				}
				else
				{
					this->assign_to<dynamic_states>(state, state_t::unknown, std::forward<decltype(other_value)>(other_value));
				}
			}
			else
			{
				this->assign_to<dynamic_states>(state, state_t::unknown, std::forward<decltype(other_value)>(other_value));
			}
		}

		template <dynamic_states_t DynamicStates, typename OtherSinglesStatesType, typename OtherValueType, size_t Index, typename ...OtherValuesTypes>
			requires
		(
			requires (OtherSinglesStatesType other_single_states)
		{
			{
				other_single_states.size()
			} -> std::convertible_to<size_t>;
			{
				other_single_states[0]
			} -> std::same_as<state_t>;
		} &&
			(
				true &&
				... &&
				std::is_same_v<nulluple, std::remove_cvref_t<OtherValuesTypes>>
				)
			)
			constexpr void assign_to_impl(const state_t state, const OtherSinglesStatesType& other_singles_states, OtherValueType&& other_value)&
		{
			constexpr size_t number_singles = helper_count_singles<OtherValuesTypes ...>(std::make_index_sequence<Index>());

			if constexpr (std::is_same_v<std::remove_cvref_t<OtherValueType>, this_type>)
			{
				if (number_singles < other_singles_states.size())
				{
					const state_t other_single_state = other_singles_states[number_singles];
					this->assign_to<dynamic_states>(state, other_single_state, std::forward<decltype(other_value)>(other_value));
				}
				else
				{
					this->assign_to<dynamic_states>(state, state_t::unknown, std::forward<decltype(other_value)>(other_value));
				}
			}
			else
			{
				this->assign_to<dynamic_states>(state, state_t::unknown, std::forward<decltype(other_value)>(other_value));
			}
		}

		template <dynamic_states_t DynamicStates, typename OtherSinglesStatesType, typename OtherValueType, size_t Index, typename ...OtherValuesTypes>
			requires
		(
			requires (OtherSinglesStatesType other_single_states)
		{
			{
				other_single_states.size()
			} -> std::convertible_to<size_t>;
			{
				other_single_states[0]
			} -> std::same_as<state_t>;
		} &&
			(
				true &&
				... &&
				std::is_same_v<nulluple, std::remove_cvref_t<OtherValuesTypes>>
				)
			)
			constexpr void assign_to_impl(const state_t state, const OtherSinglesStatesType& other_singles_states, OtherValueType&& other_value) const&&
		{
			constexpr size_t number_singles = helper_count_singles<OtherValuesTypes ...>(std::make_index_sequence<Index>());

			if constexpr (std::is_same_v<std::remove_cvref_t<OtherValueType>, this_type>)
			{
				if (number_singles < other_singles_states.size())
				{
					const state_t other_single_state = other_singles_states[number_singles];
					this->assign_to<dynamic_states>(state, other_single_state, std::forward<decltype(other_value)>(other_value));
				}
				else
				{
					this->assign_to<dynamic_states>(state, state_t::unknown, std::forward<decltype(other_value)>(other_value));
				}
			}
			else
			{
				this->assign_to<dynamic_states>(state, state_t::unknown, std::forward<decltype(other_value)>(other_value));
			}
		}

		template <dynamic_states_t DynamicStates, typename OtherSinglesStatesType, typename OtherValueType, size_t Index, typename ...OtherValuesTypes>
			requires
		(
			requires (OtherSinglesStatesType other_single_states)
		{
			{
				other_single_states.size()
			} -> std::convertible_to<size_t>;
			{
				other_single_states[0]
			} -> std::same_as<state_t>;
		} &&
			(
				true &&
				... &&
				std::is_same_v<nulluple, std::remove_cvref_t<OtherValuesTypes>>
				)
			)
			constexpr void assign_to_impl(const state_t state, const OtherSinglesStatesType& other_singles_states, OtherValueType&& other_value)&&
		{
			constexpr size_t number_singles = helper_count_singles<OtherValuesTypes ...>(std::make_index_sequence<Index>());

			if constexpr (std::is_same_v<std::remove_cvref_t<OtherValueType>, this_type>)
			{
				if (number_singles < other_singles_states.size())
				{
					const state_t other_single_state = other_singles_states[number_singles];
					this->assign_to<dynamic_states>(state, other_single_state, std::forward<decltype(other_value)>(other_value));
				}
				else
				{
					this->assign_to<dynamic_states>(state, state_t::unknown, std::forward<decltype(other_value)>(other_value));
				}
			}
			else
			{
				this->assign_to<dynamic_states>(state, state_t::unknown, std::forward<decltype(other_value)>(other_value));
			}
		}

		template <dynamic_states_t DynamicStates, typename ...OtherValuesTypes, typename OtherSinglesStatesType, size_t ...OthersTypesIndexes>
			requires
		(
			requires (OtherSinglesStatesType other_single_states)
		{
			{
				other_single_states.size()
			} -> std::convertible_to<size_t>;
			{
				other_single_states[0]
			} -> std::same_as<state_t>;
		} &&
			(
				true &&
				... &&
				std::is_same_v<nulluple, std::remove_cvref_t<OtherValuesTypes>>
				)
			)
			constexpr void assign_to_helper(const state_t state, const OtherSinglesStatesType& other_singles_states, OtherValuesTypes &&...other_values, std::index_sequence<OthersTypesIndexes ...>) const&
		{
			(
				this->template assign_to_impl<OtherValuesTypes, OthersTypesIndexes, OtherValuesTypes ...>(state, other_singles_states, std::forward<OtherValuesTypes>(other_values)),
				...
				);
		}

		template <dynamic_states_t DynamicStates, typename ...OtherValuesTypes, typename OtherSinglesStatesType, size_t ...OthersTypesIndexes>
			requires
		(
			requires (OtherSinglesStatesType other_single_states)
		{
			{
				other_single_states.size()
			} -> std::convertible_to<size_t>;
			{
				other_single_states[0]
			} -> std::same_as<state_t>;
		} &&
			(
				true &&
				... &&
				std::is_same_v<nulluple, std::remove_cvref_t<OtherValuesTypes>>
				)
			)
			constexpr void assign_to_helper(const state_t state, const OtherSinglesStatesType& other_singles_states, OtherValuesTypes &&...other_values, std::index_sequence<OthersTypesIndexes ...>)&
		{
			(
				this->template assign_to_impl<OtherValuesTypes, OthersTypesIndexes, OtherValuesTypes ...>(state, other_singles_states, std::forward<OtherValuesTypes>(other_values)),
				...
				);
		}

		template <dynamic_states_t DynamicStates, typename ...OtherValuesTypes, typename OtherSinglesStatesType, size_t ...OthersTypesIndexes>
			requires
		(
			requires (OtherSinglesStatesType other_single_states)
		{
			{
				other_single_states.size()
			} -> std::convertible_to<size_t>;
			{
				other_single_states[0]
			} -> std::same_as<state_t>;
		} &&
			(
				true &&
				... &&
				std::is_same_v<nulluple, std::remove_cvref_t<OtherValuesTypes>>
				)
			)
			constexpr void assign_to_helper(const state_t state, const OtherSinglesStatesType& other_singles_states, OtherValuesTypes &&...other_values, std::index_sequence<OthersTypesIndexes ...>) const&&
		{
			(
				this->template assign_to_impl<OtherValuesTypes, OthersTypesIndexes, OtherValuesTypes ...>(state, other_singles_states, std::forward<OtherValuesTypes>(other_values)),
				...
				);
		}

		template <dynamic_states_t DynamicStates, typename ...OtherValuesTypes, typename OtherSinglesStatesType, size_t ...OthersTypesIndexes>
			requires
		(
			requires (OtherSinglesStatesType other_single_states)
		{
			{
				other_single_states.size()
			} -> std::convertible_to<size_t>;
			{
				other_single_states[0]
			} -> std::same_as<state_t>;
		} &&
			(
				true &&
				... &&
				std::is_same_v<nulluple, std::remove_cvref_t<OtherValuesTypes>>
				)
			)
			constexpr void assign_to_helper(const state_t state, const OtherSinglesStatesType& other_singles_states, OtherValuesTypes &&...other_values, std::index_sequence<OthersTypesIndexes ...>)&&
		{
			(
				this->template assign_to_impl<OtherValuesTypes, OthersTypesIndexes, OtherValuesTypes ...>(state, other_singles_states, std::forward<OtherValuesTypes>(other_values)),
				...
				);
		}

	public:

		template <dynamic_states_t DynamicStates, typename OtherSinglesStatesType, typename ...OtherValuesTypes>
			requires
		(
			requires (OtherSinglesStatesType other_single_states)
		{
			{
				other_single_states.size()
			} -> std::convertible_to<size_t>;
			{
				other_single_states[0]
			} -> std::same_as<state_t>;
		} &&
			(
				true &&
				... &&
				std::is_same_v<nulluple, std::remove_cvref_t<OtherValuesTypes>>
				)
			)
			constexpr const single& assign_to(const state_t state, const OtherSinglesStatesType& other_singles_states, OtherValuesTypes &&...other_values) const&
		{
			this->template assign_to_helper<OtherValuesTypes ...>(state, other_singles_states, std::forward<OtherValuesTypes>(other_values) ..., std::make_index_sequence < sizeof...(OtherValuesTypes) > {});
			return *this;
		}

		template <dynamic_states_t DynamicStates, typename OtherSinglesStatesType, typename ...OtherValuesTypes>
			requires
		(
			requires (OtherSinglesStatesType other_single_states)
		{
			{
				other_single_states.size()
			} -> std::convertible_to<size_t>;
			{
				other_single_states[0]
			} -> std::same_as<state_t>;
		} &&
			(
				true &&
				... &&
				std::is_same_v<nulluple, std::remove_cvref_t<OtherValuesTypes>>
				)
			)
			constexpr single& assign_to(const state_t state, const OtherSinglesStatesType& other_singles_states, OtherValuesTypes &&...other_values)&
		{
			this->template assign_to_helper<OtherValuesTypes ...>(state, other_singles_states, std::forward<OtherValuesTypes>(other_values) ..., std::make_index_sequence < sizeof...(OtherValuesTypes) > {});
			return *this;
		}

		template <dynamic_states_t DynamicStates, typename OtherSinglesStatesType, typename ...OtherValuesTypes>
			requires
		(
			requires (OtherSinglesStatesType other_single_states)
		{
			{
				other_single_states.size()
			} -> std::convertible_to<size_t>;
			{
				other_single_states[0]
			} -> std::same_as<state_t>;
		} &&
			(
				true &&
				... &&
				std::is_same_v<nulluple, std::remove_cvref_t<OtherValuesTypes>>
				)
			)
			constexpr const single&& assign_to(const state_t state, const OtherSinglesStatesType& other_singles_states, OtherValuesTypes &&...other_values) const&&
		{
			this->template assign_to_helper<OtherValuesTypes ...>(state, other_singles_states, std::forward<OtherValuesTypes>(other_values) ..., std::make_index_sequence < sizeof...(OtherValuesTypes) > {});
			return *this;
		}

		template <dynamic_states_t DynamicStates, typename OtherSinglesStatesType, typename ...OtherValuesTypes>
			requires
		(
			requires (OtherSinglesStatesType other_single_states)
		{
			{
				other_single_states.size()
			} -> std::convertible_to<size_t>;
			{
				other_single_states[0]
			} -> std::same_as<state_t>;
		} &&
			(
				true &&
				... &&
				std::is_same_v<nulluple, std::remove_cvref_t<OtherValuesTypes>>
				)
			)
			constexpr single&& assign_to(const state_t state, const OtherSinglesStatesType& other_singles_states, OtherValuesTypes &&...other_values)&&
		{
			this->template assign_to_helper<OtherValuesTypes ...>(state, other_singles_states, std::forward<OtherValuesTypes>(other_values) ..., std::make_index_sequence < sizeof...(OtherValuesTypes) > {});
			return *this;
		}

	private:

		template <dynamic_states_t DynamicStates, typename OtherSinglesStatesType, typename OtherValueType, size_t Index, typename ...OtherValuesTypes>
			requires
		(
			requires (OtherSinglesStatesType other_single_states)
		{
			{
				*(other_single_states + 2).begin()
			} -> std::same_as<state_t>;
			other_single_states.end();
		} &&
			(
				true &&
				... &&
				std::is_same_v<nulluple, std::remove_cvref_t<OtherValuesTypes>>
				)
			)
			constexpr void assign_to_impl(const state_t state, const OtherSinglesStatesType& other_singles_states, OtherValueType&& other_value) const&
		{
			constexpr size_t number_singles = helper_count_singles<OtherValuesTypes ...>(std::make_index_sequence<Index>());

			if constexpr (std::is_same_v<std::remove_cvref_t<OtherValueType>, this_type>)
			{
				if (other_singles_states.begin() + number_singles < other_singles_states.end())
				{
					const state_t other_single_state = *(other_singles_states.begin() + number_singles);
					this->assign_to<dynamic_states>(state, other_single_state, std::forward<decltype(other_value)>(other_value));
				}
				else
				{
					this->assign_to<dynamic_states>(state, state_t::unknown, std::forward<decltype(other_value)>(other_value));
				}
			}
			else
			{
				this->assign_to<dynamic_states>(state, state_t::unknown, std::forward<decltype(other_value)>(other_value));
			}
		}

		template <dynamic_states_t DynamicStates, typename OtherSinglesStatesType, typename OtherValueType, size_t Index, typename ...OtherValuesTypes>
			requires
		(
			requires (OtherSinglesStatesType other_single_states)
		{
			{
				*(other_single_states + 2).begin()
			} -> std::same_as<state_t>;
			other_single_states.end();
		} &&
			(
				true &&
				... &&
				std::is_same_v<nulluple, std::remove_cvref_t<OtherValuesTypes>>
				)
			)
			constexpr void assign_to_impl(const state_t state, const OtherSinglesStatesType& other_singles_states, OtherValueType&& other_value)&
		{
			constexpr size_t number_singles = helper_count_singles<OtherValuesTypes ...>(std::make_index_sequence<Index>());

			if constexpr (std::is_same_v<std::remove_cvref_t<OtherValueType>, this_type>)
			{
				if (other_singles_states.begin() + number_singles < other_singles_states.end())
				{
					const state_t other_single_state = *(other_singles_states.begin() + number_singles);
					this->assign_to<dynamic_states>(state, other_single_state, std::forward<decltype(other_value)>(other_value));
				}
				else
				{
					this->assign_to<dynamic_states>(state, state_t::unknown, std::forward<decltype(other_value)>(other_value));
				}
			}
			else
			{
				this->assign_to<dynamic_states>(state, state_t::unknown, std::forward<decltype(other_value)>(other_value));
			}
		}

		template <dynamic_states_t DynamicStates, typename OtherSinglesStatesType, typename OtherValueType, size_t Index, typename ...OtherValuesTypes>
			requires
		(
			requires (OtherSinglesStatesType other_single_states)
		{
			{
				*(other_single_states + 2).begin()
			} -> std::same_as<state_t>;
			other_single_states.end();
		} &&
			(
				true &&
				... &&
				std::is_same_v<nulluple, std::remove_cvref_t<OtherValuesTypes>>
				)
			)
			constexpr void assign_to_impl(const state_t state, const OtherSinglesStatesType& other_singles_states, OtherValueType&& other_value) const&&
		{
			constexpr size_t number_singles = helper_count_singles<OtherValuesTypes ...>(std::make_index_sequence<Index>());

			if constexpr (std::is_same_v<std::remove_cvref_t<OtherValueType>, this_type>)
			{
				if (other_singles_states.begin() + number_singles < other_singles_states.end())
				{
					const state_t other_single_state = *(other_singles_states.begin() + number_singles);
					this->assign_to<dynamic_states>(state, other_single_state, std::forward<decltype(other_value)>(other_value));
				}
				else
				{
					this->assign_to<dynamic_states>(state, state_t::unknown, std::forward<decltype(other_value)>(other_value));
				}
			}
			else
			{
				this->assign_to<dynamic_states>(state, state_t::unknown, std::forward<decltype(other_value)>(other_value));
			}
		}

		template <dynamic_states_t DynamicStates, typename OtherSinglesStatesType, typename OtherValueType, size_t Index, typename ...OtherValuesTypes>
			requires
		(
			requires (OtherSinglesStatesType other_single_states)
		{
			{
				*(other_single_states + 2).begin()
			} -> std::same_as<state_t>;
			other_single_states.end();
		} &&
			(
				true &&
				... &&
				std::is_same_v<nulluple, std::remove_cvref_t<OtherValuesTypes>>
				)
			)
			constexpr void assign_to_impl(const state_t state, const OtherSinglesStatesType& other_singles_states, OtherValueType&& other_value)&&
		{
			constexpr size_t number_singles = helper_count_singles<OtherValuesTypes ...>(std::make_index_sequence<Index>());

			if constexpr (std::is_same_v<std::remove_cvref_t<OtherValueType>, this_type>)
			{
				if (other_singles_states.begin() + number_singles < other_singles_states.end())
				{
					const state_t other_single_state = *(other_singles_states.begin() + number_singles);
					this->assign_to<dynamic_states>(state, other_single_state, std::forward<decltype(other_value)>(other_value));
				}
				else
				{
					this->assign_to<dynamic_states>(state, state_t::unknown, std::forward<decltype(other_value)>(other_value));
				}
			}
			else
			{
				this->assign_to<dynamic_states>(state, state_t::unknown, std::forward<decltype(other_value)>(other_value));
			}
		}

		template <dynamic_states_t DynamicStates, typename ...OtherValuesTypes, typename OtherSinglesStatesType, size_t ...OthersTypesIndexes>
			requires
		(
			requires (OtherSinglesStatesType other_single_states)
		{
			{
				*(other_single_states + 2).begin()
			} -> std::same_as<state_t>;
			other_single_states.end();
		} &&
			(
				true &&
				... &&
				std::is_same_v<nulluple, std::remove_cvref_t<OtherValuesTypes>>
				)
			)
			constexpr void assign_to_helper(const state_t state, const OtherSinglesStatesType& other_singles_states, OtherValuesTypes &&...other_values, std::index_sequence<OthersTypesIndexes ...>) const&
		{
			(
				this->template assign_to_impl<OtherValuesTypes, OthersTypesIndexes, OtherValuesTypes ...>(state, other_singles_states, std::forward<OtherValuesTypes>(other_values)),
				...
				);
		}

		template <dynamic_states_t DynamicStates, typename ...OtherValuesTypes, typename OtherSinglesStatesType, size_t ...OthersTypesIndexes>
			requires
		(
			requires (OtherSinglesStatesType other_single_states)
		{
			{
				*(other_single_states + 2).begin()
			} -> std::same_as<state_t>;
			other_single_states.end();
		} &&
			(
				true &&
				... &&
				std::is_same_v<nulluple, std::remove_cvref_t<OtherValuesTypes>>
				)
			)
			constexpr void assign_to_helper(const state_t state, const OtherSinglesStatesType& other_singles_states, OtherValuesTypes &&...other_values, std::index_sequence<OthersTypesIndexes ...>)&
		{
			(
				this->template assign_to_impl<OtherValuesTypes, OthersTypesIndexes, OtherValuesTypes ...>(state, other_singles_states, std::forward<OtherValuesTypes>(other_values)),
				...
				);
		}

		template <dynamic_states_t DynamicStates, typename ...OtherValuesTypes, typename OtherSinglesStatesType, size_t ...OthersTypesIndexes>
			requires
		(
			requires (OtherSinglesStatesType other_single_states)
		{
			{
				*(other_single_states + 2).begin()
			} -> std::same_as<state_t>;
			other_single_states.end();
		} &&
			(
				true &&
				... &&
				std::is_same_v<nulluple, std::remove_cvref_t<OtherValuesTypes>>
				)
			)
			constexpr void assign_to_helper(const state_t state, const OtherSinglesStatesType& other_singles_states, OtherValuesTypes &&...other_values, std::index_sequence<OthersTypesIndexes ...>) const&&
		{
			(
				this->template assign_to_impl<OtherValuesTypes, OthersTypesIndexes, OtherValuesTypes ...>(state, other_singles_states, std::forward<OtherValuesTypes>(other_values)),
				...
				);
		}

		template <dynamic_states_t DynamicStates, typename ...OtherValuesTypes, typename OtherSinglesStatesType, size_t ...OthersTypesIndexes>
			requires
		(
			requires (OtherSinglesStatesType other_single_states)
		{
			{
				*(other_single_states + 2).begin()
			} -> std::same_as<state_t>;
			other_single_states.end();
		} &&
			(
				true &&
				... &&
				std::is_same_v<nulluple, std::remove_cvref_t<OtherValuesTypes>>
				)
			)
			constexpr void assign_to_helper(const state_t state, const OtherSinglesStatesType& other_singles_states, OtherValuesTypes &&...other_values, std::index_sequence<OthersTypesIndexes ...>)&&
		{
			(
				this->template assign_to_impl<OtherValuesTypes, OthersTypesIndexes, OtherValuesTypes ...>(state, other_singles_states, std::forward<OtherValuesTypes>(other_values)),
				...
				);
		}

	public:

		template <dynamic_states_t DynamicStates, typename OtherSinglesStatesType, typename ...OtherValuesTypes>
			requires
		(
			requires (OtherSinglesStatesType other_single_states)
		{
			{
				*(other_single_states + 2).begin()
			} -> std::same_as<state_t>;
			other_single_states.end();
		} &&
			(
				true &&
				... &&
				std::is_same_v<nulluple, std::remove_cvref_t<OtherValuesTypes>>
				)
			)
			constexpr const single& assign_to(const state_t state, const OtherSinglesStatesType& other_singles_states, OtherValuesTypes &&...other_values) const&
		{
			this->template assign_to_helper<OtherValuesTypes ...>(state, other_singles_states, std::forward<OtherValuesTypes>(other_values) ..., std::make_index_sequence < sizeof...(OtherValuesTypes) > {});
			return *this;
		}

		template <dynamic_states_t DynamicStates, typename OtherSinglesStatesType, typename ...OtherValuesTypes>
			requires
		(
			requires (OtherSinglesStatesType other_single_states)
		{
			{
				*(other_single_states + 2).begin()
			} -> std::same_as<state_t>;
			other_single_states.end();
		} &&
			(
				true &&
				... &&
				std::is_same_v<nulluple, std::remove_cvref_t<OtherValuesTypes>>
				)
			)
			constexpr single& assign_to(const state_t state, const OtherSinglesStatesType& other_singles_states, OtherValuesTypes &&...other_values)&
		{
			this->template assign_to_helper<OtherValuesTypes ...>(state, other_singles_states, std::forward<OtherValuesTypes>(other_values) ..., std::make_index_sequence < sizeof...(OtherValuesTypes) > {});
			return *this;
		}

		template <dynamic_states_t DynamicStates, typename OtherSinglesStatesType, typename ...OtherValuesTypes>
			requires
		(
			requires (OtherSinglesStatesType other_single_states)
		{
			{
				*(other_single_states + 2).begin()
			} -> std::same_as<state_t>;
			other_single_states.end();
		} &&
			(
				true &&
				... &&
				std::is_same_v<nulluple, std::remove_cvref_t<OtherValuesTypes>>
				)
			)
			constexpr const single&& assign_to(const state_t state, const OtherSinglesStatesType& other_singles_states, OtherValuesTypes &&...other_values) const&&
		{
			this->template assign_to_helper<OtherValuesTypes ...>(state, other_singles_states, std::forward<OtherValuesTypes>(other_values) ..., std::make_index_sequence < sizeof...(OtherValuesTypes) > {});
			return *this;
		}

		template <dynamic_states_t DynamicStates, typename OtherSinglesStatesType, typename ...OtherValuesTypes>
			requires
		(
			requires (OtherSinglesStatesType other_single_states)
		{
			{
				*(other_single_states + 2).begin()
			} -> std::same_as<state_t>;
			other_single_states.end();
		} &&
			(
				true &&
				... &&
				std::is_same_v<nulluple, std::remove_cvref_t<OtherValuesTypes>>
				)
			)
			constexpr single&& assign_to(const state_t state, const OtherSinglesStatesType& other_singles_states, OtherValuesTypes &&...other_values)&&
		{
			this->template assign_to_helper<OtherValuesTypes ...>(state, other_singles_states, std::forward<OtherValuesTypes>(other_values) ..., std::make_index_sequence < sizeof...(OtherValuesTypes) > {});
			return *this;
		}

	public:

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown, typename OtherSingleType>
			requires
			(
				std::is_same_v<std::remove_cvref_t<OtherSingleType>, single>
			)
		constexpr void assign_from_helper(OtherSingleType&& other)
			noexcept
			(
				(
					(
						State == state_t::initialized ||
						State == state_t::unknown
					) && 
					(
						(
							(
								OtherState == state_t::initialized ||
								OtherState == state_t::unknown
							) && 
							(
								std::is_nothrow_assignable_v<FirstValueType, decltype(other.template get<0>()) && > ||
								(
									!std::is_assignable_v<FirstValueType, decltype(other.template get<0>()) && >&& 
									std::is_nothrow_constructible_v<FirstValueType, decltype(other.template get<0>()) && >&& 
									std::is_nothrow_destructible_v<FirstValueType>
								)
							)
						) ||
						OtherState == state_t::uninitialized
					)
				) ||
				(
					State == state_t::uninitialized&& 
					(
						(
							(
								OtherState == state_t::initialized ||
								OtherState == state_t::unknown
							) && 
							std::is_nothrow_constructible_v<FirstValueType, decltype(other.template get<0>()) && >
						) ||
						OtherState == state_t::uninitialized
					)
				)
			)
		{
			if constexpr (State == state_t::initialized || State == state_t::unknown)
			{
				if constexpr (OtherState == state_t::initialized || OtherState == state_t::unknown)
				{
					if constexpr (std::is_assignable_v<FirstValueType, decltype(other.template get<0>()) && >)
					{
						first = std::forward<decltype(other.template get<0>())>(other.template get<0>());
					}
					else
					{
						std::destroy_at(std::addressof(first));
						std::construct_at(std::addressof(first), std::forward<decltype(other.template get<0>())>(other.template get<0>()));
					}
				}
			}
			else if constexpr (OtherState == state_t::initialized || OtherState == state_t::unknown)
			{
				std::construct_at(std::addressof(first), std::forward<decltype(other.template get<0>())>(other.template get<0>()));
			}
		}

	public:

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown, typename OtherSingleType>
			requires
		(
			std::is_same_v<std::remove_cvref_t<OtherSingleType>, single>
			)
			constexpr single &assign_from(OtherSingleType&& other) & 
			noexcept
			(
				(
					(
						State == state_t::initialized ||
						State == state_t::unknown
						) && 
					(
						(
							(
								OtherState == state_t::initialized ||
								OtherState == state_t::unknown
								) && 
							(
								std::is_nothrow_assignable_v<FirstValueType, decltype(other.template get<0>()) && > ||
								(
									!std::is_assignable_v<FirstValueType, decltype(other.template get<0>()) && >&& 
									std::is_nothrow_constructible_v<FirstValueType, decltype(other.template get<0>()) && >&& 
									std::is_nothrow_destructible_v<FirstValueType>
									)
								)
							) ||
						OtherState == state_t::uninitialized
						)
					) ||
				(
					State == state_t::uninitialized&& 
					(
						(
							(
								OtherState == state_t::initialized ||
								OtherState == state_t::unknown
								) && 
							std::is_nothrow_constructible_v<FirstValueType, decltype(other.template get<0>()) && >
							) ||
						OtherState == state_t::uninitialized
						)
					)
				)
		{
			this->template assign_from_helper<State, OtherState>(other);
			return *this;
		}

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown, typename OtherSingleType>
			requires
		(
			std::is_same_v<std::remove_cvref_t<OtherSingleType>, single>
			)
			constexpr single &&assign_from(OtherSingleType&& other) && 
			noexcept
			(
				(
					(
						State == state_t::initialized ||
						State == state_t::unknown
						) && 
					(
						(
							(
								OtherState == state_t::initialized ||
								OtherState == state_t::unknown
								) && 
							(
								std::is_nothrow_assignable_v<FirstValueType, decltype(other.template get<0>()) && > ||
								(
									!std::is_assignable_v<FirstValueType, decltype(other.template get<0>()) && >&& 
									std::is_nothrow_constructible_v<FirstValueType, decltype(other.template get<0>()) && >&& 
									std::is_nothrow_destructible_v<FirstValueType>
									)
								)
							) ||
						OtherState == state_t::uninitialized
						)
					) ||
				(
					State == state_t::uninitialized&& 
					(
						(
							(
								OtherState == state_t::initialized ||
								OtherState == state_t::unknown
								) && 
							std::is_nothrow_constructible_v<FirstValueType, decltype(other.template get<0>()) && >
							) ||
						OtherState == state_t::uninitialized
						)
					)
				)
		{
			this->template assign_from_helper<State, OtherState>(other);
			return *this;
		}

	private:

		template <dynamic_states_t DynamicStates, typename OtherSingleType>
			requires
		(
			std::is_same_v<std::remove_cvref_t<OtherSingleType>, single>
			)
			constexpr void assign_from_helper(const state_t state, const state_t other_state, OtherSingleType&& other)
			noexcept
			(
				std::is_nothrow_assignable_v<FirstValueType, decltype(other.template get<0>()) && >&&
				std::is_nothrow_constructible_v<FirstValueType, decltype(other.template get<0>()) && >&&
				std::is_nothrow_destructible_v<FirstValueType>
				)
		{
			if (state == state_t::initialized || state == state_t::unknown)
			{
				if (other_state == state_t::initialized || other_state == state_t::unknown)
				{
					if constexpr (std::is_assignable_v<FirstValueType, decltype(other.template get<0>()) && >)
					{
						first = std::forward<decltype(other.template get<0>())>(other.template get<0>());
					}
					else
					{
						std::destroy_at(std::addressof(first));
						std::construct_at(std::addressof(first), std::forward<decltype(other.template get<0>())>(other.template get<0>()));
					}
				}
			}
			else if (state == state_t::uninitialized)
			{
				std::construct_at(std::addressof(first), std::forward<decltype(other.template get<0>())>(other.template get<0>()));
			}
		}

	public:

		template <dynamic_states_t DynamicStates, typename OtherSingleType>
			requires
		(
			std::is_same_v<std::remove_cvref_t<OtherSingleType>, single>
			)
			constexpr single &assign_from(const state_t state, const state_t other_state, OtherSingleType&& other) & 
			noexcept
			(
				std::is_nothrow_assignable_v<FirstValueType, decltype(other.template get<0>()) && >&&
				std::is_nothrow_constructible_v<FirstValueType, decltype(other.template get<0>()) && >&&
				std::is_nothrow_destructible_v<FirstValueType>
				)
		{
			this->template assign_from_helper<dynamic_states>(state, other_state, std::forward<OtherSingleType>(other));
			return *this;
		}

		template <dynamic_states_t DynamicStates, typename OtherSingleType>
			requires
		(
			std::is_same_v<std::remove_cvref_t<OtherSingleType>, single>
			)
			constexpr single &&assign_from(const state_t state, const state_t other_state, OtherSingleType&& other) && 
			noexcept
			(
				std::is_nothrow_assignable_v<FirstValueType, decltype(other.template get<0>()) && >&&
				std::is_nothrow_constructible_v<FirstValueType, decltype(other.template get<0>()) && >&&
				std::is_nothrow_destructible_v<FirstValueType>
				)
		{
			this->template assign_from_helper<dynamic_states>(state, other_state, std::forward<OtherSingleType>(other));
			return *this;
		}

	private:

		template <state_t State = state_t::unknown, typename OtherFirstValueType>
			requires
		(
			!std::is_same_v<std::remove_cvref_t<OtherFirstValueType>, single>
			)
			constexpr void assign_from_helper(OtherFirstValueType &&other)
			noexcept
			(
				(
					(
						State == state_t::initialized ||
						State == state_t::unknown
						) && 
					(
						std::is_nothrow_assignable_v<FirstValueType, OtherFirstValueType&&> ||
						(
							!std::is_assignable_v<FirstValueType, OtherFirstValueType&&>&& 
							std::is_nothrow_constructible_v<FirstValueType, OtherFirstValueType&&>&& 
							std::is_nothrow_destructible_v<FirstValueType>
							)
						)
					) ||
				(
					State == state_t::uninitialized&& 
					std::is_nothrow_constructible_v<FirstValueType, OtherFirstValueType&&>
					)
				)
		{
			if constexpr (State == state_t::initialized || State == state_t::unknown)
			{
				if constexpr (std::is_assignable_v<FirstValueType, OtherFirstValueType&&>)
				{
					first = std::forward<OtherFirstValueType>(other);
				}
				else
				{
					std::destroy_at(std::addressof(first));
					std::construct_at(std::addressof(first), std::forward<OtherFirstValueType>(other));
				}
			}
			else
			{
				std::construct_at(std::addressof(first), std::forward<OtherFirstValueType>(other));
			}
		}

	public:

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown, typename OtherFirstValueType>
			requires
		(
			!std::is_same_v<std::remove_cvref_t<OtherFirstValueType>, single>
			)
			constexpr single &assign_from(OtherFirstValueType &&other) & 
			noexcept
			(
				(
					(
						State == state_t::initialized ||
						State == state_t::unknown
						) && 
					(
						std::is_nothrow_assignable_v<FirstValueType, OtherFirstValueType&&> ||
						(
							!std::is_assignable_v<FirstValueType, OtherFirstValueType&&>&& 
							std::is_nothrow_constructible_v<FirstValueType, OtherFirstValueType&&>&& 
							std::is_nothrow_destructible_v<FirstValueType>
							)
						)
					) ||
				(
					State == state_t::uninitialized&& 
					std::is_nothrow_constructible_v<FirstValueType, OtherFirstValueType&&>
					)
				)
		{
			this->template assign_from_helper<State, OtherState>(std::forward<OtherFirstValueType>(other));
			return *this;
		}

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown, typename OtherFirstValueType>
			requires
		(
			!std::is_same_v<std::remove_cvref_t<OtherFirstValueType>, single>
			)
			constexpr single &&assign_from(OtherFirstValueType &&other) && 
			noexcept
			(
				(
					(
						State == state_t::initialized ||
						State == state_t::unknown
						) && 
					(
						std::is_nothrow_assignable_v<FirstValueType, OtherFirstValueType&&> ||
						(
							!std::is_assignable_v<FirstValueType, OtherFirstValueType&&>&& 
							std::is_nothrow_constructible_v<FirstValueType, OtherFirstValueType&&>&& 
							std::is_nothrow_destructible_v<FirstValueType>
							)
						)
					) ||
				(
					State == state_t::uninitialized&& 
					std::is_nothrow_constructible_v<FirstValueType, OtherFirstValueType&&>
					)
				)
		{
			this->template assign_from_helper<State, OtherState>(std::forward<OtherFirstValueType>(other));
			return *this;
		}

	private:

		template <dynamic_states_t DynamicStates, typename OtherFirstValueType>
			requires
		(
			!std::is_same_v<std::remove_cvref_t<OtherFirstValueType>, single>
			)
			constexpr void assign_from_helper(const state_t state, OtherFirstValueType &&other)
			noexcept
			(
				std::is_nothrow_assignable_v<FirstValueType, OtherFirstValueType&&>&&
				std::is_nothrow_constructible_v<FirstValueType, OtherFirstValueType&&>&&
				std::is_nothrow_destructible_v<FirstValueType>
				)
		{
			if (state == state_t::initialized || state == state_t::unknown)
			{
				if constexpr (std::is_assignable_v<FirstValueType, OtherFirstValueType&&>)
				{
					first = std::forward<OtherFirstValueType>(other);
				}
				else
				{
					std::destroy_at(std::addressof(first));
					std::construct_at(std::addressof(first), std::forward<OtherFirstValueType>(other));
				}
			}
			else if (state == state_t::uninitialized)
			{
				std::construct_at(std::addressof(first), std::forward<OtherFirstValueType>(other));
			}
		}

	public:

		template <dynamic_states_t DynamicStates, typename OtherFirstValueType>
			requires
		(
			!std::is_same_v<std::remove_cvref_t<OtherFirstValueType>, single>
			)
			constexpr single &assign_from(const state_t state, const state_t other_state, OtherFirstValueType &&other) & 
			noexcept
			(
				std::is_nothrow_assignable_v<FirstValueType, OtherFirstValueType&&>&&
				std::is_nothrow_constructible_v<FirstValueType, OtherFirstValueType&&>&&
				std::is_nothrow_destructible_v<FirstValueType>
				)
		{
			this->template assign_from_helper<dynamic_states>(state, std::forward<OtherFirstValueType>(other));
			return *this;
		}

		template <dynamic_states_t DynamicStates, typename OtherFirstValueType>
			requires
		(
			!std::is_same_v<std::remove_cvref_t<OtherFirstValueType>, single>
			)
			constexpr single &&assign_from(const state_t state, const state_t other_state, OtherFirstValueType &&other) && 
			noexcept
			(
				std::is_nothrow_assignable_v<FirstValueType, OtherFirstValueType&&>&&
				std::is_nothrow_constructible_v<FirstValueType, OtherFirstValueType&&>&&
				std::is_nothrow_destructible_v<FirstValueType>
				)
		{
			this->template assign_from_helper<dynamic_states>(state, std::forward<OtherFirstValueType>(other));
			return *this;
		}

	private:

		template <state_t State = state_t::unknown, typename ...ArgsTypes>
		constexpr void emplace_from_helper(ArgsTypes&& ...args)
			noexcept
			(
				(
					(
						State == state_t::initialized ||
						State == state_t::unknown
						) && 
					std::is_nothrow_constructible_v<FirstValueType, ArgsTypes&& ...>&&
					std::is_nothrow_destructible_v<FirstValueType>
					) ||
				(
					State == state_t::uninitialized&& 
					std::is_nothrow_constructible_v<FirstValueType, ArgsTypes&& ...>
					)
				)
		{
			if constexpr (State == state_t::initialized || State == state_t::unknown)
			{
				std::destroy_at(std::addressof(first));
				std::construct_at(std::addressof(first), std::forward<ArgsTypes>(args)...);
			}
			else
			{
				std::construct_at(std::addressof(first), std::forward<ArgsTypes>(args)...);
			}
		}

	public:

		template <state_t State = state_t::unknown, typename ...ArgsTypes>
		constexpr single &emplace_from(ArgsTypes&& ...args) & 
			noexcept
			(
				(
					(
						State == state_t::initialized ||
						State == state_t::unknown
						) && 
					std::is_nothrow_constructible_v<FirstValueType, ArgsTypes&& ...>&&
					std::is_nothrow_destructible_v<FirstValueType>
					) ||
				(
					State == state_t::uninitialized&& 
					std::is_nothrow_constructible_v<FirstValueType, ArgsTypes&& ...>
					)
				)
		{
			this->template emplace_from_helper<State>(std::forward<ArgsTypes>(args)...);
			return *this;
		}

		template <state_t State = state_t::unknown, typename ...ArgsTypes>
		constexpr single &&emplace_from(ArgsTypes&& ...args) && 
			noexcept
			(
				(
					(
						State == state_t::initialized ||
						State == state_t::unknown
						) && 
					std::is_nothrow_constructible_v<FirstValueType, ArgsTypes&& ...>&&
					std::is_nothrow_destructible_v<FirstValueType>
					) ||
				(
					State == state_t::uninitialized&& 
					std::is_nothrow_constructible_v<FirstValueType, ArgsTypes&& ...>
					)
				)
		{
			this->template emplace_from_helper<State>(std::forward<ArgsTypes>(args)...);
			return *this;
		}

	private:

		template <dynamic_states_t DynamicStates, typename ...ArgsTypes>
		constexpr void emplace_from_helper(const state_t state, ArgsTypes&& ...args)
			noexcept
			(
				std::is_nothrow_constructible_v<FirstValueType, ArgsTypes&& ...>&&
				std::is_nothrow_destructible_v<FirstValueType>
				)
		{
			if (state == state_t::initialized || state == state_t::unknown)
			{
				std::destroy_at(std::addressof(first));
				std::construct_at(std::addressof(first), std::forward<ArgsTypes>(args)...);
			}
			else
			{
				std::construct_at(std::addressof(first), std::forward<ArgsTypes>(args)...);
			}
		}

	public:

		template <dynamic_states_t DynamicStates, typename ...ArgsTypes>
		constexpr single &emplace_from(const state_t state, ArgsTypes&& ...args) & 
			noexcept
			(
				std::is_nothrow_constructible_v<FirstValueType, ArgsTypes&& ...>&&
				std::is_nothrow_destructible_v<FirstValueType>
				)
		{
			this->template emplace_from_helper<dynamic_states>(state, std::forward<ArgsTypes>(args)...);
			return *this;
		}

		template <dynamic_states_t DynamicStates, typename ...ArgsTypes>
		constexpr single &&emplace_from(const state_t state, ArgsTypes&& ...args) && 
			noexcept
			(
				std::is_nothrow_constructible_v<FirstValueType, ArgsTypes&& ...>&&
				std::is_nothrow_destructible_v<FirstValueType>
				)
		{
			this->template emplace_from_helper<dynamic_states>(state, std::forward<ArgsTypes>(args)...);
			return *this;
		}

		template <typename ...ArgsTypes>
		[[nodiscard]] static
#if WOJ_HAS_CXX20
			consteval
#else
			constexpr
#endif
			single emplaced_from(ArgsTypes&& ...args)
			noexcept
			(
				std::is_nothrow_constructible_v<FirstValueType, ArgsTypes&& ...>
				)
		{
			single temp{ noinit };
			temp.template emplace_from<state_t::uninitialized>(std::forward<ArgsTypes>(args)...);
			return std::move(temp);
		}

	private:

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown>
		constexpr void copy_from_helper(const single &other)
			noexcept
			(
				(
					(
						State == state_t::initialized ||
						State == state_t::unknown
						) && 
					(
						(
							(
								OtherState == state_t::initialized ||
								OtherState == state_t::unknown
								) && 
							(
								std::is_nothrow_copy_assignable_v<FirstValueType> ||
								(
									!std::is_copy_assignable_v<FirstValueType>&& 
									std::is_nothrow_copy_constructible_v<FirstValueType>&& 
									std::is_nothrow_destructible_v<FirstValueType>
									)
								)
							) ||
						OtherState == state_t::uninitialized
						)
					) ||
				(
					State == state_t::uninitialized&& 
					(
						(
							(
								OtherState == state_t::initialized ||
								OtherState == state_t::unknown
								) && 
							std::is_nothrow_copy_constructible_v<FirstValueType>
							) ||
						OtherState == state_t::uninitialized
						)
					)
				)
		{
			if constexpr (State == state_t::initialized || State == state_t::unknown)
			{
				if constexpr (OtherState == state_t::initialized || OtherState == state_t::unknown)
				{
					if constexpr (std::is_copy_assignable_v<FirstValueType>)
					{
						first = other.first;
					}
					else
					{
						std::destroy_at(std::addressof(first));
						std::construct_at(std::addressof(first), other.first);
					}
				}
			}
			else if constexpr (OtherState == state_t::initialized || OtherState == state_t::unknown)
			{
				std::construct_at(std::addressof(first), other.first);
			}
		}

	public:

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown>
		constexpr single &copy_from(const single &other) & 
			noexcept
			(
				(
					(
						State == state_t::initialized ||
						State == state_t::unknown
						) && 
					(
						(
							(
								OtherState == state_t::initialized ||
								OtherState == state_t::unknown
								) && 
							(
								std::is_nothrow_copy_assignable_v<FirstValueType> ||
								(
									!std::is_copy_assignable_v<FirstValueType>&& 
									std::is_nothrow_copy_constructible_v<FirstValueType>&& 
									std::is_nothrow_destructible_v<FirstValueType>
									)
								)
							) ||
						OtherState == state_t::uninitialized
						)
					) ||
				(
					State == state_t::uninitialized&& 
					(
						(
							(
								OtherState == state_t::initialized ||
								OtherState == state_t::unknown
								) && 
							std::is_nothrow_copy_constructible_v<FirstValueType>
							) ||
						OtherState == state_t::uninitialized
						)
					)
				)
		{
			this->copy_from_helper<State, OtherState>(other);
			return *this;
		}

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown>
		constexpr single &&copy_from(const single &other) && 
			noexcept
			(
				(
					(
						State == state_t::initialized ||
						State == state_t::unknown
						) && 
					(
						(
							(
								OtherState == state_t::initialized ||
								OtherState == state_t::unknown
								) && 
							(
								std::is_nothrow_copy_assignable_v<FirstValueType> ||
								(
									!std::is_copy_assignable_v<FirstValueType>&& 
									std::is_nothrow_copy_constructible_v<FirstValueType>&& 
									std::is_nothrow_destructible_v<FirstValueType>
									)
								)
							) ||
						OtherState == state_t::uninitialized
						)
					) ||
				(
					State == state_t::uninitialized&& 
					(
						(
							(
								OtherState == state_t::initialized ||
								OtherState == state_t::unknown
								) && 
							std::is_nothrow_copy_constructible_v<FirstValueType>
							) ||
						OtherState == state_t::uninitialized
						)
					)
				)
		{
			this->copy_from_helper<State, OtherState>(other);
			return *this;
		}

	private:

		template <dynamic_states_t DynamicStates>
		constexpr void copy_from_helper(const state_t state, const state_t other_state, const single &other)
			noexcept
			(
				std::is_nothrow_copy_assignable_v<FirstValueType>&&
				std::is_nothrow_copy_constructible_v<FirstValueType>&&
				std::is_nothrow_destructible_v<FirstValueType>
				)
		{
			if (state == state_t::initialized || state == state_t::unknown)
			{
				if (other_state == state_t::initialized || other_state == state_t::unknown)
				{
					if constexpr (std::is_copy_assignable_v<FirstValueType>)
					{
						first = other.first;
					}
					else
					{
						std::destroy_at(std::addressof(first));
						std::construct_at(std::addressof(first), other.first);
					}
				}
			}
			else if (other_state == state_t::initialized || other_state == state_t::unknown)
			{
				std::construct_at(std::addressof(first), other.first);
			}
		}

	public:

		template <dynamic_states_t DynamicStates>
		constexpr single &copy_from(const state_t state, const state_t other_state, const single &other) & 
			noexcept
			(
				std::is_nothrow_copy_assignable_v<FirstValueType>&&
				std::is_nothrow_copy_constructible_v<FirstValueType>&&
				std::is_nothrow_destructible_v<FirstValueType>
				)
		{
			this->copy_from_helper<dynamic_states>(state, other_state, other);
			return *this;
		}

		template <dynamic_states_t DynamicStates>
		constexpr single &&copy_from(const state_t state, const state_t other_state, const single &other) && 
			noexcept
			(
				std::is_nothrow_copy_assignable_v<FirstValueType>&&
				std::is_nothrow_copy_constructible_v<FirstValueType>&&
				std::is_nothrow_destructible_v<FirstValueType>
				)
		{
			this->copy_from_helper<dynamic_states>(state, other_state, other);
			return *this;
		}

	private:

		template <state_t State = state_t::unknown, typename OtherFirstValueType>
			requires
		(
			!std::is_same_v<std::remove_cvref_t<OtherFirstValueType>, single>
			)
			constexpr void copy_from_helper(OtherFirstValueType &&other)
			noexcept
			(
				(
					(
						State == state_t::initialized ||
						State == state_t::unknown
						) && 
					std::is_nothrow_assignable_v<FirstValueType, OtherFirstValueType&&>&& 
					(
						!std::is_copy_constructible_v<FirstValueType>&&
						std::is_nothrow_copy_constructible_v<FirstValueType>
						) && 
					std::is_nothrow_destructible_v<FirstValueType>
					) ||
				(
					State == state_t::uninitialized&& 
					std::is_nothrow_copy_constructible_v<FirstValueType>
					)
				)
		{
			if constexpr (State == state_t::initialized || State == state_t::unknown)
			{
				if constexpr (std::is_assignable_v<FirstValueType, OtherFirstValueType&&>)
				{
					first = std::forward<OtherFirstValueType>(other);
				}
				else
				{
					std::destroy_at(std::addressof(first));
					std::construct_at(std::addressof(first), std::forward<OtherFirstValueType>(other));
				}
			}
			else
			{
				std::construct_at(std::addressof(first), std::forward<OtherFirstValueType>(other));
			}
		}

	public:

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown, typename OtherFirstValueType>
			requires
		(
			!std::is_same_v<std::remove_cvref_t<OtherFirstValueType>, single>
			)
			constexpr single &copy_from(OtherFirstValueType &&other) & 
			noexcept
			(
				(
					(
						State == state_t::initialized ||
						State == state_t::unknown
						) && 
					std::is_nothrow_assignable_v<FirstValueType, OtherFirstValueType&&>&& 
					(
						!std::is_copy_constructible_v<FirstValueType>&&
						std::is_nothrow_copy_constructible_v<FirstValueType>
						) && 
					std::is_nothrow_destructible_v<FirstValueType>
					) ||
				(
					State == state_t::uninitialized&& 
					std::is_nothrow_copy_constructible_v<FirstValueType>
					)
				)
		{
			this->copy_from_helper<State>(std::forward<OtherFirstValueType>(other));
			return *this;
		}

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown, typename OtherFirstValueType>
			requires
		(
			!std::is_same_v<std::remove_cvref_t<OtherFirstValueType>, single>
			)
			constexpr single &&copy_from(OtherFirstValueType &&other) && 
			noexcept
			(
				(
					(
						State == state_t::initialized ||
						State == state_t::unknown
						) && 
					std::is_nothrow_assignable_v<FirstValueType, OtherFirstValueType&&>&& 
					(
						!std::is_copy_constructible_v<FirstValueType>&&
						std::is_nothrow_copy_constructible_v<FirstValueType>
						) && 
					std::is_nothrow_destructible_v<FirstValueType>
					) ||
				(
					State == state_t::uninitialized&& 
					std::is_nothrow_copy_constructible_v<FirstValueType>
					)
				)
		{
			this->copy_from_helper<State>(std::forward<OtherFirstValueType>(other));
			return *this;
		}

	private:

		template <dynamic_states_t DynamicStates, typename OtherFirstValueType>
			requires
		(
			!std::is_same_v<std::remove_cvref_t<OtherFirstValueType>, single>
			)
			constexpr void copy_from_helper(const state_t state, const state_t other_state, OtherFirstValueType &&other)
			noexcept
			(
				std::is_nothrow_assignable_v<FirstValueType, OtherFirstValueType&&>&&
				std::is_nothrow_constructible_v<FirstValueType, OtherFirstValueType&&>&&
				std::is_nothrow_destructible_v<FirstValueType>
				)
		{
			if (state == state_t::initialized || state == state_t::unknown)
			{
				if (other_state == state_t::initialized || other_state == state_t::unknown)
				{
					if constexpr (std::is_assignable_v<FirstValueType, OtherFirstValueType&&>)
					{
						first = std::forward<OtherFirstValueType>(other);
					}
					else
					{
						std::destroy_at(std::addressof(first));
						std::construct_at(std::addressof(first), std::forward<OtherFirstValueType>(other));
					}
				}
			}
			else
			{
				std::construct_at(std::addressof(first), std::forward<OtherFirstValueType>(other));
			}
		}

	public:

		template <dynamic_states_t DynamicStates, typename OtherFirstValueType>
			requires
		(
			!std::is_same_v<std::remove_cvref_t<OtherFirstValueType>, single>
			)
			constexpr single &copy_from(const state_t state, const state_t other_state, OtherFirstValueType &&other) & 
			noexcept
			(
				std::is_nothrow_assignable_v<FirstValueType, OtherFirstValueType&&>&&
				std::is_nothrow_constructible_v<FirstValueType, OtherFirstValueType&&>&&
				std::is_nothrow_destructible_v<FirstValueType>
				)
		{
			this->copy_from_helper<dynamic_states>(state, other_state, std::forward<OtherFirstValueType>(other));
			return *this;
		}

		template <dynamic_states_t DynamicStates, typename OtherFirstValueType>
			requires
		(
			!std::is_same_v<std::remove_cvref_t<OtherFirstValueType>, single>
			)
			constexpr single &&copy_from(const state_t state, const state_t other_state, OtherFirstValueType &&other) && 
			noexcept
			(
				std::is_nothrow_assignable_v<FirstValueType, OtherFirstValueType&&>&&
				std::is_nothrow_constructible_v<FirstValueType, OtherFirstValueType&&>&&
				std::is_nothrow_destructible_v<FirstValueType>
				)
		{
			this->copy_from_helper<dynamic_states>(state, other_state, std::forward<OtherFirstValueType>(other));
			return *this;
		}

		template <state_t OtherState = state_t::unknown>
		static
#if WOJ_HAS_CXX20
			consteval
#else
			constexpr
#endif
			single copied_from(const single &other)
			noexcept
			(
				std::is_nothrow_copy_constructible_v<FirstValueType>
				)
		{
			single temp{ noinit };
			temp.copy_from<state_t::uninitialized, OtherState>(other);
			return std::move(temp);
		}

		template <dynamic_states_t DynamicStates>
		static
#if WOJ_HAS_CXX20
			consteval
#else
			constexpr
#endif
			single copied_from(const state_t other_state, const single &other)
			noexcept
			(
				std::is_nothrow_copy_constructible_v<FirstValueType>
				)
		{
			single temp{ noinit };
			temp.copy_from(state_t::uninitialized, other_state, other);
			return std::move(temp);
		}

		template <state_t OtherState = state_t::unknown, typename OtherFirstValueType>
			requires
		(
			!std::is_same_v<std::remove_cvref_t<OtherFirstValueType>, single>
			)
			static
#if WOJ_HAS_CXX20
			consteval
#else
			constexpr
#endif
			single copied_from(OtherFirstValueType &&other)
			noexcept
			(
				std::is_nothrow_constructible_v<FirstValueType, OtherFirstValueType&&>
				)
		{
			single temp{ noinit };
			temp.copy_from<state_t::uninitialized, OtherState>(std::forward<OtherFirstValueType>(other));
			return std::move(temp);
		}

		template <dynamic_states_t DynamicStates, typename OtherFirstValueType>
			requires
		(
			!std::is_same_v<std::remove_cvref_t<OtherFirstValueType>, single>
			)
			static
#if WOJ_HAS_CXX20
			consteval
#else
			constexpr
#endif
			single copied_from(const state_t other_state, OtherFirstValueType &&other)
			noexcept
			(
				std::is_nothrow_constructible_v<FirstValueType, OtherFirstValueType&&>
				)
		{
			single temp{ noinit };
			temp.copy_from(state_t::uninitialized, other_state, std::forward<OtherFirstValueType>(other));
			return std::move(temp);
		}

	private:

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown, typename OtherSingleType>
			requires
		(
			std::is_same_v<std::remove_cvref_t<OtherSingleType>, single>
			)
			constexpr void copy_to_helper(OtherSingleType&& other) const
			noexcept
			(
				(
					(
						State == state_t::initialized ||
						State == state_t::unknown
						) && 
					(
						(
							OtherState == state_t::initialized&& 
							(
								std::is_nothrow_copy_assignable_v<FirstValueType> ||
								(
									!std::is_copy_assignable_v<FirstValueType>&& 
									std::is_nothrow_copy_constructible_v<FirstValueType>
									)
								)
							) ||
						(
							OtherState == state_t::uninitialized&& 
							std::is_nothrow_copy_constructible_v<FirstValueType>
							)
						)
					) ||
				State == state_t::uninitialized
				)
		{
			if constexpr (State == state_t::initialized || State == state_t::unknown)
			{
				if constexpr (OtherState == state_t::initialized)
				{
					if constexpr (std::is_copy_assignable_v<FirstValueType>)
					{
						other.first = first;
					}
					else
					{
						std::destroy_at(std::addressof(other.first));
						std::construct_at(std::addressof(other.first), first);
					}
				}
				else
				{
					std::construct_at(std::addressof(other.first), first);
				}
			}
		}

	public:

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown, typename OtherSingleType>
			requires
		(
			std::is_same_v<std::remove_cvref_t<OtherSingleType>, single>
			)
			constexpr const single &copy_to(OtherSingleType&& other) const &
			noexcept
			(
				(
					(
						State == state_t::initialized ||
						State == state_t::unknown
						) && 
					(
						(
							OtherState == state_t::initialized&& 
							(
								std::is_nothrow_copy_assignable_v<FirstValueType> ||
								(
									!std::is_copy_assignable_v<FirstValueType>&& 
									std::is_nothrow_copy_constructible_v<FirstValueType>
									)
								)
							) ||
						(
							OtherState == state_t::uninitialized&& 
							std::is_nothrow_copy_constructible_v<FirstValueType>
							)
						)
					) ||
				State == state_t::uninitialized
				)
		{
			this->template copy_to_helper<State, OtherState>(other);
			return *this;
		}

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown, typename OtherSingleType>
			requires
		(
			std::is_same_v<std::remove_cvref_t<OtherSingleType>, single>
			)
			constexpr single &copy_to(OtherSingleType&& other) & 
			noexcept
			(
				(
					(
						State == state_t::initialized ||
						State == state_t::unknown
						) && 
					(
						(
							OtherState == state_t::initialized&& 
							(
								std::is_nothrow_copy_assignable_v<FirstValueType> ||
								(
									!std::is_copy_assignable_v<FirstValueType>&& 
									std::is_nothrow_copy_constructible_v<FirstValueType>
									)
								)
							) ||
						(
							OtherState == state_t::uninitialized&& 
							std::is_nothrow_copy_constructible_v<FirstValueType>
							)
						)
					) ||
				State == state_t::uninitialized
				)
		{
			this->template copy_to_helper<State, OtherState>(other);
			return *this;
		}

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown, typename OtherSingleType>
			requires
		(
			std::is_same_v<std::remove_cvref_t<OtherSingleType>, single>
			)
			constexpr const single &&copy_to(OtherSingleType&& other) const &&
			noexcept
			(
				(
					(
						State == state_t::initialized ||
						State == state_t::unknown
						) && 
					(
						(
							OtherState == state_t::initialized&& 
							(
								std::is_nothrow_copy_assignable_v<FirstValueType> ||
								(
									!std::is_copy_assignable_v<FirstValueType>&& 
									std::is_nothrow_copy_constructible_v<FirstValueType>
									)
								)
							) ||
						(
							OtherState == state_t::uninitialized&& 
							std::is_nothrow_copy_constructible_v<FirstValueType>
							)
						)
					) ||
				State == state_t::uninitialized
				)
		{
			this->template copy_to_helper<State, OtherState>(other);
			return *this;
		}

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown, typename OtherSingleType>
			requires
		(
			std::is_same_v<std::remove_cvref_t<OtherSingleType>, single>
			)
			constexpr single &&copy_to(OtherSingleType&& other) && 
			noexcept
			(
				(
					(
						State == state_t::initialized ||
						State == state_t::unknown
						) && 
					(
						(
							OtherState == state_t::initialized&& 
							(
								std::is_nothrow_copy_assignable_v<FirstValueType> ||
								(
									!std::is_copy_assignable_v<FirstValueType>&& 
									std::is_nothrow_copy_constructible_v<FirstValueType>
									)
								)
							) ||
						(
							OtherState == state_t::uninitialized&& 
							std::is_nothrow_copy_constructible_v<FirstValueType>
							)
						)
					) ||
				State == state_t::uninitialized
				)
		{
			this->template copy_to_helper<State, OtherState>(other);
			return *this;
		}

	private:

		template <dynamic_states_t DynamicStates, typename OtherSingleType>
			requires
		(
			std::is_same_v<std::remove_cvref_t<OtherSingleType>, single>
			)
			constexpr void copy_to_helper(const state_t state, const state_t other_state, OtherSingleType&& other) const
			noexcept
			(
				std::is_nothrow_copy_assignable_v<FirstValueType>&&
				std::is_nothrow_copy_constructible_v<FirstValueType>&&
				std::is_nothrow_destructible_v<FirstValueType>
				)
		{
			if (state == state_t::initialized || state == state_t::unknown)
			{
				if (other_state == state_t::initialized)
				{
					if constexpr (std::is_copy_assignable_v<FirstValueType>)
					{
						other.first = first;
					}
					else
					{
						std::destroy_at(std::addressof(other.first));
						std::construct_at(std::addressof(other.first), first);
					}
				}
				else
				{
					std::construct_at(std::addressof(other.first), first);
				}
			}
		}

	public:

		template <dynamic_states_t DynamicStates, typename OtherSingleType>
			requires
		(
			std::is_same_v<std::remove_cvref_t<OtherSingleType>, single>
			)
			constexpr const single &copy_to(const state_t state, const state_t other_state, OtherSingleType&& other) const &
			noexcept
			(
				std::is_nothrow_copy_assignable_v<FirstValueType>&&
				std::is_nothrow_copy_constructible_v<FirstValueType>&&
				std::is_nothrow_destructible_v<FirstValueType>
				)
		{
			this->template copy_to_helper<dynamic_states>(state, other_state, std::forward<OtherSingleType>(other));
			return *this;
		}

		template <dynamic_states_t DynamicStates, typename OtherSingleType>
			requires
		(
			std::is_same_v<std::remove_cvref_t<OtherSingleType>, single>
			)
			constexpr single &copy_to(const state_t state, const state_t other_state, OtherSingleType&& other) & 
			noexcept
			(
				std::is_nothrow_copy_assignable_v<FirstValueType>&&
				std::is_nothrow_copy_constructible_v<FirstValueType>&&
				std::is_nothrow_destructible_v<FirstValueType>
				)
		{
			this->template copy_to_helper<dynamic_states>(state, other_state, std::forward<OtherSingleType>(other));
			return *this;
		}

		template <dynamic_states_t DynamicStates, typename OtherSingleType>
			requires
		(
			std::is_same_v<std::remove_cvref_t<OtherSingleType>, single>
			)
			constexpr const single &&copy_to(const state_t state, const state_t other_state, OtherSingleType&& other) const &&
			noexcept
			(
				std::is_nothrow_copy_assignable_v<FirstValueType>&&
				std::is_nothrow_copy_constructible_v<FirstValueType>&&
				std::is_nothrow_destructible_v<FirstValueType>
				)
		{
			this->template copy_to_helper<dynamic_states>(state, other_state, std::forward<OtherSingleType>(other));
			return *this;
		}

		template <dynamic_states_t DynamicStates, typename OtherSingleType>
			requires
		(
			std::is_same_v<std::remove_cvref_t<OtherSingleType>, single>
			)
			constexpr single &&copy_to(const state_t state, const state_t other_state, OtherSingleType&& other) && 
			noexcept
			(
				std::is_nothrow_copy_assignable_v<FirstValueType>&&
				std::is_nothrow_copy_constructible_v<FirstValueType>&&
				std::is_nothrow_destructible_v<FirstValueType>
				)
		{
			this->template copy_to_helper<dynamic_states>(state, other_state, std::forward<OtherSingleType>(other));
			return *this;
		}

	private:

		template <state_t State = state_t::unknown, typename OtherFirstValueType>
			requires
		(
			!std::is_same_v<std::remove_cvref_t<OtherFirstValueType>, single>
			)
			constexpr void copy_to_helper(OtherFirstValueType &&other) const
			noexcept
			(
				(
					(
						State == state_t::uninitialized || State == state_t::unknown
						) && 
					(
						std::is_nothrow_assignable_v<FirstValueType, OtherFirstValueType&&> ||
						(
							!std::is_assignable_v<FirstValueType, OtherFirstValueType&&>&& 
							std::is_nothrow_constructible_v<FirstValueType, OtherFirstValueType&&>&& 
							std::is_nothrow_destructible_v<FirstValueType>
							)
						)
					) ||
				State == state_t::uninitialized
				)
		{
			if constexpr (State == state_t::initialized || State == state_t::unknown)
			{
				if constexpr (std::is_assignable_v<FirstValueType, OtherFirstValueType&&>)
				{
					other.first = first;
				}
				else
				{
					std::destroy_at(std::addressof(other.first));
					std::construct_at(std::addressof(other.first), first);
				}
			}
		}

	public:

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown, typename OtherFirstValueType>
			requires
		(
			!std::is_same_v<std::remove_cvref_t<OtherFirstValueType>, single>
			)
			constexpr const single &copy_to(OtherFirstValueType &&other) const &
			noexcept
			(
				(
					(
						State == state_t::uninitialized || State == state_t::unknown
						) && 
					(
						std::is_nothrow_assignable_v<FirstValueType, OtherFirstValueType&&> ||
						(
							!std::is_assignable_v<FirstValueType, OtherFirstValueType&&>&& 
							std::is_nothrow_constructible_v<FirstValueType, OtherFirstValueType&&>&& 
							std::is_nothrow_destructible_v<FirstValueType>
							)
						)
					) ||
				State == state_t::uninitialized
				)
		{
			this->template copy_to_helper<State>(std::forward<OtherFirstValueType>(other));

			return *this;
		}

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown, typename OtherFirstValueType>
			requires
		(
			!std::is_same_v<std::remove_cvref_t<OtherFirstValueType>, single>
			)
			constexpr single &copy_to(OtherFirstValueType &&other) & 
			noexcept
			(
				(
					(
						State == state_t::uninitialized || State == state_t::unknown
						) && 
					(
						std::is_nothrow_assignable_v<FirstValueType, OtherFirstValueType&&> ||
						(
							!std::is_assignable_v<FirstValueType, OtherFirstValueType&&>&& 
							std::is_nothrow_constructible_v<FirstValueType, OtherFirstValueType&&>&& 
							std::is_nothrow_destructible_v<FirstValueType>
							)
						)
					) ||
				State == state_t::uninitialized
				)
		{
			this->template copy_to_helper<State>(std::forward<OtherFirstValueType>(other));

			return *this;
		}

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown, typename OtherFirstValueType>
			requires
		(
			!std::is_same_v<std::remove_cvref_t<OtherFirstValueType>, single>
			)
			constexpr const single &&copy_to(OtherFirstValueType &&other) const &&
			noexcept
			(
				(
					(
						State == state_t::uninitialized || State == state_t::unknown
						) && 
					(
						std::is_nothrow_assignable_v<FirstValueType, OtherFirstValueType&&> ||
						(
							!std::is_assignable_v<FirstValueType, OtherFirstValueType&&>&& 
							std::is_nothrow_constructible_v<FirstValueType, OtherFirstValueType&&>&& 
							std::is_nothrow_destructible_v<FirstValueType>
							)
						)
					) ||
				State == state_t::uninitialized
				)
		{
			this->template copy_to_helper<State>(std::forward<OtherFirstValueType>(other));

			return *this;
		}

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown, typename OtherFirstValueType>
			requires
		(
			!std::is_same_v<std::remove_cvref_t<OtherFirstValueType>, single>
			)
			constexpr single &&copy_to(OtherFirstValueType &&other) && 
			noexcept
			(
				(
					(
						State == state_t::uninitialized || State == state_t::unknown
						) && 
					(
						std::is_nothrow_assignable_v<FirstValueType, OtherFirstValueType&&> ||
						(
							!std::is_assignable_v<FirstValueType, OtherFirstValueType&&>&& 
							std::is_nothrow_constructible_v<FirstValueType, OtherFirstValueType&&>&& 
							std::is_nothrow_destructible_v<FirstValueType>
							)
						)
					) ||
				State == state_t::uninitialized
				)
		{
			this->template copy_to_helper<State>(std::forward<OtherFirstValueType>(other));

			return *this;
		}

	private:

		template <dynamic_states_t DynamicStates, typename OtherFirstValueType>
			requires
		(
			!std::is_same_v<std::remove_cvref_t<OtherFirstValueType>, single>
			)
			constexpr void copy_to_helper(const state_t state, OtherFirstValueType &&other) const
			noexcept
			(
				std::is_nothrow_assignable_v<FirstValueType, OtherFirstValueType&&>&&
				std::is_nothrow_copy_constructible_v<FirstValueType>&&
				std::is_nothrow_destructible_v<FirstValueType>
				)
		{
			if (state == state_t::initialized || state == state_t::unknown)
			{
				if constexpr (std::is_assignable_v<FirstValueType, OtherFirstValueType&&>)
				{
					other.first = first;
				}
				else
				{
					std::destroy_at(std::addressof(other.first));
					std::construct_at(std::addressof(other.first), first);
				}
			}
		}

	public:

		template <dynamic_states_t DynamicStates, typename OtherFirstValueType>
			requires
		(
			!std::is_same_v<std::remove_cvref_t<OtherFirstValueType>, single>
			)
			constexpr const single &copy_to(const state_t state, const state_t other_state, OtherFirstValueType &&other) const &
			noexcept
			(
				std::is_nothrow_assignable_v<FirstValueType, OtherFirstValueType&&>&&
				std::is_nothrow_copy_constructible_v<FirstValueType>&&
				std::is_nothrow_destructible_v<FirstValueType>
				)
		{
			this->template copy_to_helper<dynamic_states>(state, std::forward<OtherFirstValueType>(other));
			return *this;
		}

		template <dynamic_states_t DynamicStates, typename OtherFirstValueType>
			requires
		(
			!std::is_same_v<std::remove_cvref_t<OtherFirstValueType>, single>
			)
			constexpr single &copy_to(const state_t state, const state_t other_state, OtherFirstValueType &&other) & 
			noexcept
			(
				std::is_nothrow_assignable_v<FirstValueType, OtherFirstValueType&&>&&
				std::is_nothrow_copy_constructible_v<FirstValueType>&&
				std::is_nothrow_destructible_v<FirstValueType>
				)
		{
			this->template copy_to_helper<dynamic_states>(state, std::forward<OtherFirstValueType>(other));
			return *this;
		}

		template <dynamic_states_t DynamicStates, typename OtherFirstValueType>
			requires
		(
			!std::is_same_v<std::remove_cvref_t<OtherFirstValueType>, single>
			)
			constexpr const single &&copy_to(const state_t state, const state_t other_state, OtherFirstValueType &&other) const &&
			noexcept
			(
				std::is_nothrow_assignable_v<FirstValueType, OtherFirstValueType&&>&&
				std::is_nothrow_copy_constructible_v<FirstValueType>&&
				std::is_nothrow_destructible_v<FirstValueType>
				)
		{
			this->template copy_to_helper<dynamic_states>(state, std::forward<OtherFirstValueType>(other));
			return *this;
		}

		template <dynamic_states_t DynamicStates, typename OtherFirstValueType>
			requires
		(
			!std::is_same_v<std::remove_cvref_t<OtherFirstValueType>, single>
			)
			constexpr single &&copy_to(const state_t state, const state_t other_state, OtherFirstValueType &&other) && 
			noexcept
			(
				std::is_nothrow_assignable_v<FirstValueType, OtherFirstValueType&&>&&
				std::is_nothrow_copy_constructible_v<FirstValueType>&&
				std::is_nothrow_destructible_v<FirstValueType>
				)
		{
			this->template copy_to_helper<dynamic_states>(state, std::forward<OtherFirstValueType>(other));
			return *this;
		}

	private:

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown, typename OtherSingleType>
			requires
		(
			std::is_same_v<std::remove_cvref_t<OtherSingleType>, single>
			)
			constexpr void move_from_helper(OtherSingleType&& other)
			noexcept
			(
				(
					(
						State == state_t::initialized ||
						State == state_t::unknown
						) && 
					(
						(
							(
								OtherState == state_t::initialized ||
								OtherState == state_t::unknown
								) && 
							(
								std::is_nothrow_move_assignable_v<FirstValueType> ||
								(
									!std::is_move_assignable_v<FirstValueType>&& 
									std::is_nothrow_move_constructible_v<FirstValueType>&& 
									std::is_nothrow_destructible_v<FirstValueType>
									)
								)
							) ||
						OtherState == state_t::uninitialized
						)
					) ||
				(
					State == state_t::uninitialized&& 
					(
						(
							(
								OtherState == state_t::initialized ||
								OtherState == state_t::unknown
								) && 
							std::is_nothrow_move_constructible_v<FirstValueType>
							) ||
						OtherState == state_t::uninitialized
						)
					)
				)
		{
			if constexpr
				(
					(
						State == state_t::initialized ||
						State == state_t::unknown
						) && 
					(
						OtherState == state_t::initialized ||
						OtherState == state_t::unknown
						)
					)
			{
				if constexpr (std::is_move_assignable_v<FirstValueType>)
				{
					first = std::move(other.first);
				}
				else
				{
					std::destroy_at(std::addressof(first));
					std::construct_at(std::addressof(first), std::move(other.first));
				}
			}
			else if constexpr (OtherState == state_t::initialized || OtherState == state_t::unknown)
			{
				std::construct_at(std::addressof(first), std::move(other.first));
			}
		}

	public:

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown, typename OtherSingleType>
			requires
		(
			std::is_same_v<std::remove_cvref_t<OtherSingleType>, single>
			)
			constexpr single &move_from(OtherSingleType&& other) & 
			noexcept
			(
				(
					(
						State == state_t::initialized ||
						State == state_t::unknown
						) && 
					(
						(
							(
								OtherState == state_t::initialized ||
								OtherState == state_t::unknown
								) && 
							(
								std::is_nothrow_move_assignable_v<FirstValueType> ||
								(
									!std::is_move_assignable_v<FirstValueType>&& 
									std::is_nothrow_move_constructible_v<FirstValueType>&& 
									std::is_nothrow_destructible_v<FirstValueType>
									)
								)
							) ||
						OtherState == state_t::uninitialized
						)
					) ||
				(
					State == state_t::uninitialized&& 
					(
						(
							(
								OtherState == state_t::initialized ||
								OtherState == state_t::unknown
								) && 
							std::is_nothrow_move_constructible_v<FirstValueType>
							) ||
						OtherState == state_t::uninitialized
						)
					)
				)
		{
			this->template move_from_helper<State, OtherState>(std::forward<OtherSingleType>(other));
			return *this;
		}

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown, typename OtherSingleType>
			requires
		(
			std::is_same_v<std::remove_cvref_t<OtherSingleType>, single>
			)
			constexpr single &&move_from(OtherSingleType&& other) && 
			noexcept
			(
				(
					(
						State == state_t::initialized ||
						State == state_t::unknown
						) && 
					(
						(
							(
								OtherState == state_t::initialized ||
								OtherState == state_t::unknown
								) && 
							(
								std::is_nothrow_move_assignable_v<FirstValueType> ||
								(
									!std::is_move_assignable_v<FirstValueType>&& 
									std::is_nothrow_move_constructible_v<FirstValueType>&& 
									std::is_nothrow_destructible_v<FirstValueType>
									)
								)
							) ||
						OtherState == state_t::uninitialized
						)
					) ||
				(
					State == state_t::uninitialized&& 
					(
						(
							(
								OtherState == state_t::initialized ||
								OtherState == state_t::unknown
								) && 
							std::is_nothrow_move_constructible_v<FirstValueType>
							) ||
						OtherState == state_t::uninitialized
						)
					)
				)
		{
			this->template move_from_helper<State, OtherState>(std::forward<OtherSingleType>(other));
			return *this;
		}

	private:

		template <dynamic_states_t DynamicStates, typename OtherSingleType>
			requires
		(
			std::is_same_v<std::remove_cvref_t<OtherSingleType>, single>
			)
			constexpr void move_from_helper(const state_t state, const state_t other_state, OtherSingleType&& other)
			noexcept
			(
				std::is_nothrow_move_assignable_v<FirstValueType>&&
				std::is_nothrow_move_constructible_v<FirstValueType>&&
				std::is_nothrow_destructible_v<FirstValueType>
				)
		{
			if
				(
					(
						state == state_t::initialized || state == state_t::unknown
						) && 
					(
						other_state == state_t::initialized || other_state == state_t::unknown
						)
					)
			{
				if constexpr (std::is_move_assignable_v<FirstValueType>)
				{
					first = std::move(other.first);
				}
				else
				{
					std::destroy_at(std::addressof(first));
					std::construct_at(std::addressof(first), std::move(other.first));
				}
			}
			else if (other_state == state_t::initialized || other_state == state_t::unknown)
			{
				std::construct_at(std::addressof(first), std::move(other.first));
			}
		}

	public:

		template <dynamic_states_t DynamicStates, typename OtherSingleType>
			requires
		(
			std::is_same_v<std::remove_cvref_t<OtherSingleType>, single>
			)
			constexpr single &move_from(const state_t state, const state_t other_state, OtherSingleType&& other) & 
			noexcept
			(
				std::is_nothrow_move_assignable_v<FirstValueType>&&
				std::is_nothrow_move_constructible_v<FirstValueType>&&
				std::is_nothrow_destructible_v<FirstValueType>
				)
		{
			this->template move_from_helper<dynamic_states>(state, other_state, std::forward<OtherSingleType>(other));
			return *this;
		}

		template <dynamic_states_t DynamicStates, typename OtherSingleType>
			requires
		(
			std::is_same_v<std::remove_cvref_t<OtherSingleType>, single>
			)
			constexpr single &&move_from(const state_t state, const state_t other_state, OtherSingleType&& other) && 
			noexcept
			(
				std::is_nothrow_move_assignable_v<FirstValueType>&&
				std::is_nothrow_move_constructible_v<FirstValueType>&&
				std::is_nothrow_destructible_v<FirstValueType>
				)
		{
			this->template move_from_helper<dynamic_states>(state, other_state, std::forward<OtherSingleType>(other));
			return *this;
		}

	private:

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown, typename OtherFirstValueType>
			requires
		(
			!std::is_same_v<std::remove_cvref_t<OtherFirstValueType>, single>
			)
			constexpr void move_from_helper(OtherFirstValueType &&other)
			noexcept
			(
				(
					(
						State == state_t::initialized ||
						State == state_t::unknown
						) && 
					(
						std::is_nothrow_assignable_v<FirstValueType, OtherFirstValueType&&> ||
						(
							!std::is_assignable_v<FirstValueType, OtherFirstValueType&&>&& 
							std::is_nothrow_constructible_v<FirstValueType, OtherFirstValueType&&>&& 
							std::is_nothrow_destructible_v<FirstValueType>
							)
						)
					) ||
				(
					State == state_t::uninitialized&& 
					std::is_nothrow_constructible_v<FirstValueType, OtherFirstValueType&&>
					)
				)
		{
			if constexpr (State == state_t::initialized || State == state_t::unknown)
			{
				if constexpr (std::is_assignable_v<FirstValueType, OtherFirstValueType&&>)
				{
					first = std::move(other);
				}
				else
				{
					std::destroy_at(std::addressof(first));
					std::construct_at(std::addressof(first), std::move(other));
				}
			}
			else
			{
				std::construct_at(std::addressof(first), std::move(other));
			}
		}

	public:

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown, typename OtherFirstValueType>
			requires
		(
			!std::is_same_v<std::remove_cvref_t<OtherFirstValueType>, single>
			)
			constexpr single &move_from(OtherFirstValueType &&other) & 
			noexcept
			(
				(
					(
						State == state_t::initialized ||
						State == state_t::unknown
						) && 
					(
						std::is_nothrow_assignable_v<FirstValueType, OtherFirstValueType&&> ||
						(
							!std::is_assignable_v<FirstValueType, OtherFirstValueType&&>&& 
							std::is_nothrow_constructible_v<FirstValueType, OtherFirstValueType&&>&& 
							std::is_nothrow_destructible_v<FirstValueType>
							)
						)
					) ||
				(
					State == state_t::uninitialized&& 
					std::is_nothrow_constructible_v<FirstValueType, OtherFirstValueType&&>
					)
				)
		{
			this->template move_from_helper<State, OtherState>(std::forward<OtherFirstValueType>(other));
			return *this;
		}

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown, typename OtherFirstValueType>
			requires
		(
			!std::is_same_v<std::remove_cvref_t<OtherFirstValueType>, single>
			)
			constexpr single &&move_from(OtherFirstValueType &&other) && 
			noexcept
			(
				(
					(
						State == state_t::initialized ||
						State == state_t::unknown
						) && 
					(
						std::is_nothrow_assignable_v<FirstValueType, OtherFirstValueType&&> ||
						(
							!std::is_assignable_v<FirstValueType, OtherFirstValueType&&>&& 
							std::is_nothrow_constructible_v<FirstValueType, OtherFirstValueType&&>&& 
							std::is_nothrow_destructible_v<FirstValueType>
							)
						)
					) ||
				(
					State == state_t::uninitialized&& 
					std::is_nothrow_constructible_v<FirstValueType, OtherFirstValueType&&>
					)
				)
		{
			this->template move_from_helper<State, OtherState>(std::forward<OtherFirstValueType>(other));
			return *this;
		}

	private:

		template <dynamic_states_t DynamicStates, typename OtherFirstValueType>
			requires
		(
			!std::is_same_v<std::remove_cvref_t<OtherFirstValueType>, single>
			)
			constexpr void move_from_helper(const state_t state, const state_t other_state, OtherFirstValueType &&other)
			noexcept
			(
				std::is_nothrow_assignable_v<FirstValueType, OtherFirstValueType&&>&&
				std::is_nothrow_move_constructible_v<FirstValueType>&&
				std::is_nothrow_destructible_v<FirstValueType>
				)
		{
			if (state == state_t::initialized || state == state_t::unknown)
			{
				if constexpr (std::is_assignable_v<FirstValueType, OtherFirstValueType&&>)
				{
					first = std::move(other);
				}
				else
				{
					std::destroy_at(std::addressof(first));
					std::construct_at(std::addressof(first), std::move(other));
				}
			}
			else
			{
				std::construct_at(std::addressof(first), std::move(other));
			}
		}

	public:

		template <dynamic_states_t DynamicStates, typename OtherFirstValueType>
			requires
		(
			!std::is_same_v<std::remove_cvref_t<OtherFirstValueType>, single>
			)
			constexpr single &move_from(const state_t state, const state_t other_state, OtherFirstValueType &&other)
			noexcept
			(
				std::is_nothrow_assignable_v<FirstValueType, OtherFirstValueType&&>&&
				std::is_nothrow_move_constructible_v<FirstValueType>&&
				std::is_nothrow_destructible_v<FirstValueType>
				)
		{
			if (state == state_t::initialized || state == state_t::unknown)
			{
				if (other_state == state_t::initialized || other_state == state_t::unknown)
				{
					if constexpr (std::is_assignable_v<FirstValueType, OtherFirstValueType&&>)
					{
						first = std::move(other);
					}
					else
					{
						std::destroy_at(std::addressof(first));
						std::construct_at(std::addressof(first), std::move(other));
					}
				}
				else
				{
					std::construct_at(std::addressof(first), std::move(other));
				}
			}
			return *this;
		}

		template <state_t OtherState = state_t::unknown, typename OtherSingleType>
			requires
		(
			std::is_same_v<std::remove_cvref_t<OtherSingleType>, single>
			)
			static
#if WOJ_HAS_CXX20
			consteval
#else
			constexpr
#endif
			single moved_from(OtherSingleType&& other)
			noexcept
			(
				std::is_nothrow_move_constructible_v<FirstValueType>
				)
		{
			single temp{ noinit };
			temp.template move_from<state_t::uninitialized, OtherState>(std::forward<OtherSingleType>(other));
			return std::move(temp);
		}

		template <dynamic_states_t DynamicStates, typename OtherSingleType>
			requires
		(
			std::is_same_v<std::remove_cvref_t<OtherSingleType>, single>
			)
			static
#if WOJ_HAS_CXX20
			consteval
#else
			constexpr
#endif
			single moved_from(const state_t other_state, OtherSingleType&& other)
			noexcept
			(
				std::is_nothrow_move_constructible_v<FirstValueType>
				)
		{
			single temp{ noinit };
			temp.move_from(state_t::uninitialized, other_state, std::forward<OtherSingleType>(other));
			return std::move(temp);
		}

		template <state_t OtherState = state_t::unknown, typename OtherFirstValueType>
			requires
		(
			!std::is_same_v<std::remove_cvref_t<OtherFirstValueType>, single>
			)
			static
#if WOJ_HAS_CXX20
			consteval
#else
			constexpr
#endif
			single moved_from(OtherFirstValueType &&other)
			noexcept
			(
				std::is_nothrow_constructible_v<FirstValueType, OtherFirstValueType&&>
				)
		{
			single temp{ noinit };
			temp.template move_from<state_t::uninitialized, OtherState>(std::forward<OtherFirstValueType>(other));
			return std::move(temp);
		}

		template <dynamic_states_t DynamicStates, typename OtherFirstValueType>
			requires
		(
			!std::is_same_v<std::remove_cvref_t<OtherFirstValueType>, single>
			)
			static
#if WOJ_HAS_CXX20
			consteval
#else
			constexpr
#endif
			single moved_from(const state_t other_state, OtherFirstValueType &&other)
			noexcept
			(
				std::is_nothrow_constructible_v<FirstValueType, OtherFirstValueType&&>
				)
		{
			single temp{ noinit };
			temp.move_from(state_t::uninitialized, other_state, std::forward<OtherFirstValueType>(other));
			return std::move(temp);
		}

	private:

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown, typename OtherSingleType>
			requires
		(
			std::is_same_v<std::remove_cvref_t<OtherSingleType>, single>
			)
			constexpr void move_to_helper(OtherSingleType&& other) const
			noexcept
			(
				(
					(
						State == state_t::initialized ||
						State == state_t::unknown
						) && 
					(
						(
							(
								OtherState == state_t::initialized ||
								OtherState == state_t::unknown
								) && 
							std::is_nothrow_move_assignable_v<FirstValueType>
							) ||
						(
							OtherState == state_t::uninitialized&& 
							std::is_nothrow_move_constructible_v<FirstValueType>
							)
						)
					) ||
				State == state_t::uninitialized
				)
		{
			if constexpr (State == state_t::initialized || State == state_t::unknown)
			{
				if constexpr (OtherState == state_t::initialized || OtherState == state_t::unknown)
				{
					if constexpr (std::is_move_assignable_v<FirstValueType>)
					{
						other.first = std::move(first);
					}
					else
					{
						std::destroy_at(std::addressof(other.first));
						std::construct_at(std::addressof(other.first), std::move(first));
					}
				}
				else
				{
					std::construct_at(std::addressof(other.first), std::move(first));
				}
			}
		}

	public:

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown, typename OtherSingleType>
			requires
		(
			std::is_same_v<std::remove_cvref_t<OtherSingleType>, single>
			)
			constexpr const single &move_to(OtherSingleType&& other) const &
			noexcept
			(
				(
					(
						State == state_t::initialized ||
						State == state_t::unknown
						) && 
					(
						(
							(
								OtherState == state_t::initialized ||
								OtherState == state_t::unknown
								) && 
							std::is_nothrow_move_assignable_v<FirstValueType>
							) ||
						(
							OtherState == state_t::uninitialized&& 
							std::is_nothrow_move_constructible_v<FirstValueType>
							)
						)
					) ||
				State == state_t::uninitialized
				)
		{
			this->template move_to_helper<State, OtherState>(std::forward<OtherSingleType>(other));
			return *this;
		}

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown, typename OtherSingleType>
			requires
		(
			std::is_same_v<std::remove_cvref_t<OtherSingleType>, single>
			)
			constexpr single &move_to(OtherSingleType&& other) & 
			noexcept
			(
				(
					(
						State == state_t::initialized ||
						State == state_t::unknown
						) && 
					(
						(
							(
								OtherState == state_t::initialized ||
								OtherState == state_t::unknown
								) && 
							std::is_nothrow_move_assignable_v<FirstValueType>
							) ||
						(
							OtherState == state_t::uninitialized&& 
							std::is_nothrow_move_constructible_v<FirstValueType>
							)
						)
					) ||
				State == state_t::uninitialized
				)
		{
			this->template move_to_helper<State, OtherState>(std::forward<OtherSingleType>(other));
			return *this;
		}

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown, typename OtherSingleType>
			requires
		(
			std::is_same_v<std::remove_cvref_t<OtherSingleType>, single>
			)
			constexpr const single &&move_to(OtherSingleType&& other) const &&
			noexcept
			(
				(
					(
						State == state_t::initialized ||
						State == state_t::unknown
						) && 
					(
						(
							(
								OtherState == state_t::initialized ||
								OtherState == state_t::unknown
								) && 
							std::is_nothrow_move_assignable_v<FirstValueType>
							) ||
						(
							OtherState == state_t::uninitialized&& 
							std::is_nothrow_move_constructible_v<FirstValueType>
							)
						)
					) ||
				State == state_t::uninitialized
				)
		{
			this->template move_to_helper<State, OtherState>(std::forward<OtherSingleType>(other));
			return *this;
		}

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown, typename OtherSingleType>
			requires
		(
			std::is_same_v<std::remove_cvref_t<OtherSingleType>, single>
			)
			constexpr single &&move_to(OtherSingleType&& other) && 
			noexcept
			(
				(
					(
						State == state_t::initialized ||
						State == state_t::unknown
						) && 
					(
						(
							(
								OtherState == state_t::initialized ||
								OtherState == state_t::unknown
								) && 
							std::is_nothrow_move_assignable_v<FirstValueType>
							) ||
						(
							OtherState == state_t::uninitialized&& 
							std::is_nothrow_move_constructible_v<FirstValueType>
							)
						)
					) ||
				State == state_t::uninitialized
				)
		{
			this->template move_to_helper<State, OtherState>(std::forward<OtherSingleType>(other));
			return *this;
		}

	private:

		template <dynamic_states_t DynamicStates, typename OtherSingleType>
			requires
		(
			std::is_same_v<std::remove_cvref_t<OtherSingleType>, single>
			)
			constexpr void move_to_helper(const state_t state, const state_t other_state, OtherSingleType&& other) const
			noexcept
			(
				std::is_nothrow_move_assignable_v<FirstValueType>&&
				std::is_nothrow_move_constructible_v<FirstValueType>&&
				std::is_nothrow_destructible_v<FirstValueType>
				)
		{
			if (state == state_t::initialized || state == state_t::unknown)
			{
				if (other_state == state_t::initialized || other_state == state_t::unknown)
				{
					if constexpr (std::is_move_assignable_v<FirstValueType>)
					{
						other.first = std::move(first);
					}
					else
					{
						std::destroy_at(std::addressof(other.first));
						std::construct_at(std::addressof(other.first), std::move(first));
					}
				}
				else
				{
					std::construct_at(std::addressof(other.first), std::move(first));
				}
			}
		}

	public:

		template <dynamic_states_t DynamicStates, typename OtherSingleType>
			requires
		(
			std::is_same_v<std::remove_cvref_t<OtherSingleType>, single>
			)
			constexpr const single &move_to(const state_t state, const state_t other_state, OtherSingleType&& other) const &
			noexcept
			(
				std::is_nothrow_move_assignable_v<FirstValueType>&&
				std::is_nothrow_move_constructible_v<FirstValueType>&&
				std::is_nothrow_destructible_v<FirstValueType>
				)
		{
			this->template move_to_helper<dynamic_states>(state, other_state, std::forward<OtherSingleType>(other));
			return *this;
		}

		template <dynamic_states_t DynamicStates, typename OtherSingleType>
			requires
		(
			std::is_same_v<std::remove_cvref_t<OtherSingleType>, single>
			)
			constexpr single &move_to(const state_t state, const state_t other_state, OtherSingleType&& other) & 
			noexcept
			(
				std::is_nothrow_move_assignable_v<FirstValueType>&&
				std::is_nothrow_move_constructible_v<FirstValueType>&&
				std::is_nothrow_destructible_v<FirstValueType>
				)
		{
			this->template move_to_helper<dynamic_states>(state, other_state, std::forward<OtherSingleType>(other));
			return *this;
		}

		template <dynamic_states_t DynamicStates, typename OtherSingleType>
			requires
		(
			std::is_same_v<std::remove_cvref_t<OtherSingleType>, single>
			)
			constexpr const single &&move_to(const state_t state, const state_t other_state, OtherSingleType&& other) const &&
			noexcept
			(
				std::is_nothrow_move_assignable_v<FirstValueType>&&
				std::is_nothrow_move_constructible_v<FirstValueType>&&
				std::is_nothrow_destructible_v<FirstValueType>
				)
		{
			this->template move_to_helper<dynamic_states>(state, other_state, std::forward<OtherSingleType>(other));
			return *this;
		}

		template <dynamic_states_t DynamicStates, typename OtherSingleType>
			requires
		(
			std::is_same_v<std::remove_cvref_t<OtherSingleType>, single>
			)
			constexpr single &&move_to(const state_t state, const state_t other_state, OtherSingleType&& other) && 
			noexcept
			(
				std::is_nothrow_move_assignable_v<FirstValueType>&&
				std::is_nothrow_move_constructible_v<FirstValueType>&&
				std::is_nothrow_destructible_v<FirstValueType>
				)
		{
			this->template move_to_helper<dynamic_states>(state, other_state, std::forward<OtherSingleType>(other));
			return *this;
		}

	private:

		template <state_t State = state_t::unknown, typename OtherFirstValueType>
			requires
		(
			!std::is_same_v<std::remove_cvref_t<OtherFirstValueType>, single>
			)
			constexpr void move_to_helper(OtherFirstValueType &&other) const
			noexcept
			(
				(
					(
						State == state_t::initialized ||
						State == state_t::unknown
						) && 
					(
						std::is_nothrow_assignable_v<FirstValueType, OtherFirstValueType&&> ||
						(
							!std::is_assignable_v<FirstValueType, OtherFirstValueType&&>&& 
							std::is_nothrow_constructible_v<FirstValueType, OtherFirstValueType&&>&& 
							std::is_nothrow_destructible_v<FirstValueType>
							)
						)
					) ||
				State == state_t::uninitialized
				)
		{
			if constexpr (State == state_t::initialized || State == state_t::unknown)
			{
				if constexpr (std::is_assignable_v<FirstValueType, OtherFirstValueType&&>)
				{
					other = std::move(first);
				}
				else
				{
					std::destroy_at(std::addressof(other));
					std::construct_at(std::addressof(other), std::move(first));
				}
			}
		}

	public:

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown, typename OtherFirstValueType>
			requires
		(
			!std::is_same_v<std::remove_cvref_t<OtherFirstValueType>, single>
			)
			constexpr const single &move_to(OtherFirstValueType &&other) const &
			noexcept
			(
				(
					(
						State == state_t::initialized ||
						State == state_t::unknown
						) && 
					(
						std::is_nothrow_assignable_v<FirstValueType, OtherFirstValueType&&> ||
						(
							!std::is_assignable_v<FirstValueType, OtherFirstValueType&&>&& 
							std::is_nothrow_constructible_v<FirstValueType, OtherFirstValueType&&>&& 
							std::is_nothrow_destructible_v<FirstValueType>
							)
						)
					) ||
				State == state_t::uninitialized
				)
		{
			this->template move_to_helper<State>(std::forward<OtherFirstValueType>(other));
			return *this;
		}

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown, typename OtherFirstValueType>
			requires
		(
			!std::is_same_v<std::remove_cvref_t<OtherFirstValueType>, single>
			)
			constexpr single &move_to(OtherFirstValueType &&other) & 
			noexcept
			(
				(
					(
						State == state_t::initialized ||
						State == state_t::unknown
						) && 
					(
						std::is_nothrow_assignable_v<FirstValueType, OtherFirstValueType&&> ||
						(
							!std::is_assignable_v<FirstValueType, OtherFirstValueType&&>&& 
							std::is_nothrow_constructible_v<FirstValueType, OtherFirstValueType&&>&& 
							std::is_nothrow_destructible_v<FirstValueType>
							)
						)
					) ||
				State == state_t::uninitialized
				)
		{
			this->template move_to_helper<State>(std::forward<OtherFirstValueType>(other));
			return *this;
		}

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown, typename OtherFirstValueType>
			requires
		(
			!std::is_same_v<std::remove_cvref_t<OtherFirstValueType>, single>
			)
			constexpr const single &&move_to(OtherFirstValueType &&other) const &&
			noexcept
			(
				(
					(
						State == state_t::initialized ||
						State == state_t::unknown
						) && 
					(
						std::is_nothrow_assignable_v<FirstValueType, OtherFirstValueType&&> ||
						(
							!std::is_assignable_v<FirstValueType, OtherFirstValueType&&>&& 
							std::is_nothrow_constructible_v<FirstValueType, OtherFirstValueType&&>&& 
							std::is_nothrow_destructible_v<FirstValueType>
							)
						)
					) ||
				State == state_t::uninitialized
				)
		{
			this->template move_to_helper<State>(std::forward<OtherFirstValueType>(other));
			return *this;
		}

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown, typename OtherFirstValueType>
			requires
		(
			!std::is_same_v<std::remove_cvref_t<OtherFirstValueType>, single>
			)
			constexpr single &&move_to(OtherFirstValueType &&other) && 
			noexcept
			(
				(
					(
						State == state_t::initialized ||
						State == state_t::unknown
						) && 
					(
						std::is_nothrow_assignable_v<FirstValueType, OtherFirstValueType&&> ||
						(
							!std::is_assignable_v<FirstValueType, OtherFirstValueType&&>&& 
							std::is_nothrow_constructible_v<FirstValueType, OtherFirstValueType&&>&& 
							std::is_nothrow_destructible_v<FirstValueType>
							)
						)
					) ||
				State == state_t::uninitialized
				)
		{
			this->template move_to_helper<State>(std::forward<OtherFirstValueType>(other));
			return *this;
		}

	private:

		template <state_t State = state_t::unknown>
		constexpr void reset_helper()
			noexcept
			(
				(
					(
						(
							State == state_t::initialized ||
							State == state_t::unknown
							) && 
						std::is_nothrow_destructible_v<FirstValueType>
						) ||
					State == state_t::uninitialized
					) && 
				(
					std::is_nothrow_default_constructible_v<FirstValueType> ||
					!std::is_default_constructible_v<FirstValueType>
					)
				)
		{
			if constexpr (State == state_t::initialized || State == state_t::unknown)
			{
				std::destroy_at(std::addressof(first));
			}
			if constexpr (std::is_default_constructible_v<FirstValueType>)
			{
				std::construct_at(std::addressof(first));
			}
		}

	public:

		template <state_t State = state_t::unknown>
		constexpr single &reset() & 
			noexcept
			(
				(
					(
						(
							State == state_t::initialized ||
							State == state_t::unknown
							) && 
						std::is_nothrow_destructible_v<FirstValueType>
						) ||
					State == state_t::uninitialized
					) && 
				(
					std::is_nothrow_default_constructible_v<FirstValueType> ||
					!std::is_default_constructible_v<FirstValueType>
					)
				)
		{
			this->reset_helper<State>();
			return *this;
		}

		template <state_t State = state_t::unknown>
		constexpr single &&reset() && 
			noexcept
			(
				(
					(
						(
							State == state_t::initialized ||
							State == state_t::unknown
							) && 
						std::is_nothrow_destructible_v<FirstValueType>
						) ||
					State == state_t::uninitialized
					) && 
				(
					std::is_nothrow_default_constructible_v<FirstValueType> ||
					!std::is_default_constructible_v<FirstValueType>
					)
				)
		{
			this->reset_helper<State>();
			return *this;
		}

	private:

		template <dynamic_states_t DynamicStates>
		constexpr void reset_helper(const state_t state)
			noexcept
			(
				std::is_nothrow_destructible_v<FirstValueType>&&
				std::is_nothrow_default_constructible_v<FirstValueType>
				)
		{
			if (state == state_t::initialized || state == state_t::unknown)
			{
				std::destroy_at(std::addressof(first));
			}
			if constexpr (std::is_default_constructible_v<FirstValueType>)
			{
				std::construct_at(std::addressof(first));
			}
		}

	public:

		template <dynamic_states_t DynamicStates>
		constexpr single &reset(const state_t state) & 
			noexcept
			(
				std::is_nothrow_destructible_v<FirstValueType>&&
				std::is_nothrow_default_constructible_v<FirstValueType>
				)
		{
			this->reset_helper(state);
			return *this;
		}

		template <dynamic_states_t DynamicStates>
		constexpr single &&reset(const state_t state) && 
			noexcept
			(
				std::is_nothrow_destructible_v<FirstValueType>&&
				std::is_nothrow_default_constructible_v<FirstValueType>
				)
		{
			this->reset_helper(state);
			return *this;
		}

		static constexpr single resetted()
			noexcept
			(
				std::is_nothrow_default_constructible_v<FirstValueType>
				)
		{
			single temp{ noinit };
			temp.reset<state_t::uninitialized>();
			return std::move(temp);
		}

		template <size_t Index>
		constexpr const FirstValueType& get() const &
			noexcept
#ifndef NDEBUG
			(
				!Index
			)
#endif
		{
#ifndef NDEBUG
			if constexpr (!Index)
				return first;

			throw bad_tuple_access{ __LINE__, "Single access out of bounds.", __FILE__, __func__ };
#else
			return first;
#endif
		}

		template <size_t Index>
		constexpr FirstValueType& get() & 
			noexcept
#ifndef NDEBUG
			(
				!Index
			)
#endif
		{
#ifndef NDEBUG
			if constexpr (!Index)
				return first;

			throw bad_tuple_access{ __LINE__, "Single access out of bounds.", __FILE__, __func__ };
#else
			return first;
#endif
		}

		template <size_t Index>
		constexpr const FirstValueType&& get() const &&
			noexcept
#ifndef NDEBUG
			(
				!Index
			)
#endif
		{
#ifndef NDEBUG
			if constexpr (!Index)
				return std::move(first);

			throw bad_tuple_access{ __LINE__, "Single access out of bounds.", __FILE__, __func__ };
#else
			return std::move(first);
#endif
		}

		template <size_t Index>
		constexpr FirstValueType&& get() && 
			noexcept
#ifndef NDEBUG
			(
				!Index
			)
#endif
		{
#ifndef NDEBUG
			if constexpr (!Index)
				return std::move(first);

			throw bad_tuple_access{ __LINE__, "Single access out of bounds.", __FILE__, __func__ };
#else
			return std::move(first);
#endif
		}

		template <size_t Index>
		constexpr const FirstValueType& at() const &
			noexcept
#ifndef NDEBUG
			(
				!Index
			)
#endif
		{
#ifndef NDEBUG
			if constexpr (!Index)
				return first;

			throw bad_tuple_access{ __LINE__, "Single access out of bounds.", __FILE__, __func__ };
#else
			return first;
#endif
		}

		template <size_t Index>
		constexpr FirstValueType& at() & 
			noexcept
#ifndef NDEBUG
			(
				!Index
			)
#endif
		{
#ifndef NDEBUG
			if constexpr (!Index)
				return first;

			throw bad_tuple_access{ __LINE__, "Single access out of bounds.", __FILE__, __func__ };
#else
			return first;
#endif
		}

		template <size_t Index>
		constexpr const FirstValueType&& at() const &&
			noexcept
#ifndef NDEBUG
			(
				!Index
			)
#endif
		{
#ifndef NDEBUG
			if constexpr (!Index)
				return std::move(first);

			throw bad_tuple_access{ __LINE__, "Single access out of bounds.", __FILE__, __func__ };
#else
			return std::move(first);
#endif
		}

		template <size_t Index>
		constexpr FirstValueType&& at() && 
			noexcept
#ifndef NDEBUG
			(
				!Index
			)
#endif
		{
#ifndef NDEBUG
			if constexpr (!Index)
				return std::move(first);

			throw bad_tuple_access{ __LINE__, "Single access out of bounds.", __FILE__, __func__ };
#else
			return std::move(first);
#endif
		}

		static
#if WOJ_HAS_CXX20
			consteval
#else
			constexpr
#endif
			size_t size()
			noexcept
		{
			return 1;
		}

	private:

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown, typename OtherSingleType>
			requires
		(
			std::is_same_v<std::remove_cvref_t<OtherSingleType>, single>
			)
			constexpr void swap_with_helper(OtherSingleType&& other)
			noexcept
			(
				(
					(
						State == state_t::initialized ||
						State == state_t::unknown
						) && 
					(
						(
							(
								OtherState == state_t::initialized ||
								OtherState == state_t::unknown
								) && 
							std::is_nothrow_swappable_v<FirstValueType>
							) ||
						(
							OtherState == state_t::uninitialized&& 
							std::is_nothrow_move_constructible_v<FirstValueType>
							)
						)
					) ||
				(
					State == state_t::uninitialized&& 
					(
						(
							(
								OtherState == state_t::initialized ||
								OtherState == state_t::unknown
								) && 
							std::is_nothrow_move_constructible_v<FirstValueType>
							) ||
						OtherState == state_t::uninitialized
						)
					)
				)
		{
			if constexpr (State == state_t::initialized || State == state_t::unknown)
			{
				if constexpr (OtherState == state_t::initialized || OtherState == state_t::unknown)
				{
					std::swap(first, other.first);
				}
				else
				{
					std::construct_at(std::addressof(other.first), std::move(first));
				}
			}
			else if constexpr (OtherState == state_t::initialized || OtherState == state_t::unknown)
			{
				std::construct_at(std::addressof(first), std::move(other.first));
			}
		}

	public:

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown, typename OtherSingleType>
			requires
		(
			std::is_same_v<std::remove_cvref_t<OtherSingleType>, single>
			)
			constexpr single &swap_with(OtherSingleType&& other) & 
			noexcept
			(
				(
					(
						State == state_t::initialized ||
						State == state_t::unknown
						) && 
					(
						(
							(
								OtherState == state_t::initialized ||
								OtherState == state_t::unknown
								) && 
							std::is_nothrow_swappable_v<FirstValueType>
							) ||
						(
							OtherState == state_t::uninitialized&& 
							std::is_nothrow_move_constructible_v<FirstValueType>
							)
						)
					) ||
				(
					State == state_t::uninitialized&& 
					(
						(
							(
								OtherState == state_t::initialized ||
								OtherState == state_t::unknown
								) && 
							std::is_nothrow_move_constructible_v<FirstValueType>
							) ||
						OtherState == state_t::uninitialized
						)
					)
				)
		{
			this->template swap_with_helper<State, OtherState>(std::forward<OtherSingleType>(other));
			return *this;
		}

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown, typename OtherSingleType>
			requires
		(
			std::is_same_v<std::remove_cvref_t<OtherSingleType>, single>
			)
			constexpr single &&swap_with(OtherSingleType&& other) && 
			noexcept
			(
				(
					(
						State == state_t::initialized ||
						State == state_t::unknown
						) && 
					(
						(
							(
								OtherState == state_t::initialized ||
								OtherState == state_t::unknown
								) && 
							std::is_nothrow_swappable_v<FirstValueType>
							) ||
						(
							OtherState == state_t::uninitialized&& 
							std::is_nothrow_move_constructible_v<FirstValueType>
							)
						)
					) ||
				(
					State == state_t::uninitialized&& 
					(
						(
							(
								OtherState == state_t::initialized ||
								OtherState == state_t::unknown
								) && 
							std::is_nothrow_move_constructible_v<FirstValueType>
							) ||
						OtherState == state_t::uninitialized
						)
					)
				)
		{
			this->template swap_with_helper<State, OtherState>(std::forward<OtherSingleType>(other));
			return *this;
		}

	private:

		template <dynamic_states_t DynamicStates, typename OtherSingleType>
			requires
		(
			std::is_same_v<std::remove_cvref_t<OtherSingleType>, single>
			)
			constexpr void swap_with_helper(const state_t state, const state_t other_state, OtherSingleType&& other)
			noexcept
			(
				std::is_nothrow_swappable_v<FirstValueType>&&
				std::is_nothrow_move_constructible_v<FirstValueType>
				)
		{
			if (state == state_t::initialized || state == state_t::unknown)
			{
				if (other_state == state_t::initialized || other_state == state_t::unknown)
				{
					std::swap(first, other.first);
				}
				else
				{
					std::construct_at(std::addressof(other.first), std::move(first));
				}
			}
			else if (other_state == state_t::initialized || other_state == state_t::unknown)
			{
				std::construct_at(std::addressof(first), std::move(other.first));
			}
		}

	public:

		template <dynamic_states_t DynamicStates, typename OtherSingleType>
			requires
		(
			std::is_same_v<std::remove_cvref_t<OtherSingleType>, single>
			)
			constexpr single &swap_with(const state_t state, const state_t other_state, OtherSingleType&& other) & 
			noexcept
			(
				std::is_nothrow_swappable_v<FirstValueType>&&
				std::is_nothrow_move_constructible_v<FirstValueType>
				)
		{
			this->template swap_with_helper<dynamic_states>(state, other_state, std::forward<OtherSingleType>(other));
			return *this;
		}

		template <dynamic_states_t DynamicStates, typename OtherSingleType>
			requires
		(
			std::is_same_v<std::remove_cvref_t<OtherSingleType>, single>
			)
			constexpr single &&swap_with(const state_t state, const state_t other_state, OtherSingleType&& other) && 
			noexcept
			(
				std::is_nothrow_swappable_v<FirstValueType>&&
				std::is_nothrow_move_constructible_v<FirstValueType>
				)
		{
			this->template swap_with_helper<dynamic_states>(state, other_state, std::forward<OtherSingleType>(other));
			return *this;
		}

	private:

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown, typename OtherFirstValueType>
			requires
		(
			!std::is_same_v<std::remove_cvref_t<OtherFirstValueType>, single>
			)
			constexpr void swap_with_helper(OtherFirstValueType &&other) const
			noexcept
			(
				(
					(
						State == state_t::initialized ||
						State == state_t::unknown
						) && 
					std::is_nothrow_swappable_v<FirstValueType>
					) ||
				(
					State == state_t::uninitialized&& 
					std::is_nothrow_move_constructible_v<FirstValueType>
					)
				)
		{
			if constexpr (State == state_t::initialized || State == state_t::unknown)
			{
				std::swap(first, other);
			}
			else
			{
				std::construct_at(std::addressof(first), std::move(other));
			}
		}

	public:

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown, typename OtherFirstValueType>
			requires
		(
			!std::is_same_v<std::remove_cvref_t<OtherFirstValueType>, single>
			)
			constexpr single &swap_with(OtherFirstValueType &&other) & 
			noexcept
			(
				(
					(
						(
							State == state_t::initialized ||
							State == state_t::unknown
							) && 
						std::is_nothrow_swappable_v<FirstValueType>
						) ||
					(
						State == state_t::uninitialized&& 
						std::is_nothrow_move_constructible_v<FirstValueType>
						)
					)
				)
		{
			this->template swap_with_helper<State>(std::forward<OtherFirstValueType>(other));
			return *this;
		}

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown, typename OtherFirstValueType>
			requires
		(
			!std::is_same_v<std::remove_cvref_t<OtherFirstValueType>, single>
			)
			constexpr single &&swap_with(OtherFirstValueType &&other) && 
			noexcept
			(
				(
					(
						State == state_t::initialized ||
						State == state_t::unknown
						) && 
					std::is_nothrow_swappable_v<FirstValueType>
					) ||
				(
					State == state_t::uninitialized&& 
					std::is_nothrow_move_constructible_v<FirstValueType>
					)
				)
		{
			this->template swap_with_helper<State>(std::forward<OtherFirstValueType>(other));
			return *this;
		}

	private:

		template <dynamic_states_t DynamicStates, typename OtherFirstValueType>
			requires
		(
			!std::is_same_v<std::remove_cvref_t<OtherFirstValueType>, single>
			)
			constexpr void swap_with_helper(const state_t state, const state_t other_state, OtherFirstValueType &&other) const
			noexcept
			(
				std::is_nothrow_swappable_v<FirstValueType>&&
				std::is_nothrow_move_constructible_v<FirstValueType>
				)
		{
			if (state == state_t::initialized || state == state_t::unknown)
			{
				std::swap(first, other);
			}
			else
			{
				std::construct_at(std::addressof(first), std::move(other));
			}
		}

	public:

		template <dynamic_states_t DynamicStates, typename OtherFirstValueType>
			requires
		(
			!std::is_same_v<std::remove_cvref_t<OtherFirstValueType>, single>
			)
			constexpr single &swap_with(const state_t state, const state_t other_state, OtherFirstValueType &&other) & 
			noexcept
			(
				std::is_nothrow_swappable_v<FirstValueType>&&
				std::is_nothrow_move_constructible_v<FirstValueType>
				)
		{
			this->template swap_with_helper<dynamic_states>(state, other_state, std::forward<OtherFirstValueType>(other));
			return *this;
		}

		template <dynamic_states_t DynamicStates, typename OtherFirstValueType>
			requires
		(
			!std::is_same_v<std::remove_cvref_t<OtherFirstValueType>, single>
			)
			constexpr single &&swap_with(const state_t state, const state_t other_state, OtherFirstValueType &&other) && 
			noexcept
			(
				std::is_nothrow_swappable_v<FirstValueType>&&
				std::is_nothrow_move_constructible_v<FirstValueType>
				)
		{
			this->template swap_with_helper<dynamic_states>(state, other_state, std::forward<OtherFirstValueType>(other));
			return *this;
		}
	};

	/*template <typename FirstValueType, typename SecondType>
	class pair
	{
	public:
		enum class state_t : uint8_t
		{
			unknown,
			initialized,
			uninitialized
		};

		union
		{
			FirstValueType first;
		};

		union
		{
			SecondType second;
		};

		using first_type = FirstValueType;
		using second_type = SecondType;

		constexpr pair()
			noexcept
			(
				std::is_nothrow_default_constructible_v<FirstValueType>&& 
				std::is_nothrow_default_constructible_v<SecondType>
			)
			: first{}, second{} {
		}

		explicit constexpr pair(const noinit_t noinit)
			noexcept {}

		template <typename OtherFirstValueType, typename OtherSecondType>
			requires
			(
				!std::is_same_v<std::remove_cvref_t<OtherFirstValueType>, in_place_t>
			)
		explicit constexpr pair(OtherFirstValueType &&first, OtherSecondType&& second)
			noexcept
			(
				std::is_nothrow_constructible_v<FirstValueType, OtherFirstValueType &&>&& 
				std::is_nothrow_constructible_v<SecondType, OtherSecondType&& >
			)
			: first{ std::forward<OtherFirstValueType>(first) }, second{ std::forward<OtherSecondType>(second) } {}

		template <typename OtherPairType>
			requires
			(
				!std::is_same_v<std::remove_cvref_t<OtherPairType>, noinit_t>&& 
				!std::is_same_v<std::remove_cvref_t<OtherPairType>, in_place_t>
			)
		explicit constexpr pair(OtherPairType&& other)
			noexcept
			(
				std::is_nothrow_constructible_v<FirstValueType, typename OtherPairType::first_type&& >&&
				std::is_nothrow_constructible_v<SecondType, typename OtherPairType::second_type&& >
				)
			: first{ std::forward<typename OtherPairType::first_type>(other.first) }, second{ std::forward<typename OtherPairType::second_type>(other.second) } {
		}

		template <typename OtherPairType>
			requires
			(
				!std::is_same_v<std::remove_cvref_t<OtherPairType>, noinit_t>&& 
				!std::is_same_v<std::remove_cvref_t<OtherPairType>, in_place_t>
			)
		constexpr pair(const state_t other_state, OtherPairType&& other)
			noexcept
			(
				std::is_nothrow_constructible_v<FirstValueType, typename OtherPairType::first_type&& >&&
				std::is_nothrow_constructible_v<SecondType, typename OtherPairType::second_type&& >
			)
			: first{ std::forward<typename OtherPairType::first_type>(other.first) }, second{ std::forward<typename OtherPairType::second_type>(other.second) } {}

		template <typename ...FirstArgsValueTypes, typename ...SecondArgsTypes>
		explicit constexpr pair(const in_place_t in_place, FirstArgsValueTypes&& ...args_first, const delimiter_t delimiter, SecondArgsTypes&& ...args_second)
			noexcept
			(
				std::is_nothrow_constructible_v<FirstValueType, FirstArgsValueTypes&& ...>&&
				std::is_nothrow_constructible_v<SecondType, SecondArgsTypes&& ...>
				)
			: first{ std::forward<FirstArgsValueTypes>(args_first)... }, second{ std::forward<SecondArgsTypes>(args_second)... } {}

		template <typename OtherPairType>
		constexpr pair& operator=(OtherPairType&& other)
			noexcept
			(
				(
					std::is_nothrow_assignable_v<FirstValueType, typename OtherPairType::first_type&& > ||
					(
						!std::is_assignable_v<FirstValueType, typename OtherPairType::first_type&& >&& 
						std::is_nothrow_constructible_v<FirstValueType, typename OtherPairType::first_type&& >&& 
						std::is_nothrow_destructible_v<FirstValueType>
					)
				) && 
				(
					std::is_nothrow_assignable_v<SecondType, typename OtherPairType::second_type&& > ||
					(
						!std::is_assignable_v<SecondType, typename OtherPairType::second_type&& >&&
						std::is_nothrow_constructible_v<SecondType, typename OtherPairType::second_type&& >&&
						std::is_nothrow_destructible_v<SecondType>
					)
				)
			)
		{
			if constexpr (std::is_copy_assignable_v<FirstValueType>)
			{
				first = other.first;
			}
			else
			{
				std::destroy_at(std::addressof(first));
				std::construct_at(std::addressof(first), other.first);
			}
			if constexpr (std::is_copy_assignable_v<SecondType>)
			{
				second = other.second;
			}
			else
			{
				std::destroy_at(std::addressof(second));
				std::construct_at(std::addressof(second), other.second);
			}
			return *this;
		}

		constexpr ~pair()
			noexcept
			(
				std::is_nothrow_destructible_v<FirstValueType>&& 
				std::is_nothrow_destructible_v<SecondType>
			)
		{
			std::destroy_at(std::addressof(first));
			std::destroy_at(std::addressof(second));
		}

		constexpr bool operator==(const pair& other) const
			noexcept
			(
				(
					std::is_arithmetic_v<FirstValueType> ||
					std::is_pointer_v<FirstValueType>
				) && 
				(
					std::is_arithmetic_v<SecondType> ||
					std::is_pointer_v<SecondType>
				)
			)
		{
			return first == other.first&& second == other.second;
		}

		constexpr std::strong_ordering operator<=>(const pair& other) const
			noexcept
			(
				(
					std::is_arithmetic_v<FirstValueType> ||
					std::is_pointer_v<FirstValueType>
					) && 
				(
					std::is_arithmetic_v<SecondType> ||
					std::is_pointer_v<SecondType>
					)
				)
		{
			if (first == other.first)
			{
				if (second == other.second)
				{
					return std::strong_ordering::equal;
				}
				if (second < other.second)
				{
					return std::strong_ordering::less;
				}
				return std::strong_ordering::greater;
			}
			if (first < other.first)
			{
				return std::strong_ordering::less;
			}
			return std::strong_ordering::greater;
		}

		constexpr auto& operator[](const size_t index)
			noexcept
#ifndef NDEBUG
			(
				false
			)
#endif
		{
#ifndef NDEBUG
			if (!index)
			{
				return first;
			}
			if (index == 1)
			{
				return second;
			}

			throw bad_tuple_access{ __LINE__, "Pair access out of bounds.", __FILE__, __func__ };
#else
			if (!index)
			{
				return first;
			}
			return second;
#endif
		}

		constexpr const auto& operator[](const size_t index) const
			noexcept
#ifndef NDEBUG
			(
				false
			)
#endif
		{
#ifndef NDEBUG
			if (!index)
			{
				return first;
			}
			if (index == 1)
			{
				return second;
			}

			throw bad_tuple_access{ __LINE__, "Pair access out of bounds.", __FILE__, __func__ };
#else
			if (!index)
			{
				return first;
			}
			return second;
#endif
		}

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown>
		constexpr pair& copy_from(const pair& other)
			noexcept
			(
				(
					State == state_t::initialized&& 
					(
						std::is_nothrow_copy_assignable_v<FirstValueType> ||
						(
							!std::is_copy_assignable_v<FirstValueType>&& 
							std::is_nothrow_copy_constructible_v<FirstValueType>
						)
					) && 
					(
						std::is_nothrow_copy_assignable_v<SecondType> ||
						(
							!std::is_copy_assignable_v<SecondType>&& 
							std::is_nothrow_copy_constructible_v<SecondType>
						)
					)
				) ||
				(
					State == state_t::uninitialized&& 
					std::is_nothrow_copy_constructible_v<FirstValueType>&& 
					std::is_nothrow_copy_constructible_v<SecondType>
				) ||
				(
					State == state_t::unknown&& 
					std::is_nothrow_copy_constructible_v<FirstValueType>&& 
					std::is_nothrow_copy_constructible_v<SecondType>
				)
			)
		{
			if constexpr (State == state_t::initialized)
			{
				if constexpr (std::is_copy_assignable_v<FirstValueType>)
				{
					first = other.first;
				}
				else
				{
					std::destroy_at(std::addressof(first));
					std::construct_at(std::addressof(first), other.first);
				}
				if constexpr (std::is_copy_assignable_v<SecondType>)
				{
					second = other.second;
				}
				else
				{
					std::destroy_at(std::addressof(second));
					std::construct_at(std::addressof(second), other.second);
				}
			}
			else if constexpr (State == state_t::uninitialized)
			{
				std::construct_at(std::addressof(first), other.first);
				std::construct_at(std::addressof(second), other.second);
			}
			else
			{
				std::destroy_at(std::addressof(first));
				std::construct_at(std::addressof(first), other.first);
				std::destroy_at(std::addressof(second));
				std::construct_at(std::addressof(second), other.second);
			}
			return *this;
		}

		template <dynamic_states_t DynamicStates>
		constexpr pair& copy_from(const state_t state, const state_t other_state, const pair& other)
			noexcept
			(
				std::is_nothrow_copy_constructible_v<FirstValueType>&&
				std::is_nothrow_copy_assignable_v<FirstValueType>&&
				std::is_nothrow_destructible_v<FirstValueType>&&
				std::is_nothrow_copy_constructible_v<SecondType>&&
				std::is_nothrow_copy_assignable_v<SecondType>&&
				std::is_nothrow_destructible_v<SecondType>
			)
		{
			if (state == state_t::initialized)
			{
				if constexpr (std::is_copy_assignable_v<FirstValueType>)
				{
					first = other.first;
				}
				else
				{
					std::destroy_at(std::addressof(first));
					std::construct_at(std::addressof(first), other.first);
				}
				if constexpr (std::is_copy_assignable_v<SecondType>)
				{
					second = other.second;
				}
				else
				{
					std::destroy_at(std::addressof(second));
					std::construct_at(std::addressof(second), other.second);
				}
			}
			else if (state == state_t::uninitialized)
			{
				std::construct_at(std::addressof(first), other.first);
				std::construct_at(std::addressof(second), other.second);
			}
			else
			{
				std::destroy_at(std::addressof(first));
				std::construct_at(std::addressof(first), other.first);
				std::destroy_at(std::addressof(second));
				std::construct_at(std::addressof(second), other.second);
			}
			return *this;
		}

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown, typename OtherFirstValueType, typename OtherSecondType>
		constexpr pair& copy_from(OtherFirstValueType &&other_first, OtherSecondType&& other_second)
			noexcept
			(
				(
					State == state_t::initialized&& 
					(
						std::is_nothrow_copy_assignable_v<FirstValueType> ||
						(
							!std::is_copy_assignable_v<FirstValueType>&& 
							std::is_nothrow_copy_constructible_v<FirstValueType>&& 
							std::is_nothrow_destructible_v<FirstValueType>
						)
					)
				) ||
				(
					State == state_t::uninitialized&& 
					std::is_nothrow_copy_constructible_v<FirstValueType>
				) ||
				(
					State == state_t::unknown&& 
					std::is_nothrow_copy_constructible_v<FirstValueType>&& 
					std::is_nothrow_destructible_v<FirstValueType>
				)
			)
		{
			if constexpr (State == state_t::initialized)
			{
				if constexpr (std::is_copy_assignable_v<FirstValueType>)
				{
					first = std::forward<OtherFirstValueType>(other_first);
				}
				else
				{
					std::destroy_at(std::addressof(first));
					std::construct_at(std::addressof(first), std::forward<OtherFirstValueType>(other_first));
				}
				if constexpr (std::is_copy_assignable_v<SecondType>)
				{
					second = std::forward<OtherSecondType>(other_second);
				}
				else
				{
					std::destroy_at(std::addressof(second));
					std::construct_at(std::addressof(second), std::forward<OtherSecondType>(other_second));
				}
			}
			else if constexpr (State == state_t::uninitialized)
			{
				std::construct_at(std::addressof(first), std::forward<OtherFirstValueType>(other_first));
				std::construct_at(std::addressof(second), std::forward<OtherSecondType>(other_second));
			}
			else
			{
				std::destroy_at(std::addressof(first));
				std::construct_at(std::addressof(first), std::forward<OtherFirstValueType>(other_first));
				std::destroy_at(std::addressof(second));
				std::construct_at(std::addressof(second), std::forward<OtherSecondType>(other_second));
			}
			return *this;
		}

		template <dynamic_states_t DynamicStates, typename OtherFirstValueType, typename OtherSecondType>
		constexpr pair& copy_from(const state_t state, const state_t other_state, OtherFirstValueType &&other_first, OtherSecondType&& other_second)
			noexcept
			(
				std::is_nothrow_copy_constructible_v<FirstValueType>&& 
				std::is_nothrow_copy_assignable_v<FirstValueType>&& 
				std::is_nothrow_destructible_v<FirstValueType>&& 
				std::is_nothrow_copy_constructible_v<SecondType>&& 
				std::is_nothrow_copy_assignable_v<SecondType>&& 
				std::is_nothrow_destructible_v<SecondType>
			)
		{
			if (state == state_t::initialized)
			{
				if constexpr (std::is_copy_assignable_v<FirstValueType>)
				{
					first = std::forward<OtherFirstValueType>(other_first);
				}
				else
				{
					std::destroy_at(std::addressof(first));
					std::construct_at(std::addressof(first), std::forward<OtherFirstValueType>(other_first));
				}
				if constexpr (std::is_copy_assignable_v<SecondType>)
				{
					second = std::forward<OtherSecondType>(other_second);
				}
				else
				{
					std::destroy_at(std::addressof(second));
					std::construct_at(std::addressof(second), std::forward<OtherSecondType>(other_second));
				}
			}
			else if (state == state_t::uninitialized)
			{
				std::construct_at(std::addressof(first), std::forward<OtherFirstValueType>(other_first));
				std::construct_at(std::addressof(second), std::forward<OtherSecondType>(other_second));
			}
			else
			{
				std::destroy_at(std::addressof(first));
				std::construct_at(std::addressof(first), std::forward<OtherFirstValueType>(other_first));
				std::destroy_at(std::addressof(second));
				std::construct_at(std::addressof(second), std::forward<OtherSecondType>(other_second));
			}
			return *this;
		}

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown, typename OtherPairType>
			requires
			(
				std::is_same_v<std::remove_cvref_t<OtherPairType>, pair>
			)
		constexpr pair& construct_from(OtherPairType&& other)
			noexcept
			(
				(
					(
						State == state_t::initialized ||
						State == state_t::unknown
					) && 
					std::is_nothrow_constructible_v<FirstValueType, OtherPairType&& >&& 
					std::is_nothrow_destructible_v<FirstValueType>
				) ||
				(
					State == state_t::uninitialized&& 
					std::is_nothrow_constructible_v<FirstValueType, OtherPairType&& >
				)
			)
		{
			if constexpr (State == state_t::initialized)
			{
				std::destroy_at(std::addressof(first));
				std::construct_at(std::addressof(first), std::forward<OtherPairType>(other));
			}
			else if constexpr (State == state_t::uninitialized)
			{
				std::construct_at(std::addressof(first), std::forward<OtherPairType>(other));
			}
			else
			{
				std::destroy_at(std::addressof(first));
				std::construct_at(std::addressof(first), std::forward<OtherPairType>(other));
			}
			return *this;
		}

		template <dynamic_states_t DynamicStates, typename OtherPairType>
			requires
			(
				std::is_same_v<std::remove_cvref_t<OtherPairType>, pair>
			)
		constexpr pair& construct_from(const state_t state, const state_t other_state, OtherPairType&& other)
			noexcept
			(
				std::is_nothrow_constructible_v<FirstValueType, OtherPairType&& >&&
				std::is_nothrow_destructible_v<FirstValueType>
			)
		{
			if (state == state_t::initialized)
			{
				std::destroy_at(std::addressof(first));
				std::construct_at(std::addressof(first), std::forward<OtherPairType>(other));
			}
			else if (state == state_t::uninitialized)
			{
				std::construct_at(std::addressof(first), std::forward<OtherPairType>(other));
			}
			else
			{
				std::destroy_at(std::addressof(first));
				std::construct_at(std::addressof(first), std::forward<OtherPairType>(other));
			}
			return *this;
		}

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown, typename OtherPairType>
			requires
			(
				std::is_same_v<std::remove_cvref_t<OtherPairType>, pair>
			)
		constexpr pair& copy_to(OtherPairType&& other)
			noexcept
			(
				(
					State == state_t::initialized&& 
					(
						std::is_nothrow_copy_assignable_v<FirstValueType> ||
						(
							!std::is_copy_assignable_v<FirstValueType>&& 
							std::is_nothrow_copy_constructible_v<FirstValueType>&& 
							std::is_nothrow_destructible_v<FirstValueType>
						)
					) && 
					(
						std::is_nothrow_copy_assignable_v<SecondType> ||
						(
							!std::is_copy_assignable_v<SecondType>&& 
							std::is_nothrow_copy_constructible_v<SecondType>&& 
							std::is_nothrow_destructible_v<SecondType>
						)
					)
				) ||
				(
					State == state_t::uninitialized&& 
					std::is_nothrow_copy_constructible_v<FirstValueType>&& 
					std::is_nothrow_copy_constructible_v<SecondType>
				) ||
				(
					State == state_t::unknown&& 
					std::is_nothrow_copy_constructible_v<FirstValueType>&& 
					std::is_nothrow_destructible_v<FirstValueType>&& 
					std::is_nothrow_copy_constructible_v<SecondType>&& 
					std::is_nothrow_destructible_v<SecondType>
				)
			)
		{
			if constexpr (State == state_t::initialized)
			{
				if constexpr (std::is_copy_constructible_v<FirstValueType>)
				{
					other.first = first;
				}
				else
				{
					std::destroy_at(std::addressof(other.first));
					std::construct_at(std::addressof(other.first), first);
				}
				if constexpr (std::is_copy_constructible_v<SecondType>)
				{
					other.second = second;
				}
				else
				{
					std::destroy_at(std::addressof(other.second));
					std::construct_at(std::addressof(other.second), second);
				}
			}
			else if constexpr (State == state_t::uninitialized)
			{
				std::construct_at(std::addressof(other.first), first);
				std::construct_at(std::addressof(other.second), second);
			}
			else
			{
				std::destroy_at(std::addressof(other.first));
				std::construct_at(std::addressof(other.first), first);
				std::destroy_at(std::addressof(other.second));
				std::construct_at(std::addressof(other.second), second);
			}
			return *this;
		}

		template <dynamic_states_t DynamicStates, typename OtherPairType>
			requires
			(
				std::is_same_v<std::remove_cvref_t<OtherPairType>, pair>
			)
		constexpr pair& copy_to(const state_t state, const state_t other_state, OtherPairType&& other)
			noexcept
			(
				std::is_nothrow_copy_constructible_v<FirstValueType>&&
				std::is_nothrow_copy_assignable_v<FirstValueType>&&
				std::is_nothrow_destructible_v<FirstValueType>&&
				std::is_nothrow_copy_constructible_v<SecondType>&&
				std::is_nothrow_copy_assignable_v<SecondType>&&
				std::is_nothrow_destructible_v<SecondType>
			)
		{
			if (state == state_t::initialized)
			{
				if constexpr (std::is_copy_constructible_v<FirstValueType>)
				{
					other.first = first;
				}
				else
				{
					std::destroy_at(std::addressof(other.first));
					std::construct_at(std::addressof(other.first), first);
				}
				if constexpr (std::is_copy_constructible_v<SecondType>)
				{
					other.second = second;
				}
				else
				{
					std::destroy_at(std::addressof(other.second));
					std::construct_at(std::addressof(other.second), second);
				}
			}
			else if (state == state_t::uninitialized)
			{
				std::construct_at(std::addressof(other.first), first);
				std::construct_at(std::addressof(other.second), second);
			}
			else
			{
				std::destroy_at(std::addressof(other.first));
				std::construct_at(std::addressof(other.first), first);
				std::destroy_at(std::addressof(other.second));
				std::construct_at(std::addressof(other.second), second);
			}
			return *this;
		}

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown, typename OtherFirstValueType>
		constexpr pair& copy_to(OtherFirstValueType &&other)
			noexcept
			(
				(
					State == state_t::initialized&& 
					(
						std::is_nothrow_assignable_v<OtherFirstValueType &&, FirstValueType> ||
						(
							!std::is_assignable_v<OtherFirstValueType &&, FirstValueType>&& 
							std::is_nothrow_constructible_v<OtherFirstValueType, FirstValueType>
						)
					)
				) ||
				(
					State == state_t::uninitialized&& 
					std::is_nothrow_constructible_v<OtherFirstValueType, FirstValueType>
				) ||
				(
					State == state_t::unknown&& 
					std::is_nothrow_constructible_v<OtherFirstValueType, FirstValueType>
				)
			)
		{
			if constexpr (State == state_t::initialized)
			{
				if constexpr (std::is_assignable_v<OtherFirstValueType &&, FirstValueType>)
				{
					other = first;
				}
				else
				{
					std::destroy_at(std::addressof(other));
					std::construct_at(std::addressof(other), first);
				}
			}
			else if constexpr (State == state_t::uninitialized)
			{
				std::construct_at(std::addressof(other), first);
			}
			else
			{
				std::destroy_at(std::addressof(other));
				std::construct_at(std::addressof(other), first);
			}
			return *this;
		}

		template <dynamic_states_t DynamicStates, typename OtherFirstValueType>
		constexpr pair& copy_to(const state_t state, const state_t other_state, OtherFirstValueType &&other)
			noexcept
			(
				std::is_nothrow_assignable_v<OtherFirstValueType &&, FirstValueType> ||
				(
					!std::is_assignable_v<OtherFirstValueType &&, FirstValueType>&& 
					std::is_nothrow_constructible_v<OtherFirstValueType, FirstValueType>
				)
			)
		{
			if (state == state_t::initialized)
			{
				if constexpr (std::is_assignable_v<OtherFirstValueType &&, FirstValueType>)
				{
					other = first;
				}
				else
				{
					std::destroy_at(std::addressof(other));
					std::construct_at(std::addressof(other), first);
				}
			}
			else if (state == state_t::uninitialized)
			{
				std::construct_at(std::addressof(other), first);
			}
			else
			{
				std::destroy_at(std::addressof(other));
				std::construct_at(std::addressof(other), first);
			}
			return *this;
		}

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown, typename OtherPairType>
			requires
			(
				std::is_same_v<std::remove_cvref_t<OtherPairType>, pair>
			)
		constexpr pair& move_from(OtherPairType&& other)
			noexcept
			(
				(
					State == state_t::initialized&& 
					(
						std::is_nothrow_move_assignable_v<FirstValueType> ||
						(
							!std::is_move_assignable_v<FirstValueType>&& 
							std::is_nothrow_move_constructible_v<FirstValueType>&& 
							std::is_nothrow_destructible_v<FirstValueType>
						)
					) && 
					(
						std::is_nothrow_move_assignable_v<SecondType> ||
						(
							!std::is_move_assignable_v<SecondType>&& 
							std::is_nothrow_move_constructible_v<SecondType>&& 
							std::is_nothrow_destructible_v<SecondType>
						)
					)
				) ||
				(
					State == state_t::uninitialized&& 
					std::is_nothrow_move_constructible_v<FirstValueType>&& 
					std::is_nothrow_move_constructible_v<SecondType>
				) ||
				(
					State == state_t::unknown&& 
					std::is_nothrow_move_constructible_v<FirstValueType>&& 
					std::is_nothrow_move_constructible_v<SecondType>
				)
			)
		{
			if constexpr (State == state_t::initialized)
			{
				if constexpr (std::is_move_assignable_v<FirstValueType>)
				{
					first = std::move(other.first);
				}
				else
				{
					std::destroy_at(std::addressof(first));
					std::construct_at(std::addressof(first), std::move(other.first));
				}
				if constexpr (std::is_move_assignable_v<SecondType>)
				{
					second = std::move(other.second);
				}
				else
				{
					std::destroy_at(std::addressof(second));
					std::construct_at(std::addressof(second), std::move(other.second));
				}
			}
			else if constexpr (State == state_t::uninitialized)
			{
				std::construct_at(std::addressof(first), std::move(other.first));
				std::construct_at(std::addressof(second), std::move(other.second));
			}
			else
			{
				std::destroy_at(std::addressof(first));
				std::construct_at(std::addressof(first), std::move(other.first));
				std::destroy_at(std::addressof(second));
				std::construct_at(std::addressof(second), std::move(other.second));
			}
			return *this;
		}

		template <dynamic_states_t DynamicStates, typename OtherPairType>
			requires
			(
				std::is_same_v<std::remove_cvref_t<OtherPairType>, pair>
			)
		constexpr pair& move_from(const state_t state, const state_t other_state, OtherPairType&& other)
			noexcept
			(
				std::is_nothrow_move_constructible_v<FirstValueType>&&
				std::is_nothrow_move_assignable_v<FirstValueType>&&
				std::is_nothrow_destructible_v<FirstValueType>&&
				std::is_nothrow_move_constructible_v<SecondType>&&
				std::is_nothrow_move_assignable_v<SecondType>&&
				std::is_nothrow_destructible_v<SecondType>
			)
		{
			if (state == state_t::initialized)
			{
				if constexpr (std::is_move_assignable_v<FirstValueType>)
				{
					first = std::move(other.first);
				}
				else
				{
					std::destroy_at(std::addressof(first));
					std::construct_at(std::addressof(first), std::move(other.first));
				}
				if constexpr (std::is_move_assignable_v<SecondType>)
				{
					second = std::move(other.second);
				}
				else
				{
					std::destroy_at(std::addressof(second));
					std::construct_at(std::addressof(second), std::move(other.second));
				}
			}
			else if (state == state_t::uninitialized)
			{
				std::construct_at(std::addressof(first), std::move(other.first));
				std::construct_at(std::addressof(second), std::move(other.second));
			}
			else
			{
				std::destroy_at(std::addressof(first));
				std::construct_at(std::addressof(first), std::move(other.first));
				std::destroy_at(std::addressof(second));
				std::construct_at(std::addressof(second), std::move(other.second));
			}
			return *this;
		}

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown, typename OtherFirstValueType, typename OtherSecondType>
		constexpr pair& move_from(OtherFirstValueType &&other_first, OtherSecondType&& other_second)
			noexcept
			(
				(
					State == state_t::initialized&& 
					(
						std::is_nothrow_assignable_v<FirstValueType, OtherFirstValueType &&> ||
						(
							!std::is_assignable_v<FirstValueType, OtherFirstValueType &&>&& 
							std::is_nothrow_constructible_v<FirstValueType, OtherFirstValueType &&>&& 
							std::is_nothrow_destructible_v<FirstValueType>
						)
					) && 
					(
						std::is_nothrow_assignable_v<SecondType, OtherSecondType&& > ||
						(
							!std::is_assignable_v<SecondType, OtherSecondType&& >&& 
							std::is_nothrow_constructible_v<SecondType, OtherSecondType&& >&& 
							std::is_nothrow_destructible_v<SecondType>
						)
					)
				) ||
				(
					State == state_t::uninitialized&& 
					std::is_nothrow_constructible_v<FirstValueType, OtherFirstValueType &&>&& 
					std::is_nothrow_constructible_v<SecondType, OtherSecondType&& >
				) ||
				(
					State == state_t::unknown&& 
					std::is_nothrow_constructible_v<FirstValueType, OtherFirstValueType &&>&& 
					std::is_nothrow_constructible_v<SecondType, OtherSecondType&& >
				)
			)
		{
			if constexpr (State == state_t::initialized)
			{
				if constexpr (std::is_move_assignable_v<FirstValueType>)
				{
					first = std::forward<OtherFirstValueType>(other_first);
				}
				else
				{
					std::destroy_at(std::addressof(first));
					std::construct_at(std::addressof(first), std::forward<OtherFirstValueType>(other_first));
				}
				if constexpr (std::is_move_assignable_v<SecondType>)
				{
					second = std::forward<OtherFirstValueType>(other_second);
				}
				else
				{
					std::destroy_at(std::addressof(second));
					std::construct_at(std::addressof(second), std::forward<OtherSecondType>(other_second));
				}
			}
			else if constexpr (State == state_t::uninitialized)
			{
				std::construct_at(std::addressof(first), std::forward<OtherFirstValueType>(other_first));
				std::construct_at(std::addressof(second), std::forward<OtherSecondType>(other_second));
			}
			else
			{
				std::destroy_at(std::addressof(first));
				std::construct_at(std::addressof(first), std::forward<OtherFirstValueType>(other_first));
				std::destroy_at(std::addressof(second));
				std::construct_at(std::addressof(second), std::forward<OtherSecondType>(other_second));
			}
			return *this;
		}

		template <dynamic_states_t DynamicStates, typename OtherFirstValueType, typename OtherSecondType>
		constexpr pair& move_from(const state_t state, const state_t other_state, OtherFirstValueType &&other_first, OtherSecondType&& other_second)
			noexcept
			(
				std::is_nothrow_move_constructible_v<FirstValueType>&&
				std::is_nothrow_move_assignable_v<FirstValueType>&&
				std::is_nothrow_destructible_v<FirstValueType>&&
				std::is_nothrow_move_constructible_v<SecondType>&&
				std::is_nothrow_move_assignable_v<SecondType>&&
				std::is_nothrow_destructible_v<SecondType>
			)
		{
			if (state == state_t::initialized)
			{
				if constexpr (std::is_move_assignable_v<FirstValueType>)
				{
					first = std::forward<OtherFirstValueType>(other_first);
				}
				else
				{
					std::destroy_at(std::addressof(first));
					std::construct_at(std::addressof(first), std::forward<OtherFirstValueType>(other_first));
				}
				if constexpr (std::is_move_assignable_v<SecondType>)
				{
					second = std::forward<OtherSecondType>(other_second);
				}
				else
				{
					std::destroy_at(std::addressof(second));
					std::construct_at(std::addressof(second), std::forward<OtherSecondType>(other_second));
				}
			}
			else if (state == state_t::uninitialized)
			{
				std::construct_at(std::addressof(first), std::forward<OtherFirstValueType>(other_first));
				std::construct_at(std::addressof(second), std::forward<OtherSecondType>(other_second));
			}
			else
			{
				std::destroy_at(std::addressof(first));
				std::construct_at(std::addressof(first), std::forward<OtherFirstValueType>(other_first));
				std::destroy_at(std::addressof(second));
				std::construct_at(std::addressof(second), std::forward<OtherSecondType>(other_second));
			}
			return *this;
		}

		template <size_t Index>
		constexpr auto get() const
			noexcept
#ifndef NDEBUG
			(
				Index < 2
			)
#endif
		{
#ifndef NDEBUG
			if constexpr (!Index)
			{
				return first;
			}
			if constexpr (Index == 1)
			{
				return second;
			}
			throw bad_tuple_access{ __LINE__, "Pair access out of bounds.", __FILE__, __func__ };
#else
			if constexpr (!Index)
			{
				return first;
			}
			return second;
#endif
		}

		constexpr auto get(const size_t index) const
			noexcept
#ifndef NDEBUG
			(
				false
			)
#endif
		{
#ifndef NDEBUG
			if (!index)
			{
				return first;
			}
			if (index == 1)
			{
				return second;
			}
			throw bad_tuple_access{ __LINE__, "Pair access out of bounds.", __FILE__, __func__ };
#else
			if (!index)
			{
				return first;
			}
			return second;
#endif
		}

		static constexpr size_t size()
			noexcept
		{
			return 2;
		}

		constexpr explicit operator bool() const
			noexcept
		{
			return true;
		}

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown>
		constexpr pair& swap(pair& other)
			noexcept
			(
				(
					State == state_t::initialized&& 
					(
						(
							OtherState == state_t::initialized&& 
							std::is_nothrow_swappable_v<FirstValueType>&& 
							std::is_nothrow_swappable_v<SecondType>
						) ||
						(
							OtherState == state_t::uninitialized&& 
							std::is_nothrow_move_constructible_v<FirstValueType>&& 
							std::is_nothrow_move_constructible_v<SecondType>
						)
					)
				) ||
				(
					State == state_t::uninitialized&& 
					(
						(
							OtherState == state_t::initialized&& 
							std::is_nothrow_move_constructible_v<FirstValueType>&& 
							std::is_nothrow_move_constructible_v<SecondType>
						) ||
						OtherState == state_t::uninitialized
					)
				)
			)
		{
			if constexpr (State == state_t::initialized)
			{
				if constexpr (OtherState == state_t::initialized)
				{
					std::swap(first, other.first);
					std::swap(second, other.second);
				}
				else
				{
					std::construct_at(std::addressof(other.first), std::move(first));
					std::construct_at(std::addressof(other.second), std::move(second));
				}
			}
			else
			{
				if constexpr (OtherState == state_t::initialized)
				{
					std::construct_at(std::addressof(first), std::move(other.first));
					std::construct_at(std::addressof(second), std::move(other.second));
				}
			}
			return *this;
		}

		template <dynamic_states_t DynamicStates>
		constexpr pair& swap(const state_t state, const state_t other_state, pair& other)
			noexcept
			(
				std::is_nothrow_swappable_v<FirstValueType>&&
				std::is_nothrow_swappable_v<SecondType>
			)
		{
			if (state == state_t::initialized)
			{
				if (other_state == state_t::initialized)
				{
					std::swap(first, other.first);
					std::swap(second, other.second);
				}
				else
				{
					std::construct_at(std::addressof(other.first), std::move(first));
					std::construct_at(std::addressof(other.second), std::move(second));
				}
			}
			else
			{
				if (other_state == state_t::initialized)
				{
					std::construct_at(std::addressof(first), std::move(other.first));
					std::construct_at(std::addressof(second), std::move(other.second));
				}
			}
			return *this;
		}

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown>
		constexpr pair& swap(FirstValueType& other_first, SecondType& other_second)
			noexcept
			(
				(
					State == state_t::initialized&& 
					(
						(
							OtherState == state_t::initialized&& 
							std::is_nothrow_swappable_v<FirstValueType>&& 
							std::is_nothrow_swappable_v<SecondType>
						) ||
						(
							OtherState == state_t::uninitialized&& 
							std::is_nothrow_move_constructible_v<FirstValueType>&& 
							std::is_nothrow_move_constructible_v<SecondType>
						)
					)
				) ||
				(
					State == state_t::uninitialized&& 
					(
						(
							OtherState == state_t::initialized&& 
							std::is_nothrow_move_constructible_v<FirstValueType>&& 
							std::is_nothrow_move_constructible_v<SecondType>
						) ||
						OtherState == state_t::uninitialized
					)
				)
			)
		{
			if constexpr (State == state_t::initialized)
			{
				if constexpr (OtherState == state_t::initialized)
				{
					std::swap(first, other_first);
					std::swap(second, other_second);
				}
				else
				{
					std::construct_at(std::addressof(other_first), std::move(first));
					std::construct_at(std::addressof(other_second), std::move(second));
				}
			}
			else
			{
				if constexpr (OtherState == state_t::initialized)
				{
					std::construct_at(std::addressof(first), std::move(other_first));
					std::construct_at(std::addressof(second), std::move(other_second));
				}
			}
			return *this;
		}

		template <dynamic_states_t DynamicStates>
		constexpr pair& swap(const state_t state, const state_t other_state, FirstValueType& other_first, SecondType& other_second)
			noexcept
			(
				std::is_nothrow_swappable_v<FirstValueType>&& 
				std::is_nothrow_move_constructible_v<FirstValueType>&& 
				std::is_nothrow_swappable_v<SecondType>&& 
				std::is_nothrow_move_constructible_v<SecondType>
			)
		{
			if (state == state_t::initialized)
			{
				if (other_state == state_t::initialized)
				{
					std::swap(first, other_first);
					std::swap(second, other_second);
				}
				else
				{
					std::construct_at(std::addressof(other_first), std::move(first));
					std::construct_at(std::addressof(other_second), std::move(second));
				}
			}
			else
			{
				if (other_state == state_t::initialized)
				{
					std::construct_at(std::addressof(first), std::move(other_first));
					std::construct_at(std::addressof(second), std::move(other_second));
				}
			}
			return *this;
		}
	};*/



} // namespace woj
