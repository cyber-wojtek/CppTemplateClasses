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
#define __WOJ_RETURN_MOVE_THIS_FUNCTION_METHOD_BODY { return /*std::move*/(*this); }
#define __WOJ_RETURN_MOVE_THIS_FUNCTION_METHOD_NOEXCEPT_BODY noexcept __WOJ_RETURN_MOVE_THIS_FUNCTION_METHOD_BODY
/*
#define __WOJ_RETURN_FORWARD_THIS_FUNCTION_METHOD_BODY { return std::forward<nulluple>(*this); }
#define __WOJ_RETURN_MOVE_THIS_FUNCTION_METHOD_NOEXCEPT_BODY noexcept __WOJ_RETURN_FORWARD_THIS_FUNCTION_METHOD_BODY
#define __WOJ_RETURN_FORWARD_CONST_THIS_FUNCTION_METHOD_BODY { return std::forward<const nulluple>(*this); }
#define __WOJ_RETURN_MOVE_THIS_FUNCTION_METHOD_NOEXCEPT_BODY noexcept __WOJ_RETURN_FORWARD_CONST_THIS_FUNCTION_METHOD_BODY
*/

namespace woj
{
	class bad_tuple_access final : public exception
	{
	public:
		constexpr bad_tuple_access()
			noexcept
			: exception{ static_cast<uint64_t>(-1), "Nulluple access out of bounds.", nullptr, nullptr } {
		}

		constexpr bad_tuple_access(const size_t line, const char* message, const char* const file, const char* const function)
			noexcept
			: exception{ line, message, file, function } {
		}
	};

	/**
	 * Class representing a null tuple (0-tuple)
	 */
	class nulluple;

	/**
	 * Type trait to check if a type is a nulluple
	 * @tparam Type Type to check
	 */
	template <typename Type>
	class is_nulluple : public std::false_type {};

	/**
	 * Type trait to check if a type is a nulluple
	 */
	template <>
	class is_nulluple<nulluple> : public std::true_type {};

	/**
	 * Type trait to check if a type is a nulluple
	 * @tparam Type Type to check.
	 */
	template <typename Type>
	constexpr bool is_nulluple_v = is_nulluple<Type>::value;

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
		constexpr nulluple(const nulluple& other)
			noexcept = default;

		/**
		 * Constructs a nulluple from another nulluple
		 * @param other_state State of the other nulluple
		 * @param other	Other nulluple
		 */
		constexpr nulluple(const state_t other_state, const nulluple& other)
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

		constexpr nulluple& operator =(const nulluple other)
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
		constexpr const nulluple& construct_from(const noinit_t noinit) const&
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Constructs current nulluple from a noinit tag (does nothing)
		 * @tparam State State of the current nulluple
		 * @tparam OtherState UNUSED. State of the other nulluple
		 * @param noinit No initialization tag
		 * @return lvalue reference to the current nulluple
		 */
		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown>
		constexpr nulluple& construct_from(const noinit_t noinit) &
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Constructs current nulluple from a noinit tag (does nothing)
		 * @tparam State State of the current nulluple
		 * @tparam OtherState UNUSED. State of the other nulluple
		 * @param noinit No initialization tag
		 * @return const rvalue reference to the current nulluple
		 */
		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown>
		constexpr const nulluple &&construct_from(const noinit_t noinit) const&&
		__WOJ_RETURN_MOVE_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Constructs current nulluple from a noinit tag (does nothing)
		 * @tparam State State of the current nulluple
		 * @tparam OtherState UNUSED. State of the other nulluple
		 * @param noinit No initialization tag
		 * @return rvalue reference to the current nulluple
		 */
		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown>
		constexpr nulluple &&construct_from(const noinit_t noinit) &&
		__WOJ_RETURN_MOVE_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Constructs current nulluple from another nulluple (does nothing)
		 * @tparam DynamicStates Dynamic states tag
		 * @param state State of the current nulluple
		 * @param other_state UNUSED. State of the other nulluple
		 * @param noinit No initialization tag
		 * @return const lvalue reference to the current nulluple
		 */
		template <dynamic_states_t DynamicStates = dynamic_states>
		constexpr const nulluple& construct_from(const state_t state, const state_t other_state, const noinit_t noinit) const&
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Constructs current nulluple from another nulluple (does nothing)
		 * @tparam DynamicStates Dynamic states tag
		 * @param state State of the current nulluple
		 * @param other_state UNUSED. State of the other nulluple
		 * @param noinit No initialization tag
		 * @return lvalue reference to the current nulluple
		 */
		template <dynamic_states_t DynamicStates = dynamic_states>
		constexpr nulluple& construct_from(const state_t state, const state_t other_state, const noinit_t noinit) &
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Constructs current nulluple from another nulluple (does nothing)
		 * @tparam DynamicStates Dynamic states tag
		 * @param state State of the current nulluple
		 * @param other_state UNUSED. State of the other nulluple
		 * @param noinit No initialization tag
		 * @return const rvalue reference to the current nulluple
		 */
		template <dynamic_states_t DynamicStates = dynamic_states>
		constexpr const nulluple &&construct_from(const state_t state, const state_t other_state, const noinit_t noinit) const&&
		__WOJ_RETURN_MOVE_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Constructs current nulluple from another nulluple (does nothing)
		 * @tparam DynamicStates Dynamic states tag
		 * @param state State of the current nulluple
		 * @param other_state UNUSED. State of the other nulluple
		 * @param noinit No initialization tag
		 * @return rvalue reference to the current nulluple
		 */
		template <dynamic_states_t DynamicStates = dynamic_states>
		constexpr nulluple &&construct_from(const state_t state, const state_t other_state, const noinit_t noinit) &&
		__WOJ_RETURN_MOVE_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Constructs current nulluple from another nulluple (does nothing)
		 * @tparam State State of the current nulluple
		 * @tparam OtherState State of the other nulluple
		 * @param other Other nulluple
		 * @return const lvalue reference to the current nulluple
		 */
		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown>
		constexpr const nulluple& construct_from(const nulluple other) const&
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Constructs current nulluple from another nulluple (does nothing)
		 * @tparam State State of the current nulluple
		 * @tparam OtherState State of the other nulluple
		 * @param other Other nulluple
		 * @return lvalue reference to the current nulluple
		 */
		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown>
		constexpr nulluple& construct_from(const nulluple other) &
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Constructs current nulluple from another nulluple (does nothing)
		 * @tparam State State of the current nulluple
		 * @tparam OtherState State of the other nulluple
		 * @param other Other nulluple
		 * @return const rvalue reference to the current nulluple
		 */
		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown>
		constexpr const nulluple &&construct_from(const nulluple other) const&&
		__WOJ_RETURN_MOVE_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Constructs current nulluple from another nulluple (does nothing)
		 * @tparam State State of the current nulluple
		 * @tparam OtherState State of the other nulluple
		 * @param other Other nulluple
		 * @return rvalue reference to the current nulluple
		 */
		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown>
		constexpr nulluple &&construct_from(const nulluple other) &&
		__WOJ_RETURN_MOVE_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Constructs current nulluple from another nulluple (does nothing)
		 * @tparam DynamicStates Dynamic states tag
		 * @param state State of the current nulluple
		 * @param other_state State of the other nulluple
		 * @param other Other nulluple
		 * @return const lvalue reference to the current nulluple
		 */
		template <dynamic_states_t DynamicStates = dynamic_states>
		constexpr const nulluple& construct_from(const state_t state, const state_t other_state, const nulluple other) const&
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Constructs current nulluple from another nulluple (does nothing)
		 * @tparam DynamicStates Dynamic states tag
		 * @param state State of the current nulluple
		 * @param other_state State of the other nulluple
		 * @param other Other nulluple
		 * @return lvalue reference to the current nulluple
		 */
		template <dynamic_states_t DynamicStates = dynamic_states>
		constexpr nulluple& construct_from(const state_t state, const state_t other_state, const nulluple other)&
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Constructs current nulluple from another nulluple (does nothing)
		 * @tparam DynamicStates Dynamic states tag
		 * @param state State of the current nulluple
		 * @param other_state State of the other nulluple
		 * @param other Other nulluple
		 * @return const rvalue reference to the current nulluple
		 */
		template <dynamic_states_t DynamicStates = dynamic_states>
		constexpr const nulluple &&construct_from(const state_t state, const state_t other_state, const nulluple other) const&&
		__WOJ_RETURN_MOVE_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Constructs current nulluple from another nulluple (does nothing)
		 * @tparam DynamicStates Dynamic states tag
		 * @param state State of the current nulluple
		 * @param other_state State of the other nulluple
		 * @param other Other nulluple
		 * @return rvalue reference to the current nulluple
		 */
		template <dynamic_states_t DynamicStates = dynamic_states>
		constexpr nulluple &&construct_from(const state_t state, const state_t other_state, const nulluple other) &&
		__WOJ_RETURN_MOVE_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

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
		template <dynamic_states_t DynamicStates = dynamic_states>
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
		template <dynamic_states_t DynamicStates = dynamic_states>
		[[nodiscard]] static
#if WOJ_HAS_CXX20
			consteval
#else
			constexpr
#endif
			nulluple constructed_from(const state_t other_state, const nulluple other)
			noexcept
		{
			return nulluple{};
		}

		/**
		 * Constructs to many other nulluples from current nulluple (does nothing)
		 * @tparam State State of the current nulluple
		 * @tparam OthersStates States of the other nulluples
		 * @tparam OthersNullupleTypes Types of the other nulluples
		 * @param others Other nulluples
		 * @return const lvalue reference to the current nulluple
		 */
		template <state_t State = state_t::unknown, state_t ...OthersStates, typename ...OthersNullupleTypes>
			requires
			(
				(
					true &&
					... &&
					std::is_same_v<OthersNullupleTypes, nulluple>
				)
			)
		constexpr const nulluple& construct_to(const OthersNullupleTypes ...others) const&
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Constructs to many other nulluples from current nulluple (does nothing)
		 * @tparam State State of the current nulluple
		 * @tparam OthersStates States of the other nulluples
		 * @tparam OthersNullupleTypes Types of the other nulluples
		 * @param others Other nulluples
		 * @return lvalue reference to the current nulluple
		 */
		template <state_t State = state_t::unknown, state_t ...OthersStates, typename ...OthersNullupleTypes>
			requires
			(
				(
					true &&
					... &&
					std::is_same_v<OthersNullupleTypes, nulluple>
				)
			)
		constexpr nulluple& construct_to(const OthersNullupleTypes ...others)&
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY


		/**
		 * Constructs to many other nulluples from current nulluple (does nothing)
		 * @tparam State State of the current nulluple
		 * @tparam OthersStates States of the other nulluples
		 * @tparam OthersNullupleTypes Types of the other nulluples
		 * @param others Other nulluples
		 * @return const rvalue reference to the current nulluple
		 */
		template <state_t State = state_t::unknown, state_t ...OthersStates, typename ...OthersNullupleTypes>
			requires
			(
				(
					true &&
					... &&
					std::is_same_v<OthersNullupleTypes, nulluple>
				)
			)
		constexpr const nulluple &&construct_to(const OthersNullupleTypes ...others) const&&
		__WOJ_RETURN_MOVE_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Constructs to many other nulluples from current nulluple (does nothing)
		 * @tparam State State of the current nulluple
		 * @tparam OthersStates States of the other nulluples
		 * @tparam OthersNullupleTypes Types of the other nulluples
		 * @param others Other nulluples
		 * @return rvalue reference to the current nulluple
		 */
		template <state_t State = state_t::unknown, state_t ...OthersStates, typename ...OthersNullupleTypes>
			requires
			(
				(
					true &&
					... &&
					std::is_same_v<OthersNullupleTypes, nulluple>
				)
			)
		constexpr nulluple&& construct_to(const OthersNullupleTypes ...others) &&
		__WOJ_RETURN_MOVE_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Constructs to many other nulluples from current nulluple (does nothing)
		 * @tparam DynamicStates Dynamic states tag
		 * @tparam OthersNullupleTypes Types of the other nulluples
		 * @param state State of the current nulluple
		 * @param others_states States of the other nulluples
		 * @param others Other nulluples
		 * @return const lvalue reference to the current nulluple
		 */
		template <dynamic_states_t DynamicStates = dynamic_states, size_t SizeOthersStates, typename ...OthersNullupleTypes>
			requires
			(
				(
					true &&
					... &&
					std::is_same_v<OthersNullupleTypes, nulluple>
				)
			)
		constexpr const nulluple& construct_to(const state_t state, const state_t(&others_states)[SizeOthersStates], const OthersNullupleTypes ...others) const&
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Constructs to many other nulluples from current nulluple (does nothing)
		 * @tparam DynamicStates Dynamic states tag
		 * @tparam OthersNullupleTypes Types of the other nulluples
		 * @param state State of the current nulluple
		 * @param others_states States of the other nulluples
		 * @param others Other nulluples
		 * @return lvalue reference to the current nulluple
		 */
		template <dynamic_states_t DynamicStates = dynamic_states, size_t SizeOthersStates, typename ...OthersNullupleTypes>
			requires
			(
				(
					true &&
					... &&
					std::is_same_v<OthersNullupleTypes, nulluple>
				)
			)
		constexpr nulluple& construct_to(const state_t state, const state_t(&others_states)[SizeOthersStates], const OthersNullupleTypes ...others)&
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Constructs to many other nulluples from current nulluple (does nothing)
		 * @tparam DynamicStates Dynamic states tag
		 * @tparam OthersNullupleTypes Types of the other nulluples
		 * @param state State of the current nulluple
		 * @param others_states States of the other nulluples
		 * @param others Other nulluples
		 * @return const rvalue reference to the current nulluple
		 */
		template <dynamic_states_t DynamicStates = dynamic_states, size_t SizeOthersStates, typename ...OthersNullupleTypes>
			requires
			(
				(
					true &&
					... &&
					std::is_same_v<OthersNullupleTypes, nulluple>
				)
			)
		constexpr const nulluple &&construct_to(const state_t state, const state_t(&others_states)[SizeOthersStates], const OthersNullupleTypes ...others) const&&
		__WOJ_RETURN_MOVE_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Constructs to many other nulluples from current nulluple (does nothing)
		 * @tparam DynamicStates Dynamic states tag
		 * @tparam OthersNullupleTypes Types of the other nulluples
		 * @param state State of the current nulluple
		 * @param others_states States of the other nulluples
		 * @param others Other nulluples
		 * @return rvalue reference to the current nulluple
		 */
		template <dynamic_states_t DynamicStates = dynamic_states, size_t SizeOthersStates, typename ...OthersNullupleTypes>
			requires
			(
				(
					true &&
					... &&
					std::is_same_v<OthersNullupleTypes, nulluple>
				)
			)
		constexpr nulluple &&construct_to(const state_t state, const state_t(&others_states)[SizeOthersStates], const OthersNullupleTypes ...others) &&
		__WOJ_RETURN_MOVE_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Constructs to many other nulluples from current nulluple (does nothing)
		 * @tparam DynamicStates Dynamic states tag
		 * @tparam OthersNullupleTypes Types of the other nulluples
		 * @param state State of the current nulluple
		 * @param others_states States of the other nulluples
		 * @param others Other nulluples
		 * @return const lvalue reference to the current nulluple
		 */
		template <dynamic_states_t DynamicStates = dynamic_states, size_t SizeOthersStates, typename ...OthersNullupleTypes>
			requires
			(
				(
					true &&
					... &&
					std::is_same_v<OthersNullupleTypes, nulluple>
				)
			)
		constexpr const nulluple& construct_to(const state_t state, const stack::vector<state_t, SizeOthersStates>& others_states, const OthersNullupleTypes ...others) const&
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Constructs to many other nulluples from current nulluple (does nothing)
		 * @tparam DynamicStates Dynamic states tag
		 * @tparam OthersNullupleTypes Types of the other nulluples
		 * @param state State of the current nulluple
		 * @param others_states States of the other nulluples
		 * @param others Other nulluples
		 * @return lvalue reference to the current nulluple
		 */
		template <dynamic_states_t DynamicStates = dynamic_states, size_t SizeOthersStates, typename ...OthersNullupleTypes>
			requires
			(
				(
					true &&
					... &&
					std::is_same_v<OthersNullupleTypes, nulluple>
				)
			)
		constexpr nulluple& construct_to(const state_t state, const stack::vector<state_t, SizeOthersStates>& others_states, const OthersNullupleTypes ...others)&
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Constructs to many other nulluples from current nulluple (does nothing)
		 * @tparam DynamicStates Dynamic states tag
		 * @tparam OthersNullupleTypes Types of the other nulluples
		 * @param state State of the current nulluple
		 * @param others_states States of the other nulluples
		 * @param others Other nulluples
		 * @return const rvalue reference to the current nulluple
		 */
		template <dynamic_states_t DynamicStates = dynamic_states, size_t SizeOthersStates, typename ...OthersNullupleTypes>
			requires
			(
				(
					true &&
					... &&
					std::is_same_v<OthersNullupleTypes, nulluple>
				)
			)
		constexpr const nulluple &&construct_to(const state_t state, const stack::vector<state_t, SizeOthersStates>& others_states, const OthersNullupleTypes ...others) const&&
		__WOJ_RETURN_MOVE_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Constructs to many other nulluples from current nulluple (does nothing)
		 * @tparam DynamicStates Dynamic states tag
		 * @tparam OthersNullupleTypes Types of the other nulluples
		 * @param state State of the current nulluple
		 * @param others_states States of the other nulluples
		 * @param others Other nulluples
		 * @return rvalue reference to the current nulluple
		 */
		template <dynamic_states_t DynamicStates = dynamic_states, size_t SizeOthersStates, typename ...OthersNullupleTypes>
			requires
			(
				(
					true &&
					... &&
					std::is_same_v<OthersNullupleTypes, nulluple>
				)
			)
		constexpr nulluple &&construct_to(const state_t state, const stack::vector<state_t, SizeOthersStates>& others_states, const OthersNullupleTypes ...others) &&
		__WOJ_RETURN_MOVE_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		* Constructs to many other nulluples from current nulluple (does nothing)
		* @tparam DynamicStates Dynamic states tag
		* @tparam OthersNullupleTypes Types of the other nulluples
		* @param state State of the current nulluple
		* @param others_states States of the other nulluples
		* @param others Other nulluples
		* @return const lvalue reference to the current nulluple
		*/
		template <dynamic_states_t DynamicStates = dynamic_states, typename ...OthersNullupleTypes>
			requires
			(
				(
					true &&
					... &&
					std::is_same_v<OthersNullupleTypes, nulluple>
				)
			)
		constexpr const nulluple& construct_to(const state_t state, const empty_t others_states, const OthersNullupleTypes ...others) const&
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		* Constructs to many other nulluples from current nulluple (does nothing)
		* @tparam DynamicStates Dynamic states tag
		* @tparam OthersNullupleTypes Types of the other nulluples
		* @param state State of the current nulluple
		* @param others_states States of the other nulluples
		* @param others Other nulluples
		* @return lvalue reference to the current nulluple
		*/
		template <dynamic_states_t DynamicStates = dynamic_states, typename ...OthersNullupleTypes>
			requires
			(
				(
					true &&
					... &&
					std::is_same_v<OthersNullupleTypes, nulluple>
				)
			)
		constexpr nulluple& construct_to(const state_t state, const empty_t others_states, const OthersNullupleTypes ...others) &
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		* Constructs to many other nulluples from current nulluple (does nothing)
		* @tparam DynamicStates Dynamic states tag
		* @tparam OthersNullupleTypes Types of the other nulluples
		* @param state State of the current nulluple
		* @param others_states States of the other nulluples
		* @param others Other nulluples
		* @return const lvalue reference to the current nulluple
		*/
		template <dynamic_states_t DynamicStates = dynamic_states, typename ...OthersNullupleTypes>
			requires
			(
				(
					true &&
					... &&
				std::is_same_v<OthersNullupleTypes, nulluple>
				)
			)
		constexpr const nulluple &&construct_to(const state_t state, const empty_t others_states, const OthersNullupleTypes ...others) const&&
		__WOJ_RETURN_MOVE_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		* Constructs to many other nulluples from current nulluple (does nothing)
		* @tparam DynamicStates Dynamic states tag
		* @tparam OthersNullupleTypes Types of the other nulluples
		* @param state State of the current nulluple
		* @param others_states States of the other nulluples
		* @param others Other nulluples
		* @return const lvalue reference to the current nulluple
		*/
		template <dynamic_states_t DynamicStates = dynamic_states, typename ...OthersNullupleTypes>
			requires
			(
				(
					true &&
					... &&
					std::is_same_v<OthersNullupleTypes, nulluple>
				)
			)
		constexpr nulluple &&construct_to(const state_t state, const empty_t others_states, const OthersNullupleTypes ...others) &&
		__WOJ_RETURN_MOVE_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Assigns current nulluple from another nulluple (does nothing)
		 * @tparam State State of the current nulluple
		 * @tparam OtherState State of the other nulluple
		 * @param other Other nulluple
		 * @return const lvalue reference to the current nulluple
		 */
		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown>
		constexpr const nulluple& assign_from(const nulluple other) const&
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Assigns current nulluple from another nulluple (does nothing)
		 * @tparam State State of the current nulluple
		 * @tparam OtherState State of the other nulluple
		 * @param other Other nulluple
		 * @return lvalue reference to the current nulluple
		 */
		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown>
		constexpr nulluple& assign_from(const nulluple other)&
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Assigns current nulluple from another nulluple (does nothing)
		 * @tparam State State of the current nulluple
		 * @tparam OtherState State of the other nulluple
		 * @param other Other nulluple
		 * @return const rvalue reference to the current nulluple
		 */
		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown>
		constexpr const nulluple &&assign_from(const nulluple other) const&&
		__WOJ_RETURN_MOVE_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Assigns current nulluple from another nulluple (does nothing)
		 * @tparam State State of the current nulluple
		 * @tparam OtherState State of the other nulluple
		 * @param other Other nulluple
		 * @return rvalue reference to the current nulluple
		 */
		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown>
		constexpr nulluple &&assign_from(const nulluple other) &&
		__WOJ_RETURN_MOVE_THIS_FUNCTION_METHOD_NOEXCEPT_BODY


		/**
		 * Assigns current nulluple from another nulluple (does nothing)
		 * @tparam DynamicStates Dynamic states tag
		 * @param state State of the current nulluple
		 * @param other_state State of the other nulluple
		 * @param other Other nulluple
		 * @return const lvalue reference to the current nulluple
		 */
		template <dynamic_states_t DynamicStates = dynamic_states>
		constexpr const nulluple& assign_from(const state_t state, const state_t other_state, const nulluple other) const&
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Assigns current nulluple from another nulluple (does nothing)
		 * @tparam DynamicStates Dynamic states tag
		 * @param state State of the current nulluple
		 * @param other_state State of the other nulluple
		 * @param other Other nulluple
		 * @return lvalue reference to the current nulluple
		 */
		template <dynamic_states_t DynamicStates = dynamic_states>
		constexpr nulluple& assign_from(const state_t state, const state_t other_state, const nulluple other)&
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Assigns current nulluple from another nulluple (does nothing)
		 * @tparam DynamicStates Dynamic states tag
		 * @param state State of the current nulluple
		 * @param other_state State of the other nulluple
		 * @param other Other nulluple
		 * @return const rvalue reference to the current nulluple
		 */
		template <dynamic_states_t DynamicStates = dynamic_states>
		constexpr const nulluple &&assign_from(const state_t state, const state_t other_state, const nulluple other) const&&
		__WOJ_RETURN_MOVE_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Assigns current nulluple from another nulluple (does nothing)
		 * @tparam DynamicStates Dynamic states tag
		 * @param state State of the current nulluple
		 * @param other_state State of the other nulluple
		 * @param other Other nulluple
		 * @return rvalue reference to the current nulluple
		 */
		template <dynamic_states_t DynamicStates = dynamic_states>
		constexpr nulluple &&assign_from(const state_t state, const state_t other_state, const nulluple other) &&
		__WOJ_RETURN_MOVE_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Assigns from current nulluple to many other nulluples (does nothing)
		 * @tparam State State of the current nulluple
		 * @tparam OthersStates States of the other nulluples
		 * @tparam OthersNullupleTypes Types of the other nulluples
		 * @param others Other nulluples
		 * @return const lvalue reference to the current nulluple
		 */
		template <state_t State = state_t::unknown, state_t ...OthersStates, typename ...OthersNullupleTypes>
			requires
			(
				(
					true &&
					... &&
					std::is_same_v<OthersNullupleTypes, nulluple>
				)
			)
		constexpr const nulluple& assign_to(const OthersNullupleTypes ...others) const&
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Assigns from current nulluple to many other nulluples (does nothing)
		 * @tparam State State of the current nulluple
		 * @tparam OthersStates States of the other nulluples
		 * @tparam OthersNullupleTypes Types of the other nulluples
		 * @param others Other nulluples
		 * @return lvalue reference to the current nulluple
		 */
		template <state_t State = state_t::unknown, state_t ...OthersStates, typename ...OthersNullupleTypes>
			requires
			(
				(
					true &&
					... &&
					std::is_same_v<OthersNullupleTypes, nulluple>
				)
			)
		constexpr nulluple& assign_to(const OthersNullupleTypes ...others) &
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Assigns from current nulluple to many other nulluples (does nothing)
		 * @tparam State State of the current nulluple
		 * @tparam OthersStates States of the other nulluples
		 * @tparam OthersNullupleTypes Types of the other nulluples
		 * @param others Other nulluples
		 * @return const rvalue reference to the current nulluple
		 */
		template <state_t State = state_t::unknown, state_t ...OthersStates, typename ...OthersNullupleTypes>
			requires
			(
				(
					true &&
					... &&
					std::is_same_v<OthersNullupleTypes, nulluple>
				)
			)
		constexpr const nulluple &&assign_to(const OthersNullupleTypes ...others) const&&
		__WOJ_RETURN_MOVE_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Assigns from current nulluple to many other nulluples (does nothing)
		 * @tparam State State of the current nulluple
		 * @tparam OthersStates States of the other nulluples
		 * @tparam OthersNullupleTypes Types of the other nulluples
		 * @param others Other nulluples
		 * @return rvalue reference to the current nulluple
		 */
		template <state_t State = state_t::unknown, state_t ...OthersStates, typename ...OthersNullupleTypes>
			requires
			(
				(
					true &&
					... &&
					std::is_same_v<OthersNullupleTypes, nulluple>
				)
			)
		constexpr nulluple &&assign_to(const OthersNullupleTypes ...others) &&
		__WOJ_RETURN_MOVE_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Assigns from current nulluple to many other nulluples (does nothing)
		 * @tparam DynamicStates Dynamic states tag
		 * @tparam OthersNullupleTypes Types of the other nulluples
		 * @param state State of the current nulluple
		 * @param others_states States of the other nulluples
		 * @param others Other nulluples
		 * @return const lvalue reference to the current nulluple
		 */
		template <dynamic_states_t DynamicStates = dynamic_states, size_t SizeOthersStates, typename ...OthersNullupleTypes>
			requires
			(
				(
					true &&
					... &&
					std::is_same_v<OthersNullupleTypes, nulluple>
				)
			)
		constexpr const nulluple& assign_to(const state_t state, const state_t(&others_states)[SizeOthersStates], const OthersNullupleTypes ...others) const&
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Assigns from current nulluple to many other nulluples (does nothing)
		 * @tparam DynamicStates Dynamic states tag
		 * @tparam OthersNullupleTypes Types of the other nulluples
		 * @param state State of the current nulluple
		 * @param others_states States of the other nulluples
		 * @param others Other nulluples
		 * @return lvalue reference to the current nulluple
		 */
		template <dynamic_states_t DynamicStates = dynamic_states, size_t SizeOthersStates, typename ...OthersNullupleTypes>
			requires
			(
				(
					true &&
					... &&
					std::is_same_v<OthersNullupleTypes, nulluple>
				)
			)
		constexpr nulluple& assign_to(const state_t state, const state_t(&others_states)[SizeOthersStates], const OthersNullupleTypes ...others)&
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Assigns from current nulluple to many other nulluples (does nothing)
		 * @tparam DynamicStates Dynamic states tag
		 * @tparam OthersNullupleTypes Types of the other nulluples
		 * @param state State of the current nulluple
		 * @param others_states States of the other nulluples
		 * @param others Other nulluples
		 * @return const rvalue reference to the current nulluple
		 */
		template <dynamic_states_t DynamicStates = dynamic_states, size_t SizeOthersStates, typename ...OthersNullupleTypes>
			requires
			(
				(
					true &&
					... &&
					std::is_same_v<OthersNullupleTypes, nulluple>
				)
			)
		constexpr const nulluple &&assign_to(const state_t state, const state_t(&others_states)[SizeOthersStates], const OthersNullupleTypes ...others) const&&
		__WOJ_RETURN_MOVE_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Assigns from current nulluple to many other nulluples (does nothing)
		 * @tparam DynamicStates Dynamic states tag
		 * @tparam OthersNullupleTypes Types of the other nulluples
		 * @param state State of the current nulluple
		 * @param others_states States of the other nulluples
		 * @param others Other nulluples
		 * @return rvalue reference to the current nulluple
		 */
		template <dynamic_states_t DynamicStates = dynamic_states, size_t SizeOthersStates, typename ...OthersNullupleTypes>
			requires
			(
				(
					true &&
					... &&
					std::is_same_v<OthersNullupleTypes, nulluple>
				)
			)
		constexpr nulluple &&assign_to(const state_t state, const state_t(&others_states)[SizeOthersStates], const OthersNullupleTypes ...others) &&
		__WOJ_RETURN_MOVE_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Assigns from current nulluple to many other nulluples (does nothing)
		 * @tparam DynamicStates Dynamic states tag
		 * @tparam OthersNullupleTypes Types of the other nulluples
		 * @param state State of the current nulluple
		 * @param others_states States of the other nulluples
		 * @param others Other nulluples
		 * @return const lvalue reference to the current nulluple
		 */
		template <dynamic_states_t DynamicStates = dynamic_states, size_t SizeOthersStates, typename ...OthersNullupleTypes>
			requires
			(
				(
					true &&
					... &&
					std::is_same_v<OthersNullupleTypes, nulluple>
				)
			)
		constexpr const nulluple& assign_to(const state_t state, const stack::vector<state_t, SizeOthersStates>& others_states, const OthersNullupleTypes ...others) const&
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Assigns from current nulluple to many other nulluples (does nothing)
		 * @tparam DynamicStates Dynamic states tag
		 * @tparam OthersNullupleTypes Types of the other nulluples
		 * @param state State of the current nulluple
		 * @param others_states States of the other nulluples
		 * @param others Other nulluples
		 * @return lvalue reference to the current nulluple
		 */
		template <dynamic_states_t DynamicStates = dynamic_states, size_t SizeOthersStates, typename ...OthersNullupleTypes>
			requires
			(
				(
					true &&
					... &&
					std::is_same_v<OthersNullupleTypes, nulluple>
				)
			)
		constexpr nulluple& assign_to(const state_t state, const stack::vector<state_t, SizeOthersStates>& others_states, const OthersNullupleTypes ...others)&
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Assigns from current nulluple to many other nulluples (does nothing)
		 * @tparam DynamicStates Dynamic states tag
		 * @tparam OthersNullupleTypes Types of the other nulluples
		 * @param state State of the current nulluple
		 * @param others_states States of the other nulluples
		 * @param others Other nulluples
		 * @return const rvalue reference to the current nulluple
		 */
		template <dynamic_states_t DynamicStates = dynamic_states, size_t SizeOthersStates, typename ...OthersNullupleTypes>
			requires
			(
				(
					true &&
					... &&
					std::is_same_v<OthersNullupleTypes, nulluple>
				)
			)
		constexpr const nulluple &&assign_to(const state_t state, const stack::vector<state_t, SizeOthersStates>& others_states, const OthersNullupleTypes ...others) const&&
		__WOJ_RETURN_MOVE_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Assigns from current nulluple to many other nulluples (does nothing)
		 * @tparam DynamicStates Dynamic states tag
		 * @tparam OthersNullupleTypes Types of the other nulluples
		 * @param state State of the current nulluple
		 * @param others_states States of the other nulluples
		 * @param others Other nulluples
		 * @return rvalue reference to the current nulluple
		 */
		template <dynamic_states_t DynamicStates = dynamic_states, size_t SizeOthersStates, typename ...OthersNullupleTypes>
			requires
			(
				(
					true &&
					... &&
					std::is_same_v<OthersNullupleTypes, nulluple>
				)
			)
		constexpr nulluple &&assign_to(const state_t state, const stack::vector<state_t, SizeOthersStates>& others_states, const OthersNullupleTypes ...others) &&
		__WOJ_RETURN_MOVE_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Assigns from current nulluple to many other nulluples (does nothing)
		 * @tparam DynamicStates Dynamic states tag
		 * @tparam OthersNullupleTypes Types of the other nulluples
		 * @param state State of the current nulluple
		 * @param others_states States of the other nulluples
		 * @param others Other nulluples
		 * @return const lvalue reference to the current nulluple
		 */
		template <dynamic_states_t DynamicStates = dynamic_states, typename ...OthersNullupleTypes>
			requires
			(
				(
					true &&
					... &&
					std::is_same_v<OthersNullupleTypes, nulluple>
				)
			)
		constexpr const nulluple& assign_to(const state_t state, const empty_t others_states, const OthersNullupleTypes ...others) const&
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Assigns from current nulluple to many other nulluples (does nothing)
		 * @tparam DynamicStates Dynamic states tag
		 * @tparam OthersNullupleTypes Types of the other nulluples
		 * @param state State of the current nulluple
		 * @param others_states States of the other nulluples
		 * @param others Other nulluples
		 * @return lvalue reference to the current nulluple
		 */
		template <dynamic_states_t DynamicStates = dynamic_states, size_t SizeOthersStates, typename ...OthersNullupleTypes>
			requires
			(
				(
					true &&
					... &&
					std::is_same_v<OthersNullupleTypes, nulluple>
				)
			)
		constexpr nulluple& assign_to(const state_t state, const empty_t others_states, const OthersNullupleTypes ...others)&
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Assigns from current nulluple to many other nulluples (does nothing)
		 * @tparam DynamicStates Dynamic states tag
		 * @tparam OthersNullupleTypes Types of the other nulluples
		 * @param state State of the current nulluple
		 * @param others_states States of the other nulluples
		 * @param others Other nulluples
		 * @return const rvalue reference to the current nulluple
		 */
		template <dynamic_states_t DynamicStates = dynamic_states, size_t SizeOthersStates, typename ...OthersNullupleTypes>
			requires
			(
				(
					true &&
					... &&
					std::is_same_v<OthersNullupleTypes, nulluple>
				)
			)
		constexpr const nulluple &&assign_to(const state_t state, const empty_t others_states, const OthersNullupleTypes ...others) const&&
		__WOJ_RETURN_MOVE_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Assigns from current nulluple to many other nulluples (does nothing)
		 * @tparam DynamicStates Dynamic states tag
		 * @tparam OthersNullupleTypes Types of the other nulluples
		 * @param state State of the current nulluple
		 * @param others_states States of the other nulluples
		 * @param others Other nulluples
		 * @return rvalue reference to the current nulluple
		 */
		template <dynamic_states_t DynamicStates = dynamic_states, size_t SizeOthersStates, typename ...OthersNullupleTypes>
			requires
			(
				(
					true &&
					... &&
					std::is_same_v<OthersNullupleTypes, nulluple>
				)
			)
		constexpr nulluple&& assign_to(const state_t state, const empty_t others_states, const OthersNullupleTypes ...others) &&
		__WOJ_RETURN_MOVE_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Emplaces fields from provided arguments, each field has its arguments separated by delimiter tag (does nothing)
		 * @tparam State State of the current nulluple
		 * @return const lvalue reference to the current nulluple
		 */
		template <state_t State = state_t::unknown>
		constexpr const nulluple& emplace_from() const&
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Emplaces fields from provided arguments, each field has its arguments separated by delimiter tag (does nothing)
		 * @tparam State State of the current nulluple
		 * @return lvalue reference to the current nulluple
		 */
		template <state_t State = state_t::unknown>
		constexpr nulluple& emplace_from() &
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Emplaces from provided arguments (does nothing)
		 * @tparam State State of the current nulluple
		 * @return const rvalue reference to the current nulluple
		 */
		template <state_t State = state_t::unknown>
		constexpr const nulluple &&emplace_from() const&&
		__WOJ_RETURN_MOVE_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Emplaces from provided arguments (does nothing)
		 * @tparam State State of the current nulluple
		 * @return rvalue reference to the current nulluple
		 */
		template <state_t State = state_t::unknown>
		constexpr nulluple &&emplace_from() &&
		__WOJ_RETURN_MOVE_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Emplaces fields from provided arguments, each field has its arguments separated by delimiter tag (does nothing)
		 * @tparam DynamicStates Dynamic states tag
		 * @return const lvalue reference to the current nulluple
		 */
		template <dynamic_states_t DynamicStates = dynamic_states>
		constexpr const nulluple& emplace_from(const state_t state) const&
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Emplaces fields from provided arguments, each field has its arguments separated by delimiter tag (does nothing)
		 * @tparam DynamicStates Dynamic states tag
		 * @param state State of the current nulluple
		 * @return lvalue reference to the current nulluple
		 */
		template <dynamic_states_t DynamicStates = dynamic_states>
		constexpr nulluple& emplace_from(const state_t state) &
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Emplaces from provided arguments (does nothing)
		 * @tparam DynamicStates Dynamic states tag
		 * @param state State of the current nulluple
		 * @return const rvalue reference to the current nulluple
		 */
		template <dynamic_states_t DynamicStates = dynamic_states>
		constexpr const nulluple &&emplace_from(const state_t state, const state_t other_state) const&&
		__WOJ_RETURN_MOVE_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Emplaces from provided arguments (does nothing)
		 * @tparam DynamicStates Dynamic states tag
		 * @param state State of the current nulluple
		 * @return rvalue reference to the current nulluple
		 */
		template <dynamic_states_t DynamicStates = dynamic_states>
		constexpr nulluple &&emplace_from(const state_t state) &&
		__WOJ_RETURN_MOVE_THIS_FUNCTION_METHOD_NOEXCEPT_BODY


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
		constexpr const nulluple& copy_from(const nulluple other) const&
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Copies into current nulluple from another nulluple (does nothing)
		 * @tparam State State of the current nulluple
		 * @tparam OtherState State of the other nulluple
		 * @param other Other nulluple
		 * @return lvalue reference to the current nulluple
		 */
		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown>
		constexpr nulluple& copy_from(const nulluple other)&
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Copies into current nulluple from another nulluple (does nothing)
		 * @tparam State State of the current nulluple
		 * @tparam OtherState State of the other nulluple
		 * @param other Other nulluple
		 * @return const rvalue reference to the current nulluple
		 */
		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown>
		constexpr const nulluple &&copy_from(const nulluple other) const&&
		__WOJ_RETURN_MOVE_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Copies into current nulluple from another nulluple (does nothing)
		 * @tparam State State of the current nulluple
		 * @tparam OtherState State of the other nulluple
		 * @param other Other nulluple
		 * @return rvalue reference to the current nulluple
		 */
		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown>
		constexpr nulluple &&copy_from(const nulluple other) &&
		__WOJ_RETURN_MOVE_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Copies into current nulluple from another nulluple (does nothing)
		 * @tparam DynamicStates Dynamic states tag
		 * @param state State of the current nulluple
		 * @param other_state State of the other nulluple
		 * @param other Other nulluple
		 * @return const lvalue reference to the current nulluple
		 */
		template <dynamic_states_t DynamicStates = dynamic_states>
		constexpr const nulluple& copy_from(const state_t state, const state_t other_state, const nulluple other) const&
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Copies into current nulluple from another nulluple (does nothing)
		 * @tparam DynamicStates Dynamic states tag
		 * @param state State of the current nulluple
		 * @param other_state State of the other nulluple
		 * @param other Other nulluple
		 * @return lvalue reference to the current nulluple
		 */
		template <dynamic_states_t DynamicStates = dynamic_states>
		constexpr nulluple& copy_from(const state_t state, const state_t other_state, const nulluple other)&
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Copies into current nulluple from another nulluple (does nothing)
		 * @tparam DynamicStates Dynamic states tag
		 * @param state State of the current nulluple
		 * @param other_state State of the other nulluple
		 * @param other Other nulluple
		 * @return const rvalue reference to the current nulluple
		 */
		template <dynamic_states_t DynamicStates = dynamic_states>
		constexpr const nulluple &&copy_from(const state_t state, const state_t other_state, const nulluple other) const&&
		__WOJ_RETURN_MOVE_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Copies into current nulluple from another nulluple (does nothing)
		 * @tparam DynamicStates Dynamic states tag
		 * @param state State of the current nulluple
		 * @param other_state State of the other nulluple
		 * @param other Other nulluple
		 * @return rvalue reference to the current nulluple
		 */
		template <dynamic_states_t DynamicStates = dynamic_states>
		constexpr nulluple &&copy_from(const state_t state, const state_t other_state, const nulluple other) &&
		__WOJ_RETURN_MOVE_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

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
		template <dynamic_states_t DynamicStates = dynamic_states>
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
		template <state_t State = state_t::unknown, state_t ...OthersStates, typename ...OthersNullupleTypes>
			requires
			(
				(
					true &&
					... &&
					std::is_same_v<OthersNullupleTypes, nulluple>
				)
			)
		constexpr const nulluple& copy_to(const OthersNullupleTypes ...others) const&
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Copies to many other nulluples from current nulluple (does nothing)
		 * @tparam State State of the current nulluple
		 * @tparam OthersStates States of the other nulluples
		 * @tparam OthersNullupleTypes Types of the other nulluples
		 * @param others Other nulluples
		 * @return lvalue reference to the current nulluple
		 */
		template <state_t State = state_t::unknown, state_t ...OthersStates, typename ...OthersNullupleTypes>
			requires
			(
				(
					true &&
					... &&
					std::is_same_v<OthersNullupleTypes, nulluple>
				)
			)
		constexpr nulluple& copy_to(const OthersNullupleTypes ...others) &
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Copies to many other nulluples from current nulluple (does nothing)
		 * @tparam State State of the current nulluple
		 * @tparam OthersStates States of the other nulluples
		 * @tparam OthersNullupleTypes Types of the other nulluples
		 * @param others Other nulluples
		 * @return const rvalue reference to the current nulluple
		 */
		template <state_t State = state_t::unknown, state_t ...OthersStates, typename ...OthersNullupleTypes>
			requires
			(
				(
					true &&
					... &&
					std::is_same_v<OthersNullupleTypes, nulluple>
				)
			)
		constexpr const nulluple &&copy_to(const OthersNullupleTypes ...others) const&&
		__WOJ_RETURN_MOVE_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Copies to many other nulluples from current nulluple (does nothing)
		 * @tparam State State of the current nulluple
		 * @tparam OthersStates States of the other nulluples
		 * @tparam OthersNullupleTypes Types of the other nulluples
		 * @param others Other nulluples
		 * @return rvalue reference to the current nulluple
		 */
		template <state_t State = state_t::unknown, state_t ...OthersStates, typename ...OthersNullupleTypes>
			requires
			(
				(
					true &&
					... &&
					std::is_same_v<OthersNullupleTypes, nulluple>
				)
			)
		constexpr nulluple&& copy_to(const OthersNullupleTypes ...others) &&
		__WOJ_RETURN_MOVE_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		/**
		 * Copies to many other nulluples from current nulluple (does nothing)
		 * @tparam DynamicStates Dynamic states tag
		 * @tparam OthersNullupleTypes Types of the other nulluples
		 * @param state State of the current nulluple
		 * @param others_states States of the other nulluples
		 * @param others Other nulluples
		 * @return const lvalue reference to the current nulluple
		 */
		template <dynamic_states_t DynamicStates = dynamic_states, size_t SizeOthersStates, typename ...OthersNullupleTypes>
			requires
			(
				(
					true &&
					... &&
					std::is_same_v<OthersNullupleTypes, nulluple>
				)
			)
		constexpr const nulluple& copy_to(const state_t state, const state_t(&others_states)[SizeOthersStates], const OthersNullupleTypes ...others) const&
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		template <dynamic_states_t DynamicStates = dynamic_states, size_t SizeOthersStates, typename ...OthersNullupleTypes>
			requires
			(
				(
					true &&
					... &&
					std::is_same_v<OthersNullupleTypes, nulluple>
				)
			)
		constexpr nulluple& copy_to(const state_t state, const state_t(&others_states)[SizeOthersStates], const OthersNullupleTypes ...others)&
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		template <dynamic_states_t DynamicStates = dynamic_states, size_t SizeOthersStates, typename ...OthersNullupleTypes>
			requires
			(
				(
					true &&
					... &&
					std::is_same_v<OthersNullupleTypes, nulluple>
				)
			)
		constexpr const nulluple &&copy_to(const state_t state, const state_t(&others_states)[SizeOthersStates], const OthersNullupleTypes ...others) const&&
		__WOJ_RETURN_MOVE_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		template <dynamic_states_t DynamicStates = dynamic_states, size_t SizeOthersStates, typename ...OthersNullupleTypes>
			requires
			(
				(
					true &&
					... &&
					std::is_same_v<OthersNullupleTypes, nulluple>
				)
			)
		constexpr nulluple &&copy_to(const state_t state, const state_t(&others_states)[SizeOthersStates], const OthersNullupleTypes ...others) &&
		__WOJ_RETURN_MOVE_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		template <dynamic_states_t DynamicStates = dynamic_states, size_t SizeOthersStates, typename ...OthersNullupleTypes>
			requires
			(
				(
					true &&
					... &&
					std::is_same_v<OthersNullupleTypes, nulluple>
				)
			)
		constexpr const nulluple& copy_to(const state_t state, const stack::vector<state_t, SizeOthersStates>& others_states, const OthersNullupleTypes ...others) const&
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		template <dynamic_states_t DynamicStates = dynamic_states, size_t SizeOthersStates, typename ...OthersNullupleTypes>
			requires
			(
				(
					true &&
					... &&
					std::is_same_v<OthersNullupleTypes, nulluple>
				)
			)
		constexpr nulluple& copy_to(const state_t state, const stack::vector<state_t, SizeOthersStates>& others_states, const OthersNullupleTypes ...others)&
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		template <dynamic_states_t DynamicStates = dynamic_states, size_t SizeOthersStates, typename ...OthersNullupleTypes>
			requires
			(
				(
					true &&
					... &&
					std::is_same_v<OthersNullupleTypes, nulluple>
				)
			)
		constexpr const nulluple &&copy_to(const state_t state, const stack::vector<state_t, SizeOthersStates>& others_states, const OthersNullupleTypes ...others) const&&
		__WOJ_RETURN_MOVE_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		template <dynamic_states_t DynamicStates = dynamic_states, size_t SizeOthersStates, typename ...OthersNullupleTypes>
			requires
			(
				(
					true &&
					... &&
					std::is_same_v<OthersNullupleTypes, nulluple>
					)
			)
		constexpr nulluple &&copy_to(const state_t state, const stack::vector<state_t, SizeOthersStates>& others_states, const OthersNullupleTypes ...others) &&
		__WOJ_RETURN_MOVE_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		template <dynamic_states_t DynamicStates = dynamic_states, typename ...OthersNullupleTypes>
			requires
			(
				(
					true &&
					... &&
					std::is_same_v<OthersNullupleTypes, nulluple>
				)
			)
		constexpr const nulluple& copy_to(const state_t state, const empty_t empty, const OthersNullupleTypes ...others) const&
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		template <dynamic_states_t DynamicStates = dynamic_states, size_t SizeOthersStates, typename ...OthersNullupleTypes>
			requires
			(
				(
					true &&
					... &&
					std::is_same_v<OthersNullupleTypes, nulluple>
				)
			)
		constexpr nulluple& copy_to(const state_t state, const empty_t empty, const OthersNullupleTypes ...others)&
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		template <dynamic_states_t DynamicStates = dynamic_states, size_t SizeOthersStates, typename ...OthersNullupleTypes>
			requires
			(
				(
					true &&
					... &&
					std::is_same_v<OthersNullupleTypes, nulluple>
				)
			)
		constexpr const nulluple &&copy_to(const state_t state, const empty_t empty, const OthersNullupleTypes ...others) const&&
		__WOJ_RETURN_MOVE_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		template <dynamic_states_t DynamicStates = dynamic_states, size_t SizeOthersStates, typename ...OthersNullupleTypes>
			requires
			(
				(
					true &&
					... &&
					std::is_same_v<OthersNullupleTypes, nulluple>
				)
			)
		constexpr nulluple &&copy_to(const state_t state, const empty_t empty, const OthersNullupleTypes ...others) &&
		__WOJ_RETURN_MOVE_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown>
		constexpr const nulluple& move_from(const nulluple other) const&
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown>
		constexpr nulluple& move_from(const nulluple other)&
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown>
		constexpr const nulluple &&move_from(const nulluple other) const&&
		__WOJ_RETURN_MOVE_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown>
		constexpr nulluple &&move_from(const nulluple other) &&
		__WOJ_RETURN_MOVE_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		template <dynamic_states_t DynamicStates = dynamic_states>
		constexpr const nulluple& move_from(const state_t state, const state_t other_state, const nulluple other) const&
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		template <dynamic_states_t DynamicStates = dynamic_states>
		constexpr nulluple& move_from(const state_t state, const state_t other_state, const nulluple other)&
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		template <dynamic_states_t DynamicStates = dynamic_states>
		constexpr const nulluple&& move_from(const state_t state, const state_t other_state, const nulluple other) const&&
		__WOJ_RETURN_MOVE_THIS_FUNCTION_METHOD_NOEXCEPT_BODY;

		template <dynamic_states_t DynamicStates = dynamic_states>
		constexpr nulluple &&move_from(const state_t state, const state_t other_state, const nulluple other) &&
		__WOJ_RETURN_MOVE_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

			template <state_t OtherState = state_t::unknown>
		[[nodiscard]] static
#if WOJ_HAS_CXX20
			consteval
#else
			constexpr
#endif
			nulluple moved_from(const nulluple other)
			noexcept
		{
			return nulluple{ other };
		}

		template <dynamic_states_t DynamicStates = dynamic_states>
		[[nodiscard]] static
#if WOJ_HAS_CXX20
			consteval
#else
			constexpr
#endif
			nulluple moved_from(const state_t state, const state_t other_state, const nulluple other)
			noexcept
		{
			return nulluple{ other };
		}

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown>
#if WOJ_HAS_CXX20
		consteval
#else
		constexpr
#endif
			const nulluple& move_to(const nulluple& other) const&
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY


		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown>
		constexpr nulluple& move_to(const nulluple& other)&
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY


		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown>
		constexpr const nulluple &&move_to(const nulluple& other) const&&
		__WOJ_RETURN_MOVE_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown>
		constexpr nulluple &&move_to(const nulluple& other) &&
		__WOJ_RETURN_MOVE_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		template <dynamic_states_t DynamicStates = dynamic_states>
		constexpr const nulluple& move_to(const state_t state, const state_t other_state, const nulluple& other) const&
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		template <dynamic_states_t DynamicStates = dynamic_states>
		constexpr nulluple& move_to(const state_t state, const state_t other_state, const nulluple& other)&
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		template <dynamic_states_t DynamicStates = dynamic_states>
		constexpr const nulluple &&move_to(const state_t state, const state_t other_state, const nulluple& other) const&&
		__WOJ_RETURN_MOVE_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		template <dynamic_states_t DynamicStates = dynamic_states>
		constexpr nulluple &&move_to(const state_t state, const state_t other_state, const nulluple& other) &&
		__WOJ_RETURN_MOVE_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		template <state_t State = state_t::unknown>
		constexpr const nulluple& reset() const&
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		template <state_t State = state_t::unknown>
		constexpr nulluple& reset()&
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		template <state_t State = state_t::unknown>
		constexpr const nulluple &&reset() const&&
		__WOJ_RETURN_MOVE_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		template <state_t State = state_t::unknown>
		constexpr nulluple &&reset() &&
		__WOJ_RETURN_MOVE_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		template <dynamic_states_t DynamicStates = dynamic_states>
		constexpr const nulluple& reset(const state_t state) const&
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		template <dynamic_states_t DynamicStates = dynamic_states>
		constexpr nulluple& reset(const state_t state)&
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		template <dynamic_states_t DynamicStates = dynamic_states>
		constexpr const nulluple &&reset(const state_t state) const&&
		__WOJ_RETURN_MOVE_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		template <dynamic_states_t DynamicStates = dynamic_states>
		constexpr nulluple &&reset(const state_t state) &&
			__WOJ_RETURN_MOVE_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

			[[nodiscard]] static
#if WOJ_HAS_CXX20
			consteval
#else
			constexpr
#endif
			nulluple resetted()
			noexcept
		{
			return nulluple{};
		}

		template <size_t Index>
		[[nodiscard]] static
#if WOJ_HAS_CXX20 && defined(NDEBUG)
			consteval
#else
			constexpr
#endif
			invalid_t
			get
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
			throw bad_tuple_access{ __LINE__, "Nulluple access out of bounds.", __FILE__, __func__ };
#endif
			return invalid;
		}

		template <size_t Index>
		[[nodiscard]] static
#if WOJ_HAS_CXX20 && defined(NDEBUG)
			consteval
#else
			constexpr
#endif
			invalid_t
			at
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
			throw bad_tuple_access{ __LINE__, "Nulluple access out of bounds.", __FILE__, __func__ };
#endif
			return invalid;
		}

		[[nodiscard]] static
#if WOJ_HAS_CXX20
			consteval
#else
			constexpr
#endif
			size_t size()
			noexcept
		{
			return 0;
		}

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown>
		constexpr const nulluple& swap_with(const nulluple other) const&
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown>
		constexpr nulluple& swap_with(const nulluple other)&
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown>
		constexpr const nulluple &&swap_with(const nulluple other) const&&
		__WOJ_RETURN_MOVE_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown>
		constexpr nulluple &&swap_with(const nulluple other) &&
		__WOJ_RETURN_MOVE_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		template <dynamic_states_t DynamicStates = dynamic_states>
		constexpr const nulluple& swap_with(const state_t state, const state_t other_state, const nulluple other) const&
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		template <dynamic_states_t DynamicStates = dynamic_states>
		constexpr nulluple& swap_with(const state_t state, const state_t other_state, const nulluple other)&
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		template <dynamic_states_t DynamicStates = dynamic_states>
		constexpr const nulluple &&swap_with(const state_t state, const state_t other_state, const nulluple other) const&&
		__WOJ_RETURN_MOVE_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		template <dynamic_states_t DynamicStates = dynamic_states>
		constexpr nulluple &&swap_with(const state_t state, const state_t other_state, const nulluple other) &&
		__WOJ_RETURN_MOVE_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		template <state_t State = state_t::unknown, typename VisitFunctionType, typename ...VisitArgumentsTypes>
		constexpr const nulluple& visit(VisitFunctionType&& visit_function, VisitArgumentsTypes &&...visit_arguments) const&
			noexcept
#ifndef NDEBUG
			(
				false
			)
#endif
		{
#ifndef NDEBUG
			throw bad_tuple_access{ __LINE__, "Nulluple access out of bounds.", __FILE__, __func__ };
#endif
			return *this; 
		}
	};

	template <typename FirstType>
	class single;

	template <typename Type>
	class is_single : public std::false_type {};

	template <typename Type>
	class is_single<single<Type>> : public std::true_type {};

	template <typename Type>
	constexpr bool is_single_v = is_single<Type>::value;

	template <typename FirstType>
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
			FirstType first;
		};

		using this_type = single;
		using first_value_type = FirstType;
		using value_type = FirstType;
		using reference = FirstType&;
		using const_reference = const FirstType&;
		using rvalue_reference = FirstType&&;
		using const_rvalue_reference = const FirstType&&;
		using pointer = FirstType*;
		using const_pointer = const FirstType*;

		constexpr single()
			noexcept
			(
				std::is_nothrow_default_constructible_v<FirstType>
			)
			requires
			(
				std::is_default_constructible_v<FirstType>
			)
			: first{} {}

		constexpr single()
			noexcept
			requires
			(
				!std::is_default_constructible_v<FirstType>
			) {}

		explicit constexpr single(const noinit_t noinit)
			noexcept {}

		template <typename OtherFirstType>
			requires
			(
				!std::is_same_v<std::remove_cvref_t<OtherFirstType>, single>
			)
			constexpr single(OtherFirstType &&first)
			noexcept
			(
				std::is_nothrow_constructible_v<FirstType, OtherFirstType&&>
			)
			: first{ std::forward<OtherFirstType>(first) } {}

		template <typename OtherFirstType>
			requires
			(
				!std::is_same_v<std::remove_cvref_t<OtherFirstType>, single>
			)
			constexpr single(const state_t other_state, OtherFirstType &&first)
			noexcept
			(
				std::is_nothrow_constructible_v<FirstType, OtherFirstType&&>
			)
			: first{ std::forward<OtherFirstType>(first) } {
		}

		constexpr single(const single& other)
			noexcept
			(
				std::is_nothrow_copy_constructible_v<FirstType>
			)
			: first{ other.first } {}

		constexpr single(single &&other)
			noexcept
			(
				std::is_nothrow_move_constructible_v<FirstType>
			)
			: first{ std::move(other.first) } {}

		constexpr single(const state_t other_state, const single& other)
			noexcept
			(
				std::is_nothrow_copy_constructible_v<FirstType>
			)
			: first{ other.first } {}

		constexpr single(const state_t other_state, single &&other)
			noexcept
			(
				std::is_nothrow_move_constructible_v<FirstType>
			)
			: first{ std::move(other.first) } {}

		template <typename OtherSingleType>
			requires
			(
				is_single_v<OtherSingleType> &&
				!std::is_same_v<OtherSingleType, single>
			)
		constexpr single(OtherSingleType &&other)
			noexcept
			(
				std::is_nothrow_constructible_v<FirstType, decltype(other.template get<0>()) &&>
			)
			: first{ std::forward<decltype(other.template get<0>())>(other.template get<0>()) } {}

		template <typename OtherSingleType>
			requires
			(
				is_single_v<OtherSingleType> &&
				!std::is_same_v<OtherSingleType, single>
			)
		constexpr single(const state_t other_state, OtherSingleType&& other)
			noexcept
			(
				std::is_nothrow_constructible_v<FirstType, decltype(other.template get<0>())&&>
			)
			: first{ std::forward<decltype(other.template get<0>())>(other.template get<0>()) } {}

		template <typename ...FirstArgsValueTypes>
			requires
			(
				sizeof...(FirstArgsValueTypes) != 0
			)
		constexpr single(const in_place_t in_place, FirstArgsValueTypes &&...first_args)
			noexcept
			(
				std::is_nothrow_constructible_v<FirstType, FirstArgsValueTypes &&...>
			)
			: first{ std::forward<FirstArgsValueTypes>(first_args)... } {
		}


		constexpr ~single()
			noexcept
			(
				std::is_nothrow_destructible_v<FirstType>
			)
		{
			std::destroy_at(std::addressof(first));
		}

		template <typename OtherFirstType>
			requires
			(
				!std::is_same_v<std::remove_cvref_t<OtherFirstType>, single>
			)
			constexpr single& operator=(OtherFirstType &&other)
			noexcept
			(
				std::is_nothrow_assignable_v<FirstType, OtherFirstType&&> ||
				(
					!std::is_copy_assignable_v<FirstType> &&
					std::is_nothrow_copy_constructible_v<FirstType> &&
					std::is_nothrow_destructible_v<FirstType>
				)
			)
		{
			if constexpr (std::is_assignable_v<FirstType, OtherFirstType&&>)
			{
				first = std::forward<OtherFirstType>(other);
			}
			else
			{
				std::destroy_at(std::addressof(first));
				std::construct_at(std::addressof(first), std::forward<OtherFirstType>(other));
			}
			return *this;
		}

		constexpr single& operator=(const single& other) &
			noexcept
			(
				std::is_nothrow_copy_assignable_v<FirstType> ||
				(
					!std::is_copy_assignable_v<FirstType> &&
					std::is_nothrow_copy_constructible_v<FirstType> &&
					std::is_nothrow_destructible_v<FirstType>
				)
			)
		{
			if constexpr (std::is_copy_assignable_v<FirstType>)
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

		constexpr single &&operator=(const single& other) &&
			noexcept
			(
				std::is_nothrow_copy_assignable_v<FirstType> ||
				(
					!std::is_copy_assignable_v<FirstType> &&
					std::is_nothrow_copy_constructible_v<FirstType> &&
					std::is_nothrow_destructible_v<FirstType>
				)
			)
		{
			if constexpr (std::is_copy_assignable_v<FirstType>)
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

		constexpr single& operator=(single &&other) &
			noexcept
			(
				std::is_nothrow_copy_assignable_v<FirstType> ||
				(
					!std::is_copy_assignable_v<FirstType> &&
					std::is_nothrow_copy_constructible_v<FirstType> &&
					std::is_nothrow_destructible_v<FirstType>
				)
			)
		{
			if constexpr (std::is_copy_assignable_v<FirstType>)
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
				std::is_nothrow_copy_assignable_v<FirstType> ||
				(
					!std::is_copy_assignable_v<FirstType> &&
					std::is_nothrow_copy_constructible_v<FirstType> &&
					std::is_nothrow_destructible_v<FirstType>
				)
			)
		{
			if constexpr (std::is_copy_assignable_v<FirstType>)
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

		template <typename OtherSingleType>
			requires
			(
				is_single_v<OtherSingleType> &&
				!std::is_same_v<OtherSingleType, single>
			)
		constexpr single& operator=(OtherSingleType&& other) &
			noexcept
			(
				std::is_nothrow_assignable_v<FirstType, decltype(other.template get<0>())&&> ||
				(
					!std::is_copy_assignable_v<FirstType> &&
					std::is_nothrow_constructible_v<FirstType, decltype(other.template get<0>())&&> &&
					std::is_nothrow_destructible_v<FirstType>
				)
			)
		{
			if constexpr (std::is_assignable_v<FirstType, decltype(other.template get<0>())&&>)
			{
				first = std::forward<decltype(other.template get<0>())>(other.template get<0>());
			}
			else
			{
				std::destroy_at(std::addressof(first));
				std::construct_at(std::addressof(first), std::forward<decltype(other.template get<0>())>(other.template get<0>()));
			}
			return *this;
		}

		template <typename OtherSingleType>
			requires
			(
				is_single_v<OtherSingleType> &&
				!std::is_same_v<OtherSingleType, single>
			)
		constexpr single&& operator=(OtherSingleType&& other) &&
			noexcept
			(
				std::is_nothrow_assignable_v<FirstType, decltype(other.template get<0>())&&> ||
				(
					!std::is_copy_assignable_v<FirstType> &&
					std::is_nothrow_constructible_v<FirstType, decltype(other.template get<0>())&&> &&
					std::is_nothrow_destructible_v<FirstType>
				)
			)
		{
			if constexpr (std::is_assignable_v<FirstType, decltype(other.template get<0>())&&>)
			{
				first = std::forward<decltype(other.template get<0>())>(other.template get<0>());
			}
			else
			{
				std::destroy_at(std::addressof(first));
				std::construct_at(std::addressof(first), std::forward<decltype(other.template get<0>())>(other.template get<0>()));
			}
			return *this;
		}

		explicit constexpr operator bool() const
			noexcept
		{
			return true;
		}

		[[nodiscard]] constexpr bool operator ==(const single& other) const
			noexcept
			(
				std::is_arithmetic_v<FirstType> ||
				std::is_pointer_v<FirstType>
			)
		{
			return first == other.first;
		}

		[[nodiscard]] constexpr std::strong_ordering operator <=>(const single& other) const
			noexcept
			(
				std::is_arithmetic_v<FirstType> ||
				std::is_pointer_v<FirstType>
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
		constexpr const single& construct_from(const noinit_t noinit) const&
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY


		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown>
		constexpr single& construct_from(const noinit_t noinit) &
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown>
		constexpr const single &&construct_from(const noinit_t noinit) const&&
		__WOJ_RETURN_MOVE_THIS_FUNCTION_METHOD_NOEXCEPT_BODY


		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown>
		constexpr single &&construct_from(const noinit_t noinit) &&
		__WOJ_RETURN_MOVE_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		template <dynamic_states_t DynamicStates = dynamic_states>
		constexpr const single& construct_from(const state_t state, const state_t other_state, const noinit_t noinit) const&
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		template <dynamic_states_t DynamicStates = dynamic_states>
		constexpr single& construct_from(const state_t state, const state_t other_state, const noinit_t noinit) &
		__WOJ_RETURN_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		template <dynamic_states_t DynamicStates = dynamic_states>
		constexpr const single &&construct_from(const state_t state, const state_t other_state, const noinit_t noinit) const&&
		__WOJ_RETURN_MOVE_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

		template <dynamic_states_t DynamicStates = dynamic_states>
		constexpr single &&construct_from(const state_t state, const state_t other_state, const noinit_t noinit) &&
		__WOJ_RETURN_MOVE_THIS_FUNCTION_METHOD_NOEXCEPT_BODY

	private:
		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown, typename OtherSingleType>
			requires
		(
			std::is_same_v<std::remove_cvref_t<OtherSingleType>, single>
			)
			constexpr void construct_from_helper(OtherSingleType &&other)
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
							std::is_nothrow_constructible_v<FirstType, decltype(other.template get<0>())&&>&&
							std::is_nothrow_destructible_v<FirstType>
						) ||
						OtherState == state_t::uninitialized
					)
				) ||
				(
					State == state_t::uninitialized &&
					(
						(
							(
								OtherState == state_t::initialized ||
								OtherState == state_t::unknown
							) &&
							std::is_nothrow_constructible_v<FirstType, decltype(other.template get<0>())&&>
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
				std::destroy_at(std::addressof(first));
				std::construct_at(std::addressof(first), std::forward<decltype(other.template get<0>())>(other.template get<0>()));
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
				std::construct_at(std::addressof(first), std::forward<decltype(other.template get<0>())>(other.template get<0>()));
			}
		}
	public:

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown, typename OtherSingleType>
			requires
			(
				std::is_same_v<std::remove_cvref_t<OtherSingleType>, single>
			)
		constexpr single& construct_from(OtherSingleType &&other) &
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
							std::is_nothrow_constructible_v<FirstType, decltype(other.template get<0>())&&>&&
							std::is_nothrow_destructible_v<FirstType>
						) ||
						OtherState == state_t::uninitialized
					)
				) ||
				(
					State == state_t::uninitialized &&
					(
						(
							(
								OtherState == state_t::initialized ||
								OtherState == state_t::unknown
							) &&
							std::is_nothrow_constructible_v<FirstType, decltype(other.template get<0>())&&>
						) ||
						OtherState == state_t::uninitialized
					)
				)
			)
		{
			this->template construct_from_helper<State, OtherState>(other);
			return *this;
		}

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown, typename OtherSingleType>
			requires
			(
				std::is_same_v<std::remove_cvref_t<OtherSingleType>, single>
			)
		constexpr single &&construct_from(OtherSingleType &&other) &&
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
							std::is_nothrow_constructible_v<FirstType, decltype(other.template get<0>())&&>&&
							std::is_nothrow_destructible_v<FirstType>
						) ||
						OtherState == state_t::uninitialized
					)
				) ||
				(
					State == state_t::uninitialized &&
					(
						(
							(
								OtherState == state_t::initialized ||
								OtherState == state_t::unknown
							) &&
							std::is_nothrow_constructible_v<FirstType, decltype(other.template get<0>())&&>
						) ||
						OtherState == state_t::uninitialized
					)
				)
			)
		{
			this->template construct_from_helper<State, OtherState>(other);
			return *this;
		}

	private:
		template <dynamic_states_t DynamicStates = dynamic_states, typename OtherSingleType>
			requires
			(
				std::is_same_v<std::remove_cvref_t<OtherSingleType>, single>
			)
		constexpr void construct_from_helper(const state_t state, const state_t other_state, OtherSingleType &&other)
			noexcept
			(
				std::is_nothrow_constructible_v<FirstType, decltype(other.template get<0>())&&>&&
				std::is_nothrow_destructible_v<FirstType>
			)
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
				std::construct_at(std::addressof(first), std::forward<decltype(other.template get<0>())>(other.template get<0>()));
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
				std::construct_at(std::addressof(first), std::forward<decltype(other.template get<0>())>(other.template get<0>()));
			}
		}
	public:

		template <dynamic_states_t DynamicStates = dynamic_states, typename OtherSingleType>
			requires
			(
				std::is_same_v<std::remove_cvref_t<OtherSingleType>, single>
			)
		constexpr single& construct_from(const state_t state, const state_t other_state, OtherSingleType &&other) &
			noexcept
			(
				std::is_nothrow_constructible_v<FirstType, decltype(other.template get<0>())&&>&&
				std::is_nothrow_destructible_v<FirstType>
			)
		{
			this->template construct_from_helper<dynamic_states>(state, other_state, std::forward<OtherSingleType>(other));
			return *this;
		}

		template <dynamic_states_t DynamicStates = dynamic_states, typename OtherSingleType>
			requires
			(
				std::is_same_v<std::remove_cvref_t<OtherSingleType>, single>
			)
		constexpr single &&construct_from(const state_t state, const state_t other_state, OtherSingleType &&other) &&
			noexcept
			(
				std::is_nothrow_constructible_v<FirstType, decltype(other.template get<0>())&&>&&
				std::is_nothrow_destructible_v<FirstType>
			)
		{
			this->template construct_from_helper<dynamic_states>(state, other_state, std::forward<OtherSingleType>(other));
			return *this;
		}

	private:
		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown, typename OtherFirstType>
			requires
			(
				!std::is_same_v<std::remove_cvref_t<OtherFirstType>, single>
			)
		constexpr void construct_from_helper(OtherFirstType &&other)
			noexcept
			(
				(
					(
						State == state_t::initialized ||
						State == state_t::unknown
					) &&
					std::is_nothrow_constructible_v<FirstType, OtherFirstType&&>&&
					std::is_nothrow_destructible_v<FirstType>
				) ||
				(
					State == state_t::uninitialized &&
					std::is_nothrow_constructible_v<FirstType, OtherFirstType&&>
				)
			)
		{
			if constexpr (State == state_t::initialized || State == state_t::unknown)
			{
				std::destroy_at(std::addressof(first));
				std::construct_at(std::addressof(first), std::forward<OtherFirstType>(other));
			}
			else
			{
				std::construct_at(std::addressof(first), std::forward<OtherFirstType>(other));
			}
		}
	public:

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown, typename OtherFirstType>
			requires
			(
				!std::is_same_v<std::remove_cvref_t<OtherFirstType>, single>
			)
		constexpr single& construct_from(OtherFirstType &&other) &
			noexcept
			(
				(
					(
						State == state_t::initialized ||
						State == state_t::unknown
					) &&
					std::is_nothrow_constructible_v<FirstType, OtherFirstType&&>&&
					std::is_nothrow_destructible_v<FirstType>
				) ||
				(
					State == state_t::uninitialized &&
					std::is_nothrow_constructible_v<FirstType, OtherFirstType&&>
				)
			)
		{
			this->template construct_from_helper<State, OtherState>(std::forward<OtherFirstType>(other));

			return *this;
		}

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown, typename OtherFirstType>
			requires
			(
				!std::is_same_v<std::remove_cvref_t<OtherFirstType>, single>
			)
			constexpr single &&construct_from(OtherFirstType &&other) &&
			noexcept
			(
				(
					(
						State == state_t::initialized ||
						State == state_t::unknown
					) &&
					std::is_nothrow_constructible_v<FirstType, OtherFirstType&&>&&
					std::is_nothrow_destructible_v<FirstType>
				) ||
				(
					State == state_t::uninitialized &&
					std::is_nothrow_constructible_v<FirstType, OtherFirstType&&>
				)
			)
		{
			this->template construct_from_helper<State, OtherState>(std::forward<OtherFirstType>(other));

			return *this;
		}

	private:

		template <dynamic_states_t DynamicStates = dynamic_states, typename OtherFirstType>
			requires
			(
				!std::is_same_v<std::remove_cvref_t<OtherFirstType>, single>
			)
		constexpr void construct_from_helper(const state_t state, const state_t other_state, OtherFirstType &&other)
			noexcept
			(
				std::is_nothrow_constructible_v<FirstType, OtherFirstType&&>&&
				std::is_nothrow_destructible_v<FirstType>
			)
		{
			if (state == state_t::initialized || state == state_t::unknown)
			{
				std::destroy_at(std::addressof(first));
				std::construct_at(std::addressof(first), std::forward<OtherFirstType>(other));
			}
			else
			{
				std::construct_at(std::addressof(first), std::forward<OtherFirstType>(other));
			}
		}

	public:

		template <dynamic_states_t DynamicStates = dynamic_states, typename OtherFirstType>
			requires
			(
				!std::is_same_v<std::remove_cvref_t<OtherFirstType>, single>
			)
		constexpr single& construct_from(const state_t state, const state_t other_state, OtherFirstType &&other) &
			noexcept
			(
				std::is_nothrow_constructible_v<FirstType, OtherFirstType&&>&&
				std::is_nothrow_destructible_v<FirstType>
			)
		{
			this->construct_from_helper(state, other_state, std::forward<OtherFirstType>(other));
			return *this;
		}

		template <dynamic_states_t DynamicStates = dynamic_states, typename OtherFirstType>
			requires
			(
				!std::is_same_v<std::remove_cvref_t<OtherFirstType>, single>
			)
		constexpr single &&construct_from(const state_t state, const state_t other_state, OtherFirstType &&other) &&
			noexcept
			(
				std::is_nothrow_constructible_v<FirstType, OtherFirstType&&>&&
				std::is_nothrow_destructible_v<FirstType>
			)
		{
			this->construct_from_helper(state, other_state, std::forward<OtherFirstType>(other));
			return *this;
		}

		template <state_t OtherState = state_t::unknown>
		[[nodiscard]] static
#if WOJ_HAS_CXX20
			consteval
#else
			constexpr
#endif
			single constructed_from(const noinit_t noinit)
			noexcept
		{
			return single{ noinit };
		}

		template <dynamic_states_t DynamicStates = dynamic_states>
		[[nodiscard]] static
#if WOJ_HAS_CXX20
			consteval
#else
			constexpr
#endif
			single constructed_from(const state_t other_state, const noinit_t noinit)
			noexcept
		{
			return single{ noinit };
		}

		template <state_t OtherState = state_t::unknown, typename OtherSingleType>
			requires
			(
				std::is_same_v<std::remove_cvref_t<OtherSingleType>, single>
			)
			[[nodiscard]] static
#if WOJ_HAS_CXX20
			consteval
#else
			constexpr
#endif
			single constructed_from(OtherSingleType &&other)
			noexcept
			(
				std::is_nothrow_constructible_v<FirstType, decltype(other.template get<0>())&&>
			)
		{
			single temp{ noinit };
			temp.construct_from<state_t::uninitialized, OtherState>(std::forward<decltype(other.template get<0>())>(other.template get<0>()));
			return std::move(temp);
		}

		template <dynamic_states_t DynamicStates = dynamic_states, typename OtherSingleType>
			requires
			(
				std::is_same_v<std::remove_cvref_t<OtherSingleType>, single>
			)
			[[nodiscard]] static
#if WOJ_HAS_CXX20
			consteval
#else
			constexpr
#endif
			single constructed_from(const state_t other_state, OtherSingleType &&other)
			noexcept
			(
				std::is_nothrow_constructible_v<FirstType, decltype(other.template get<0>())&&>
			)
		{
			single temp{ noinit };
			temp.construct_from(state_t::uninitialized, other_state, std::forward<decltype(other.template get<0>())>(other.template get<0>()));
			return std::move(temp);
		}

		template <state_t OtherState = state_t::unknown, typename OtherFirstType>
			requires
			(
				!std::is_same_v<std::remove_cvref_t<OtherFirstType>, single>
			)
			[[nodiscard]] static
#if WOJ_HAS_CXX20
			consteval
#else
			constexpr
#endif
			single constructed_from(OtherFirstType &&other)
			noexcept
			(
				std::is_nothrow_constructible_v<FirstType, OtherFirstType&&>
			)
		{
			single temp{ noinit };
			temp.construct_from<state_t::uninitialized, OtherState>(std::forward<OtherFirstType>(other));
			return std::move(temp);
		}

		template <dynamic_states_t DynamicStates = dynamic_states, typename OtherFirstType>
			requires
			(
				!std::is_same_v<std::remove_cvref_t<OtherFirstType>, single>
			)
			[[nodiscard]] static
#if WOJ_HAS_CXX20
			consteval
#else
			constexpr
#endif
			single constructed_from(const state_t other_state, OtherFirstType &&other)
			noexcept
			(
				std::is_nothrow_constructible_v<FirstType, OtherFirstType&&>
			)
		{
			single temp{ noinit };
			temp.construct_from(state_t::uninitialized, other_state, std::forward<OtherFirstType>(other));
			return std::move(temp);
		}

	private:

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown, typename OtherSingleType>
			requires
			(
				std::is_same_v<std::remove_reference_t<OtherSingleType>, single>
			)
		constexpr void construct_to_helper(OtherSingleType &&other) const
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
		}

	public:

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown, typename OtherSingleType>
			requires
			(
				std::is_same_v<std::remove_reference_t<OtherSingleType>, single>
			)
		constexpr const single &construct_to(OtherSingleType &&other) const &
		{
			this->template construct_to_helper<State, OtherState>(other);
			return *this;
		}

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown, typename OtherSingleType>
			requires
			(
				std::is_same_v<std::remove_reference_t<OtherSingleType>, single>
			)
		constexpr single &construct_to(OtherSingleType &&other) &
		{
			this->template construct_to_helper<State, OtherState>(other);
			return *this;
		}

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown, typename OtherSingleType>
			requires
			(
				std::is_same_v<std::remove_reference_t<OtherSingleType>, single>
			)
		constexpr const single &&construct_to(OtherSingleType &&other) const &&
		{
			this->template construct_to_helper<State, OtherState>(other);
			return *this;
		}

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown, typename OtherSingleType>
			requires
			(
				std::is_same_v<std::remove_reference_t<OtherSingleType>, single>
			)
		constexpr single &&construct_to(OtherSingleType &&other) &&
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
			return *this;
		}

	private:

		template <dynamic_states_t DynamicStates = dynamic_states, typename OtherSingleType>
			requires
			(
				std::is_same_v<std::remove_reference_t<OtherSingleType>, single>
			)
			constexpr void construct_to_helper(const state_t state, const state_t other_state, OtherSingleType&& other) const
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
		}

	public:

		template <dynamic_states_t DynamicStates = dynamic_states, typename OtherSingleType>
			requires
			(
				std::is_same_v<std::remove_reference_t<OtherSingleType>, single>
			)
		constexpr const single& construct_to(const state_t state, const state_t other_state, OtherSingleType&& other) const&
		{
			this->template construct_to_helper<dynamic_states>(state, other_state, other);
			return *this;
		}

		template <dynamic_states_t DynamicStates = dynamic_states, typename OtherSingleType>
			requires
			(
				std::is_same_v<std::remove_reference_t<OtherSingleType>, single>
			)
		constexpr single& construct_to(const state_t state, const state_t other_state, OtherSingleType&& other) &
		{
			this->template construct_to_helper<dynamic_states>(state, other_state, other);
			return *this;
		}

		template <dynamic_states_t DynamicStates = dynamic_states, typename OtherSingleType>
			requires
			(
				std::is_same_v<std::remove_reference_t<OtherSingleType>, single>
			)
		constexpr const single&& construct_to(const state_t state, const state_t other_state, OtherSingleType&& other) const&&
		{
			this->template construct_to_helper<dynamic_states>(state, other_state, other);
			return *this;
		}

		template <dynamic_states_t DynamicStates = dynamic_states, typename OtherSingleType>
			requires
			(
				std::is_same_v<std::remove_reference_t<OtherSingleType>, single>
			)
		constexpr single&& construct_to(const state_t state, const state_t other_state, OtherSingleType&& other)&&
		{
			if (state == state_t::initialized || state == state_t::unknown)
			{
				if (other_state == state_t::initialized || other_state == state_t::unknown)
				{
					std::destroy_at(std::addressof(other.first));
					std::construct_at(std::addressof(other.first), std::move(first));
				}
				else
				{
					std::construct_at(std::addressof(other.first), std::move(first));
				}
			}
			return *this;
		}

	private:

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown, typename OtherFirstType>
			requires
			(
				!std::is_same_v<std::remove_cvref_t<OtherFirstType>, single>
			)
		constexpr void construct_to_helper(OtherFirstType&& other) const
		{
			if constexpr (State == state_t::initialized || State == state_t::unknown)
			{
				std::destroy_at(std::addressof(other));
				std::construct_at(std::addressof(other), first);
			}
		}

	public:

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown, typename OtherFirstType>
			requires
			(
				!std::is_same_v<std::remove_cvref_t<OtherFirstType>, single>
			)
		constexpr const single& construct_to(OtherFirstType&& other) const&
		{
			this->template construct_to_helper<State, OtherState>(other);
			return *this;
		}

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown, typename OtherFirstType>
			requires
			(
				!std::is_same_v<std::remove_cvref_t<OtherFirstType>, single>
			)
		constexpr single& construct_to(OtherFirstType&& other) &
		{
			this->template construct_to_helper<State, OtherState>(other);
			return *this;
		}

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown, typename OtherFirstType>
			requires
			(
				!std::is_same_v<std::remove_cvref_t<OtherFirstType>, single>
			)
		constexpr const single&& construct_to(OtherFirstType&& other) const&&
		{
			this->template construct_to_helper<State, OtherState>(other);
			return *this;
		}

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown, typename OtherFirstType>
			requires
			(
				!std::is_same_v<std::remove_cvref_t<OtherFirstType>, single>
			)
		constexpr single&& construct_to(OtherFirstType&& other) &&
		{
			if (State == state_t::initialized || State == state_t::unknown)
			{
				std::destroy_at(std::addressof(other));
				std::construct_at(std::addressof(other), std::move(first));
			}
			return *this;
		}

	private:

		template <dynamic_states_t DynamicStates = dynamic_states, typename OtherFirstType>
			requires
			(
				!std::is_same_v<std::remove_cvref_t<OtherFirstType>, single>
			)
		constexpr void construct_to_helper(const state_t state, const state_t other_state, OtherFirstType&& other) const
		{
			if (state == state_t::initialized || state == state_t::unknown)
			{
				std::destroy_at(std::addressof(other));
				std::construct_at(std::addressof(other), first);
			}
		}

	public:

		template <dynamic_states_t DynamicStates = dynamic_states, typename OtherFirstType>
			requires
			(
				!std::is_same_v<std::remove_cvref_t<OtherFirstType>, single>
			)
		constexpr const single& construct_to(const state_t state, const state_t other_state, OtherFirstType&& other) const&
		{
			this->template construct_to_helper<dynamic_states>(state, other_state, other);
			return *this;
		}

		template <dynamic_states_t DynamicStates = dynamic_states, typename OtherFirstType>
			requires
			(
				!std::is_same_v<std::remove_cvref_t<OtherFirstType>, single>
			)
		constexpr single& construct_to(const state_t state, const state_t other_state, OtherFirstType&& other)&
		{
			this->template construct_to_helper<dynamic_states>(state, other_state, other);
			return *this;
		}

		template <dynamic_states_t DynamicStates = dynamic_states, typename OtherFirstType>
			requires
			(
				!std::is_same_v<std::remove_cvref_t<OtherFirstType>, single>
			)
		constexpr const single&& construct_to(const state_t state, const state_t other_state, OtherFirstType&& other) const&&
		{
			this->template construct_to_helper<dynamic_states>(state, other_state, other);
			return *this;
		}

		template <dynamic_states_t DynamicStates = dynamic_states, typename OtherFirstType>
			requires
			(
				!std::is_same_v<std::remove_cvref_t<OtherFirstType>, single>
			)
		constexpr single&& construct_to(const state_t state, const state_t other_state, OtherFirstType&& other) &&
		{
			this->template construct_to_helper<dynamic_states>(state, other_state, other);
			return *this;
		}


	private:
		template <typename ...OthersTypes, size_t ...OthersTypesIndexes>
		static
#if WOJ_HAS_CXX20
			consteval
#else
			constexpr
#endif
		size_t helper_count_singles(std::index_sequence<OthersTypesIndexes...>) noexcept
		{
			using tuple_type = std::tuple<std::remove_cvref_t<OthersTypes>...>;

			constexpr size_t res = (0 + ... + std::is_same_v<std::tuple_element_t<OthersTypesIndexes, tuple_type>, this_type>);
			return res;
		}

		template <state_t State = state_t::unknown, typename OtherType, size_t Index, typename ...OthersTypes, state_t ...OthersSingleStates>
		constexpr void construct_to_impl(OtherType &&other, const woj::meta::value_sequence<OthersSingleStates...> others_states) const&
		{
			constexpr size_t number_singles = helper_count_singles<OthersTypes...>(std::make_index_sequence<Index>());

			if constexpr (is_single_v<OtherType>)
			{
				if constexpr (number_singles < sizeof...(OthersSingleStates))
				{
					constexpr stack::vector<state_t, sizeof...(OthersSingleStates)> others_states{ std::forward<decltype(OthersSingleStates)>(OthersSingleStates)... };
					constexpr state_t other_state = others_states[number_singles];
					this->template construct_to<State, other_state>(std::forward<decltype(other)>(other));
				}
				else
				{
					this->template construct_to<State>(std::forward<decltype(other)>(other));
				}
			}
			else
			{
				this->template construct_to<State>(std::forward<decltype(other)>(other));
			}
		}

		template <state_t State = state_t::unknown, typename OtherType, size_t Index, typename ...OthersTypes, state_t ...OthersSingleStates>
		constexpr void construct_to_impl(OtherType&& other, const woj::meta::value_sequence<OthersSingleStates...> others_states) &
		{
			constexpr size_t number_singles = helper_count_singles<OthersTypes...>(std::make_index_sequence<Index>());

			if constexpr (is_single_v<OtherType>)
			{
				if constexpr (number_singles < sizeof...(OthersSingleStates))
				{
					constexpr stack::vector<state_t, sizeof...(OthersSingleStates)> others_states{ std::forward<decltype(OthersSingleStates)>(OthersSingleStates)... };
					constexpr state_t other_state = others_states[number_singles];
					this->template construct_to<State, other_state>(std::forward<decltype(other)>(other));
				}
				else
				{
					this->template construct_to<State>(std::forward<decltype(other)>(other));
				}
			}
			else
			{
				this->template construct_to<State>(std::forward<decltype(other)>(other));
			}
		}

		template <state_t State = state_t::unknown, typename OtherType, size_t Index, typename ...OthersTypes, state_t ...OthersSingleStates>
		constexpr void construct_to_impl(OtherType&& other, const woj::meta::value_sequence<OthersSingleStates...> others_states) const&&
		{
			constexpr size_t number_singles = helper_count_singles<OthersTypes...>(std::make_index_sequence<Index>());

			if constexpr (is_single_v<OtherType>)
			{
				if constexpr (number_singles < sizeof...(OthersSingleStates))
				{
					constexpr stack::vector<state_t, sizeof...(OthersSingleStates)> others_states{ std::forward<decltype(OthersSingleStates)>(OthersSingleStates)... };
					constexpr state_t other_state = others_states[number_singles];
					this->template construct_to<State, other_state>(std::forward<decltype(other)>(other));
				}
				else
				{
					this->template construct_to<State>(std::forward<decltype(other)>(other));
				}
			}
			else
			{
				this->template construct_to<State>(std::forward<decltype(other)>(other));
			}
		}

		template <state_t State = state_t::unknown, typename OtherType, size_t Index, typename ...OthersTypes, state_t ...OthersSingleStates>
		constexpr void construct_to_impl(OtherType&& other, const woj::meta::value_sequence<OthersSingleStates...> others_states) &&
		{
			constexpr size_t number_singles = helper_count_singles<OthersTypes...>(std::make_index_sequence<Index>());

			if constexpr (is_single_v<OtherType>)
			{
				if constexpr (number_singles < sizeof...(OthersSingleStates))
				{
					constexpr stack::vector<state_t, sizeof...(OthersSingleStates)> others_states{ std::forward<decltype(OthersSingleStates)>(OthersSingleStates)... };
					constexpr state_t other_state = others_states[number_singles];
					this->template construct_to<State, other_state>(std::forward<decltype(other)>(other));
				}
				else
				{
					this->template construct_to<State>(std::forward<decltype(other)>(other));
				}
			}
			else
			{
				this->template construct_to<State>(std::forward<decltype(other)>(other));
			}
		}

		template <state_t State = state_t::unknown, state_t ...OthersSingleStates, typename ...OthersTypes, size_t ...OthersTypesIndexes>
		constexpr void construct_to_helper(OthersTypes &&...others, std::index_sequence<OthersTypesIndexes...>) const&
		{
			(
				this->template construct_to_impl<State, OthersTypes, OthersTypesIndexes, OthersTypes...>(std::forward<OthersTypes>(others), woj::meta::value_sequence<OthersSingleStates...>{}), 
				...
			);
		}

		template <state_t State = state_t::unknown, state_t ...OthersSingleStates, typename ...OthersTypes, size_t ...OthersTypesIndexes>
		constexpr void construct_to_helper(OthersTypes &&...others, std::index_sequence<OthersTypesIndexes...>) &
		{
			(
				this->template construct_to_impl<State, OthersTypes, OthersTypesIndexes, OthersTypes...>(std::forward<OthersTypes>(others), woj::meta::value_sequence<OthersSingleStates...>{}),
				...
				);
		}

		template <state_t State = state_t::unknown, state_t ...OthersSingleStates, typename ...OthersTypes, size_t ...OthersTypesIndexes>
		constexpr void construct_to_helper(OthersTypes &&...others, std::index_sequence<OthersTypesIndexes...>) const&&
		{
			(
				this->template construct_to_impl<State, OthersTypes, OthersTypesIndexes, OthersTypes...>(std::forward<OthersTypes>(others), woj::meta::value_sequence<OthersSingleStates...>{}),
				...
				);
		}

		template <state_t State = state_t::unknown, state_t ...OthersSingleStates, typename ...OthersTypes, size_t ...OthersTypesIndexes>
		constexpr void construct_to_helper(OthersTypes &&...others, std::index_sequence<OthersTypesIndexes...>) &&
		{
			(
				this->template construct_to_impl<State, OthersTypes, OthersTypesIndexes, OthersTypes...>(std::forward<OthersTypes>(others), woj::meta::value_sequence<OthersSingleStates...>{}),
				...
				);
		}

	public:

		template <state_t State = state_t::unknown, state_t ...OthersSingleStates, typename ...OthersTypes>
		constexpr const single& construct_to(OthersTypes &&...others) const&
		{
			this->template construct_to_helper<State, OthersSingleStates..., OthersTypes...>(std::forward<OthersTypes>(others)..., std::make_index_sequence<sizeof...(OthersTypes)>{});
			return *this;
		}

		template <state_t State = state_t::unknown, state_t ...OthersSingleStates, typename ...OthersTypes>
		constexpr single& construct_to(OthersTypes &&...others) &
		{
			this->template construct_to_helper<State, OthersSingleStates..., OthersTypes...>(std::forward<OthersTypes>(others)..., std::make_index_sequence<sizeof...(OthersTypes)>{});
			return *this;
		}



		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown, typename OtherSingleType>
			requires
			(
				std::is_same_v<std::remove_cvref_t<OtherSingleType>, single>
			)
		constexpr void assign_from_helper(OtherSingleType &&other)
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
								std::is_nothrow_assignable_v<FirstType, decltype(other.template get<0>())&&> ||
								(
									!std::is_assignable_v<FirstType, decltype(other.template get<0>())&&> &&
									std::is_nothrow_constructible_v<FirstType, decltype(other.template get<0>())&&> &&
									std::is_nothrow_destructible_v<FirstType>
								)
							)
						) ||
						OtherState == state_t::uninitialized
					)
				) ||
				(
					State == state_t::uninitialized &&
					(
						(
							(
								OtherState == state_t::initialized ||
								OtherState == state_t::unknown
							) &&
							std::is_nothrow_constructible_v<FirstType, decltype(other.template get<0>())&&>
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
					if constexpr (std::is_assignable_v<FirstType, decltype(other.template get<0>())&&>)
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
			constexpr single& assign_from(OtherSingleType &&other) &
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
								std::is_nothrow_assignable_v<FirstType, decltype(other.template get<0>())&&> ||
								(
									!std::is_assignable_v<FirstType, decltype(other.template get<0>())&&> &&
									std::is_nothrow_constructible_v<FirstType, decltype(other.template get<0>())&&> &&
									std::is_nothrow_destructible_v<FirstType>
									)
								)
							) ||
						OtherState == state_t::uninitialized
						)
					) ||
				(
					State == state_t::uninitialized &&
					(
						(
							(
								OtherState == state_t::initialized ||
								OtherState == state_t::unknown
								) &&
							std::is_nothrow_constructible_v<FirstType, decltype(other.template get<0>())&&>
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
			constexpr single &&assign_from(OtherSingleType &&other) &&
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
								std::is_nothrow_assignable_v<FirstType, decltype(other.template get<0>())&&> ||
								(
									!std::is_assignable_v<FirstType, decltype(other.template get<0>())&&> &&
									std::is_nothrow_constructible_v<FirstType, decltype(other.template get<0>())&&> &&
									std::is_nothrow_destructible_v<FirstType>
									)
								)
							) ||
						OtherState == state_t::uninitialized
						)
					) ||
				(
					State == state_t::uninitialized &&
					(
						(
							(
								OtherState == state_t::initialized ||
								OtherState == state_t::unknown
								) &&
							std::is_nothrow_constructible_v<FirstType, decltype(other.template get<0>())&&>
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

		template <dynamic_states_t DynamicStates = dynamic_states, typename OtherSingleType>
			requires
		(
			std::is_same_v<std::remove_cvref_t<OtherSingleType>, single>
			)
			constexpr void assign_from_helper(const state_t state, const state_t other_state, OtherSingleType &&other)
			noexcept
			(
				std::is_nothrow_assignable_v<FirstType, decltype(other.template get<0>())&&>&&
				std::is_nothrow_constructible_v<FirstType, decltype(other.template get<0>())&&>&&
				std::is_nothrow_destructible_v<FirstType>
				)
		{
			if (state == state_t::initialized || state == state_t::unknown)
			{
				if (other_state == state_t::initialized || other_state == state_t::unknown)
				{
					if constexpr (std::is_assignable_v<FirstType, decltype(other.template get<0>())&&>)
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

		template <dynamic_states_t DynamicStates = dynamic_states, typename OtherSingleType>
			requires
		(
			std::is_same_v<std::remove_cvref_t<OtherSingleType>, single>
			)
			constexpr single& assign_from(const state_t state, const state_t other_state, OtherSingleType &&other) &
			noexcept
			(
				std::is_nothrow_assignable_v<FirstType, decltype(other.template get<0>())&&>&&
				std::is_nothrow_constructible_v<FirstType, decltype(other.template get<0>())&&>&&
				std::is_nothrow_destructible_v<FirstType>
				)
		{
			this->template assign_from_helper<dynamic_states>(state, other_state, std::forward<OtherSingleType>(other));
			return *this;
		}

		template <dynamic_states_t DynamicStates = dynamic_states, typename OtherSingleType>
			requires
		(
			std::is_same_v<std::remove_cvref_t<OtherSingleType>, single>
			)
			constexpr single &&assign_from(const state_t state, const state_t other_state, OtherSingleType &&other) &&
			noexcept
			(
				std::is_nothrow_assignable_v<FirstType, decltype(other.template get<0>())&&>&&
				std::is_nothrow_constructible_v<FirstType, decltype(other.template get<0>())&&>&&
				std::is_nothrow_destructible_v<FirstType>
				)
		{
			this->template assign_from_helper<dynamic_states>(state, other_state, std::forward<OtherSingleType>(other));
			return *this;
		}

	private:

		template <state_t State = state_t::unknown, typename OtherFirstType>
			requires
		(
			!std::is_same_v<std::remove_cvref_t<OtherFirstType>, single>
			)
			constexpr void assign_from_helper(OtherFirstType &&other)
			noexcept
			(
				(
					(
						State == state_t::initialized ||
						State == state_t::unknown
						) &&
					(
						std::is_nothrow_assignable_v<FirstType, OtherFirstType&&> ||
						(
							!std::is_assignable_v<FirstType, OtherFirstType&&> &&
							std::is_nothrow_constructible_v<FirstType, OtherFirstType&&> &&
							std::is_nothrow_destructible_v<FirstType>
							)
						)
					) ||
				(
					State == state_t::uninitialized &&
					std::is_nothrow_constructible_v<FirstType, OtherFirstType&&>
					)
				)
		{
			if constexpr (State == state_t::initialized || State == state_t::unknown)
			{
				if constexpr (std::is_assignable_v<FirstType, OtherFirstType&&>)
				{
					first = std::forward<OtherFirstType>(other);
				}
				else
				{
					std::destroy_at(std::addressof(first));
					std::construct_at(std::addressof(first), std::forward<OtherFirstType>(other));
				}
			}
			else
			{
				std::construct_at(std::addressof(first), std::forward<OtherFirstType>(other));
			}
		}

	public:

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown, typename OtherFirstType>
			requires
		(
			!std::is_same_v<std::remove_cvref_t<OtherFirstType>, single>
			)
			constexpr single& assign_from(OtherFirstType &&other) &
			noexcept
			(
				(
					(
						State == state_t::initialized ||
						State == state_t::unknown
						) &&
					(
						std::is_nothrow_assignable_v<FirstType, OtherFirstType&&> ||
						(
							!std::is_assignable_v<FirstType, OtherFirstType&&> &&
							std::is_nothrow_constructible_v<FirstType, OtherFirstType&&> &&
							std::is_nothrow_destructible_v<FirstType>
							)
						)
					) ||
				(
					State == state_t::uninitialized &&
					std::is_nothrow_constructible_v<FirstType, OtherFirstType&&>
					)
				)
		{
			this->template assign_from_helper<State, OtherState>(std::forward<OtherFirstType>(other));
			return *this;
		}

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown, typename OtherFirstType>
			requires
		(
			!std::is_same_v<std::remove_cvref_t<OtherFirstType>, single>
			)
			constexpr single &&assign_from(OtherFirstType &&other) &&
			noexcept
			(
				(
					(
						State == state_t::initialized ||
						State == state_t::unknown
						) &&
					(
						std::is_nothrow_assignable_v<FirstType, OtherFirstType&&> ||
						(
							!std::is_assignable_v<FirstType, OtherFirstType&&> &&
							std::is_nothrow_constructible_v<FirstType, OtherFirstType&&> &&
							std::is_nothrow_destructible_v<FirstType>
							)
						)
					) ||
				(
					State == state_t::uninitialized &&
					std::is_nothrow_constructible_v<FirstType, OtherFirstType&&>
					)
				)
		{
			this->template assign_from_helper<State, OtherState>(std::forward<OtherFirstType>(other));
			return *this;
		}

	private:

		template <dynamic_states_t DynamicStates = dynamic_states, typename OtherFirstType>
			requires
		(
			!std::is_same_v<std::remove_cvref_t<OtherFirstType>, single>
			)
			constexpr void assign_from_helper(const state_t state, OtherFirstType &&other)
			noexcept
			(
				std::is_nothrow_assignable_v<FirstType, OtherFirstType&&>&&
				std::is_nothrow_constructible_v<FirstType, OtherFirstType&&>&&
				std::is_nothrow_destructible_v<FirstType>
				)
		{
			if (state == state_t::initialized || state == state_t::unknown)
			{
				if constexpr (std::is_assignable_v<FirstType, OtherFirstType&&>)
				{
					first = std::forward<OtherFirstType>(other);
				}
				else
				{
					std::destroy_at(std::addressof(first));
					std::construct_at(std::addressof(first), std::forward<OtherFirstType>(other));
				}
			}
			else if (state == state_t::uninitialized)
			{
				std::construct_at(std::addressof(first), std::forward<OtherFirstType>(other));
			}
		}

	public:

		template <dynamic_states_t DynamicStates = dynamic_states, typename OtherFirstType>
			requires
		(
			!std::is_same_v<std::remove_cvref_t<OtherFirstType>, single>
			)
			constexpr single& assign_from(const state_t state, const state_t other_state, OtherFirstType &&other) &
			noexcept
			(
				std::is_nothrow_assignable_v<FirstType, OtherFirstType&&>&&
				std::is_nothrow_constructible_v<FirstType, OtherFirstType&&>&&
				std::is_nothrow_destructible_v<FirstType>
				)
		{
			this->template assign_from_helper<dynamic_states>(state, std::forward<OtherFirstType>(other));
			return *this;
		}

		template <dynamic_states_t DynamicStates = dynamic_states, typename OtherFirstType>
			requires
		(
			!std::is_same_v<std::remove_cvref_t<OtherFirstType>, single>
			)
			constexpr single &&assign_from(const state_t state, const state_t other_state, OtherFirstType &&other) &&
			noexcept
			(
				std::is_nothrow_assignable_v<FirstType, OtherFirstType&&>&&
				std::is_nothrow_constructible_v<FirstType, OtherFirstType&&>&&
				std::is_nothrow_destructible_v<FirstType>
				)
		{
			this->template assign_from_helper<dynamic_states>(state, std::forward<OtherFirstType>(other));
			return *this;
		}

	private:

		template <state_t State = state_t::unknown, typename ...ArgsTypes>
		constexpr void emplace_from_helper(ArgsTypes &&...args)
			noexcept
			(
				(
					(
						State == state_t::initialized ||
						State == state_t::unknown
						) &&
					std::is_nothrow_constructible_v<FirstType, ArgsTypes &&...>&&
					std::is_nothrow_destructible_v<FirstType>
					) ||
				(
					State == state_t::uninitialized &&
					std::is_nothrow_constructible_v<FirstType, ArgsTypes &&...>
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
		constexpr single& emplace_from(ArgsTypes &&...args) &
			noexcept
			(
				(
					(
						State == state_t::initialized ||
						State == state_t::unknown
						) &&
					std::is_nothrow_constructible_v<FirstType, ArgsTypes &&...>&&
					std::is_nothrow_destructible_v<FirstType>
					) ||
				(
					State == state_t::uninitialized &&
					std::is_nothrow_constructible_v<FirstType, ArgsTypes &&...>
					)
				)
		{
			this->template emplace_from_helper<State>(std::forward<ArgsTypes>(args)...);
			return *this;
		}

		template <state_t State = state_t::unknown, typename ...ArgsTypes>
		constexpr single &&emplace_from(ArgsTypes &&...args) &&
			noexcept
			(
				(
					(
						State == state_t::initialized ||
						State == state_t::unknown
						) &&
					std::is_nothrow_constructible_v<FirstType, ArgsTypes &&...>&&
					std::is_nothrow_destructible_v<FirstType>
					) ||
				(
					State == state_t::uninitialized &&
					std::is_nothrow_constructible_v<FirstType, ArgsTypes &&...>
					)
				)
		{
			this->template emplace_from_helper<State>(std::forward<ArgsTypes>(args)...);
			return *this;
		}

	private:

		template <dynamic_states_t DynamicStates = dynamic_states, typename ...ArgsTypes>
		constexpr void emplace_from_helper(const state_t state, ArgsTypes &&...args)
			noexcept
			(
				std::is_nothrow_constructible_v<FirstType, ArgsTypes &&...>&&
				std::is_nothrow_destructible_v<FirstType>
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

		template <dynamic_states_t DynamicStates = dynamic_states, typename ...ArgsTypes>
		constexpr single& emplace_from(const state_t state, ArgsTypes &&...args) &
			noexcept
			(
				std::is_nothrow_constructible_v<FirstType, ArgsTypes &&...>&&
				std::is_nothrow_destructible_v<FirstType>
				)
		{
			this->template emplace_from_helper<dynamic_states>(state, std::forward<ArgsTypes>(args)...);
			return *this;
		}

		template <dynamic_states_t DynamicStates = dynamic_states, typename ...ArgsTypes>
		constexpr single &&emplace_from(const state_t state, ArgsTypes &&...args) &&
			noexcept
			(
				std::is_nothrow_constructible_v<FirstType, ArgsTypes &&...>&&
				std::is_nothrow_destructible_v<FirstType>
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
			single emplaced_from(ArgsTypes &&...args)
			noexcept
			(
				std::is_nothrow_constructible_v<FirstType, ArgsTypes &&...>
				)
		{
			single temp{ noinit };
			temp.template emplace_from<state_t::uninitialized>(std::forward<ArgsTypes>(args)...);
			return std::move(temp);
		}

	private:

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown>
		constexpr void copy_from_helper(const single& other)
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
								std::is_nothrow_copy_assignable_v<FirstType> ||
								(
									!std::is_copy_assignable_v<FirstType> &&
									std::is_nothrow_copy_constructible_v<FirstType> &&
									std::is_nothrow_destructible_v<FirstType>
									)
								)
							) ||
						OtherState == state_t::uninitialized
						)
					) ||
				(
					State == state_t::uninitialized &&
					(
						(
							(
								OtherState == state_t::initialized ||
								OtherState == state_t::unknown
								) &&
							std::is_nothrow_copy_constructible_v<FirstType>
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
					if constexpr (std::is_copy_assignable_v<FirstType>)
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
		constexpr single& copy_from(const single& other) &
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
								std::is_nothrow_copy_assignable_v<FirstType> ||
								(
									!std::is_copy_assignable_v<FirstType> &&
									std::is_nothrow_copy_constructible_v<FirstType> &&
									std::is_nothrow_destructible_v<FirstType>
									)
								)
							) ||
						OtherState == state_t::uninitialized
						)
					) ||
				(
					State == state_t::uninitialized &&
					(
						(
							(
								OtherState == state_t::initialized ||
								OtherState == state_t::unknown
								) &&
							std::is_nothrow_copy_constructible_v<FirstType>
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
		constexpr single &&copy_from(const single& other) &&
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
								std::is_nothrow_copy_assignable_v<FirstType> ||
								(
									!std::is_copy_assignable_v<FirstType> &&
									std::is_nothrow_copy_constructible_v<FirstType> &&
									std::is_nothrow_destructible_v<FirstType>
									)
								)
							) ||
						OtherState == state_t::uninitialized
						)
					) ||
				(
					State == state_t::uninitialized &&
					(
						(
							(
								OtherState == state_t::initialized ||
								OtherState == state_t::unknown
								) &&
							std::is_nothrow_copy_constructible_v<FirstType>
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

		template <dynamic_states_t DynamicStates = dynamic_states>
		constexpr void copy_from_helper(const state_t state, const state_t other_state, const single& other)
			noexcept
			(
				std::is_nothrow_copy_assignable_v<FirstType>&&
				std::is_nothrow_copy_constructible_v<FirstType>&&
				std::is_nothrow_destructible_v<FirstType>
				)
		{
			if (state == state_t::initialized || state == state_t::unknown)
			{
				if (other_state == state_t::initialized || other_state == state_t::unknown)
				{
					if constexpr (std::is_copy_assignable_v<FirstType>)
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

		template <dynamic_states_t DynamicStates = dynamic_states>
		constexpr single& copy_from(const state_t state, const state_t other_state, const single& other) &
			noexcept
			(
				std::is_nothrow_copy_assignable_v<FirstType>&&
				std::is_nothrow_copy_constructible_v<FirstType>&&
				std::is_nothrow_destructible_v<FirstType>
				)
		{
			this->copy_from_helper<dynamic_states>(state, other_state, other);
			return *this;
		}

		template <dynamic_states_t DynamicStates = dynamic_states>
		constexpr single &&copy_from(const state_t state, const state_t other_state, const single& other) &&
			noexcept
			(
				std::is_nothrow_copy_assignable_v<FirstType>&&
				std::is_nothrow_copy_constructible_v<FirstType>&&
				std::is_nothrow_destructible_v<FirstType>
				)
		{
			this->copy_from_helper<dynamic_states>(state, other_state, other);
			return *this;
		}

	private:

		template <state_t State = state_t::unknown, typename OtherFirstType>
			requires
		(
			!std::is_same_v<std::remove_cvref_t<OtherFirstType>, single>
			)
			constexpr void copy_from_helper(OtherFirstType &&other)
			noexcept
			(
				(
					(
						State == state_t::initialized ||
						State == state_t::unknown
						) &&
					std::is_nothrow_assignable_v<FirstType, OtherFirstType&&> &&
					(
						!std::is_copy_constructible_v<FirstType>&&
						std::is_nothrow_copy_constructible_v<FirstType>
						) &&
					std::is_nothrow_destructible_v<FirstType>
					) ||
				(
					State == state_t::uninitialized &&
					std::is_nothrow_copy_constructible_v<FirstType>
					)
				)
		{
			if constexpr (State == state_t::initialized || State == state_t::unknown)
			{
				if constexpr (std::is_assignable_v<FirstType, OtherFirstType&&>)
				{
					first = std::forward<OtherFirstType>(other);
				}
				else
				{
					std::destroy_at(std::addressof(first));
					std::construct_at(std::addressof(first), std::forward<OtherFirstType>(other));
				}
			}
			else
			{
				std::construct_at(std::addressof(first), std::forward<OtherFirstType>(other));
			}
		}

	public:

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown, typename OtherFirstType>
			requires
		(
			!std::is_same_v<std::remove_cvref_t<OtherFirstType>, single>
			)
			constexpr single& copy_from(OtherFirstType &&other) &
			noexcept
			(
				(
					(
						State == state_t::initialized ||
						State == state_t::unknown
						) &&
					std::is_nothrow_assignable_v<FirstType, OtherFirstType&&> &&
					(
						!std::is_copy_constructible_v<FirstType>&&
						std::is_nothrow_copy_constructible_v<FirstType>
						) &&
					std::is_nothrow_destructible_v<FirstType>
					) ||
				(
					State == state_t::uninitialized &&
					std::is_nothrow_copy_constructible_v<FirstType>
					)
				)
		{
			this->copy_from_helper<State>(std::forward<OtherFirstType>(other));
			return *this;
		}

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown, typename OtherFirstType>
			requires
		(
			!std::is_same_v<std::remove_cvref_t<OtherFirstType>, single>
			)
			constexpr single &&copy_from(OtherFirstType &&other) &&
			noexcept
			(
				(
					(
						State == state_t::initialized ||
						State == state_t::unknown
						) &&
					std::is_nothrow_assignable_v<FirstType, OtherFirstType&&> &&
					(
						!std::is_copy_constructible_v<FirstType>&&
						std::is_nothrow_copy_constructible_v<FirstType>
						) &&
					std::is_nothrow_destructible_v<FirstType>
					) ||
				(
					State == state_t::uninitialized &&
					std::is_nothrow_copy_constructible_v<FirstType>
					)
				)
		{
			this->copy_from_helper<State>(std::forward<OtherFirstType>(other));
			return *this;
		}

	private:

		template <dynamic_states_t DynamicStates = dynamic_states, typename OtherFirstType>
			requires
		(
			!std::is_same_v<std::remove_cvref_t<OtherFirstType>, single>
			)
			constexpr void copy_from_helper(const state_t state, const state_t other_state, OtherFirstType &&other)
			noexcept
			(
				std::is_nothrow_assignable_v<FirstType, OtherFirstType&&>&&
				std::is_nothrow_constructible_v<FirstType, OtherFirstType&&>&&
				std::is_nothrow_destructible_v<FirstType>
				)
		{
			if (state == state_t::initialized || state == state_t::unknown)
			{
				if (other_state == state_t::initialized || other_state == state_t::unknown)
				{
					if constexpr (std::is_assignable_v<FirstType, OtherFirstType&&>)
					{
						first = std::forward<OtherFirstType>(other);
					}
					else
					{
						std::destroy_at(std::addressof(first));
						std::construct_at(std::addressof(first), std::forward<OtherFirstType>(other));
					}
				}
			}
			else
			{
				std::construct_at(std::addressof(first), std::forward<OtherFirstType>(other));
			}
		}

	public:

		template <dynamic_states_t DynamicStates = dynamic_states, typename OtherFirstType>
			requires
		(
			!std::is_same_v<std::remove_cvref_t<OtherFirstType>, single>
			)
			constexpr single& copy_from(const state_t state, const state_t other_state, OtherFirstType &&other) &
			noexcept
			(
				std::is_nothrow_assignable_v<FirstType, OtherFirstType&&>&&
				std::is_nothrow_constructible_v<FirstType, OtherFirstType&&>&&
				std::is_nothrow_destructible_v<FirstType>
				)
		{
			this->copy_from_helper<dynamic_states>(state, other_state, std::forward<OtherFirstType>(other));
			return *this;
		}

		template <dynamic_states_t DynamicStates = dynamic_states, typename OtherFirstType>
			requires
		(
			!std::is_same_v<std::remove_cvref_t<OtherFirstType>, single>
			)
			constexpr single &&copy_from(const state_t state, const state_t other_state, OtherFirstType &&other) &&
			noexcept
			(
				std::is_nothrow_assignable_v<FirstType, OtherFirstType&&>&&
				std::is_nothrow_constructible_v<FirstType, OtherFirstType&&>&&
				std::is_nothrow_destructible_v<FirstType>
				)
		{
			this->copy_from_helper<dynamic_states>(state, other_state, std::forward<OtherFirstType>(other));
			return *this;
		}

		template <state_t OtherState = state_t::unknown>
		static
#if WOJ_HAS_CXX20
			consteval
#else
			constexpr
#endif
			single copied_from(const single& other)
			noexcept
			(
				std::is_nothrow_copy_constructible_v<FirstType>
				)
		{
			single temp{ noinit };
			temp.copy_from<state_t::uninitialized, OtherState>(other);
			return std::move(temp);
		}

		template <dynamic_states_t DynamicStates = dynamic_states>
		static
#if WOJ_HAS_CXX20
			consteval
#else
			constexpr
#endif
			single copied_from(const state_t other_state, const single& other)
			noexcept
			(
				std::is_nothrow_copy_constructible_v<FirstType>
				)
		{
			single temp{ noinit };
			temp.copy_from(state_t::uninitialized, other_state, other);
			return std::move(temp);
		}

		template <state_t OtherState = state_t::unknown, typename OtherFirstType>
			requires
		(
			!std::is_same_v<std::remove_cvref_t<OtherFirstType>, single>
			)
			static
#if WOJ_HAS_CXX20
			consteval
#else
			constexpr
#endif
			single copied_from(OtherFirstType &&other)
			noexcept
			(
				std::is_nothrow_constructible_v<FirstType, OtherFirstType&&>
				)
		{
			single temp{ noinit };
			temp.copy_from<state_t::uninitialized, OtherState>(std::forward<OtherFirstType>(other));
			return std::move(temp);
		}

		template <dynamic_states_t DynamicStates = dynamic_states, typename OtherFirstType>
			requires
		(
			!std::is_same_v<std::remove_cvref_t<OtherFirstType>, single>
			)
			static
#if WOJ_HAS_CXX20
			consteval
#else
			constexpr
#endif
			single copied_from(const state_t other_state, OtherFirstType &&other)
			noexcept
			(
				std::is_nothrow_constructible_v<FirstType, OtherFirstType&&>
				)
		{
			single temp{ noinit };
			temp.copy_from(state_t::uninitialized, other_state, std::forward<OtherFirstType>(other));
			return std::move(temp);
		}

	private:

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown, typename OtherSingleType>
			requires
		(
			std::is_same_v<std::remove_cvref_t<OtherSingleType>, single>
			)
			constexpr void copy_to_helper(OtherSingleType &&other) const
			noexcept
			(
				(
					(
						State == state_t::initialized ||
						State == state_t::unknown
						) &&
					(
						(
							OtherState == state_t::initialized &&
							(
								std::is_nothrow_copy_assignable_v<FirstType> ||
								(
									!std::is_copy_assignable_v<FirstType> &&
									std::is_nothrow_copy_constructible_v<FirstType>
									)
								)
							) ||
						(
							OtherState == state_t::uninitialized &&
							std::is_nothrow_copy_constructible_v<FirstType>
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
					if constexpr (std::is_copy_assignable_v<FirstType>)
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
			constexpr const single& copy_to(OtherSingleType &&other) const&
			noexcept
			(
				(
					(
						State == state_t::initialized ||
						State == state_t::unknown
						) &&
					(
						(
							OtherState == state_t::initialized &&
							(
								std::is_nothrow_copy_assignable_v<FirstType> ||
								(
									!std::is_copy_assignable_v<FirstType> &&
									std::is_nothrow_copy_constructible_v<FirstType>
									)
								)
							) ||
						(
							OtherState == state_t::uninitialized &&
							std::is_nothrow_copy_constructible_v<FirstType>
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
			constexpr single& copy_to(OtherSingleType &&other) &
			noexcept
			(
				(
					(
						State == state_t::initialized ||
						State == state_t::unknown
						) &&
					(
						(
							OtherState == state_t::initialized &&
							(
								std::is_nothrow_copy_assignable_v<FirstType> ||
								(
									!std::is_copy_assignable_v<FirstType> &&
									std::is_nothrow_copy_constructible_v<FirstType>
									)
								)
							) ||
						(
							OtherState == state_t::uninitialized &&
							std::is_nothrow_copy_constructible_v<FirstType>
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
			constexpr const single &&copy_to(OtherSingleType &&other) const&&
			noexcept
			(
				(
					(
						State == state_t::initialized ||
						State == state_t::unknown
						) &&
					(
						(
							OtherState == state_t::initialized &&
							(
								std::is_nothrow_copy_assignable_v<FirstType> ||
								(
									!std::is_copy_assignable_v<FirstType> &&
									std::is_nothrow_copy_constructible_v<FirstType>
									)
								)
							) ||
						(
							OtherState == state_t::uninitialized &&
							std::is_nothrow_copy_constructible_v<FirstType>
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
			constexpr single &&copy_to(OtherSingleType &&other) &&
			noexcept
			(
				(
					(
						State == state_t::initialized ||
						State == state_t::unknown
						) &&
					(
						(
							OtherState == state_t::initialized &&
							(
								std::is_nothrow_copy_assignable_v<FirstType> ||
								(
									!std::is_copy_assignable_v<FirstType> &&
									std::is_nothrow_copy_constructible_v<FirstType>
									)
								)
							) ||
						(
							OtherState == state_t::uninitialized &&
							std::is_nothrow_copy_constructible_v<FirstType>
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

		template <dynamic_states_t DynamicStates = dynamic_states, typename OtherSingleType>
			requires
		(
			std::is_same_v<std::remove_cvref_t<OtherSingleType>, single>
			)
			constexpr void copy_to_helper(const state_t state, const state_t other_state, OtherSingleType &&other) const
			noexcept
			(
				std::is_nothrow_copy_assignable_v<FirstType>&&
				std::is_nothrow_copy_constructible_v<FirstType>&&
				std::is_nothrow_destructible_v<FirstType>
				)
		{
			if (state == state_t::initialized || state == state_t::unknown)
			{
				if (other_state == state_t::initialized)
				{
					if constexpr (std::is_copy_assignable_v<FirstType>)
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

		template <dynamic_states_t DynamicStates = dynamic_states, typename OtherSingleType>
			requires
		(
			std::is_same_v<std::remove_cvref_t<OtherSingleType>, single>
			)
			constexpr const single& copy_to(const state_t state, const state_t other_state, OtherSingleType &&other) const&
			noexcept
			(
				std::is_nothrow_copy_assignable_v<FirstType>&&
				std::is_nothrow_copy_constructible_v<FirstType>&&
				std::is_nothrow_destructible_v<FirstType>
				)
		{
			this->template copy_to_helper<dynamic_states>(state, other_state, std::forward<OtherSingleType>(other));
			return *this;
		}

		template <dynamic_states_t DynamicStates = dynamic_states, typename OtherSingleType>
			requires
		(
			std::is_same_v<std::remove_cvref_t<OtherSingleType>, single>
			)
			constexpr single& copy_to(const state_t state, const state_t other_state, OtherSingleType &&other) &
			noexcept
			(
				std::is_nothrow_copy_assignable_v<FirstType>&&
				std::is_nothrow_copy_constructible_v<FirstType>&&
				std::is_nothrow_destructible_v<FirstType>
				)
		{
			this->template copy_to_helper<dynamic_states>(state, other_state, std::forward<OtherSingleType>(other));
			return *this;
		}

		template <dynamic_states_t DynamicStates = dynamic_states, typename OtherSingleType>
			requires
		(
			std::is_same_v<std::remove_cvref_t<OtherSingleType>, single>
			)
			constexpr const single &&copy_to(const state_t state, const state_t other_state, OtherSingleType &&other) const&&
			noexcept
			(
				std::is_nothrow_copy_assignable_v<FirstType>&&
				std::is_nothrow_copy_constructible_v<FirstType>&&
				std::is_nothrow_destructible_v<FirstType>
				)
		{
			this->template copy_to_helper<dynamic_states>(state, other_state, std::forward<OtherSingleType>(other));
			return *this;
		}

		template <dynamic_states_t DynamicStates = dynamic_states, typename OtherSingleType>
			requires
		(
			std::is_same_v<std::remove_cvref_t<OtherSingleType>, single>
			)
			constexpr single &&copy_to(const state_t state, const state_t other_state, OtherSingleType &&other) &&
			noexcept
			(
				std::is_nothrow_copy_assignable_v<FirstType>&&
				std::is_nothrow_copy_constructible_v<FirstType>&&
				std::is_nothrow_destructible_v<FirstType>
				)
		{
			this->template copy_to_helper<dynamic_states>(state, other_state, std::forward<OtherSingleType>(other));
			return *this;
		}

	private:

		template <state_t State = state_t::unknown, typename OtherFirstType>
			requires
		(
			!std::is_same_v<std::remove_cvref_t<OtherFirstType>, single>
			)
			constexpr void copy_to_helper(OtherFirstType &&other) const
			noexcept
			(
				(
					(
						State == state_t::uninitialized || State == state_t::unknown
						) &&
					(
						std::is_nothrow_assignable_v<FirstType, OtherFirstType&&> ||
						(
							!std::is_assignable_v<FirstType, OtherFirstType&&> &&
							std::is_nothrow_constructible_v<FirstType, OtherFirstType&&> &&
							std::is_nothrow_destructible_v<FirstType>
							)
						)
					) ||
				State == state_t::uninitialized
				)
		{
			if constexpr (State == state_t::initialized || State == state_t::unknown)
			{
				if constexpr (std::is_assignable_v<FirstType, OtherFirstType&&>)
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

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown, typename OtherFirstType>
			requires
		(
			!std::is_same_v<std::remove_cvref_t<OtherFirstType>, single>
			)
			constexpr const single& copy_to(OtherFirstType &&other) const&
			noexcept
			(
				(
					(
						State == state_t::uninitialized || State == state_t::unknown
						) &&
					(
						std::is_nothrow_assignable_v<FirstType, OtherFirstType&&> ||
						(
							!std::is_assignable_v<FirstType, OtherFirstType&&> &&
							std::is_nothrow_constructible_v<FirstType, OtherFirstType&&> &&
							std::is_nothrow_destructible_v<FirstType>
							)
						)
					) ||
				State == state_t::uninitialized
				)
		{
			this->template copy_to_helper<State>(std::forward<OtherFirstType>(other));

			return *this;
		}

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown, typename OtherFirstType>
			requires
		(
			!std::is_same_v<std::remove_cvref_t<OtherFirstType>, single>
			)
			constexpr single& copy_to(OtherFirstType &&other) &
			noexcept
			(
				(
					(
						State == state_t::uninitialized || State == state_t::unknown
						) &&
					(
						std::is_nothrow_assignable_v<FirstType, OtherFirstType&&> ||
						(
							!std::is_assignable_v<FirstType, OtherFirstType&&> &&
							std::is_nothrow_constructible_v<FirstType, OtherFirstType&&> &&
							std::is_nothrow_destructible_v<FirstType>
							)
						)
					) ||
				State == state_t::uninitialized
				)
		{
			this->template copy_to_helper<State>(std::forward<OtherFirstType>(other));

			return *this;
		}

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown, typename OtherFirstType>
			requires
		(
			!std::is_same_v<std::remove_cvref_t<OtherFirstType>, single>
			)
			constexpr const single &&copy_to(OtherFirstType &&other) const&&
			noexcept
			(
				(
					(
						State == state_t::uninitialized || State == state_t::unknown
						) &&
					(
						std::is_nothrow_assignable_v<FirstType, OtherFirstType&&> ||
						(
							!std::is_assignable_v<FirstType, OtherFirstType&&> &&
							std::is_nothrow_constructible_v<FirstType, OtherFirstType&&> &&
							std::is_nothrow_destructible_v<FirstType>
							)
						)
					) ||
				State == state_t::uninitialized
				)
		{
			this->template copy_to_helper<State>(std::forward<OtherFirstType>(other));

			return *this;
		}

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown, typename OtherFirstType>
			requires
		(
			!std::is_same_v<std::remove_cvref_t<OtherFirstType>, single>
			)
			constexpr single &&copy_to(OtherFirstType &&other) &&
			noexcept
			(
				(
					(
						State == state_t::uninitialized || State == state_t::unknown
						) &&
					(
						std::is_nothrow_assignable_v<FirstType, OtherFirstType&&> ||
						(
							!std::is_assignable_v<FirstType, OtherFirstType&&> &&
							std::is_nothrow_constructible_v<FirstType, OtherFirstType&&> &&
							std::is_nothrow_destructible_v<FirstType>
							)
						)
					) ||
				State == state_t::uninitialized
				)
		{
			this->template copy_to_helper<State>(std::forward<OtherFirstType>(other));

			return *this;
		}

	private:

		template <dynamic_states_t DynamicStates = dynamic_states, typename OtherFirstType>
			requires
		(
			!std::is_same_v<std::remove_cvref_t<OtherFirstType>, single>
			)
			constexpr void copy_to_helper(const state_t state, OtherFirstType &&other) const
			noexcept
			(
				std::is_nothrow_assignable_v<FirstType, OtherFirstType&&>&&
				std::is_nothrow_copy_constructible_v<FirstType>&&
				std::is_nothrow_destructible_v<FirstType>
				)
		{
			if (state == state_t::initialized || state == state_t::unknown)
			{
				if constexpr (std::is_assignable_v<FirstType, OtherFirstType&&>)
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

		template <dynamic_states_t DynamicStates = dynamic_states, typename OtherFirstType>
			requires
		(
			!std::is_same_v<std::remove_cvref_t<OtherFirstType>, single>
			)
			constexpr const single& copy_to(const state_t state, const state_t other_state, OtherFirstType &&other) const&
			noexcept
			(
				std::is_nothrow_assignable_v<FirstType, OtherFirstType&&>&&
				std::is_nothrow_copy_constructible_v<FirstType>&&
				std::is_nothrow_destructible_v<FirstType>
				)
		{
			this->template copy_to_helper<dynamic_states>(state, std::forward<OtherFirstType>(other));
			return *this;
		}

		template <dynamic_states_t DynamicStates = dynamic_states, typename OtherFirstType>
			requires
		(
			!std::is_same_v<std::remove_cvref_t<OtherFirstType>, single>
			)
			constexpr single& copy_to(const state_t state, const state_t other_state, OtherFirstType &&other) &
			noexcept
			(
				std::is_nothrow_assignable_v<FirstType, OtherFirstType&&>&&
				std::is_nothrow_copy_constructible_v<FirstType>&&
				std::is_nothrow_destructible_v<FirstType>
				)
		{
			this->template copy_to_helper<dynamic_states>(state, std::forward<OtherFirstType>(other));
			return *this;
		}

		template <dynamic_states_t DynamicStates = dynamic_states, typename OtherFirstType>
			requires
		(
			!std::is_same_v<std::remove_cvref_t<OtherFirstType>, single>
			)
			constexpr const single &&copy_to(const state_t state, const state_t other_state, OtherFirstType &&other) const&&
			noexcept
			(
				std::is_nothrow_assignable_v<FirstType, OtherFirstType&&>&&
				std::is_nothrow_copy_constructible_v<FirstType>&&
				std::is_nothrow_destructible_v<FirstType>
				)
		{
			this->template copy_to_helper<dynamic_states>(state, std::forward<OtherFirstType>(other));
			return *this;
		}

		template <dynamic_states_t DynamicStates = dynamic_states, typename OtherFirstType>
			requires
		(
			!std::is_same_v<std::remove_cvref_t<OtherFirstType>, single>
			)
			constexpr single &&copy_to(const state_t state, const state_t other_state, OtherFirstType &&other) &&
			noexcept
			(
				std::is_nothrow_assignable_v<FirstType, OtherFirstType&&>&&
				std::is_nothrow_copy_constructible_v<FirstType>&&
				std::is_nothrow_destructible_v<FirstType>
				)
		{
			this->template copy_to_helper<dynamic_states>(state, std::forward<OtherFirstType>(other));
			return *this;
		}

	private:

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown, typename OtherSingleType>
			requires
		(
			std::is_same_v<std::remove_cvref_t<OtherSingleType>, single>
			)
			constexpr void move_from_helper(OtherSingleType &&other)
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
								std::is_nothrow_move_assignable_v<FirstType> ||
								(
									!std::is_move_assignable_v<FirstType> &&
									std::is_nothrow_move_constructible_v<FirstType> &&
									std::is_nothrow_destructible_v<FirstType>
									)
								)
							) ||
						OtherState == state_t::uninitialized
						)
					) ||
				(
					State == state_t::uninitialized &&
					(
						(
							(
								OtherState == state_t::initialized ||
								OtherState == state_t::unknown
								) &&
							std::is_nothrow_move_constructible_v<FirstType>
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
				if constexpr (std::is_move_assignable_v<FirstType>)
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
			constexpr single& move_from(OtherSingleType &&other) &
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
								std::is_nothrow_move_assignable_v<FirstType> ||
								(
									!std::is_move_assignable_v<FirstType> &&
									std::is_nothrow_move_constructible_v<FirstType> &&
									std::is_nothrow_destructible_v<FirstType>
									)
								)
							) ||
						OtherState == state_t::uninitialized
						)
					) ||
				(
					State == state_t::uninitialized &&
					(
						(
							(
								OtherState == state_t::initialized ||
								OtherState == state_t::unknown
								) &&
							std::is_nothrow_move_constructible_v<FirstType>
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
			constexpr single &&move_from(OtherSingleType &&other) &&
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
								std::is_nothrow_move_assignable_v<FirstType> ||
								(
									!std::is_move_assignable_v<FirstType> &&
									std::is_nothrow_move_constructible_v<FirstType> &&
									std::is_nothrow_destructible_v<FirstType>
									)
								)
							) ||
						OtherState == state_t::uninitialized
						)
					) ||
				(
					State == state_t::uninitialized &&
					(
						(
							(
								OtherState == state_t::initialized ||
								OtherState == state_t::unknown
								) &&
							std::is_nothrow_move_constructible_v<FirstType>
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

		template <dynamic_states_t DynamicStates = dynamic_states, typename OtherSingleType>
			requires
		(
			std::is_same_v<std::remove_cvref_t<OtherSingleType>, single>
			)
			constexpr void move_from_helper(const state_t state, const state_t other_state, OtherSingleType &&other)
			noexcept
			(
				std::is_nothrow_move_assignable_v<FirstType>&&
				std::is_nothrow_move_constructible_v<FirstType>&&
				std::is_nothrow_destructible_v<FirstType>
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
				if constexpr (std::is_move_assignable_v<FirstType>)
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

		template <dynamic_states_t DynamicStates = dynamic_states, typename OtherSingleType>
			requires
		(
			std::is_same_v<std::remove_cvref_t<OtherSingleType>, single>
			)
			constexpr single& move_from(const state_t state, const state_t other_state, OtherSingleType &&other) &
			noexcept
			(
				std::is_nothrow_move_assignable_v<FirstType>&&
				std::is_nothrow_move_constructible_v<FirstType>&&
				std::is_nothrow_destructible_v<FirstType>
				)
		{
			this->template move_from_helper<dynamic_states>(state, other_state, std::forward<OtherSingleType>(other));
			return *this;
		}

		template <dynamic_states_t DynamicStates = dynamic_states, typename OtherSingleType>
			requires
		(
			std::is_same_v<std::remove_cvref_t<OtherSingleType>, single>
			)
			constexpr single &&move_from(const state_t state, const state_t other_state, OtherSingleType &&other) &&
			noexcept
			(
				std::is_nothrow_move_assignable_v<FirstType>&&
				std::is_nothrow_move_constructible_v<FirstType>&&
				std::is_nothrow_destructible_v<FirstType>
				)
		{
			this->template move_from_helper<dynamic_states>(state, other_state, std::forward<OtherSingleType>(other));
			return *this;
		}

	private:

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown, typename OtherFirstType>
			requires
		(
			!std::is_same_v<std::remove_cvref_t<OtherFirstType>, single>
			)
			constexpr void move_from_helper(OtherFirstType &&other)
			noexcept
			(
				(
					(
						State == state_t::initialized ||
						State == state_t::unknown
						) &&
					(
						std::is_nothrow_assignable_v<FirstType, OtherFirstType&&> ||
						(
							!std::is_assignable_v<FirstType, OtherFirstType&&> &&
							std::is_nothrow_constructible_v<FirstType, OtherFirstType&&> &&
							std::is_nothrow_destructible_v<FirstType>
							)
						)
					) ||
				(
					State == state_t::uninitialized &&
					std::is_nothrow_constructible_v<FirstType, OtherFirstType&&>
					)
				)
		{
			if constexpr (State == state_t::initialized || State == state_t::unknown)
			{
				if constexpr (std::is_assignable_v<FirstType, OtherFirstType&&>)
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

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown, typename OtherFirstType>
			requires
		(
			!std::is_same_v<std::remove_cvref_t<OtherFirstType>, single>
			)
			constexpr single& move_from(OtherFirstType &&other) &
			noexcept
			(
				(
					(
						State == state_t::initialized ||
						State == state_t::unknown
						) &&
					(
						std::is_nothrow_assignable_v<FirstType, OtherFirstType&&> ||
						(
							!std::is_assignable_v<FirstType, OtherFirstType&&> &&
							std::is_nothrow_constructible_v<FirstType, OtherFirstType&&> &&
							std::is_nothrow_destructible_v<FirstType>
							)
						)
					) ||
				(
					State == state_t::uninitialized &&
					std::is_nothrow_constructible_v<FirstType, OtherFirstType&&>
					)
				)
		{
			this->template move_from_helper<State, OtherState>(std::forward<OtherFirstType>(other));
			return *this;
		}

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown, typename OtherFirstType>
			requires
		(
			!std::is_same_v<std::remove_cvref_t<OtherFirstType>, single>
			)
			constexpr single &&move_from(OtherFirstType &&other) &&
			noexcept
			(
				(
					(
						State == state_t::initialized ||
						State == state_t::unknown
						) &&
					(
						std::is_nothrow_assignable_v<FirstType, OtherFirstType&&> ||
						(
							!std::is_assignable_v<FirstType, OtherFirstType&&> &&
							std::is_nothrow_constructible_v<FirstType, OtherFirstType&&> &&
							std::is_nothrow_destructible_v<FirstType>
							)
						)
					) ||
				(
					State == state_t::uninitialized &&
					std::is_nothrow_constructible_v<FirstType, OtherFirstType&&>
					)
				)
		{
			this->template move_from_helper<State, OtherState>(std::forward<OtherFirstType>(other));
			return *this;
		}

	private:

		template <dynamic_states_t DynamicStates = dynamic_states, typename OtherFirstType>
			requires
		(
			!std::is_same_v<std::remove_cvref_t<OtherFirstType>, single>
			)
			constexpr void move_from_helper(const state_t state, const state_t other_state, OtherFirstType &&other)
			noexcept
			(
				std::is_nothrow_assignable_v<FirstType, OtherFirstType&&>&&
				std::is_nothrow_move_constructible_v<FirstType>&&
				std::is_nothrow_destructible_v<FirstType>
				)
		{
			if (state == state_t::initialized || state == state_t::unknown)
			{
				if constexpr (std::is_assignable_v<FirstType, OtherFirstType&&>)
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

		template <dynamic_states_t DynamicStates = dynamic_states, typename OtherFirstType>
			requires
		(
			!std::is_same_v<std::remove_cvref_t<OtherFirstType>, single>
			)
			constexpr single& move_from(const state_t state, const state_t other_state, OtherFirstType &&other)
			noexcept
			(
				std::is_nothrow_assignable_v<FirstType, OtherFirstType&&>&&
				std::is_nothrow_move_constructible_v<FirstType>&&
				std::is_nothrow_destructible_v<FirstType>
				)
		{
			if (state == state_t::initialized || state == state_t::unknown)
			{
				if (other_state == state_t::initialized || other_state == state_t::unknown)
				{
					if constexpr (std::is_assignable_v<FirstType, OtherFirstType&&>)
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
			single moved_from(OtherSingleType &&other)
			noexcept
			(
				std::is_nothrow_move_constructible_v<FirstType>
				)
		{
			single temp{ noinit };
			temp.template move_from<state_t::uninitialized, OtherState>(std::forward<OtherSingleType>(other));
			return std::move(temp);
		}

		template <dynamic_states_t DynamicStates = dynamic_states, typename OtherSingleType>
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
			single moved_from(const state_t other_state, OtherSingleType &&other)
			noexcept
			(
				std::is_nothrow_move_constructible_v<FirstType>
				)
		{
			single temp{ noinit };
			temp.move_from(state_t::uninitialized, other_state, std::forward<OtherSingleType>(other));
			return std::move(temp);
		}

		template <state_t OtherState = state_t::unknown, typename OtherFirstType>
			requires
		(
			!std::is_same_v<std::remove_cvref_t<OtherFirstType>, single>
			)
			static
#if WOJ_HAS_CXX20
			consteval
#else
			constexpr
#endif
			single moved_from(OtherFirstType &&other)
			noexcept
			(
				std::is_nothrow_constructible_v<FirstType, OtherFirstType&&>
				)
		{
			single temp{ noinit };
			temp.template move_from<state_t::uninitialized, OtherState>(std::forward<OtherFirstType>(other));
			return std::move(temp);
		}

		template <dynamic_states_t DynamicStates = dynamic_states, typename OtherFirstType>
			requires
		(
			!std::is_same_v<std::remove_cvref_t<OtherFirstType>, single>
			)
			static
#if WOJ_HAS_CXX20
			consteval
#else
			constexpr
#endif
			single moved_from(const state_t other_state, OtherFirstType &&other)
			noexcept
			(
				std::is_nothrow_constructible_v<FirstType, OtherFirstType&&>
				)
		{
			single temp{ noinit };
			temp.move_from(state_t::uninitialized, other_state, std::forward<OtherFirstType>(other));
			return std::move(temp);
		}

	private:

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown, typename OtherSingleType>
			requires
		(
			std::is_same_v<std::remove_cvref_t<OtherSingleType>, single>
			)
			constexpr void move_to_helper(OtherSingleType &&other) const
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
							std::is_nothrow_move_assignable_v<FirstType>
							) ||
						(
							OtherState == state_t::uninitialized &&
							std::is_nothrow_move_constructible_v<FirstType>
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
					if constexpr (std::is_move_assignable_v<FirstType>)
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
			constexpr const single& move_to(OtherSingleType &&other) const&
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
							std::is_nothrow_move_assignable_v<FirstType>
							) ||
						(
							OtherState == state_t::uninitialized &&
							std::is_nothrow_move_constructible_v<FirstType>
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
			constexpr single& move_to(OtherSingleType &&other) &
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
							std::is_nothrow_move_assignable_v<FirstType>
							) ||
						(
							OtherState == state_t::uninitialized &&
							std::is_nothrow_move_constructible_v<FirstType>
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
			constexpr const single &&move_to(OtherSingleType &&other) const&&
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
							std::is_nothrow_move_assignable_v<FirstType>
							) ||
						(
							OtherState == state_t::uninitialized &&
							std::is_nothrow_move_constructible_v<FirstType>
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
			constexpr single &&move_to(OtherSingleType &&other) &&
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
							std::is_nothrow_move_assignable_v<FirstType>
							) ||
						(
							OtherState == state_t::uninitialized &&
							std::is_nothrow_move_constructible_v<FirstType>
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

		template <dynamic_states_t DynamicStates = dynamic_states, typename OtherSingleType>
			requires
		(
			std::is_same_v<std::remove_cvref_t<OtherSingleType>, single>
			)
			constexpr void move_to_helper(const state_t state, const state_t other_state, OtherSingleType &&other) const
			noexcept
			(
				std::is_nothrow_move_assignable_v<FirstType>&&
				std::is_nothrow_move_constructible_v<FirstType>&&
				std::is_nothrow_destructible_v<FirstType>
				)
		{
			if (state == state_t::initialized || state == state_t::unknown)
			{
				if (other_state == state_t::initialized || other_state == state_t::unknown)
				{
					if constexpr (std::is_move_assignable_v<FirstType>)
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

		template <dynamic_states_t DynamicStates = dynamic_states, typename OtherSingleType>
			requires
		(
			std::is_same_v<std::remove_cvref_t<OtherSingleType>, single>
			)
			constexpr const single& move_to(const state_t state, const state_t other_state, OtherSingleType &&other) const&
			noexcept
			(
				std::is_nothrow_move_assignable_v<FirstType>&&
				std::is_nothrow_move_constructible_v<FirstType>&&
				std::is_nothrow_destructible_v<FirstType>
				)
		{
			this->template move_to_helper<dynamic_states>(state, other_state, std::forward<OtherSingleType>(other));
			return *this;
		}

		template <dynamic_states_t DynamicStates = dynamic_states, typename OtherSingleType>
			requires
		(
			std::is_same_v<std::remove_cvref_t<OtherSingleType>, single>
			)
			constexpr single& move_to(const state_t state, const state_t other_state, OtherSingleType &&other) &
			noexcept
			(
				std::is_nothrow_move_assignable_v<FirstType>&&
				std::is_nothrow_move_constructible_v<FirstType>&&
				std::is_nothrow_destructible_v<FirstType>
				)
		{
			this->template move_to_helper<dynamic_states>(state, other_state, std::forward<OtherSingleType>(other));
			return *this;
		}

		template <dynamic_states_t DynamicStates = dynamic_states, typename OtherSingleType>
			requires
		(
			std::is_same_v<std::remove_cvref_t<OtherSingleType>, single>
			)
			constexpr const single &&move_to(const state_t state, const state_t other_state, OtherSingleType &&other) const&&
			noexcept
			(
				std::is_nothrow_move_assignable_v<FirstType>&&
				std::is_nothrow_move_constructible_v<FirstType>&&
				std::is_nothrow_destructible_v<FirstType>
				)
		{
			this->template move_to_helper<dynamic_states>(state, other_state, std::forward<OtherSingleType>(other));
			return *this;
		}

		template <dynamic_states_t DynamicStates = dynamic_states, typename OtherSingleType>
			requires
		(
			std::is_same_v<std::remove_cvref_t<OtherSingleType>, single>
			)
			constexpr single &&move_to(const state_t state, const state_t other_state, OtherSingleType &&other) &&
			noexcept
			(
				std::is_nothrow_move_assignable_v<FirstType>&&
				std::is_nothrow_move_constructible_v<FirstType>&&
				std::is_nothrow_destructible_v<FirstType>
				)
		{
			this->template move_to_helper<dynamic_states>(state, other_state, std::forward<OtherSingleType>(other));
			return *this;
		}

	private:

		template <state_t State = state_t::unknown, typename OtherFirstType>
			requires
		(
			!std::is_same_v<std::remove_cvref_t<OtherFirstType>, single>
			)
			constexpr void move_to_helper(OtherFirstType &&other) const
			noexcept
			(
				(
					(
						State == state_t::initialized ||
						State == state_t::unknown
						) &&
					(
						std::is_nothrow_assignable_v<FirstType, OtherFirstType&&> ||
						(
							!std::is_assignable_v<FirstType, OtherFirstType&&> &&
							std::is_nothrow_constructible_v<FirstType, OtherFirstType&&> &&
							std::is_nothrow_destructible_v<FirstType>
							)
						)
					) ||
				State == state_t::uninitialized
				)
		{
			if constexpr (State == state_t::initialized || State == state_t::unknown)
			{
				if constexpr (std::is_assignable_v<FirstType, OtherFirstType&&>)
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

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown, typename OtherFirstType>
			requires
		(
			!std::is_same_v<std::remove_cvref_t<OtherFirstType>, single>
			)
			constexpr const single& move_to(OtherFirstType &&other) const&
			noexcept
			(
				(
					(
						State == state_t::initialized ||
						State == state_t::unknown
						) &&
					(
						std::is_nothrow_assignable_v<FirstType, OtherFirstType&&> ||
						(
							!std::is_assignable_v<FirstType, OtherFirstType&&> &&
							std::is_nothrow_constructible_v<FirstType, OtherFirstType&&> &&
							std::is_nothrow_destructible_v<FirstType>
							)
						)
					) ||
				State == state_t::uninitialized
				)
		{
			this->template move_to_helper<State>(std::forward<OtherFirstType>(other));
			return *this;
		}

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown, typename OtherFirstType>
			requires
		(
			!std::is_same_v<std::remove_cvref_t<OtherFirstType>, single>
			)
			constexpr single& move_to(OtherFirstType &&other) &
			noexcept
			(
				(
					(
						State == state_t::initialized ||
						State == state_t::unknown
						) &&
					(
						std::is_nothrow_assignable_v<FirstType, OtherFirstType&&> ||
						(
							!std::is_assignable_v<FirstType, OtherFirstType&&> &&
							std::is_nothrow_constructible_v<FirstType, OtherFirstType&&> &&
							std::is_nothrow_destructible_v<FirstType>
							)
						)
					) ||
				State == state_t::uninitialized
				)
		{
			this->template move_to_helper<State>(std::forward<OtherFirstType>(other));
			return *this;
		}

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown, typename OtherFirstType>
			requires
		(
			!std::is_same_v<std::remove_cvref_t<OtherFirstType>, single>
			)
			constexpr const single &&move_to(OtherFirstType &&other) const&&
			noexcept
			(
				(
					(
						State == state_t::initialized ||
						State == state_t::unknown
						) &&
					(
						std::is_nothrow_assignable_v<FirstType, OtherFirstType&&> ||
						(
							!std::is_assignable_v<FirstType, OtherFirstType&&> &&
							std::is_nothrow_constructible_v<FirstType, OtherFirstType&&> &&
							std::is_nothrow_destructible_v<FirstType>
							)
						)
					) ||
				State == state_t::uninitialized
				)
		{
			this->template move_to_helper<State>(std::forward<OtherFirstType>(other));
			return *this;
		}

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown, typename OtherFirstType>
			requires
		(
			!std::is_same_v<std::remove_cvref_t<OtherFirstType>, single>
			)
			constexpr single &&move_to(OtherFirstType &&other) &&
			noexcept
			(
				(
					(
						State == state_t::initialized ||
						State == state_t::unknown
						) &&
					(
						std::is_nothrow_assignable_v<FirstType, OtherFirstType&&> ||
						(
							!std::is_assignable_v<FirstType, OtherFirstType&&> &&
							std::is_nothrow_constructible_v<FirstType, OtherFirstType&&> &&
							std::is_nothrow_destructible_v<FirstType>
							)
						)
					) ||
				State == state_t::uninitialized
				)
		{
			this->template move_to_helper<State>(std::forward<OtherFirstType>(other));
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
						std::is_nothrow_destructible_v<FirstType>
						) ||
					State == state_t::uninitialized
					) &&
				(
					std::is_nothrow_default_constructible_v<FirstType> ||
					!std::is_default_constructible_v<FirstType>
					)
				)
		{
			if constexpr (State == state_t::initialized || State == state_t::unknown)
			{
				std::destroy_at(std::addressof(first));
			}
			if constexpr (std::is_default_constructible_v<FirstType>)
			{
				std::construct_at(std::addressof(first));
			}
		}

	public:

		template <state_t State = state_t::unknown>
		constexpr single& reset() &
			noexcept
			(
				(
					(
						(
							State == state_t::initialized ||
							State == state_t::unknown
							) &&
						std::is_nothrow_destructible_v<FirstType>
						) ||
					State == state_t::uninitialized
					) &&
				(
					std::is_nothrow_default_constructible_v<FirstType> ||
					!std::is_default_constructible_v<FirstType>
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
						std::is_nothrow_destructible_v<FirstType>
						) ||
					State == state_t::uninitialized
					) &&
				(
					std::is_nothrow_default_constructible_v<FirstType> ||
					!std::is_default_constructible_v<FirstType>
					)
				)
		{
			this->reset_helper<State>();
			return *this;
		}

	private:

		template <dynamic_states_t DynamicStates = dynamic_states>
		constexpr void reset_helper(const state_t state)
			noexcept
			(
				std::is_nothrow_destructible_v<FirstType>&&
				std::is_nothrow_default_constructible_v<FirstType>
				)
		{
			if (state == state_t::initialized || state == state_t::unknown)
			{
				std::destroy_at(std::addressof(first));
			}
			if constexpr (std::is_default_constructible_v<FirstType>)
			{
				std::construct_at(std::addressof(first));
			}
		}

	public:

		template <dynamic_states_t DynamicStates = dynamic_states>
		constexpr single& reset(const state_t state) &
			noexcept
			(
				std::is_nothrow_destructible_v<FirstType>&&
				std::is_nothrow_default_constructible_v<FirstType>
				)
		{
			this->reset_helper(state);
			return *this;
		}

		template <dynamic_states_t DynamicStates = dynamic_states>
		constexpr single &&reset(const state_t state) &&
			noexcept
			(
				std::is_nothrow_destructible_v<FirstType>&&
				std::is_nothrow_default_constructible_v<FirstType>
				)
		{
			this->reset_helper(state);
			return *this;
		}

		static constexpr single resetted()
			noexcept
			(
				std::is_nothrow_default_constructible_v<FirstType>
				)
		{
			single temp{ noinit };
			temp.reset<state_t::uninitialized>();
			return std::move(temp);
		}

		template <size_t Index>
		constexpr const FirstType& get() const&
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
		constexpr FirstType& get() &
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
		constexpr const FirstType &&get() const&&
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
		constexpr FirstType &&get() &&
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
		constexpr const FirstType& at() const&
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
		constexpr FirstType& at() &
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
		constexpr const FirstType &&at() const&&
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
		constexpr FirstType &&at() &&
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
			constexpr void swap_with_helper(OtherSingleType &&other)
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
							std::is_nothrow_swappable_v<FirstType>
							) ||
						(
							OtherState == state_t::uninitialized &&
							std::is_nothrow_move_constructible_v<FirstType>
							)
						)
					) ||
				(
					State == state_t::uninitialized &&
					(
						(
							(
								OtherState == state_t::initialized ||
								OtherState == state_t::unknown
								) &&
							std::is_nothrow_move_constructible_v<FirstType>
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
			constexpr single& swap_with(OtherSingleType &&other) &
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
							std::is_nothrow_swappable_v<FirstType>
							) ||
						(
							OtherState == state_t::uninitialized &&
							std::is_nothrow_move_constructible_v<FirstType>
							)
						)
					) ||
				(
					State == state_t::uninitialized &&
					(
						(
							(
								OtherState == state_t::initialized ||
								OtherState == state_t::unknown
								) &&
							std::is_nothrow_move_constructible_v<FirstType>
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
			constexpr single &&swap_with(OtherSingleType &&other) &&
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
							std::is_nothrow_swappable_v<FirstType>
							) ||
						(
							OtherState == state_t::uninitialized &&
							std::is_nothrow_move_constructible_v<FirstType>
							)
						)
					) ||
				(
					State == state_t::uninitialized &&
					(
						(
							(
								OtherState == state_t::initialized ||
								OtherState == state_t::unknown
								) &&
							std::is_nothrow_move_constructible_v<FirstType>
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

		template <dynamic_states_t DynamicStates = dynamic_states, typename OtherSingleType>
			requires
		(
			std::is_same_v<std::remove_cvref_t<OtherSingleType>, single>
			)
			constexpr void swap_with_helper(const state_t state, const state_t other_state, OtherSingleType &&other)
			noexcept
			(
				std::is_nothrow_swappable_v<FirstType>&&
				std::is_nothrow_move_constructible_v<FirstType>
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

		template <dynamic_states_t DynamicStates = dynamic_states, typename OtherSingleType>
			requires
		(
			std::is_same_v<std::remove_cvref_t<OtherSingleType>, single>
			)
			constexpr single& swap_with(const state_t state, const state_t other_state, OtherSingleType &&other) &
			noexcept
			(
				std::is_nothrow_swappable_v<FirstType>&&
				std::is_nothrow_move_constructible_v<FirstType>
				)
		{
			this->template swap_with_helper<dynamic_states>(state, other_state, std::forward<OtherSingleType>(other));
			return *this;
		}

		template <dynamic_states_t DynamicStates = dynamic_states, typename OtherSingleType>
			requires
		(
			std::is_same_v<std::remove_cvref_t<OtherSingleType>, single>
			)
			constexpr single &&swap_with(const state_t state, const state_t other_state, OtherSingleType &&other) &&
			noexcept
			(
				std::is_nothrow_swappable_v<FirstType>&&
				std::is_nothrow_move_constructible_v<FirstType>
				)
		{
			this->template swap_with_helper<dynamic_states>(state, other_state, std::forward<OtherSingleType>(other));
			return *this;
		}

	private:

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown, typename OtherFirstType>
			requires
		(
			!std::is_same_v<std::remove_cvref_t<OtherFirstType>, single>
			)
			constexpr void swap_with_helper(OtherFirstType &&other) const
			noexcept
			(
				(
					(
						State == state_t::initialized ||
						State == state_t::unknown
						) &&
					std::is_nothrow_swappable_v<FirstType>
					) ||
				(
					State == state_t::uninitialized &&
					std::is_nothrow_move_constructible_v<FirstType>
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

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown, typename OtherFirstType>
			requires
		(
			!std::is_same_v<std::remove_cvref_t<OtherFirstType>, single>
			)
			constexpr single& swap_with(OtherFirstType &&other) &
			noexcept
			(
				(
					(
						(
							State == state_t::initialized ||
							State == state_t::unknown
							) &&
						std::is_nothrow_swappable_v<FirstType>
						) ||
					(
						State == state_t::uninitialized &&
						std::is_nothrow_move_constructible_v<FirstType>
						)
					)
				)
		{
			this->template swap_with_helper<State>(std::forward<OtherFirstType>(other));
			return *this;
		}

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown, typename OtherFirstType>
			requires
		(
			!std::is_same_v<std::remove_cvref_t<OtherFirstType>, single>
			)
			constexpr single &&swap_with(OtherFirstType &&other) &&
			noexcept
			(
				(
					(
						State == state_t::initialized ||
						State == state_t::unknown
						) &&
					std::is_nothrow_swappable_v<FirstType>
					) ||
				(
					State == state_t::uninitialized &&
					std::is_nothrow_move_constructible_v<FirstType>
					)
				)
		{
			this->template swap_with_helper<State>(std::forward<OtherFirstType>(other));
			return *this;
		}

	private:

		template <dynamic_states_t DynamicStates = dynamic_states, typename OtherFirstType>
			requires
		(
			!std::is_same_v<std::remove_cvref_t<OtherFirstType>, single>
			)
			constexpr void swap_with_helper(const state_t state, const state_t other_state, OtherFirstType &&other) const
			noexcept
			(
				std::is_nothrow_swappable_v<FirstType>&&
				std::is_nothrow_move_constructible_v<FirstType>
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

		template <dynamic_states_t DynamicStates = dynamic_states, typename OtherFirstType>
			requires
		(
			!std::is_same_v<std::remove_cvref_t<OtherFirstType>, single>
			)
			constexpr single& swap_with(const state_t state, const state_t other_state, OtherFirstType &&other) &
			noexcept
			(
				std::is_nothrow_swappable_v<FirstType>&&
				std::is_nothrow_move_constructible_v<FirstType>
				)
		{
			this->template swap_with_helper<dynamic_states>(state, other_state, std::forward<OtherFirstType>(other));
			return *this;
		}

		template <dynamic_states_t DynamicStates = dynamic_states, typename OtherFirstType>
			requires
		(
			!std::is_same_v<std::remove_cvref_t<OtherFirstType>, single>
			)
			constexpr single &&swap_with(const state_t state, const state_t other_state, OtherFirstType &&other) &&
			noexcept
			(
				std::is_nothrow_swappable_v<FirstType>&&
				std::is_nothrow_move_constructible_v<FirstType>
				)
		{
			this->template swap_with_helper<dynamic_states>(state, other_state, std::forward<OtherFirstType>(other));
			return *this;
		}
	};

	/*template <typename FirstType, typename SecondType>
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
			FirstType first;
		};

		union
		{
			SecondType second;
		};

		using first_type = FirstType;
		using second_type = SecondType;

		constexpr pair()
			noexcept
			(
				std::is_nothrow_default_constructible_v<FirstType> &&
				std::is_nothrow_default_constructible_v<SecondType>
			)
			: first{}, second{} {
		}

		explicit constexpr pair(const noinit_t noinit)
			noexcept {}

		template <typename OtherFirstType, typename OtherSecondType>
			requires
			(
				!std::is_same_v<std::remove_cvref_t<OtherFirstType>, in_place_t>
			)
		explicit constexpr pair(OtherFirstType &&first, OtherSecondType &&second)
			noexcept
			(
				std::is_nothrow_constructible_v<FirstType, OtherFirstType &&> &&
				std::is_nothrow_constructible_v<SecondType, OtherSecondType &&>
			)
			: first{ std::forward<OtherFirstType>(first) }, second{ std::forward<OtherSecondType>(second) } {}

		template <typename OtherPairType>
			requires
			(
				!std::is_same_v<std::remove_cvref_t<OtherPairType>, noinit_t> &&
				!std::is_same_v<std::remove_cvref_t<OtherPairType>, in_place_t>
			)
		explicit constexpr pair(OtherPairType &&other)
			noexcept
			(
				std::is_nothrow_constructible_v<FirstType, typename OtherPairType::first_type &&>&&
				std::is_nothrow_constructible_v<SecondType, typename OtherPairType::second_type &&>
				)
			: first{ std::forward<typename OtherPairType::first_type>(other.first) }, second{ std::forward<typename OtherPairType::second_type>(other.second) } {
		}

		template <typename OtherPairType>
			requires
			(
				!std::is_same_v<std::remove_cvref_t<OtherPairType>, noinit_t> &&
				!std::is_same_v<std::remove_cvref_t<OtherPairType>, in_place_t>
			)
		constexpr pair(const state_t other_state, OtherPairType &&other)
			noexcept
			(
				std::is_nothrow_constructible_v<FirstType, typename OtherPairType::first_type &&>&&
				std::is_nothrow_constructible_v<SecondType, typename OtherPairType::second_type &&>
			)
			: first{ std::forward<typename OtherPairType::first_type>(other.first) }, second{ std::forward<typename OtherPairType::second_type>(other.second) } {}

		template <typename ...FirstArgsValueTypes, typename ...SecondArgsTypes>
		explicit constexpr pair(const in_place_t in_place, FirstArgsValueTypes &&...args_first, const delimiter_t delimiter, SecondArgsTypes &&...args_second)
			noexcept
			(
				std::is_nothrow_constructible_v<FirstType, FirstArgsValueTypes &&...>&&
				std::is_nothrow_constructible_v<SecondType, SecondArgsTypes &&...>
				)
			: first{ std::forward<FirstArgsValueTypes>(args_first)... }, second{ std::forward<SecondArgsTypes>(args_second)... } {}

		template <typename OtherPairType>
		constexpr pair &operator=(OtherPairType &&other)
			noexcept
			(
				(
					std::is_nothrow_assignable_v<FirstType, typename OtherPairType::first_type &&> ||
					(
						!std::is_assignable_v<FirstType, typename OtherPairType::first_type &&> &&
						std::is_nothrow_constructible_v<FirstType, typename OtherPairType::first_type &&> &&
						std::is_nothrow_destructible_v<FirstType>
					)
				) &&
				(
					std::is_nothrow_assignable_v<SecondType, typename OtherPairType::second_type &&> ||
					(
						!std::is_assignable_v<SecondType, typename OtherPairType::second_type &&>&&
						std::is_nothrow_constructible_v<SecondType, typename OtherPairType::second_type &&>&&
						std::is_nothrow_destructible_v<SecondType>
					)
				)
			)
		{
			if constexpr (std::is_copy_assignable_v<FirstType>)
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
				std::is_nothrow_destructible_v<FirstType> &&
				std::is_nothrow_destructible_v<SecondType>
			)
		{
			std::destroy_at(std::addressof(first));
			std::destroy_at(std::addressof(second));
		}

		constexpr bool operator==(const pair &other) const
			noexcept
			(
				(
					std::is_arithmetic_v<FirstType> ||
					std::is_pointer_v<FirstType>
				) &&
				(
					std::is_arithmetic_v<SecondType> ||
					std::is_pointer_v<SecondType>
				)
			)
		{
			return first == other.first &&second == other.second;
		}

		constexpr std::strong_ordering operator<=>(const pair &other) const
			noexcept
			(
				(
					std::is_arithmetic_v<FirstType> ||
					std::is_pointer_v<FirstType>
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

		constexpr auto &operator[](const size_t index)
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

		constexpr const auto &operator[](const size_t index) const
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
		constexpr pair &copy_from(const pair &other)
			noexcept
			(
				(
					State == state_t::initialized &&
					(
						std::is_nothrow_copy_assignable_v<FirstType> ||
						(
							!std::is_copy_assignable_v<FirstType> &&
							std::is_nothrow_copy_constructible_v<FirstType>
						)
					) &&
					(
						std::is_nothrow_copy_assignable_v<SecondType> ||
						(
							!std::is_copy_assignable_v<SecondType> &&
							std::is_nothrow_copy_constructible_v<SecondType>
						)
					)
				) ||
				(
					State == state_t::uninitialized &&
					std::is_nothrow_copy_constructible_v<FirstType> &&
					std::is_nothrow_copy_constructible_v<SecondType>
				) ||
				(
					State == state_t::unknown &&
					std::is_nothrow_copy_constructible_v<FirstType> &&
					std::is_nothrow_copy_constructible_v<SecondType>
				)
			)
		{
			if constexpr (State == state_t::initialized)
			{
				if constexpr (std::is_copy_assignable_v<FirstType>)
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

		template <dynamic_states_t DynamicStates = dynamic_states>
		constexpr pair &copy_from(const state_t state, const state_t other_state, const pair &other)
			noexcept
			(
				std::is_nothrow_copy_constructible_v<FirstType>&&
				std::is_nothrow_copy_assignable_v<FirstType>&&
				std::is_nothrow_destructible_v<FirstType>&&
				std::is_nothrow_copy_constructible_v<SecondType>&&
				std::is_nothrow_copy_assignable_v<SecondType>&&
				std::is_nothrow_destructible_v<SecondType>
			)
		{
			if (state == state_t::initialized)
			{
				if constexpr (std::is_copy_assignable_v<FirstType>)
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

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown, typename OtherFirstType, typename OtherSecondType>
		constexpr pair &copy_from(OtherFirstType &&other_first, OtherSecondType &&other_second)
			noexcept
			(
				(
					State == state_t::initialized &&
					(
						std::is_nothrow_copy_assignable_v<FirstType> ||
						(
							!std::is_copy_assignable_v<FirstType> &&
							std::is_nothrow_copy_constructible_v<FirstType> &&
							std::is_nothrow_destructible_v<FirstType>
						)
					)
				) ||
				(
					State == state_t::uninitialized &&
					std::is_nothrow_copy_constructible_v<FirstType>
				) ||
				(
					State == state_t::unknown &&
					std::is_nothrow_copy_constructible_v<FirstType> &&
					std::is_nothrow_destructible_v<FirstType>
				)
			)
		{
			if constexpr (State == state_t::initialized)
			{
				if constexpr (std::is_copy_assignable_v<FirstType>)
				{
					first = std::forward<OtherFirstType>(other_first);
				}
				else
				{
					std::destroy_at(std::addressof(first));
					std::construct_at(std::addressof(first), std::forward<OtherFirstType>(other_first));
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
				std::construct_at(std::addressof(first), std::forward<OtherFirstType>(other_first));
				std::construct_at(std::addressof(second), std::forward<OtherSecondType>(other_second));
			}
			else
			{
				std::destroy_at(std::addressof(first));
				std::construct_at(std::addressof(first), std::forward<OtherFirstType>(other_first));
				std::destroy_at(std::addressof(second));
				std::construct_at(std::addressof(second), std::forward<OtherSecondType>(other_second));
			}
			return *this;
		}

		template <dynamic_states_t DynamicStates = dynamic_states, typename OtherFirstType, typename OtherSecondType>
		constexpr pair &copy_from(const state_t state, const state_t other_state, OtherFirstType &&other_first, OtherSecondType &&other_second)
			noexcept
			(
				std::is_nothrow_copy_constructible_v<FirstType> &&
				std::is_nothrow_copy_assignable_v<FirstType> &&
				std::is_nothrow_destructible_v<FirstType> &&
				std::is_nothrow_copy_constructible_v<SecondType> &&
				std::is_nothrow_copy_assignable_v<SecondType> &&
				std::is_nothrow_destructible_v<SecondType>
			)
		{
			if (state == state_t::initialized)
			{
				if constexpr (std::is_copy_assignable_v<FirstType>)
				{
					first = std::forward<OtherFirstType>(other_first);
				}
				else
				{
					std::destroy_at(std::addressof(first));
					std::construct_at(std::addressof(first), std::forward<OtherFirstType>(other_first));
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
				std::construct_at(std::addressof(first), std::forward<OtherFirstType>(other_first));
				std::construct_at(std::addressof(second), std::forward<OtherSecondType>(other_second));
			}
			else
			{
				std::destroy_at(std::addressof(first));
				std::construct_at(std::addressof(first), std::forward<OtherFirstType>(other_first));
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
		constexpr pair &construct_from(OtherPairType &&other)
			noexcept
			(
				(
					(
						State == state_t::initialized ||
						State == state_t::unknown
					) &&
					std::is_nothrow_constructible_v<FirstType, OtherPairType &&> &&
					std::is_nothrow_destructible_v<FirstType>
				) ||
				(
					State == state_t::uninitialized &&
					std::is_nothrow_constructible_v<FirstType, OtherPairType &&>
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

		template <dynamic_states_t DynamicStates = dynamic_states, typename OtherPairType>
			requires
			(
				std::is_same_v<std::remove_cvref_t<OtherPairType>, pair>
			)
		constexpr pair &construct_from(const state_t state, const state_t other_state, OtherPairType &&other)
			noexcept
			(
				std::is_nothrow_constructible_v<FirstType, OtherPairType &&>&&
				std::is_nothrow_destructible_v<FirstType>
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
		constexpr pair &copy_to(OtherPairType &&other)
			noexcept
			(
				(
					State == state_t::initialized &&
					(
						std::is_nothrow_copy_assignable_v<FirstType> ||
						(
							!std::is_copy_assignable_v<FirstType> &&
							std::is_nothrow_copy_constructible_v<FirstType> &&
							std::is_nothrow_destructible_v<FirstType>
						)
					) &&
					(
						std::is_nothrow_copy_assignable_v<SecondType> ||
						(
							!std::is_copy_assignable_v<SecondType> &&
							std::is_nothrow_copy_constructible_v<SecondType> &&
							std::is_nothrow_destructible_v<SecondType>
						)
					)
				) ||
				(
					State == state_t::uninitialized &&
					std::is_nothrow_copy_constructible_v<FirstType> &&
					std::is_nothrow_copy_constructible_v<SecondType>
				) ||
				(
					State == state_t::unknown &&
					std::is_nothrow_copy_constructible_v<FirstType> &&
					std::is_nothrow_destructible_v<FirstType> &&
					std::is_nothrow_copy_constructible_v<SecondType> &&
					std::is_nothrow_destructible_v<SecondType>
				)
			)
		{
			if constexpr (State == state_t::initialized)
			{
				if constexpr (std::is_copy_constructible_v<FirstType>)
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

		template <dynamic_states_t DynamicStates = dynamic_states, typename OtherPairType>
			requires
			(
				std::is_same_v<std::remove_cvref_t<OtherPairType>, pair>
			)
		constexpr pair &copy_to(const state_t state, const state_t other_state, OtherPairType &&other)
			noexcept
			(
				std::is_nothrow_copy_constructible_v<FirstType>&&
				std::is_nothrow_copy_assignable_v<FirstType>&&
				std::is_nothrow_destructible_v<FirstType>&&
				std::is_nothrow_copy_constructible_v<SecondType>&&
				std::is_nothrow_copy_assignable_v<SecondType>&&
				std::is_nothrow_destructible_v<SecondType>
			)
		{
			if (state == state_t::initialized)
			{
				if constexpr (std::is_copy_constructible_v<FirstType>)
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

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown, typename OtherFirstType>
		constexpr pair &copy_to(OtherFirstType &&other)
			noexcept
			(
				(
					State == state_t::initialized &&
					(
						std::is_nothrow_assignable_v<OtherFirstType &&, FirstType> ||
						(
							!std::is_assignable_v<OtherFirstType &&, FirstType> &&
							std::is_nothrow_constructible_v<OtherFirstType, FirstType>
						)
					)
				) ||
				(
					State == state_t::uninitialized &&
					std::is_nothrow_constructible_v<OtherFirstType, FirstType>
				) ||
				(
					State == state_t::unknown &&
					std::is_nothrow_constructible_v<OtherFirstType, FirstType>
				)
			)
		{
			if constexpr (State == state_t::initialized)
			{
				if constexpr (std::is_assignable_v<OtherFirstType &&, FirstType>)
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

		template <dynamic_states_t DynamicStates = dynamic_states, typename OtherFirstType>
		constexpr pair &copy_to(const state_t state, const state_t other_state, OtherFirstType &&other)
			noexcept
			(
				std::is_nothrow_assignable_v<OtherFirstType &&, FirstType> ||
				(
					!std::is_assignable_v<OtherFirstType &&, FirstType> &&
					std::is_nothrow_constructible_v<OtherFirstType, FirstType>
				)
			)
		{
			if (state == state_t::initialized)
			{
				if constexpr (std::is_assignable_v<OtherFirstType &&, FirstType>)
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
		constexpr pair &move_from(OtherPairType &&other)
			noexcept
			(
				(
					State == state_t::initialized &&
					(
						std::is_nothrow_move_assignable_v<FirstType> ||
						(
							!std::is_move_assignable_v<FirstType> &&
							std::is_nothrow_move_constructible_v<FirstType> &&
							std::is_nothrow_destructible_v<FirstType>
						)
					) &&
					(
						std::is_nothrow_move_assignable_v<SecondType> ||
						(
							!std::is_move_assignable_v<SecondType> &&
							std::is_nothrow_move_constructible_v<SecondType> &&
							std::is_nothrow_destructible_v<SecondType>
						)
					)
				) ||
				(
					State == state_t::uninitialized &&
					std::is_nothrow_move_constructible_v<FirstType> &&
					std::is_nothrow_move_constructible_v<SecondType>
				) ||
				(
					State == state_t::unknown &&
					std::is_nothrow_move_constructible_v<FirstType> &&
					std::is_nothrow_move_constructible_v<SecondType>
				)
			)
		{
			if constexpr (State == state_t::initialized)
			{
				if constexpr (std::is_move_assignable_v<FirstType>)
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

		template <dynamic_states_t DynamicStates = dynamic_states, typename OtherPairType>
			requires
			(
				std::is_same_v<std::remove_cvref_t<OtherPairType>, pair>
			)
		constexpr pair &move_from(const state_t state, const state_t other_state, OtherPairType &&other)
			noexcept
			(
				std::is_nothrow_move_constructible_v<FirstType>&&
				std::is_nothrow_move_assignable_v<FirstType>&&
				std::is_nothrow_destructible_v<FirstType>&&
				std::is_nothrow_move_constructible_v<SecondType>&&
				std::is_nothrow_move_assignable_v<SecondType>&&
				std::is_nothrow_destructible_v<SecondType>
			)
		{
			if (state == state_t::initialized)
			{
				if constexpr (std::is_move_assignable_v<FirstType>)
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

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown, typename OtherFirstType, typename OtherSecondType>
		constexpr pair &move_from(OtherFirstType &&other_first, OtherSecondType &&other_second)
			noexcept
			(
				(
					State == state_t::initialized &&
					(
						std::is_nothrow_assignable_v<FirstType, OtherFirstType &&> ||
						(
							!std::is_assignable_v<FirstType, OtherFirstType &&> &&
							std::is_nothrow_constructible_v<FirstType, OtherFirstType &&> &&
							std::is_nothrow_destructible_v<FirstType>
						)
					) &&
					(
						std::is_nothrow_assignable_v<SecondType, OtherSecondType &&> ||
						(
							!std::is_assignable_v<SecondType, OtherSecondType &&> &&
							std::is_nothrow_constructible_v<SecondType, OtherSecondType &&> &&
							std::is_nothrow_destructible_v<SecondType>
						)
					)
				) ||
				(
					State == state_t::uninitialized &&
					std::is_nothrow_constructible_v<FirstType, OtherFirstType &&> &&
					std::is_nothrow_constructible_v<SecondType, OtherSecondType &&>
				) ||
				(
					State == state_t::unknown &&
					std::is_nothrow_constructible_v<FirstType, OtherFirstType &&> &&
					std::is_nothrow_constructible_v<SecondType, OtherSecondType &&>
				)
			)
		{
			if constexpr (State == state_t::initialized)
			{
				if constexpr (std::is_move_assignable_v<FirstType>)
				{
					first = std::forward<OtherFirstType>(other_first);
				}
				else
				{
					std::destroy_at(std::addressof(first));
					std::construct_at(std::addressof(first), std::forward<OtherFirstType>(other_first));
				}
				if constexpr (std::is_move_assignable_v<SecondType>)
				{
					second = std::forward<OtherFirstType>(other_second);
				}
				else
				{
					std::destroy_at(std::addressof(second));
					std::construct_at(std::addressof(second), std::forward<OtherSecondType>(other_second));
				}
			}
			else if constexpr (State == state_t::uninitialized)
			{
				std::construct_at(std::addressof(first), std::forward<OtherFirstType>(other_first));
				std::construct_at(std::addressof(second), std::forward<OtherSecondType>(other_second));
			}
			else
			{
				std::destroy_at(std::addressof(first));
				std::construct_at(std::addressof(first), std::forward<OtherFirstType>(other_first));
				std::destroy_at(std::addressof(second));
				std::construct_at(std::addressof(second), std::forward<OtherSecondType>(other_second));
			}
			return *this;
		}

		template <dynamic_states_t DynamicStates = dynamic_states, typename OtherFirstType, typename OtherSecondType>
		constexpr pair &move_from(const state_t state, const state_t other_state, OtherFirstType &&other_first, OtherSecondType &&other_second)
			noexcept
			(
				std::is_nothrow_move_constructible_v<FirstType>&&
				std::is_nothrow_move_assignable_v<FirstType>&&
				std::is_nothrow_destructible_v<FirstType>&&
				std::is_nothrow_move_constructible_v<SecondType>&&
				std::is_nothrow_move_assignable_v<SecondType>&&
				std::is_nothrow_destructible_v<SecondType>
			)
		{
			if (state == state_t::initialized)
			{
				if constexpr (std::is_move_assignable_v<FirstType>)
				{
					first = std::forward<OtherFirstType>(other_first);
				}
				else
				{
					std::destroy_at(std::addressof(first));
					std::construct_at(std::addressof(first), std::forward<OtherFirstType>(other_first));
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
				std::construct_at(std::addressof(first), std::forward<OtherFirstType>(other_first));
				std::construct_at(std::addressof(second), std::forward<OtherSecondType>(other_second));
			}
			else
			{
				std::destroy_at(std::addressof(first));
				std::construct_at(std::addressof(first), std::forward<OtherFirstType>(other_first));
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
		constexpr pair &swap(pair &other)
			noexcept
			(
				(
					State == state_t::initialized &&
					(
						(
							OtherState == state_t::initialized &&
							std::is_nothrow_swappable_v<FirstType> &&
							std::is_nothrow_swappable_v<SecondType>
						) ||
						(
							OtherState == state_t::uninitialized &&
							std::is_nothrow_move_constructible_v<FirstType> &&
							std::is_nothrow_move_constructible_v<SecondType>
						)
					)
				) ||
				(
					State == state_t::uninitialized &&
					(
						(
							OtherState == state_t::initialized &&
							std::is_nothrow_move_constructible_v<FirstType> &&
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

		template <dynamic_states_t DynamicStates = dynamic_states>
		constexpr pair &swap(const state_t state, const state_t other_state, pair &other)
			noexcept
			(
				std::is_nothrow_swappable_v<FirstType>&&
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
		constexpr pair &swap(FirstType &other_first, SecondType &other_second)
			noexcept
			(
				(
					State == state_t::initialized &&
					(
						(
							OtherState == state_t::initialized &&
							std::is_nothrow_swappable_v<FirstType> &&
							std::is_nothrow_swappable_v<SecondType>
						) ||
						(
							OtherState == state_t::uninitialized &&
							std::is_nothrow_move_constructible_v<FirstType> &&
							std::is_nothrow_move_constructible_v<SecondType>
						)
					)
				) ||
				(
					State == state_t::uninitialized &&
					(
						(
							OtherState == state_t::initialized &&
							std::is_nothrow_move_constructible_v<FirstType> &&
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

		template <dynamic_states_t DynamicStates = dynamic_states>
		constexpr pair &swap(const state_t state, const state_t other_state, FirstType &other_first, SecondType &other_second)
			noexcept
			(
				std::is_nothrow_swappable_v<FirstType> &&
				std::is_nothrow_move_constructible_v<FirstType> &&
				std::is_nothrow_swappable_v<SecondType> &&
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
