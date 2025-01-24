#pragma once

#include <type_traits>
#include "woj/base.hpp"

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
            : exception{ line, message, file, function } {}
    };

    class nulluple
    {
    public:
		enum class state_t : uint8_t
		{
			intialized,
			uninitialized,
			unknown
		};

#if WOJ_HAS_CXX20
		consteval
#else
        constexpr
#endif
			nulluple()
			noexcept = default;

#if WOJ_HAS_CXX20
		consteval
#else
		constexpr
#endif
			nulluple(const nulluple &other)
			noexcept = default;

#if WOJ_HAS_CXX20
		consteval
#else
		constexpr
#endif
    		nulluple(const state_t other_state, const nulluple &other)
			noexcept {}


#if WOJ_HAS_CXX20
		consteval
#else
		constexpr
#endif
    		nulluple(const none_t none)
			noexcept {}

#if WOJ_HAS_CXX20
		consteval
#else
		constexpr
			#endif
    		nulluple(const noinit_t noinit)
            noexcept {}

#if WOJ_HAS_CXX20
		consteval
#else
		constexpr
#endif
			nulluple(const in_place_t in_place)
			noexcept {}

#if WOJ_HAS_CXX20
		consteval
#else
		constexpr
#endif
    		nulluple &operator=(const nulluple &) 
            noexcept = default;

#if WOJ_HAS_CXX20
		consteval
#else
		constexpr
#endif
    		nulluple &operator=(nulluple &&)
            noexcept = default;

#if WOJ_HAS_CXX20
		constexpr
#endif
    		~nulluple()
            noexcept = default;

#if WOJ_HAS_CXX20
		consteval
#else
		constexpr
#endif
    		bool operator==(const nulluple other) const
            noexcept
        {
            return true;
        }

#if WOJ_HAS_CXX20
		consteval
#else
		constexpr
#endif
    		std::strong_ordering operator<=>(const nulluple other) const
            noexcept
        {
            return std::strong_ordering::equal;
        }

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown>
#if WOJ_HAS_CXX20
		consteval
#else
		constexpr
#endif
    		const nulluple &construct_from(const none_t none) const
			noexcept
		{
			return *this;
		}

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown>
#if WOJ_HAS_CXX20
		consteval
#else
		constexpr
#endif
    		nulluple &construct_from(const none_t none)
			noexcept
		{
			return *this;
		}

		template <dynamic_states_t DynamicStates = dynamic_states>
#if WOJ_HAS_CXX20
		consteval
#else
		constexpr
#endif
    		const nulluple &construct_from(const state_t state, const state_t other_state, const none_t none) const
			noexcept
		{
			return *this;
		}

		template <dynamic_states_t DynamicStates = dynamic_states>
#if WOJ_HAS_CXX20
		consteval
#else
		constexpr
#endif
    		nulluple &construct_from(const state_t state, const state_t other_state, const none_t none)
			noexcept
		{
			return *this;
		}

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown>
#if WOJ_HAS_CXX20
		consteval
#else
		constexpr
			#endif
    		const nulluple  &construct_from(const noinit_t noinit) const
			noexcept
		{
			return *this;
		}

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown>
#if WOJ_HAS_CXX20
		consteval
#else
		constexpr
#endif
    		nulluple &construct_from(const noinit_t noinit)
			noexcept
		{
			return *this;
		}

		template <dynamic_states_t DynamicStates = dynamic_states>
#if WOJ_HAS_CXX20
		consteval
#else
		constexpr
#endif
    		const nulluple &construct_from(const state_t state, const state_t other_state, const noinit_t noinit) const
			noexcept
		{
			return *this;
		}

		template <dynamic_states_t DynamicStates = dynamic_states>
#if WOJ_HAS_CXX20
		consteval
#else
		constexpr
#endif
    		nulluple &construct_from(const state_t state, const state_t other_state, const noinit_t noinit)
			noexcept
		{
			return *this;
		}

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown>
#if WOJ_HAS_CXX20
		consteval
#else
		constexpr
#endif
    		const nulluple &construct_from(const nulluple other) const
			noexcept
		{
			return *this;
		}

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown>
#if WOJ_HAS_CXX20
		consteval
#else
		constexpr
#endif
    		nulluple &construct_from(const nulluple other)
			noexcept
		{
			return *this;
		}

		template <dynamic_states_t DynamicStates = dynamic_states>
#if WOJ_HAS_CXX20
		consteval
#else
		constexpr
#endif
    		const nulluple &construct_from(const nulluple other) const
			noexcept
		{
			return *this;
		}

		template <dynamic_states_t DynamicStates = dynamic_states>
#if WOJ_HAS_CXX20
		consteval
#else
		constexpr
#endif
    		nulluple &construct_from(const nulluple other)
			noexcept
		{
			return *this;
		}

		template <state_t OtherState = state_t::unknown>
		static 
#if WOJ_HAS_CXX20
			consteval
#else
			constexpr
#endif
    		nulluple constructed_from(const none_t none)
			noexcept
		{
			return nulluple{};
		}

		template <dynamic_states_t DynamicStates = dynamic_states>
		static
#if WOJ_HAS_CXX20
			consteval
#else
			constexpr
#endif
    		nulluple constructed_from(const state_t state, const state_t other_state, const none_t none)
			noexcept
		{
			return nulluple{};
		}

		template <state_t OtherState = state_t::unknown>
		static
#if WOJ_HAS_CXX20
			consteval	
#else
			constexpr
#endif
    		nulluple constructed_from(const noinit_t noinit)
			noexcept
		{
			return nulluple{ noinit };
		}

		template <dynamic_states_t DynamicStates = dynamic_states>
		static
#if WOJ_HAS_CXX20
			consteval
#else
			constexpr
#endif
    		nulluple constructed_from(const state_t state, const state_t other_state, const noinit_t noinit)
			noexcept
		{
			return nulluple{ noinit };
		}

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown>
		static
#if WOJ_HAS_CXX20
			consteval
#else
			constexpr
#endif
    		nulluple constructed_from(const nulluple other)
			noexcept
		{
			return nulluple{ other };
		}

		template <dynamic_states_t DynamicStates = dynamic_states>
		static
#if WOJ_HAS_CXX20
			consteval
#else
			constexpr
#endif
    		nulluple constructed_from(const nulluple other)
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
    		const nulluple  &assign_from(const none_t none) const
			noexcept
		{
			return *this;
		}

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown>
#if WOJ_HAS_CXX20
		consteval
#else
		constexpr
#endif
    		nulluple &assign_from(const none_t none)
			noexcept
		{
			return *this;
		}

		template <dynamic_states_t DynamicStates = dynamic_states>
#if WOJ_HAS_CXX20
		consteval
#else
		constexpr
#endif
    		const nulluple &assign_from(const state_t state, const state_t other_state, const none_t none) const
			noexcept
		{
			return *this;
		}

		template <dynamic_states_t DynamicStates = dynamic_states>
#if WOJ_HAS_CXX20
		consteval
#else
		constexpr
#endif
    		nulluple &assign_from(const state_t state, const state_t other_state, const none_t none)
			noexcept
		{
			return *this;
		}

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown>
#if WOJ_HAS_CXX20
		consteval
#else
		constexpr
#endif
    		const nulluple &assign_from(const nulluple other) const
			noexcept
		{
			return *this;
		}

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown>
#if WOJ_HAS_CXX20
		consteval
#else
		constexpr
#endif
    		nulluple &assign_from(const nulluple other)
			noexcept
		{
			return *this;
		}

		template <dynamic_states_t DynamicStates = dynamic_states>
#if WOJ_HAS_CXX20
		consteval
#else
		constexpr
#endif
    		const nulluple &assign_from(const nulluple other) const
			noexcept
		{
			return *this;
		}

		template <dynamic_states_t DynamicStates = dynamic_states>
#if WOJ_HAS_CXX20
		consteval
#else
		constexpr
#endif
    		nulluple &assign_from(const nulluple other)
			noexcept
		{
			return *this;
		}

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown>
#if WOJ_HAS_CXX20
		consteval
#else
		constexpr
#endif
			const nulluple &emplace_from() const
			noexcept
		{
			return *this;
		}

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown>
#if WOJ_HAS_CXX20
		consteval
#else
		constexpr
#endif
			nulluple &emplace_from()
			noexcept
		{
			return *this;
		}

		template <dynamic_states_t DynamicStates = dynamic_states>
#if WOJ_HAS_CXX20
		consteval
#else
		constexpr
#endif
			const nulluple &emplace_from(const state_t state, const state_t other_state) const
			noexcept
		{
			return *this;
		}

		template <dynamic_states_t DynamicStates = dynamic_states>
#if WOJ_HAS_CXX20
		consteval
#else
		constexpr
#endif
			nulluple &emplace_from(const state_t state, const state_t other_state)
			noexcept
		{
			return *this;
		}

		template <state_t OtherState = state_t::unknown>
		static
#if WOJ_HAS_CXX20
		consteval
#else
		constexpr
#endif
			const nulluple &emplaced_from()
			noexcept
		{
			return nulluple{ in_place };
		}

		template <dynamic_states_t DynamicStates = dynamic_states>
		static
#if WOJ_HAS_CXX20
			consteval
#else
			constexpr
#endif
			nulluple emplaced_from(const state_t state, const state_t other_state)
			noexcept
		{
			return nulluple{ in_place };
		}


		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown>
#if WOJ_HAS_CXX20
		consteval
#else
		constexpr
#endif
    		const nulluple &copy_from(const nulluple other) const
			noexcept
		{
			return *this;
		}

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown>
#if WOJ_HAS_CXX20
		consteval
#else
		constexpr
#endif
    		nulluple &copy_from(const nulluple other)
			noexcept
		{
			return *this;
		}

		template <dynamic_states_t DynamicStates = dynamic_states>
#if WOJ_HAS_CXX20
		consteval
#else
		constexpr
#endif
    		const nulluple &copy_from(const state_t state, const state_t other_state, const nulluple other) const
			noexcept
		{
			return *this;
		}

		template <dynamic_states_t DynamicStates = dynamic_states>
#if WOJ_HAS_CXX20
		consteval
#else
		constexpr
#endif
    		nulluple &copy_from(const state_t state, const state_t other_state, const nulluple other)
			noexcept
		{
			return *this;
		}

		template <state_t OtherState = state_t::unknown>
		static 
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

		template <dynamic_states_t DynamicStates = dynamic_states>
		static 
#if WOJ_HAS_CXX20
			consteval
#else
			constexpr
#endif
    		nulluple copied_from(const state_t state, const state_t other_state, const nulluple other)
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
    		const nulluple &copy_to(const nulluple other) const
            noexcept
        {
            return *this;
        }

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown>
#if WOJ_HAS_CXX20
			consteval
#else
			constexpr
#endif
    		nulluple &copy_to(const nulluple other)
		{
			return *this;
		}

		template <dynamic_states_t DynamicStates = dynamic_states>
#if WOJ_HAS_CXX20
		consteval
#else
		constexpr
#endif
    		const nulluple &copy_to(const state_t state, const state_t other_state, const nulluple other) const
			noexcept
		{
			return *this;
		}

		template <dynamic_states_t DynamicStates = dynamic_states>
#if WOJ_HAS_CXX20
		consteval
#else
		constexpr
#endif
    		nulluple &copy_to(const state_t state, const state_t other_state, const nulluple other)
			noexcept
		{
			return *this;
		}

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown>
#if WOJ_HAS_CXX20
		consteval
#else
		constexpr
#endif
    		const nulluple &move_from(const nulluple other) const
			noexcept
		{
			return *this;
		}

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown>
#if WOJ_HAS_CXX20
		consteval
#else
		constexpr
#endif
    		nulluple &move_from(const nulluple other)
			noexcept
		{
			return *this;
		}

		template <dynamic_states_t DynamicStates = dynamic_states>
#if WOJ_HAS_CXX20
		consteval
#else
		constexpr
#endif
    		const nulluple &move_from(const state_t state, const state_t other_state, const nulluple other) const
			noexcept
		{
			return *this;
		}

		template <dynamic_states_t DynamicStates = dynamic_states>
#if WOJ_HAS_CXX20
		consteval
#else
		constexpr
#endif
    		nulluple &move_from(const state_t state, const state_t other_state, const nulluple other)
			noexcept
		{
			return *this;
		}

		template <state_t OtherState = state_t::unknown>
		static 
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
		static 
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
    		const nulluple &move_to(const nulluple &other) const
			noexcept
		{
			return *this;
		}

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown>
#if WOJ_HAS_CXX20
		consteval
#else
		constexpr
#endif
    		nulluple &move_to(const nulluple &other)
			noexcept
		{
			return *this;
		}

		template <dynamic_states_t DynamicStates = dynamic_states>
#if WOJ_HAS_CXX20
		consteval
#else
		constexpr
#endif
    		const nulluple &move_to(const state_t state, const state_t other_state, const nulluple &other) const
			noexcept
		{
			return *this;
		}


		template <dynamic_states_t DynamicStates = dynamic_states>
#if WOJ_HAS_CXX20
		consteval
#else
		constexpr
#endif
    		nulluple &move_to(const state_t state, const state_t other_state, const nulluple &other)
			noexcept
		{
			return *this;
		}

        template <size_t Index>
        static 
#if WOJ_HAS_CXX20
			consteval
#else
			constexpr
#endif
    		none_t
#ifndef NDEBUG
			[[noreturn]]
#endif
    		get()
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
            return none;
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
            return 0;
        }

#if WOJ_HAS_CXX20
		consteval
#else
		constexpr
#endif
    		explicit operator bool() const
            noexcept
        {
            return false;
        }

#if WOJ_HAS_CXX20
		consteval
#else
		constexpr
#endif
    		nulluple &swap_with(const nulluple other) 
            noexcept 
        {
            return *this;
        }
    };

    template <typename FirstType>
    class single
    {
    public:
		enum class state_t : uint8_t
		{
			intialized,
			uninitialized,
			unknown
		};

        union 
        {
            FirstType first;
        };

		using first_type = FirstType;
		using value_type = FirstType;
		using reference = FirstType &;
		using const_reference = const FirstType &;
		using rvalue_reference = FirstType &&;
		using const_rvalue_reference = const FirstType &&;
		using pointer = FirstType *;
		using const_pointer = const FirstType *;

        constexpr single() 
            noexcept 
            (
                std::is_nothrow_default_constructible_v<FirstType>
            )
            : first{} {}

		explicit constexpr single(const noinit_t noinit)
			noexcept {}

		template <typename OtherFirstType>
			requires
			(
				!std::is_same_v<std::remove_cvref_t<OtherFirstType>, single>
			)
		explicit constexpr single(OtherFirstType &&first)
			noexcept
			(
				std::is_nothrow_constructible_v<FirstType, OtherFirstType &&>
			)
            : first{ std::forward<OtherFirstType>(first) } {}

        constexpr single(const single &other)
            noexcept 
            (
                std::is_nothrow_copy_constructible_v<FirstType>
            )
            : first{ other.first } {}

		constexpr single(const state_t other_state, const single &other)
			noexcept
			(
				std::is_nothrow_copy_constructible_v<FirstType>
				)
			: first{ other.first } {
		}

        constexpr single(single &&other)
            noexcept 
            (
                std::is_nothrow_move_constructible_v<FirstType>
            )
            : first{ std::move(other.first) } {}

		constexpr single(const state_t other_state, single &&other)
			noexcept
			(
				std::is_nothrow_move_constructible_v<FirstType>
				)
			: first{ std::move(other.first) } {
		}

        template <typename ...ArgsTypes>
        explicit constexpr single(in_place_t, ArgsTypes &&...args)
            noexcept 
            (
                std::is_nothrow_copy_constructible_v<FirstType>
            )
            : first{ std::forward<ArgsTypes>(args)... } {}

		template <typename OtherFirstType>
			requires
			(
				!std::is_same_v<std::remove_cvref_t<OtherFirstType>, single>
			)
			constexpr single &operator=(OtherFirstType &&other)
			noexcept
			(
				std::is_nothrow_constructible_v<FirstType, OtherFirstType &&> ||
				(
					!std::is_copy_assignable_v<FirstType> &&
					std::is_nothrow_copy_constructible_v<FirstType> &&
					std::is_nothrow_destructible_v<FirstType>
				)
			)
		{
			if constexpr (std::is_copy_assignable_v<FirstType>)
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

		template <typename OtherSingleType>
			requires
			(
				std::is_same_v<std::remove_cvref_t<OtherSingleType>, single>
			)
		constexpr single &operator=(OtherSingleType &&other)
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

        constexpr ~single()
            noexcept
            (
                std::is_nothrow_destructible_v<FirstType>
            ) = default;

        constexpr bool operator==(const single &other) const
            noexcept
			(
				std::is_arithmetic_v<FirstType> ||
				std::is_pointer_v<FirstType>
            )
        {
            return first == other.first;
        }

        constexpr std::strong_ordering operator<=>(const single &other) const
            noexcept
			(
				std::is_arithmetic_v<FirstType> ||
				std::is_pointer_v<FirstType>
            )
        {
			return first == other.first;
        }

        constexpr FirstType &operator[](const size_t index)
            noexcept
#ifndef NDEBUG
            (
                false
            )
#endif
        {
#ifndef NDEBUG
            if (!index)
                return first;
            throw bad_tuple_access{ __LINE__, "Single access out of bounds.", __FILE__, __func__ };
#else
            return first;
#endif
        }

		constexpr  const FirstType &operator[](const size_t index) const
			noexcept
#ifndef NDEBUG
			(
				false
			)
#endif
		{
#ifndef NDEBUG
			if (!index)
				return first;
			throw bad_tuple_access{ __LINE__, "Single access out of bounds.", __FILE__, __func__ };
#else
			return first;
#endif
		}

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown>
		constexpr const single &construct_from(const none_t none) const
			noexcept
		{
			return *this;
		}


		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown>
		constexpr single &construct_from(const none_t none)
			noexcept
		{
			return *this;
		}

		template <dynamic_states_t DynamicStates = dynamic_states>
		constexpr const single &construct_from(const state_t state, const state_t other_state, const none_t none) const
			noexcept
		{
			return *this;
		}

		template <dynamic_states_t DynamicStates = dynamic_states>
		constexpr single &construct_from(const state_t state, const state_t other_state, const none_t none)
			noexcept
		{
			return *this;
		}

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown>
		constexpr const single &construct_from(const noinit_t noinit) const
			noexcept
		{
			return *this;
		}


		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown>
		constexpr single &construct_from(const noinit_t noinit)
			noexcept
		{
			return *this;
		}

		template <dynamic_states_t DynamicStates = dynamic_states>
		constexpr const single &construct_from(const state_t state, const state_t other_state, const noinit_t noinit) const
			noexcept
		{
			return *this;
		}

		template <dynamic_states_t DynamicStates = dynamic_states>
		constexpr single &construct_from(const state_t state, const state_t other_state, const noinit_t noinit)
			noexcept
		{
			return *this;
		}

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown, typename OtherSingleType = void>
			requires
			(
				std::is_same_v<std::remove_cvref_t<OtherSingleType>, single>
			)
		constexpr single &construct_from(OtherSingleType &&other)
			noexcept
			
			(
				(
					(
						State == state_t::initialized ||
						State == state_t::unknown
					) &&
					std::is_nothrow_constructible_v<FirstType, OtherSingleType &&> &&
					std::is_nothrow_destructible_v<FirstType>
				) |
				(
					State == state_t::unintialized &&
					std::is_nothrow_constructible_v<FirstType, OtherSingleType &&>
				)
			)
		{
			if constexpr (State == state_t::initialized)
			{
				std::destroy_at(std::addressof(first));
				std::construct_at(std::addressof(first), std::forward<OtherSingleType>(other));
			}
			else if constexpr (State == state_t::unintialized)
			{
				std::construct_at(std::addressof(first), std::forward<OtherSingleType>(other));
			}
			else
			{
				std::destroy_at(std::addressof(first));
				std::construct_at(std::addressof(first), std::forward<OtherSingleType>(other));
			}
			return *this;
		}

		template <dynamic_states_t DynamicStates = dynamic_states, typename OtherSingleType = void>
			requires
			(
				std::is_same_v<std::remove_cvref_t<OtherSingleType>, single>
			)
		constexpr single &construct_from(const state_t state, const state_t other_state, OtherSingleType &&other)
			noexcept
			(
				std::is_nothrow_constructible_v<FirstType, OtherSingleType &&>&&
				std::is_nothrow_destructible_v<FirstType>
			)
		{
			if (state == state_t::initialized)
			{
				std::destroy_at(std::addressof(first));
				std::construct_at(std::addressof(first), std::forward<OtherSingleType>(other));
			}
			else if (state == state_t::unintialized)
			{
				std::construct_at(std::addressof(first), std::forward<OtherSingleType>(other));
			}
			else
			{
				std::destroy_at(std::addressof(first));
				std::construct_at(std::addressof(first), std::forward<OtherSingleType>(other));
			}
			return *this;
		}

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown, typename OtherValueType>
			requires
			(
				!std::is_same_v<std::remove_cvref_t<OtherValueType>, single>
			)
		constexpr single &construct_from(OtherValueType &&other)
			noexcept
			(
				(
					(
						State == state_t::initialized ||
						State == state_t::unknown
					) &&
					std::is_nothrow_constructible_v<FirstType, OtherValueType &&> &&
					std::is_nothrow_destructible_v<FirstType>
				) ||
				(
					State == state_t::unintialized &&
					std::is_nothrow_constructible_v<FirstType, OtherValueType &&>
				)
			)
        {
			if constexpr (State == state_t::initialized)
			{
				std::destroy_at(std::addressof(first));
				std::construct_at(std::addressof(first), std::forward<OtherValueType>(other));
			}
			else if constexpr (State == state_t::unintialized)
			{
				std::construct_at(std::addressof(first), std::forward<OtherValueType>(other));
			}
			else
			{
				std::destroy_at(std::addressof(first));
				std::construct_at(std::addressof(first), std::forward<OtherValueType>(other));
			}
	    }

		template <dynamic_states_t DynamicStates = dynamic_states, typename OtherValueType>
			requires
			(
				!std::is_same_v<std::remove_cvref_t<OtherValueType>, single>
			)
		constexpr single &construct_from(const state_t state, const state_t other_state, OtherValueType &&other)
			noexcept
			(
				std::is_nothrow_constructible_v<FirstType, OtherValueType &&>&&
				std::is_nothrow_destructible_v<FirstType>
			)
		{
			if (state == state_t::initialized)
			{
				std::destroy_at(std::addressof(first));
				std::construct_at(std::addressof(first), std::forward<OtherValueType>(other));
			}
			else if (state == state_t::unintialized)
			{
				std::construct_at(std::addressof(first), std::forward<OtherValueType>(other));
			}
			else
			{
				std::destroy_at(std::addressof(first));
				std::construct_at(std::addressof(first), std::forward<OtherValueType>(other));
			}
			return *this;
		}

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown>
		static constexpr single constructed_from(const none_t none)
			noexcept
			(
				std::is_nothrow_default_constructible_v<FirstType>
			)
		{
			return single{ none };
		}

		template <dynamic_states_t DynamicStates = dynamic_states>
		static constexpr single constructed_from(const state_t state, const state_t other_state, const none_t none)
			noexcept
			(
				std::is_nothrow_default_constructible_v<FirstType>
			)
		{
			return single{ none };
		}

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown>
		static constexpr single constructed_from(const noinit_t noinit)
			noexcept
		{
			return single{ noinit };
		}

		template <dynamic_states_t DynamicStates = dynamic_states>
		static constexpr single constructed_from(const state_t state, const state_t other_state, const noinit_t noinit)
			noexcept
		{
			return single{ noinit };
		}

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown, typename OtherSingleType = void>
			requires
			(
				std::is_same_v<std::remove_cvref_t<OtherSingleType>, single>
			)
		static constexpr single constructed_from(OtherSingleType &&other)
			noexcept
			(
				std::is_nothrow_constructible_v<FirstType, OtherSingleType &&>
			)
		{
			return single{ std::forward<OtherSingleType>(other) };
		}

		template <dynamic_states_t DynamicStates = dynamic_states, typename OtherSingleType = void>
			requires
			(
				std::is_same_v<std::remove_cvref_t<OtherSingleType>, single>
			)
		static constexpr single constructed_from(const state_t state, const state_t other_state, OtherSingleType &&other)
        {
			return single{ std::forward<OtherSingleType>(other) };
        }

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown, typename OtherValueType = void>
			requires
			(
				!std::is_same_v<std::remove_cvref_t<OtherValueType>, single>
			)
		static constexpr single constructed_from(OtherValueType &&other)
			noexcept
			(
				std::is_nothrow_constructible_v<FirstType, OtherValueType &&>
			)
		{
			return single{ std::forward<OtherValueType>(other) };
		}

		template <dynamic_states_t DynamicStates = dynamic_states, typename OtherValueType = void>
			requires
			(
				!std::is_same_v<std::remove_cvref_t<OtherValueType>, single>
			)
			static constexpr single constructed_from(const state_t state, const state_t other_state, OtherValueType &&other)
			noexcept
			(
				std::is_nothrow_constructible_v<FirstType, OtherValueType&&>
			)
		{
			return single{ std::forward<OtherValueType>(other) };
		}

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown, typename OtherSingleType = void>
			requires
			(
				std::is_same_v<std::remove_cvref_t<OtherSingleType>, single>
			)
		constexpr single &assign_from(OtherSingleType &&other)
			noexcept
			(
				(
					(
						State == state_t::initialized ||
						State == state_t::unknown
					) &&
					(
						std::is_nothrow_assignable_v<FirstType, OtherSingleType &&> ||
						(
							!std::is_assignable_v<FirstType, OtherSingleType &&> &&
							std::is_nothrow_constructible_v<FirstType, OtherSingleType &&> &&
							std::is_nothrow_destructible_v<FirstType>
						)
					)
				) ||
				(
					State == state_t::unintialized &&
					std::is_nothrow_constructible_v<FirstType, OtherSingleType &&>
				)
			)
		{
			if constexpr (State == state_t::initialized)
			{
				if constexpr (std::is_assignable_v<FirstType, OtherSingleType &&>)
				{
					first = std::forward<OtherSingleType>(other);
				}
				else
				{
					std::destroy_at(std::addressof(first));
					std::construct_at(std::addressof(first), std::forward<OtherSingleType>(other));
				}
			}
			else if constexpr (State == state_t::unintialized)
			{
				std::construct_at(std::addressof(first), std::forward<OtherSingleType>(other));
			}
			else
			{
				if constexpr (std::is_assignable_v<FirstType, OtherSingleType&&>)
				{
					first = std::forward<OtherSingleType>(other);
				}
				else
				{
					std::destroy_at(std::addressof(first));
					std::construct_at(std::addressof(first), std::forward<OtherSingleType>(other));
				}
			}
			return *this;
		}

		template <dynamic_states_t DynamicStates = dynamic_states, typename OtherSingleType = void>
			requires
			(
				std::is_same_v<std::remove_cvref_t<OtherSingleType>, single>
			)
		constexpr single &assign_from(const state_t state, const state_t other_state, OtherSingleType &&other)
			noexcept
			(
				std::is_nothrow_assignable_v<FirstType, OtherSingleType &&> &&
				std::is_nothrow_constructible_v<FirstType, OtherSingleType &&> &&
				std::is_nothrow_destructible_v<FirstType>
			)
		{
			if (state == state_t::initialized)
			{
				if constexpr (std::is_assignable_v<FirstType, OtherSingleType &&>)
				{
					first = std::forward<OtherSingleType>(other);
				}
				else
				{
					std::destroy_at(std::addressof(first));
					std::construct_at(std::addressof(first), std::forward<OtherSingleType>(other));
				}
			}
			else if (state == state_t::unintialized)
			{
				std::construct_at(std::addressof(first), std::forward<OtherSingleType>(other));
			}
			else
			{
				if constexpr (std::is_assignable_v<FirstType, OtherSingleType&&>)
				{
					first = std::forward<OtherSingleType>(other);
				}
				else
				{
					std::destroy_at(std::addressof(first));
					std::construct_at(std::addressof(first), std::forward<OtherSingleType>(other));
				}
			}
			return *this;
		}

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown, typename OtherValueType>
			requires
			(
				!std::is_same_v<std::remove_cvref_t<OtherValueType>, single>
			)
		constexpr single &assign_from(OtherValueType &&other)
			noexcept
			(
				(
					(
						State == state_t::initialized ||
						State == state_t::unknown
						) &&
					(
						std::is_nothrow_assignable_v<FirstType, OtherValueType &&> ||
						(
							!std::is_assignable_v<FirstType, OtherValueType &&> &&
							std::is_nothrow_constructible_v<FirstType, OtherValueType &&> &&
							std::is_nothrow_destructible_v<FirstType>
						)
					)
				) ||
				(
					State == state_t::unintialized &&
					std::is_nothrow_constructible_v<FirstType, OtherValueType &&>
				)
			)
		{
			if constexpr (State == state_t::initialized)
			{
				if constexpr (std::is_assignable_v<FirstType, OtherValueType &&>)
				{
					first = std::forward<OtherValueType>(other);
				}
				else
				{
					std::destroy_at(std::addressof(first));
					std::construct_at(std::addressof(first), std::forward<OtherValueType>(other));
				}
			}
			else if constexpr (State == state_t::unintialized)
			{
				std::construct_at(std::addressof(first), std::forward<OtherValueType>(other));
			}
			else
			{
				if constexpr (std::is_assignable_v<FirstType, OtherValueType&&>)
				{
					first = std::forward<OtherValueType>(other);
				}
				else
				{
					std::destroy_at(std::addressof(first));
					std::construct_at(std::addressof(first), std::forward<OtherValueType>(other));
				}
			}
			return *this;
		}

		template <dynamic_states_t DynamicStates = dynamic_states, typename OtherValueType>
			requires
			(
				!std::is_same_v<std::remove_cvref_t<OtherValueType>, single>
			)
		constexpr single &assign_from(const state_t state, const state_t other_state, OtherValueType &&other)
				noexcept
				(
					std::is_nothrow_assignable_v<FirstType, OtherValueType &&> &&
					std::is_nothrow_constructible_v<FirstType, OtherValueType &&> &&
					std::is_nothrow_destructible_v<FirstType>
				)
			{
				if (state == state_t::initialized)
				{
					if constexpr (std::is_assignable_v<FirstType, OtherValueType &&>)
					{
						first = std::forward<OtherValueType>(other);
					}
					else
					{
						std::destroy_at(std::addressof(first));
						std::construct_at(std::addressof(first), std::forward<OtherValueType>(other));
					}
				}
				else if (state == state_t::unintialized)
				{
					std::construct_at(std::addressof(first), std::forward<OtherValueType>(other));
				}
				else
				{
					if constexpr (std::is_assignable_v<FirstType, OtherValueType&&>)
					{
						first = std::forward<OtherValueType>(other);
					}
					else
					{
						std::destroy_at(std::addressof(first));
						std::construct_at(std::addressof(first), std::forward<OtherValueType>(other));
					}
				}
				return *this;
			}

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown, typename ...ArgsTypes>
		constexpr single &emplace_from(const ArgsTypes &&...args)
			noexcept
			(
				(
					(
						State == state_t::initialized ||
						State == state_t::unknown
					) &&
					std::is_nothrow_constructible_v<FirstType, ArgsTypes &&...> &&
					std::is_nothrow_destructible_v<FirstType>
				) ||
				(
					State == state_t::unintialized &&
					std::is_nothrow_constructible_v<FirstType, ArgsTypes &&...>
				)
			)
		{
			if constexpr (State == state_t::initialized)
			{
				std::destroy_at(std::addressof(first));
				std::construct_at(std::addressof(first), std::forward<ArgsTypes>(args)...);
			}
			else if constexpr (State == state_t::unintialized)
			{
				std::construct_at(std::addressof(first), std::forward<ArgsTypes>(args)...);
			}
			else
			{
				std::destroy_at(std::addressof(first));
				std::construct_at(std::addressof(first), std::forward<ArgsTypes>(args)...);
			}
			return *this;
		}

		template <dynamic_states_t DynamicStates = dynamic_states, typename ...ArgsTypes>
		constexpr single &emplace_from(const state_t state, const state_t other_state, const ArgsTypes &&...args)
			noexcept
			(
				std::is_nothrow_constructible_v<FirstType, ArgsTypes &&...> &&
				std::is_nothrow_destructible_v<FirstType>
			)
		{
			if (state == state_t::initialized)
			{
				std::destroy_at(std::addressof(first));
				std::construct_at(std::addressof(first), std::forward<ArgsTypes>(args)...);
			}
			else if (state == state_t::unintialized)
			{
				std::construct_at(std::addressof(first), std::forward<ArgsTypes>(args)...);
			}
			else
			{
				std::destroy_at(std::addressof(first));
				std::construct_at(std::addressof(first), std::forward<ArgsTypes>(args)...);
			}
			return *this;
		}

		template <state_t OtherState = state_t::unknown, typename ...ArgsTypes>
		static constexpr single emplaced_from(const ArgsTypes &&...args)
			noexcept
			(
				std::is_nothrow_constructible_v<FirstType, ArgsTypes &&...>
			)
		{
			return single{ in_place, std::forward<ArgsTypes>(args)... };
		}

		template <dynamic_states_t DynamicStates = dynamic_states, typename ...ArgsTypes>
		static constexpr single emplaced_from(const state_t state, const state_t other_state, const ArgsTypes &&...args)
			noexcept
			(
				std::is_nothrow_constructible_v<FirstType, ArgsTypes &&...>
			)
		{
			return single{ in_place, std::forward<ArgsTypes>(args)... };
		}

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown, typename OtherSingleType>
			requires
			(
				std::is_same_v<std::remove_cvref_t<OtherSingleType>, single>
			)
		constexpr single &copy_from(OtherSingleType &&other)
			noexcept
			(
				(
					State == state_t::initialized &&
					std::is_nothrow_copy_assignable_v<FirstType> &&
					(
						!std::is_copy_constructible_v<FirstType> &&
						std::is_nothrow_copy_constructible_v<FirstType>
					)
					
				) ||
				(
					State == state_t::unintialized &&
					std::is_nothrow_copy_constructible_v<FirstType>
				) ||
				(
					std::is_nothrow_copy_constructible_v<FirstType> &&
					std::is_nothrow_destructible_v<FirstType>
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
			}
			else if constexpr (State == state_t::unintialized)
			{
				std::construct_at(std::addressof(first), other.first);
			}
			else // ... And what to do here? I guess user would pass unitialized state if he didn't initialize it, would he?
			{
				if constexpr (std::is_copy_constructible_v<FirstType>)
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



		template <typename OtherSingleType>
			requires
			(
				std::is_same_v<std::remove_cvref_t<OtherSingleType>, single>
			)
		constexpr const single &copy_to(OtherSingleType &&other) const
			noexcept
			(
				std::is_nothrow_copy_constructible_v<FirstType> ||
				(
					!std::is_copy_constructible_v<FirstType> &&
					std::is_nothrow_copy_constructible_v<FirstType>
				)
			)
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
			return *this;
        }

		template <typename OtherSingleType>
			requires
			(
				std::is_same_v<std::remove_cvref_t<OtherSingleType>, single>
			)
		constexpr single &copy_to(OtherSingleType &&other)
			noexcept
			(
				std::is_nothrow_copy_constructible_v<FirstType> ||
				(
					!std::is_copy_constructible_v<FirstType> &&
					std::is_nothrow_copy_constructible_v<FirstType>
				)
			)
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
			return *this;
		}

		template <typename OtherValueType>
		constexpr single &copy_to(OtherValueType &&other)
			noexcept
			(
				std::is_nothrow_assignable_v<OtherValueType &&, FirstType> ||
				(
					!std::is_assignable_v<OtherValueType &&, FirstType> &&
					std::is_nothrow_constructible_v<OtherValueType, FirstType>
				)	
			)
		{
			if constexpr (std::is_assignable_v<OtherValueType &&, FirstType>)
			{
				other = first;
			}
			else
			{
				std::destroy_at(std::addressof(other));
				std::construct_at(std::addressof(other), first);
			}

        	return *this;
		}

		template <typename OtherValueType>
		constexpr const single &copy_to(OtherValueType &&other) const
			noexcept
			(
				std::is_nothrow_assignable_v<OtherValueType &&, FirstType> ||
				(
					!std::is_assignable_v<OtherValueType &&, FirstType> &&
					std::is_nothrow_constructible_v<OtherValueType, FirstType>
				)
			)
		{
			if constexpr (std::is_assignable_v<OtherValueType &&, FirstType>)
			{
				other = first;
			}
			else
			{
				std::destroy_at(std::addressof(other));
				std::construct_at(std::addressof(other), first);
			}

			return *this;
		}

        template <size_t Index>
		constexpr FirstType &get() const
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

        static constexpr size_t size()
	        noexcept
        {
            return 1;
        }

        constexpr explicit operator bool() const
            noexcept
        {
            return true;
        }

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown, typename OtherSingleType = void>
			requires
			(
				std::is_same_v<std::remove_cvref_t<OtherSingleType>, single>
			)
			constexpr single& swap_with(OtherSingleType&& other)
			noexcept
			(
				std::is_nothrow_swappable_v<FirstType>
			)
		{
			if constexpr (State == state_t::initialized)
			{
				if constexpr (OtherState == state_t::initialized)
				{
					std::swap(first, other.first);
				}
				else
				{
					std::construct_at(std::addressof(other.first), std::move(first));
				}
			}
			else
			{
				if constexpr (OtherState == state_t::initialized)
				{
					std::construct_at(std::addressof(first), std::move(other.first));
				}
				else // Idk & Idc
				{
					std::swap(first, other.first);
				}
			}
			return *this;
		}

		template <dynamic_states_t DynamicStates = dynamic_states, typename OtherSingleType = void>
			requires
			(
				std::is_same_v<std::remove_cvref_t<OtherSingleType>, single>
			)
		constexpr single& swap_with(const state_t state, const state_t other_state, OtherSingleType&& other)
			noexcept
			(
				std::is_nothrow_swappable_v<FirstType>
			)
		{
			std::swap(first, other.first);
			return *this;
		}
    };

	template <typename FirstType, typename SecondType>
	class pair
	{
	public:
		enum class state_t : uint8_t
		{
			unknown,
			initialized,
			unintialized
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
		explicit constexpr pair(OtherFirstType &&first, OtherSecondType &&second)
			noexcept
			(
				std::is_nothrow_constructible_v<FirstType, OtherFirstType &&> &&
				std::is_nothrow_constructible_v<SecondType, OtherSecondType &&>
			)
			: first{ std::forward<OtherFirstType>(first) }, second{ std::forward<OtherSecondType>(second) } {}

		constexpr pair(const pair &other)
			noexcept
			(
				std::is_nothrow_copy_constructible_v<FirstType> &&
				std::is_nothrow_copy_constructible_v<SecondType>
			)
			: first{ other.first }, second{ other.second } {}

		constexpr pair(const state_t other_state, const pair &other)
			noexcept
			(
				std::is_nothrow_copy_constructible_v<FirstType>&&
				std::is_nothrow_copy_constructible_v<SecondType>
				)
			: first{ other.first }, second{ other.second } {
		}

        constexpr pair(pair &&other)
            noexcept
            (
                std::is_nothrow_move_constructible_v<FirstType>&&
                std::is_nothrow_move_constructible_v<SecondType>
            )
            : first{ std::move(other.first) }, second{ std::move(other.second) } {}

		constexpr pair(const state_t other_state, pair &&other)
			noexcept
			(
				std::is_nothrow_move_constructible_v<FirstType>&&
				std::is_nothrow_move_constructible_v<SecondType>
				)
			: first{ std::move(other.first) }, second{ std::move(other.second) } {}

		template <typename ...ArgsTypes>
		explicit constexpr pair(in_place_t, ArgsTypes &&...args)
			noexcept
			(
				std::is_nothrow_constructible_v<FirstType, ArgsTypes &&...>&&
				std::is_nothrow_constructible_v<SecondType, ArgsTypes &&...>
			)
			: first{ std::forward<ArgsTypes>(args)... }, second{ std::forward<ArgsTypes>(args)... } {}

		template <typename OtherPairType>
		constexpr pair& operator=(OtherPairType&& other)
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
				std::is_nothrow_destructible_v<FirstType>&&
				std::is_nothrow_destructible_v<SecondType>
			) = default;

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
			return first == other.first && second == other.second;
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
					State == state_t::unintialized &&
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
			else if constexpr (State == state_t::unintialized)
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
			else if (state == state_t::unintialized)
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

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown, typename OtherFirstType = void, typename OtherSecondType = void>
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
					State == state_t::unintialized &&
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
			else if constexpr (State == state_t::unintialized)
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

		template <dynamic_states_t DynamicStates = dynamic_states, typename OtherFirstType = void, typename OtherSecondType = void> 
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
			else if (state == state_t::unintialized)
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

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown, typename OtherPairType = void>
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
					State == state_t::unintialized &&
					std::is_nothrow_constructible_v<FirstType, OtherPairType &&>
				)
			)
		{
			if constexpr (State == state_t::initialized)
			{
				std::destroy_at(std::addressof(first));
				std::construct_at(std::addressof(first), std::forward<OtherPairType>(other));
			}
			else if constexpr (State == state_t::unintialized)
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

		template <dynamic_states_t DynamicStates = dynamic_states, typename OtherPairType = void>
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
			else if (state == state_t::unintialized)
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

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown, typename OtherPairType = void>
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
					State == state_t::unintialized &&
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
			else if constexpr (State == state_t::unintialized)
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

		template <dynamic_states_t DynamicStates = dynamic_states, typename OtherPairType = void>
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
			else if (state == state_t::unintialized)
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

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown, typename OtherValueType = void>
		constexpr pair &copy_to(OtherValueType &&other)
			noexcept
			(
				(
					State == state_t::initialized &&
					(
						std::is_nothrow_assignable_v<OtherValueType &&, FirstType> ||
						(
							!std::is_assignable_v<OtherValueType &&, FirstType> &&
							std::is_nothrow_constructible_v<OtherValueType, FirstType>
						)
					)
				) ||
				(
					State == state_t::unintialized &&
					std::is_nothrow_constructible_v<OtherValueType, FirstType>
				) ||
				(
					State == state_t::unknown &&
					std::is_nothrow_constructible_v<OtherValueType, FirstType>
				)
			)
		{
			if constexpr (State == state_t::initialized)
			{
				if constexpr (std::is_assignable_v<OtherValueType &&, FirstType>)
				{
					other = first;
				}
				else
				{
					std::destroy_at(std::addressof(other));
					std::construct_at(std::addressof(other), first);
				}
			}
			else if constexpr (State == state_t::unintialized)
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

		template <dynamic_states_t DynamicStates = dynamic_states, typename OtherValueType = void>
		constexpr pair &copy_to(const state_t state, const state_t other_state, OtherValueType &&other)
			noexcept
			(
				std::is_nothrow_assignable_v<OtherValueType &&, FirstType> ||
				(
					!std::is_assignable_v<OtherValueType &&, FirstType> &&
					std::is_nothrow_constructible_v<OtherValueType, FirstType>
				)
			)
		{
			if (state == state_t::initialized)
			{
				if constexpr (std::is_assignable_v<OtherValueType &&, FirstType>)
				{
					other = first;
				}
				else
				{
					std::destroy_at(std::addressof(other));
					std::construct_at(std::addressof(other), first);
				}
			}
			else if (state == state_t::unintialized)
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

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown, typename OtherPairType = void>
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
					State == state_t::unintialized &&
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
			else if constexpr (State == state_t::unintialized)
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

		template <dynamic_states_t DynamicStates = dynamic_states, typename OtherPairType = void>
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
			else if (state == state_t::unintialized)
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

		template <state_t State = state_t::unknown, state_t OtherState = state_t::unknown, typename OtherFirstType = void, typename OtherSecondType = void>
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
					State == state_t::unintialized &&
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
					first = std::forward<OtherValueType>(other_first);
				}
				else
				{
					std::destroy_at(std::addressof(first));
					std::construct_at(std::addressof(first), std::forward<OtherFirstType>(other_first));
				}
				if constexpr (std::is_move_assignable_v<SecondType>)
				{
					second = std::forward<OtherValueType>(other_second);
				}
				else
				{
					std::destroy_at(std::addressof(second));
					std::construct_at(std::addressof(second), std::forward<OtherSecondType>(other_second));
				}
			}
			else if constexpr (State == state_t::unintialized)
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

		template <dynamic_states_t DynamicStates = dynamic_states, typename OtherFirstType = void, typename OtherSecondType = void>
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
			else if (state == state_t::unintialized)
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
							OtherState == state_t::unintialized &&
							std::is_nothrow_move_constructible_v<FirstType> &&
							std::is_nothrow_move_constructible_v<SecondType>
						)
					)
				) ||
				(
					State == state_t::unintialized &&
					(
						(
							OtherState == state_t::initialized &&
							std::is_nothrow_move_constructible_v<FirstType> &&
							std::is_nothrow_move_constructible_v<SecondType>
						) ||
						OtherState == state_t::unintialized
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
							OtherState == state_t::unintialized &&
							std::is_nothrow_move_constructible_v<FirstType> &&
							std::is_nothrow_move_constructible_v<SecondType>
						)
					)	
				) ||
				(
					State == state_t::unintialized &&
					(
						(
							OtherState == state_t::initialized &&
							std::is_nothrow_move_constructible_v<FirstType> &&
							std::is_nothrow_move_constructible_v<SecondType>
						) ||
						OtherState == state_t::unintialized
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
	};

} // namespace woj
