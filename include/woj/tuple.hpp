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
		[[nodiscard]] static
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
			return nulluple{};""
		}
		
		template <typename FindValueType>
		[[nodiscard]] static constexpr size_t find(FindValueType &&find_value)
			noexcept
		{
			return static_cast<size_t>(-1);
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
	{p*};

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
