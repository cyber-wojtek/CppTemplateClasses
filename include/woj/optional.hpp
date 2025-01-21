#pragma once

#include <cassert>
#include <type_traits>
#include <limits>
#include <cstdint>
#include <optional>
#include <iostream>

#include "base.hpp"

#include "vector.hpp"
#include "meta/sequence.hpp"

namespace woj
{
    class bad_optional_access final : exception
    {
    public:
        constexpr bad_optional_access() : exception{ static_cast<uint64_t>(-1), "Bad optional access.", nullptr, nullptr } {}

        constexpr bad_optional_access(const size_t line, const char* const file, const char* const function) noexcept
            : exception{ line, "Bad optional access", file, function } {}
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
         * The optional is uninitialized.
         */
        uninitialized = 2u,
        /**
         * The optional is in unknown state.
         */
        unknown = 3u,
    };

    template <typename>
    class optional;

    template <typename>
    struct is_optional : std::false_type {};

    template <typename T>
    struct is_optional<optional<T>> : std::true_type {};

    // Placeholder for is_optional_v type trait.
    template <typename T>
    constexpr bool is_optional_v = is_optional<T>::value;

    template <typename ValueType>
    class optional
    {
    public:
        using class_type = woj::optional;
        using this_type = optional;
        using value_type = ValueType;
    	using reference = value_type&;
        using reference_type = reference;
        using const_reference = const value_type&;
        using const_reference_type = const_reference;
        using rvalue_reference = value_type&&;
        using rvalue_reference_type = rvalue_reference;
        using const_rvalue_reference = const value_type&&;
        using const_rvalue_reference_type = const_rvalue_reference;
        using pointer = value_type*;
        using pointer_type = pointer;
        using const_pointer = const value_type*;
        using const_pointer_type = const_pointer;

        union
        {
            ValueType m_value;
        };

        union
        {
            bool m_has_value;
        };

        /**
         * Constructs an empty optional.
         */
        constexpr optional() noexcept : m_has_value{ false } {}

        /**
         * Constructs an empty optional.
		 * @param none Used to enable the constructor.
         */
        explicit constexpr optional(const none_t none) noexcept : m_has_value{ false } {}

        /**
         * Constructs an uninitialized optional.
		 * @param noinit Used to enable the constructor.
         */
        explicit constexpr optional(const noinit_t noinit) noexcept
        {
            if (is_constant_evaluated())
            {
                m_has_value = false;
            }
        }

		/**
		 * Constructs an optional from another optional by copying it.
		 * @param other The optional to copy.
		 */
		constexpr optional(const optional& other)
            noexcept
            (
				std::is_nothrow_copy_constructible_v<ValueType>
            )
			requires
			(
				std::is_copy_constructible_v<ValueType>
            )
            : m_has_value{ other.m_has_value }
        {
            if (other.m_has_value)
            {
                std::construct_at(&m_value, other.m_value);
            }
        }

        /**
         * Constructs an optional from another optional by moving it.
         * @tparam OtherOptionalType The type of the other optional.
         * @param other The optional to move.
         */
		constexpr optional(optional&& other)
			noexcept
			(
				std::is_nothrow_move_constructible_v<ValueType>
			)
			requires
			(
				std::is_move_constructible_v<ValueType>
			)
			: m_has_value{ other.m_has_value }
		{
			if (other.m_has_value)
			{
				std::construct_at(&m_value, std::move(other.m_value));
				other.m_has_value = false;
			}
		}

        /**
         * Constructs an optional from another optional by copying it.
		 * @tparam OtherOptionalType The type of the other optional.
         * @param other The optional to copy.
         */
		template <typename OtherOptionalType>
			requires
			(
				is_optional_v<std::remove_cvref_t<OtherOptionalType>> &&
				std::is_constructible_v<ValueType, const typename OtherOptionalType::value_type&>
            )
    	explicit constexpr optional(const OtherOptionalType& other)
    			noexcept
    			(
					std::is_nothrow_constructible_v<ValueType, const typename OtherOptionalType::value_type&>
	            )
			: m_has_value{ other.m_has_value }
        {
            if (other.m_has_value)
            {
                std::construct_at(&m_value, other.m_value);
            }
        }

        /**
         * Constructs an optional from another optional by copying it.
		 * @tparam OtherOptionalType The type of the other optional.
         * @param other_state State of the other optional.
         * @param other The optional to copy.
         */
		template <typename OtherOptionalType>
			requires
			(
				is_optional_v<std::remove_cvref_t<OtherOptionalType>> &&
				std::is_constructible_v<ValueType, const typename OtherOptionalType::value_type&>
            )
        explicit constexpr optional(const optional_state other_state, const OtherOptionalType& other)
    		noexcept
    		(
				std::is_nothrow_constructible_v<ValueType, const typename OtherOptionalType::value_type&>
            )
        {
            if (other_state == optional_state::has_value)
            {
                m_has_value = true;
                std::construct_at(&m_value, other.m_value);
            }
            else if (other_state == optional_state::no_value)
            {
                m_has_value = false;
            }
            else if (other_state == optional_state::uninitialized)
            {
                return;
            }
            else if (other.m_has_value)
            {
                m_has_value = true;
                std::construct_at(&m_value, other.m_value);
            }
        }

        /**
         * Constructs an optional from another optional by moving it.
		 * @tparam OtherOptionalType The type of the other optional.
         * @param other The optional to move.
         */
		template <typename OtherOptionalType>
			requires
			(
				is_optional_v<std::remove_cvref_t<OtherOptionalType>> &&
                std::is_rvalue_reference_v<OtherOptionalType> &&
				std::is_constructible_v<ValueType, typename OtherOptionalType::value_type&&>
            )
		explicit constexpr optional(OtherOptionalType other)
    		noexcept
    		(
				std::is_nothrow_constructible_v<ValueType, typename OtherOptionalType::value_type&&>
            )
			: m_has_value{ other.m_has_value }
        {
            if (other.m_has_value)
            {
                std::construct_at(&m_value, std::move(other.m_value));
                other.m_has_value = false;
            }
        }

        /**
         * Constructs an optional from another optional by moving it.
		 * @tparam OtherOptionalType The type of the other optional.
         * @param other_state State of the other optional.
         * @param other The optional to move.
         */
		template <typename OtherOptionalType>
			requires
			(
				is_optional_v<std::remove_cvref_t<OtherOptionalType>> &&
				std::is_rvalue_reference_v<OtherOptionalType> &&
				std::is_constructible_v<ValueType, typename OtherOptionalType::value_type&&>
            )
		constexpr optional(const optional_state other_state, OtherOptionalType other)   
    		noexcept
    		(
				std::is_nothrow_constructible_v<ValueType, typename OtherOptionalType::value_type&&>
            )
        {
            if (other_state == optional_state::has_value)
            {
                m_has_value = true;
                std::construct_at(&m_value, std::move(other.m_value));
                other.m_has_value = false;
            }
            else if (other_state == optional_state::no_value)
            {
                m_has_value = false;
            }
            else if (other_state == optional_state::uninitialized) {}
            else if (other.m_has_value)
            {
                m_has_value = true;
                std::construct_at(&m_value, std::move(other.m_value));
                other.m_has_value = false;
            }
        }

        /**
         * Constructs an optional from a value by copying it.
         * @tparam OtherValueType The type of the value to copy.
         * @param value The value to copy.
         */
        template <typename OtherValueType>
    		requires
    		(
                !std::is_same_v<std::remove_cvref_t<OtherValueType>, std::remove_cvref_t<this_type>> &&
				std::is_constructible_v<std::remove_cvref_t<ValueType>, const OtherValueType&>
            )
        explicit constexpr optional(const OtherValueType& value)
    		noexcept
    		(
                std::is_nothrow_constructible_v<std::remove_cvref_t<ValueType>, const OtherValueType&>
            )
            : m_value{ value }, m_has_value{ true } {}

        /**
         * Constructs an optional from a value by moving it.
         * @tparam OtherValueType The type of the value to move.
         * @param value Value to move.
         */
        template <typename OtherValueType>
    		requires
    		(
				!std::is_same_v<std::remove_cvref_t<ValueType>, std::remove_cvref_t<this_type>> &&
                std::is_constructible_v<std::remove_cvref_t<ValueType>, OtherValueType&&>
            )
        explicit constexpr optional(OtherValueType&& value)
    		noexcept
    		(
                std::is_nothrow_constructible_v<std::remove_cvref_t<ValueType>, OtherValueType&&>
            )
            : m_value{ std::move(std::forward<OtherValueType>(value)) }, m_has_value{ true } {}

        /**
         * Constructs the value of the optional by forwarding the arguments.
         * @tparam OtherValueTypes The types of the arguments to forward.
         * @param values The values to forward.
         */
        template <typename... OtherValueTypes>
        explicit constexpr optional(in_place_t, OtherValueTypes&&... values)
    		noexcept
    		(
	            std::is_nothrow_constructible_v<std::remove_cvref_t<ValueType>, OtherValueTypes...>
            )
            requires
    		(
                std::is_constructible_v<std::remove_cvref_t<ValueType>, OtherValueTypes...>
            )
			: m_value{ std::forward<OtherValueTypes>(values)... }, m_has_value{ true } {}

        /**
         * Destructs the optional.
         */
        WOJ_CONSTEXPR20 ~optional()
    		noexcept
    		(
                std::is_nothrow_destructible_v<ValueType>
            )
        {
            {
                if (*this)
                {
                    std::destroy_at(&m_value);
                }
            }
        }

        /**
         * Assigns the optional by copying another optional.
         * @param other The optional to copy.
         * @return The reference to the assigned optional.
         */
		constexpr optional& operator=(const optional& other)
    		noexcept
			(
				std::is_nothrow_copy_constructible_v<ValueType> &&
				std::is_nothrow_copy_assignable_v<ValueType>
			)
			requires
			(
				std::is_copy_constructible_v<ValueType> &&
				std::is_copy_assignable_v<ValueType>
			)
        {
            return this->copy_from(other);
        }

        /**
         * Assigns the optional by moving another optional.
         * @param other The optional to move.
         * @return The reference to the assigned optional.
         */
        constexpr optional& operator=(optional&& other)
    		noexcept
    		(
                std::is_nothrow_move_constructible_v<ValueType> &&
                std::is_nothrow_move_assignable_v<ValueType>
            )
    		requires
    		(
                std::is_move_constructible_v<ValueType> &&
                std::is_move_assignable_v<ValueType>
            )
        {
            return this->move_from(std::forward<optional>(other));
        }

        /**
         * Assigns the optional by copying another optional.
         * @param other The optional to copy.
         * @return The reference to the assigned optional.
         */
		template <typename OtherOptionalType>
			requires
			(
				is_optional_v<std::remove_cvref_t<OtherOptionalType>> &&
				std::is_constructible_v<ValueType, const typename OtherOptionalType::value_type&> &&
				std::is_assignable_v<ValueType, const typename OtherOptionalType::value_type&>
            )
        constexpr optional& operator=(const OtherOptionalType& other)
            noexcept
            (
                std::is_nothrow_copy_constructible_v<ValueType>&&
                std::is_nothrow_copy_assignable_v<ValueType>
            )
        {
            return this->copy_from(other);
        }

	    /**
	     * Assigns the optional by moving another optional.
	     * @param other The optional to move.
	     * @return The reference to the assigned optional.
		 */
		template <typename OtherOptionalType>
			requires
			(
				is_optional_v<std::remove_cvref_t<OtherOptionalType>> &&
				std::is_constructible_v<ValueType, typename OtherOptionalType::value_type&&> &&
				std::is_assignable_v<ValueType, typename OtherOptionalType::value_type&&> &&
				std::is_rvalue_reference_v<OtherOptionalType>
            )
    	constexpr optional& operator=(OtherOptionalType other)
			noexcept
			(
				std::is_nothrow_constructible_v<ValueType, typename OtherOptionalType::value_type&&> &&
				std::is_nothrow_assignable_v<ValueType, typename OtherOptionalType::value_type&&>
			)
		{
			return this->move_from(std::forward<OtherOptionalType>(other));
		}


        /**
         * Assigns the optional by copying a value.
         * @tparam OtherValueType The type of the value to copy.
         * @param value The value to copy.
         * @return The reference to the assigned optional.
         */
        template <typename OtherValueType>
    		requires
			(
				!std::is_same_v<std::remove_cvref_t<OtherValueType>, std::remove_cvref_t<this_type>> &&
				std::is_constructible_v<std::remove_cvref_t<ValueType>, const OtherValueType&> &&
				std::is_assignable_v<std::remove_cvref_t<ValueType>, const OtherValueType&>
			)   
        constexpr optional& operator=(const OtherValueType& value)
    		noexcept
    		(
                std::is_nothrow_constructible_v<std::remove_cvref_t<ValueType>, const OtherValueType&> &&
                std::is_nothrow_assignable_v<std::remove_cvref_t<ValueType>, const OtherValueType&>
            )
        {
            return this->copy_from(value);
        }

        /**
         * Assigns the optional by moving a value.
         * @tparam OtherValueType The type of the value to move.
         * @param value The value to move.
         * @return The reference to the assigned optional.
         */
        template <typename OtherValueType>
    		requires
			(
				!std::is_same_v<std::remove_cvref_t<OtherValueType>, std::remove_cvref_t<this_type>>&&
				std::is_constructible_v<std::remove_cvref_t<ValueType>, OtherValueType&&>&
				std::is_assignable_v<std::remove_cvref_t<ValueType>, OtherValueType&&>
			)
		constexpr optional& operator=(OtherValueType&& value)
    		noexcept
    		(
                std::is_nothrow_constructible_v<std::remove_cvref_t<ValueType>, OtherValueType&&> &&
                std::is_nothrow_assignable_v<std::remove_cvref_t<ValueType>, OtherValueType&&>
            )
        {
            return this->move_from(std::forward<OtherValueType>(value));
        }

        /**
         * Assigns the optional to be empty.
         * @return Reference to optional.
         */
        constexpr optional& operator=(const none_t)
    		noexcept
    		(
                std::is_nothrow_destructible_v<ValueType>
			)
        {
            return this->reset();
        }

        /**
         * Assigns the optional to be uninitialized.
         * @return Reference to optional.
         */
        constexpr optional& operator=(const noinit_t)
    		noexcept
        {
            return *this;
        }

        /**
         * Converts the optional to a boolean value.
         * @return True if the optional has a value, false otherwise.
         */
        WOJ_NODISCARD explicit constexpr operator bool() const
    		noexcept
        {
            return this->has_value();
        }

        /**
         * Returns a pointer to the value.
         * @return The pointer to the value.
         */
        WOJ_NODISCARD constexpr ValueType* operator->()
    		noexcept
#ifndef NDEBUG
			(
                false
            )
#endif
        {
#if !defined(NDEBUG)
            if (!m_has_value)
                throw bad_optional_access{ 319ull, "optional.hpp", "operator->" };
#endif

            return std::addressof(m_value);
        }

        /**
         * Returns a const pointer to the value.
         * @return The const pointer to the value.
         */
        WOJ_NODISCARD constexpr const ValueType* operator->() const
    		noexcept
#ifndef NDEBUG
			(
                false
			)
#endif
        {
#if !defined(NDEBUG)
            if (!m_has_value)
                throw bad_optional_access{ 336ull, "optional.hpp", "operator->" };
#endif

            return std::addressof(m_value);
        }

        /**
         * Returns an lvalue reference to the value.
         * @return The lvalue reference to the value.
         */
        WOJ_NODISCARD constexpr ValueType& operator*()
    		noexcept
#ifndef NDEBUG
			(
				false
            )
#endif
        {
#if !defined(NDEBUG)
            if (!m_has_value)
                throw bad_optional_access{ 353ull, "optional.hpp", "operator*" };
#endif

            return m_value;
        }

        /**
         * Returns a const lvalue reference to the value.
         * @return The const lvalue reference to the value.
         */
        WOJ_NODISCARD constexpr const ValueType& operator*() const
    		noexcept
#ifndef NDEBUG
			(
                false
            )
#endif
        {
#if !defined(NDEBUG)
            if (!m_has_value)
                throw bad_optional_access{ 370ull, "optional.hpp", "operator*" };
#endif

            return m_value;
        }

        /**
         * Copies from another value to this optional.
         * @tparam OtherState UNUSED. State of the other optional.
         * @tparam State State of the current optional.
         * @param other The value to copy from.
         * @return The lvalue reference to optional.
         */
        template <optional_state State = optional_state::unknown, optional_state OtherState = optional_state::unknown, typename OtherValueType = ValueType>
    		requires
            (
                !std::is_same_v<std::remove_cvref_t<OtherValueType>, std::remove_cvref_t<this_type>> &&
                (
                    (
						(
                            State == optional_state::no_value ||
                            State == optional_state::uninitialized
                        ) &&
                        std::is_constructible_v<std::remove_cvref_t<ValueType>, const OtherValueType&>
                    ) ||
                    (
						State == optional_state::has_value &&
                        (
							std::is_assignable_v<std::remove_cvref_t<ValueType>, const OtherValueType&> ||
                            (!std::is_assignable_v<std::remove_cvref_t<ValueType>, const OtherValueType&> && std::is_constructible_v<std::remove_cvref_t<ValueType>, const OtherValueType&>)
                        )
                    )
                )
            )
        constexpr optional& copy_from(const OtherValueType& other)
    		noexcept
            (
                (
                    (
                        State == optional_state::no_value ||
						State == optional_state::uninitialized
					) && 
                    std::is_nothrow_constructible_v<std::remove_cvref_t<ValueType>, const OtherValueType&>
                ) || 
                (
                    State == optional_state::has_value &&
                    (
						(std::is_assignable_v<std::remove_cvref_t<ValueType>, const OtherValueType&> && std::is_nothrow_assignable_v<std::remove_cvref_t<ValueType>, const OtherValueType&>) ||
                        (!std::is_assignable_v<std::remove_cvref_t<ValueType>, const OtherValueType&> && std::is_nothrow_constructible_v<std::remove_cvref_t<ValueType>, const OtherValueType&>)
                    )
                )
            )
        {
            // ----------> SELF: 1 (CEVAL) <----------------
            if constexpr (State == optional_state::has_value)
            {
                // ----->> SELF: 1 (CEVAL) ASSIGN <<--------
                if constexpr (std::is_assignable_v<std::remove_cvref_t<ValueType>, OtherValueType>)
                {
					m_value = other;
                }
                // ----->> SELF: 1 (CEVAL) CONSTRUCT <<-----
                else
                {
                    std::construct_at(&m_value, other);
                }
            }
            // ----------> SELF: 0 (CEVAL) <----------------
            else if constexpr (State == optional_state::no_value || State == optional_state::uninitialized)
            {
                std::construct_at(&m_value, other);
                m_has_value = true;
            }
            // ----------> SELF: 1 (REVAL) <----------------
            else if (*this)
            {
                // ----->> SELF: 1 (REVAL) ASSIGN <<--------
                if constexpr (std::is_assignable_v<std::remove_cvref_t<ValueType>, const OtherValueType&>)
                {
                    m_value = other;
                }
                // ----->> SELF: 1 (REVAL) CONSTRUCT <<-----
                else
                {
                    std::construct_at(&m_value, other);
                }
            }
            // ----------> SELF: 0 (REVAL) <----------------
            else
            {
                std::construct_at(&m_value, other);
                m_has_value = true;
            }

            return *this;
        }

        /**
         * Copies from another value to this optional.
		 * @tparam DynamicStates Used to enable the function.
         * @param state State of the current optional.
         * @param other_state UNUSED. State of the other optional.
         * @param other The value to copy from.
         * @return The lvalue reference to optional.
         */
        template <dynamic_states_t DynamicStates = dynamic_states, typename OtherValueType = ValueType>
    		requires
    		(
                !std::is_same_v<std::remove_cvref_t<OtherValueType>, std::remove_cvref_t<this_type>> &&
				std::is_constructible_v<std::remove_cvref_t<ValueType>, const OtherValueType&> &&
				std::is_assignable_v<std::remove_cvref_t<ValueType>, const OtherValueType&>
            )
        constexpr optional& copy_from(const optional_state state, const optional_state other_state, const OtherValueType& other)
    		noexcept
            (
                std::is_nothrow_constructible_v<std::remove_cvref_t<ValueType>, const OtherValueType&> && 
                std::is_nothrow_assignable_v<std::remove_cvref_t<ValueType>, const OtherValueType&>
            )
        {
			// ----------> SELF: 1 (CEVAL) <----------------
			if (state == optional_state::has_value)
			{
				// ---->> *SELF: 1 (CEVAL) ASSIGN <<--------
				if (std::is_assignable_v<std::remove_cvref_t<ValueType>, OtherValueType>)
				{
					m_value = other;
				}
				// ---->> *SELF: 1 (CEVAL) CONSTRUCT <<-----
				else
				{
					std::construct_at(&m_value, other);
				}
			}
			// ----------> SELF: 0 (CEVAL) <----------------
			else if (state == optional_state::no_value || state == optional_state::uninitialized)
			{
				std::construct_at(&m_value, other);
				m_has_value = true;
			}
			// ----------> SELF: 1 (REVAL) <----------------
			else if (*this)
			{
				// ---->> *SELF: 1 (REVAL) ASSIGN <<--------
				if (std::is_assignable_v<std::remove_cvref_t<ValueType>, const OtherValueType&>)
				{
					m_value = other;
				}
				// ---->> *SELF: 1 (REVAL) CONSTRUCT <<-----
				else
				{
					std::construct_at(&m_value, other);
				}
			}
			// ----------> SELF: 0 (REVAL) <----------------
			else
			{
				std::construct_at(&m_value, other);
				m_has_value = true;
			}

            return *this;
        }

        /**
         * Copies from other optional to this optional.
         * @tparam State State of the current optional.
         * @tparam OtherState State of the other optional.
         * @param other The optional to copy from.
         * @return The lvalue reference to optional.
         */
        template <optional_state State = optional_state::unknown, optional_state OtherState = optional_state::unknown, typename OtherOptionalType>
			requires
			(
				is_optional_v<std::remove_cvref_t<OtherOptionalType>> &&
                (
                    OtherState == optional_state::no_value ||
					OtherState == optional_state::uninitialized ||
					(
						(
							State == optional_state::no_value ||
							State == optional_state::uninitialized
						) &&
						std::is_constructible_v<ValueType, typename OtherOptionalType::value_type>
					) ||
					(
						State == optional_state::has_value &&
						(
							(
								OtherState == optional_state::has_value &&
								(
									std::is_assignable_v<ValueType, typename OtherOptionalType::value_type> ||
									std::is_constructible_v<ValueType, typename OtherOptionalType::value_type>
									)
								) ||
							(
								OtherState == optional_state::unknown &&
								std::is_assignable_v<ValueType, typename OtherOptionalType::value_type> &&
								std::is_constructible_v<ValueType, typename OtherOptionalType::value_type>
								)
							)
						)
                )
			)
        constexpr optional& copy_from(const OtherOptionalType& other)
    		noexcept
			(
				OtherState == optional_state::no_value ||
				OtherState == optional_state::uninitialized ||
				(
					(
						State == optional_state::no_value ||
						State == optional_state::uninitialized
					) &&
					std::is_nothrow_constructible_v<ValueType, typename OtherOptionalType::value_type>
				) ||
				(
					State == optional_state::has_value &&
					(
						std::is_assignable_v<ValueType, typename OtherOptionalType::value_type> &&
						std::is_constructible_v<ValueType, typename OtherOptionalType::value_type>
					)
				)
			)

        {
            // ---------------- OTHER: 1 (CEVAL) ----------------
            if constexpr (OtherState == optional_state::has_value)
            {
                // ----------> *OTHER: 1 (CEVAL), SELF: 1 (CEVAL) <----------------
                if constexpr (State == optional_state::has_value)
                {
                    // ----->> *OTHER: 1 (CEVAL), SELF: 1 (CEVAL) ASSIGN <<--------
                    if constexpr (std::is_assignable_v<ValueType, typename OtherOptionalType::value_type>)
                    {
						m_value = other.m_value;
                    }
                    // ----->> *OTHER: 1 (CEVAL), SELF: 1 (CEVAL) CONSTRUCT <<-----
                    else
                    {
                        std::construct_at(&m_value, other.m_value);
                    }
                }
                // ----------> *OTHER: 1 (CEVAL), SELF: 0 (CEVAL) <----------------
                else if constexpr (State == optional_state::no_value || State == optional_state::uninitialized)
                {
                    std::construct_at(&m_value, other.m_value);
                    m_has_value = true;
                }
                // ----------> *OTHER: 1 (CEVAL), SELF: 1 (REVAL) <----------------
                else if (*this)
                {
					// ----->> *OTHER: 1 (REVAL) ASSIGN <<--------
					if (std::is_assignable_v<ValueType, typename OtherOptionalType::value_type>)
					{
						m_value = other.m_value;
					}
					// ----->> *OTHER: 1 (REVAL) CONSTRUCT <<-----
					else
					{
						std::construct_at(&m_value, other.m_value);
					}
                }
                // ----------> *OTHER: 1 (CEVAL), SELF: 0 (REVAL) <----------------
                else
                {
                    std::construct_at(&m_value, other.m_value);
                    m_has_value = true;
                }
            }
            // ----------------- OTHER: 0 (CEVAL) -----------------
            else if constexpr (OtherState == optional_state::no_value)
            {
                // -----------> *OTHER: 0 (CEVAL), SELF: 1|? (CEVAL) <----------------
                if constexpr (State == optional_state::has_value || State == optional_state::unknown || State == optional_state::uninitialized)
                {
                    m_has_value = false;
                }
                // -----------> *OTHER: 0 (CEVAL), SELF: 0 (CEVAL) <---------------- OMITTED
            }
            // ----------------- OTHER: - (CEVAL) ----------------- OMITTED
            // ----------------- OTHER: ? (CEVAL) -----------------
            else if constexpr (OtherState != optional_state::uninitialized)
            {
                // ------------> OTHER: 1 (REVAL) <----------------
                if (other.m_has_value)
                {
                    // ------>> *OTHER: 1 (REVAL), SELF: 1 (CEVAL) <<---------------
                    if constexpr (State == optional_state::has_value)
                    {
						// ->>> *OTHER: 1 (CEVAL), *SELF: 1 (CEVAL) ASSIGN <<<------
						if constexpr (std::is_assignable_v<ValueType, typename OtherOptionalType::value_type>)
						{
							m_value = other.m_value;
						}
						// ->>> *OTHER: 1 (CEVAL), *SELF: 1 (CEVAL) CONSTRUCT <<<---
						else
						{
							std::construct_at(&m_value, other.m_value);
						}
                    }
                    // ------>> *OTHER: 1 (REVAL), SELF: 0|- (CEVAL) <----------------
                    else if constexpr (State == optional_state::no_value || State == optional_state::uninitialized)
                    {
                        m_has_value = true;
                        std::construct_at(&m_value, other.m_value);
                    }
                    // ------>> *OTHER: 1 (REVAL), SELF: 1 (REVAL) <----------------
                    else if (*this)
                    {
                        // ->>> *OTHER: 1 (REVAL), *SELF: 1 (REVAL) ASSIGN <<<------
                        if constexpr (std::is_assignable_v<ValueType, typename OtherOptionalType::value_type>)
                        {
                            m_value = other.m_value;
                        }
                        // ->>> *OTHER: 1 (REVAL), *SELF: 1 (REVAL) CONSTRUCT <<<---
                        else
                        {
                            std::construct_at(&m_value, other.m_value);
                        }
                    }
                    // ------>> *OTHER: 1 (REVAL), SELF: 0 (REVAL) <----------------
                    else
                    {
                        m_has_value = true;
                        std::construct_at(&m_value, other.m_value);
                    }
                }
                // ------------> OTHER: 0 (REVAL) <----------------
                else
                {
                    // ------>> *OTHER: 0 (REVAL), SELF: 1|? (CEVAL) <----------------
                    if constexpr (State == optional_state::has_value || State == optional_state::unknown || State == optional_state::uninitialized)
                    {
                        m_has_value = false;
                    }
                    // ------>> *OTHER: 0 (REVAL), SELF: 0|- (CEVAL) <---------------- OMITTED
                }
            }

            return *this;
        }

        /**
         * Copies from another optional to this optional.
		 * @tparam DynamicStates Used to enable the function.
		 * @tparam OtherOptionalType The type of the optional to copy from.
         * @param state State of the current optional.
		 * @param other_state State of the current optional to copy from.
         * @param other The optional to copy from.
         * @return The lvalue reference to optional.
         */
        template <dynamic_states_t DynamicStates = dynamic_states, typename OtherOptionalType>
			requires
			(
				is_optional_v<std::remove_cvref_t<OtherOptionalType>> &&
                std::is_assignable_v<ValueType, typename OtherOptionalType::value_type> &&
                std::is_constructible_v<ValueType, typename OtherOptionalType::value_type>
            )
        constexpr optional& copy_from(const optional_state state, const optional_state other_state, const OtherOptionalType& other)
    		noexcept
            (
                std::is_nothrow_constructible_v<ValueType, typename OtherOptionalType::value_type> &&
                std::is_nothrow_assignable_v<ValueType, typename OtherOptionalType::value_type>
            )
        {
			// ---------------- OTHER: 1 (CEVAL) ----------------
			if (other_state == optional_state::has_value)
			{
				// ----------> *OTHER: 1 (CEVAL), SELF: 1 (CEVAL) <----------------
				if (state == optional_state::has_value)
				{
					// ----->> *OTHER: 1 (CEVAL), SELF: 1 (CEVAL) ASSIGN <<--------
					if (std::is_assignable_v<ValueType, typename OtherOptionalType::value_type>)
					{
						m_value = other.m_value;
					}
					// ----->> *OTHER: 1 (CEVAL), SELF: 1 (CEVAL) CONSTRUCT <<-----
					else
					{
						std::construct_at(&m_value, other.m_value);
					}
				}
				// ----------> *OTHER: 1 (CEVAL), SELF: 0 (CEVAL) <----------------
				else if (state == optional_state::no_value || state == optional_state::uninitialized)
				{
					std::construct_at(&m_value, other.m_value);
					m_has_value = true;
				}
				// ----------> *OTHER: 1 (CEVAL), SELF: 1 (REVAL) <----------------
				else if (*this)
				{
					// ----->> *OTHER: 1 (REVAL) ASSIGN <<--------
					if (std::is_assignable_v<ValueType, typename OtherOptionalType::value_type>)
					{
						m_value = other.m_value;
					}
					// ----->> *OTHER: 1 (REVAL) CONSTRUCT <<-----
					else
					{
						std::construct_at(&m_value, other.m_value);
					}
				}
				// ----------> *OTHER: 1 (CEVAL), SELF: 0 (REVAL) <----------------
				else
				{
					std::construct_at(&m_value, other.m_value);
					m_has_value = true;
				}
			}
			// ----------------- OTHER: 0 (CEVAL) -----------------
			else if (other_state == optional_state::no_value)
			{
				// -----------> *OTHER: 0 (CEVAL), SELF: 1|? (CEVAL) <----------------
				if (state == optional_state::has_value || state == optional_state::unknown || state == optional_state::uninitialized)
				{
					m_has_value = false;
				}
				// -----------> *OTHER: 0 (CEVAL), SELF: 0 (CEVAL) <---------------- OMITTED
			}
			// ----------------- OTHER: - (CEVAL) ----------------- OMITTED
			// ----------------- OTHER: ? (CEVAL) -----------------
			else if (other_state != optional_state::uninitialized)
			{
				// ------------> OTHER: 1 (REVAL) <----------------
				if (other.m_has_value)
				{
					// ------>> *OTHER: 1 (REVAL), SELF: 1 (CEVAL) <<---------------
					if (state == optional_state::has_value)
					{
						// ->>> *OTHER: 1 (CEVAL), *SELF: 1 (CEVAL) ASSIGN <<<------
						if (std::is_assignable_v<ValueType, typename OtherOptionalType::value_type>)
						{
							m_value = other.m_value;
						}
						// ->>> *OTHER: 1 (CEVAL), *SELF: 1 (CEVAL) CONSTRUCT <<<---
						else
						{
							std::construct_at(&m_value, other.m_value);
						}
					} 
					// ------>> *OTHER: 1 (REVAL), SELF: 0|- (CEVAL) <----------------
					else if (state == optional_state::no_value || state == optional_state::uninitialized)
					{
						m_has_value = true;
						std::construct_at(&m_value, other.m_value);
					}
					// ------>> *OTHER: 1 (REVAL), SELF: 1 (REVAL) <----------------
					else if (*this)
					{
                        // ->>> *OTHER: 1 (REVAL), *SELF: 1 (REVAL) ASSIGN <<<------ 
						if (std::is_assignable_v<ValueType, typename OtherOptionalType::value_type>)
						{
							m_value = other.m_value;
						}
                        // ->>> *OTHER: 1 (REVAL), *SELF: 1 (REVAL) CONSTRUCT <<<---
						else
						{
							std::construct_at(&m_value, other.m_value);
						}
					}
					// ------>> *OTHER: 1 (REVAL), SELF: 0 (REVAL) <----------------
					else
					{
						m_has_value = true;
						std::construct_at(&m_value, other.m_value);
					}
				}
				// ------------> OTHER: 0 (REVAL) <----------------
				else
				{
					// ------>> *OTHER: 0 (REVAL), SELF: 1|? (CEVAL) <----------------
					if (state == optional_state::has_value || state == optional_state::unknown || state == optional_state::uninitialized)
					{
						m_has_value = false;
					}
					// ------>> *OTHER: 0 (REVAL), SELF: 0|- (CEVAL) <---------------- OMITTED
				}
			}

            return *this;
        }

        /**
         * Copies from another value to new optional.
		 * @tparam OtherState UNUSED. State of the current optional to copy from.
		 * @tparam OtherValueType The type of the value to copy.
         * @param other The value to copy from.
         * @return The new optional.
         */
        template <optional_state OtherState = optional_state::unknown, typename OtherValueType = ValueType>
			requires
			(
				!std::is_same_v<std::remove_cvref_t<OtherValueType>, std::remove_cvref_t<this_type>> &&
	            std::is_constructible_v<std::remove_cvref_t<ValueType>, const OtherValueType&> 
			)
        static constexpr optional copied_from(const OtherValueType& other)
			noexcept
			(
				(std::is_assignable_v<std::remove_cvref_t<ValueType>, const OtherValueType&> && std::is_nothrow_assignable_v<std::remove_cvref_t<ValueType>, const OtherValueType&>) ||
				(!std::is_assignable_v<std::remove_cvref_t<ValueType>, const OtherValueType&> && std::is_nothrow_constructible_v<std::remove_cvref_t<ValueType>, const OtherValueType&>)
            )
        {
			optional temp{ noinit };
			temp.template copy_from<optional_state::uninitialized, OtherState>(other);
            return std::move(temp);
        }

        /**
         * Copies from another value to new optional.
         * @tparam DynamicStates Used to enable the function.
		 * @tparam OtherValueType The type of the value to copy.
		 * @param other_state UNUSED. State of the current optional to copy from.
         * @param other The value to copy from.
         * @return The new optional.
         */
        template <dynamic_states_t DynamicStates = dynamic_states, typename OtherValueType = ValueType>
			requires
			(
				!std::is_same_v<std::remove_cvref_t<OtherValueType>, std::remove_cvref_t<this_type>> &&
				std::is_constructible_v<std::remove_cvref_t<ValueType>, const OtherValueType&>
            )
        static constexpr optional copied_from(const optional_state other_state, const OtherValueType& other)
    		noexcept
            (
                std::is_nothrow_constructible_v<std::remove_cvref_t<ValueType>, const OtherValueType&>
            )
        {
			optional temp{ noinit };
			temp.copy_from(optional_state::uninitialized, other_state, other);
            return std::move(temp);
        }

        /**
         * Copies from another optional to new optional.
		 * @tparam OtherState State of the current optional to copy from.
		 * @tparam OtherOptionalType Type of the optional to copy from.
         * @param other The optional to copy from.
         * @return The new optional.
         */
        template <optional_state OtherState = optional_state::unknown, typename OtherOptionalType>
			requires
			(
				is_optional_v<std::remove_cvref_t<OtherOptionalType>> &&
				(
					OtherState == optional_state::no_value ||
					OtherState == optional_state::uninitialized ||
					std::is_constructible_v<ValueType, typename OtherOptionalType::value_type>
				)
			)
		static constexpr optional copied_from(const OtherOptionalType& other)
    		noexcept
    		(
				OtherState == optional_state::no_value ||
				OtherState == optional_state::uninitialized ||
				std::is_nothrow_constructible_v<ValueType, typename OtherOptionalType::value_type>
            )
        {
			optional temp{ noinit };
			temp.template copy_from<optional_state::uninitialized, OtherState>(other);
            return std::move(temp);
        }

        /**
         * Copies from another optional to new optional.
		 * @tparam DynamicStates Used to enable the function.
		 * @tparam OtherOptionalType Type of the optional to copy from.
		 * @param other_state State of the current optional to copy from.
         * @param other The optional to copy from.
         * @return The new optional.
         */
		template <dynamic_states_t DynamicStates = dynamic_states, typename OtherOptionalType>
			requires
		    (
				std::is_constructible_v<ValueType, const typename OtherOptionalType::value_type&>
            )
		static constexpr optional copied_from(const optional_state other_state, const OtherOptionalType& other)
    		noexcept
    		(
				std::is_nothrow_constructible_v<ValueType, const typename OtherOptionalType::value_type&>
            )
        {
            optional temp{ noinit };
            temp.copy_from(optional_state::uninitialized, other_state, other);
            return std::move(temp);
        }

    private:

        /**
         * Copies from optional to another value.
         * @tparam State State of the current optional.
         * @param other The value to copy to.
         * @return The lvalue reference to optional.
         */
        template <optional_state State = optional_state::unknown, typename OtherValueType>
        constexpr void copy_to_helper(OtherValueType&& other) const
    		noexcept
#ifndef NDEBUG
			(
                State == optional_state::has_value && 
                (
                    std::is_nothrow_assignable_v<std::remove_cvref_t<OtherValueType>, ValueType> ||
					(
                        !std::is_assignable_v<std::remove_cvref_t<OtherValueType>, ValueType> &&
						std::is_nothrow_constructible_v<std::remove_cvref_t<OtherValueType>, ValueType>
					)
				)
			)
#else
				(
					std::is_nothrow_assignable_v<std::remove_cvref_t<OtherValueType>, ValueType> ||
					(
						!std::is_assignable_v<std::remove_cvref_t<OtherValueType>, ValueType> &&
						std::is_nothrow_constructible_v<std::remove_cvref_t<OtherValueType>, ValueType>
					)
				)
#endif
        {
            // ---------------- SELF: 1 (CEVAL) ----------------
            if constexpr (State == optional_state::has_value)
            {
				if constexpr (std::is_assignable_v<OtherValueType&&, const ValueType&>)
				{
					other = m_value;
				}
				else
				{
					std::construct_at(&other, m_value);
				}
            }

            /*if constexpr (State == optional_state::no_value || State == optional_state::uninitialized)
            {
#ifndef NDEBUG
                throw bad_optional_access{ 1092ull, "optional.hpp", "copy_to_helper" };
#else
                other = m_value;
#endif
            }*/

            if constexpr (State == optional_state::unknown)
            {
                if (*this)
                {
                    if constexpr (std::is_assignable_v<OtherValueType&&, const ValueType&>)
                    {
                        other = m_value;
                    }
					else
					{
						std::construct_at(&other, m_value);
					}
                }
                else
                {
#ifndef NDEBUG
                    throw bad_optional_access{ 763ull, "optional.hpp", "copy_to_helper" };
#else
					if constexpr (std::is_assignable_v<OtherValueType&&, const ValueType&>)
					{
						other = m_value;
					}
					else
					{
						std::construct_at(&other, m_value);
					}
#endif
                }
            }
        }

    public:

        /**
         * Copies from optional to another value.
         * @tparam State State of the current optional.
         * @tparam OtherState UNUSED. State of the other optional.
         * @param other The value to copy to.
         * @return The lvalue reference to optional.
         */
        template <optional_state State = optional_state::unknown, optional_state OtherState = optional_state::unknown, typename OtherValueType>
			requires
			(
				!std::is_same_v<std::remove_cvref_t<OtherValueType>, std::remove_cvref_t<this_type>> &&
				(
                    (
						State == optional_state::unknown &&&
						std::is_assignable_v<OtherValueType&&, const ValueType&> &&
						std::is_constructible_v<OtherValueType&&, const ValueType&>
					) ||
					(
						State == optional_state::has_value &&
                        (
							std::is_assignable_v<OtherValueType&&, const ValueType&> ||
							std::is_constructible_v<OtherValueType&&, const ValueType&>
                        )
                    )
                )
			)
        constexpr const optional& copy_to(OtherValueType&& other) const
    		noexcept
#ifndef NDEBUG
			(
				State == optional_state::has_value &&
				(
					std::is_nothrow_assignable_v<std::remove_cvref_t<OtherValueType>, ValueType> ||
					(
						!std::is_assignable_v<std::remove_cvref_t<OtherValueType>, ValueType> &&
						std::is_nothrow_constructible_v<std::remove_cvref_t<OtherValueType>, ValueType>
					)
				)
			)
#else
				(
					std::is_nothrow_assignable_v<std::remove_cvref_t<OtherValueType>, ValueType> ||
					(
						!std::is_assignable_v<std::remove_cvref_t<OtherValueType>, ValueType> &&
						std::is_nothrow_constructible_v<std::remove_cvref_t<OtherValueType>, ValueType>
					)
				)
#endif
        {
            this->copy_to_helper<State, OtherValueType>(std::forward<OtherValueType>(other));

            return *this;
        }

        /**
         * Copies from optional to another value.
         * @tparam State State of the current optional.
         * @tparam OtherState UNUSED. State of the other optional.
         * @param other The value to copy to.
         * @return The lvalue reference to optional.
         */
        template <optional_state State = optional_state::unknown, optional_state OtherState = optional_state::unknown, typename OtherValueType>
			requires
			(
				!std::is_same_v<std::remove_cvref_t<OtherValueType>, std::remove_cvref_t<this_type>> &&
				(
					(
						State == optional_state::unknown && &
						std::is_assignable_v<OtherValueType&&, const ValueType&>&&
						std::is_constructible_v<OtherValueType&&, const ValueType&>
						) ||
					(
						State == optional_state::has_value &&
						(
							std::is_assignable_v<OtherValueType&&, const ValueType&> ||
							std::is_constructible_v<OtherValueType&&, const ValueType&>
						)
					)
				)
			)
        constexpr optional& copy_to(OtherValueType&& other)
    		noexcept
#ifndef NDEBUG
            (
				State == optional_state::has_value &&
				(
					std::is_nothrow_assignable_v<std::remove_cvref_t<OtherValueType>, ValueType> ||
					(
						!std::is_assignable_v<std::remove_cvref_t<OtherValueType>, ValueType> &&
						std::is_nothrow_constructible_v<std::remove_cvref_t<OtherValueType>, ValueType>
					)
				)
            )
#else
			(
				std::is_nothrow_assignable_v<std::remove_cvref_t<OtherValueType>, ValueType> ||
                (
					!std::is_assignable_v<std::remove_cvref_t<OtherValueType>, ValueType> &&
					std::is_nothrow_constructible_v<std::remove_cvref_t<OtherValueType>, ValueType>
                )
			)
#endif
        {
            this->copy_to_helper<State, OtherValueType>(std::forward<OtherValueType>(other));

            return *this;
        }

    private:

        /**
         * Copies from optional to another value.
		 * @tparam DynamicStates Used to enable the function.
         * @param state State of the current optional.
         * @param other The value to copy to.
         * @return The lvalue reference to optional.
         */
        template <dynamic_states_t DynamicStates = dynamic_states, typename OtherValueType>
        constexpr void copy_to_helper(const optional_state state, OtherValueType&& other) const
    		noexcept
#ifndef NDEBUG
            (
                false
			)
#else
			(
				std::is_nothrow_assignable_v<OtherValueType&&, ValueType> ||
                (
					!std::is_assignable_v<OtherValueType&&, ValueType> &&
					std::is_nothrow_constructible_v<OtherValueType&&, ValueType>
                )
            )
#endif
        {
            // ---------------- SELF: 1 (CEVAL) ----------------
            if (state == optional_state::has_value)
            {
				if constexpr (std::is_assignable_v<OtherValueType&&, ValueType>)
				{
					other = m_value;
				}
				else
				{
					std::construct_at(&other, m_value);
				}
            }

            if (state == optional_state::no_value || state == optional_state::uninitialized)
            {
#ifndef NDEBUG
                throw bad_optional_access{ 832ull, "optional.hpp", "copy_to_helper" };
#else
				if constexpr (std::is_assignable_v<OtherValueType&&, ValueType>)
				{
					other = m_value;
				}
				else
				{
					std::construct_at(&other, m_value);
				}
#endif
            }

            if (state == optional_state::unknown)
            {
                if (*this)
                {
                    if constexpr (std::is_assignable_v<OtherValueType&&, ValueType>)
                    {
                        other = m_value;
                    }
					else
					{
						std::construct_at(&other, m_value);
					}
                }
                else
                {
#ifndef NDEBUG
                    throw bad_optional_access{ 847ull, "optional.hpp", "copy_to_helper" };
#else
					if constexpr (std::is_assignable_v<OtherValueType&&, ValueType>)
					{
						other = m_value;
					}
					else
					{
						std::construct_at(&other, m_value);
					}
#endif
                }
            }
        }

    public:

        /**
         * Copies from optional to another value.
		 * @tparam DynamicStates Used to enable the function.
         * @param state State of the current optional.
         * @param other_state UNUSED. State of the other optional.
         * @param other The value to copy to.
         * @return The lvalue reference to optional.
         */
        template <dynamic_states_t DynamicStates = dynamic_states, typename OtherValueType>
    		requires
    		(
				!std::is_same_v<std::remove_cvref_t<OtherValueType>, std::remove_cvref_t<this_type>> &&
				std::is_assignable_v<OtherValueType&&, ValueType> &&
				std::is_constructible_v<OtherValueType&&, ValueType>
            )
        constexpr const optional& copy_to(const optional_state state, const optional_state other_state, OtherValueType&& other) const
    		noexcept
#ifndef NDEBUG
            (
                false
			)
#else
			(
				std::is_nothrow_assignable_v<OtherValueType&&, ValueType> ||
				(
					!std::is_assignable_v<OtherValueType&&, ValueType> &&
					std::is_nothrow_constructible_v<OtherValueType&&, ValueType>
				)
			)
#endif
        {
            this->copy_to_helper<dynamic_states, OtherValueType>(state, std::forward<OtherValueType>(other));

            return *this;
        }

        /**
         * Copies from optional to another value.
		 * @tparam DynamicStates Used to enable the function.
		 * @tparam OtherValueType The type of the value to copy.
         * @param state State of the current optional.
         * @param other_state UNUSED. State of the other optional.
         * @param other The value to copy to.
         * @return The lvalue reference to optional.
         */
        template <dynamic_states_t DynamicStates = dynamic_states, typename OtherValueType>
			requires
			(
				!std::is_same_v<std::remove_cvref_t<OtherValueType>, std::remove_cvref_t<this_type>> &&
				(
					!std::is_same_v<std::remove_cvref_t<OtherValueType>, std::remove_cvref_t<this_type>>&&
					std::is_assignable_v<OtherValueType&&, ValueType>&&
					std::is_constructible_v<OtherValueType&&, ValueType>
				)
			)
        constexpr optional& copy_to(const optional_state state, const optional_state other_state, OtherValueType&& other) noexcept
#ifndef NDEBUG
            (
                false
			)
#else
			(
				std::is_nothrow_assignable_v<OtherValueType&&, ValueType> ||
				(
					!std::is_assignable_v<OtherValueType&&, ValueType> &&
					std::is_nothrow_constructible_v<OtherValueType&&, ValueType>
				)
            )
#endif
        {
            this->copy_to_helper<dynamic_states, OtherValueType>(state, std::forward<OtherValueType>(other));

            return *this;
        }

    private:

        /**
         * Copies from optional to another optional.
         * @tparam State State of the current optional.
         * @tparam OtherState State of the other optional.
		 * @tparam OtherOptionalType The type of the optional to copy to.
         * @param other The optional to copy to.
         */
        template <optional_state State = optional_state::unknown, optional_state OtherState = optional_state::unknown, typename OtherOptionalType>
        constexpr void copy_to_helper(OtherOptionalType&& other) const
    		noexcept
			(
				is_optional_v<std::remove_cvref_t<OtherOptionalType>> &&
				(
					State == optional_state::has_value &&
					(
						(
							(
								OtherState == optional_state::no_value ||
								OtherState == optional_state::uninitialized
							) &&
							std::is_nothrow_constructible_v<typename OtherOptionalType::value_type, ValueType>
						) ||
						(
							OtherState == optional_state::has_value &&
							(
								std::is_nothrow_assignable_v<typename OtherOptionalType::value_type, ValueType> ||
                                (
									!std::is_assignable_v<typename OtherOptionalType::value_type, ValueType> &&
                                    std::is_nothrow_constructible_v<typename OtherOptionalType::value_type, ValueType>
                                )
							)
						) ||
						(
							OtherState == optional_state::unknown &&
							(
								std::is_nothrow_assignable_v<typename OtherOptionalType::value_type, ValueType> &&
								std::is_nothrow_constructible_v<typename OtherOptionalType::value_type, ValueType>
							)
						)
					)
				)
            )
        {
            // ---------------- SELF: 1 (CEVAL) ----------------
            if constexpr (State == optional_state::has_value)
            {
                // ----------> *SELF: 1 (CEVAL), OTHER: 1 (CEVAL) <----------------
                if constexpr (OtherState == optional_state::has_value)
                {
                    other.m_value = m_value;
                }
                // ----------> *SELF: 1 (CEVAL), OTHER: 0 (CEVAL) <----------------
                else if constexpr (OtherState == optional_state::no_value || OtherState == optional_state::uninitialized)
                {
                    std::construct_at(&other.m_value, m_value);
                    other.m_has_value = true;
                }
                // ----------> *SELF: 1 (CEVAL), OTHER: 1 (REVAL) <----------------
                else if (other.m_has_value)
                {
                    other.m_value = m_value;
                }
                // ----------> *SELF: 1 (CEVAL), OTHER: 0 (REVAL) <----------------
                else
                {
                    std::construct_at(&other.m_value, m_value);
                    other.m_has_value = true;
                }
            }
            // ----------------- SELF: 0 (CEVAL) -----------------
            else if constexpr (State == optional_state::no_value)
            {
                // -----------> *SELF: 0 (CEVAL), OTHER: 1|? (CEVAL) <----------------
                if constexpr (OtherState == optional_state::has_value || OtherState == optional_state::unknown || OtherState == optional_state::uninitialized)
                {
                    other.m_has_value = false;
                }
                // -----------> *SELF: 0 (CEVAL), OTHER: 0 (CEVAL) <---------------- OMITTED
            }
            // ----------------- SELF: - (CEVAL) ----------------- OMITTED
            // ----------------- SELF: ? (CEVAL) -----------------
            else if constexpr (State != optional_state::uninitialized)
            {
                // ------------> SELF: 1 (REVAL) <----------------
                if (*this)
                {
                    // ------>> *SELF: 1 (REVAL), OTHER: 1 (CEVAL) <----------------
                    if constexpr (OtherState == optional_state::has_value)
                    {
                        other.m_value = m_value;
                    }
                    // ------>> *SELF: 1 (REVAL), OTHER: 0 (CEVAL) <----------------
                    else if constexpr (OtherState == optional_state::no_value || OtherState == optional_state::uninitialized)
                    {
                        other.m_has_value = true;
                        std::construct_at(&other.m_value, m_value);
                    }
                    // ------>> *SELF: 1 (REVAL), OTHER: 1 (REVAL) <----------------
                    else if (other.m_has_value1)
                    {
                        other.m_value = m_value;
                    }
                    // ------>> *SELF: 1 (REVAL), OTHER: 0 (REVAL) <----------------
                    else
                    {
                        other.m_has_value = true;
                        std::construct_at(&other.m_value, m_value);
                    }
                }
                // ------------> SELF: 0 (REVAL) <----------------
                else
                {
                    // ------>> *SELF: 0 (REVAL), OTHER: 1|? (CEVAL) <----------------
                    if constexpr (OtherState == optional_state::has_value || OtherState == optional_state::unknown || OtherState == optional_state::uninitialized)
                    {
                        other.m_has_value = false;
                    }
                    // ------>> *SELF: 0 (REVAL), OTHER: 0|- (CEVAL) <---------------- OMITTED
                }
            }
        }

    public:

        /**
         * Copies from optional to another optional.
         * @tparam State State of the current optional.
         * @tparam OtherState State of the other optional.
		 * @tparam OtherOptionalType Type of the optional to copy to.
         * @param other The optional to copy to.
         * @return The lvalue reference to optional.
         */
        template <optional_state State = optional_state::unknown, optional_state OtherState = optional_state::unknown, typename OtherOptionalType>
			requires
			(
				is_optional_v<std::remove_cvref_t<OtherOptionalType>> &&
				(
					State == optional_state::no_value ||
					State == optional_state::uninitialized ||
					(
						(
							State == optional_state::has_value ||
							State == optional_state::unknown
							) &&
						(
							(
								(
									OtherState == optional_state::no_value ||
									OtherState == optional_state::uninitialized
									) &&
								std::is_constructible_v<typename OtherOptionalType::value_type, ValueType>
								) ||
							(
								OtherState == optional_state::has_value &&
								(
									std::is_assignable_v<typename OtherOptionalType::value_type, ValueType> ||
									std::is_constructible_v<typename OtherOptionalType::value_type, ValueType>
									)
								) ||
							(
								OtherState == optional_state::unknown &&
								(
									std::is_assignable_v<typename OtherOptionalType::value_type, ValueType> &&
									std::is_constructible_v<typename OtherOptionalType::value_type, ValueType>
								)
							)
						)
					)
				)
			)
        constexpr const optional& copy_to(OtherOptionalType&& other) const
			noexcept
			(
				is_optional_v<std::remove_cvref_t<OtherOptionalType>> &&
				(
					State == optional_state::has_value &&
					(
						(
							(
								OtherState == optional_state::no_value ||
								OtherState == optional_state::uninitialized
								) &&
							std::is_nothrow_constructible_v<typename OtherOptionalType::value_type, ValueType>
							) ||
						(
							OtherState == optional_state::has_value &&
							(
								std::is_nothrow_assignable_v<typename OtherOptionalType::value_type, ValueType> ||
								(
									!std::is_assignable_v<typename OtherOptionalType::value_type, ValueType> &&
									std::is_nothrow_constructible_v<typename OtherOptionalType::value_type, ValueType>
									)
								)
							) ||
						(
							OtherState == optional_state::unknown &&
							(
								std::is_nothrow_assignable_v<typename OtherOptionalType::value_type, ValueType> &&
								std::is_nothrow_constructible_v<typename OtherOptionalType::value_type, ValueType>
								)
							)
						)
					)
				)
        {
            this->template copy_to_helper<State, OtherState, OtherOptionalType>(std::forward<OtherOptionalType>(other));

            return *this;
        }

            /**
             * Copies from optional to another optional.
             * @tparam State State of the current optional.
             * @tparam OtherState State of the other optional.
             * @tparam OtherOptionalType Type of the optional to copy to.
             * @param other The optional to copy to.
             * @return The lvalue reference to optional.
             */
            template <optional_state State = optional_state::unknown, optional_state OtherState = optional_state::unknown, typename OtherOptionalType>
                requires
            (
                is_optional_v<std::remove_cvref_t<OtherOptionalType>> &&
                (
                    State == optional_state::no_value ||
                    State == optional_state::uninitialized ||
                    (
                        (
                            State == optional_state::has_value ||
                            State == optional_state::unknown
                            ) &&
                        (
                            (
                                (
                                    OtherState == optional_state::no_value ||
                                    OtherState == optional_state::uninitialized
                                    ) &&
                                std::is_constructible_v<typename OtherOptionalType::value_type, ValueType>
                                ) ||
                            (
                                OtherState == optional_state::has_value &&
                                (
                                    std::is_assignable_v<typename OtherOptionalType::value_type, ValueType> ||
                                    std::is_constructible_v<typename OtherOptionalType::value_type, ValueType>
                                    )
                                ) ||
                            (
                                OtherState == optional_state::unknown &&
                                (
                                    std::is_assignable_v<typename OtherOptionalType::value_type, ValueType> &&
                                    std::is_constructible_v<typename OtherOptionalType::value_type, ValueType>
                                    )
                                )
                            )
                        )
                    )
                )
                constexpr const optional& copy_to(OtherOptionalType&& other)
                noexcept
                (
                    is_optional_v<std::remove_cvref_t<OtherOptionalType>> &&
                    (
                        State == optional_state::has_value &&
                        (
                            (
                                (
                                    OtherState == optional_state::no_value ||
                                    OtherState == optional_state::uninitialized
                                    ) &&
                                std::is_nothrow_constructible_v<typename OtherOptionalType::value_type, ValueType>
                                ) ||
                            (
                                OtherState == optional_state::has_value &&
                                (
                                    std::is_nothrow_assignable_v<typename OtherOptionalType::value_type, ValueType> ||
                                    (
                                        !std::is_assignable_v<typename OtherOptionalType::value_type, ValueType> &&
                                        std::is_nothrow_constructible_v<typename OtherOptionalType::value_type, ValueType>
                                        )
                                    )
                                ) ||
                            (
                                OtherState == optional_state::unknown &&
                                (
                                    std::is_nothrow_assignable_v<typename OtherOptionalType::value_type, ValueType> &&
                                    std::is_nothrow_constructible_v<typename OtherOptionalType::value_type, ValueType>
                                    )
                                )
                            )
                        )
                    )
            {
                this->template copy_to_helper<State, OtherState, OtherOptionalType>(std::forward<OtherOptionalType>(other));

                return *this;
            }

    private:

        /**
         * Copies from optional to another optional.
		 * @tparam DynamicStates Used to enable the function.
		 * @tparam OtherOptionalType Type of the optional to copy to.
         * @param state State of the current optional.
         * @param other_state State of the other optional.
         * @param other The optional to copy to.
         */
        template <dynamic_states_t DynamicStates, typename OtherOptionalType>
        constexpr void copy_to_helper(const optional_state state, const optional_state other_state, OtherOptionalType&& other) const
    		noexcept
			(
				std::is_nothrow_constructible_v<ValueType, const typename OtherOptionalType::value_type&> &&
				std::is_nothrow_assignable_v<ValueType, typename OtherOptionalType::value_type>
            )
        {
            // ---------------- SELF: 1 (CEVAL) ----------------
            if (state == optional_state::has_value)
            {
                // ----------> *SELF: 1 (CEVAL), OTHER: 1 (CEVAL) <----------------
                if (other_state == optional_state::has_value)
                {
                    other.m_value = m_value;
                }
                // ----------> *SELF: 1 (CEVAL), OTHER: 0 (CEVAL) <----------------
                else if (other_state == optional_state::no_value || other_state == optional_state::uninitialized)
                {
                    std::construct_at(&other.m_value, m_value);
                    other.m_has_value = true;
                }
                // ----------> *SELF: 1 (CEVAL), OTHER: 1 (REVAL) <----------------
                else if (other.m_has_value)
                {
                    other.m_value = m_value;
                }
                // ----------> *SELF: 1 (CEVAL), OTHER: 0 (REVAL) <----------------
                else
                {
                    std::construct_at(&other.m_value, m_value);
                    other.m_has_value = true;
                }
            }
            // ----------------- SELF: 0 (CEVAL) -----------------
            else if (state == optional_state::no_value)
            {
                // -----------> *SELF: 0 (CEVAL), OTHER: 1|? (CEVAL) <----------------
                if (other_state == optional_state::has_value || other_state == optional_state::unknown || other_state == optional_state::uninitialized)
                {
                    other.m_has_value = false;
                }
                // -----------> *SELF: 0 (CEVAL), OTHER: 0 (CEVAL) <---------------- OMITTED
            }
            // ----------------- SELF: - (CEVAL) ----------------- OMITTED
            // ----------------- SELF: ? (CEVAL) -----------------
            else if (state != optional_state::uninitialized)
            {
                // ------------> SELF: 1 (REVAL) <----------------
                if (*this)
                {
                    // ------>> *SELF: 1 (REVAL), OTHER: 1 (CEVAL) <----------------
                    if (other_state == optional_state::has_value)
                    {
                        other.m_value = m_value;
                    }
                    // ------>> *SELF: 1 (REVAL), OTHER: 0 (CEVAL) <----------------
                    else if (other_state == optional_state::no_value || other_state == optional_state::uninitialized)
                    {
                        other.m_has_value = true;
                        std::construct_at(&other.m_value, m_value);
                    }
                    // ------>> *SELF: 1 (REVAL), OTHER: 1 (REVAL) <----------------
                    else if (other.m_has_value)
                    {
                        other.m_value = m_value;
                    }
                    // ------>> *SELF: 1 (REVAL), OTHER: 0 (REVAL) <----------------
                    else
                    {
                        other.m_has_value = true;
                        std::construct_at(&other.m_value, m_value);
                    }
                }
                // ------------> SELF: 0 (REVAL) <----------------
                else
                {
                    // ------>> *SELF: 0 (REVAL), OTHER: 1|? (CEVAL) <----------------
                    if (other_state == optional_state::has_value || other_state == optional_state::unknown || other_state == optional_state::uninitialized)
                    {
                        other.m_has_value = false;
                    }
                    // ------>> *SELF: 0 (REVAL), OTHER: 0|- (CEVAL) <---------------- OMITTED
                }
            }
        }

    public:

        /**
         * Copies from optional to another optional.
         * @param state State of the current optional.
		 * @param other_state State of the current optional to copy to.
         * @param other The optional to copy to.
         * @return The lvalue reference to optional.
         */
        template <dynamic_states_t, typename OtherOptionalType>
			requires
			(
				is_optional_v<std::remove_cvref_t<OtherOptionalType>> &&
				std::is_constructible_v<ValueType, const typename OtherOptionalType::value_type&> &&
				std::is_assignable_v<ValueType, typename OtherOptionalType::value_type>
            )
        constexpr const optional& copy_to(const optional_state state, const optional_state other_state, OtherOptionalType&& other) const
    		noexcept
			(
				std::is_nothrow_constructible_v<ValueType, const typename OtherOptionalType::value_type&> &&
				std::is_nothrow_assignable_v<ValueType, typename OtherOptionalType::value_type>
            )
        {
            this->template copy_to_helper<dynamic_states>(state, other_state, std::forward<OtherOptionalType>(other));
            return *this;
        }

        /**
         * Copies from optional to another optional.
         * @param state State of the current optional.
		 * @param other_state State of the current optional to copy to.
         * @param other The optional to copy to.
         * @return The lvalue reference to optional.
         */
        template <dynamic_states_t, typename OtherOptionalType> 
			requires
			(
				is_optional_v<std::remove_cvref_t<OtherOptionalType>> &&
				std::is_constructible_v<ValueType, const typename OtherOptionalType::value_type&> &&
				std::is_assignable_v<ValueType, typename OtherOptionalType::value_type>
            )
        constexpr optional& copy_to(const optional_state state, const optional_state other_state, OtherOptionalType&& other)
    		noexcept
			(
				std::is_nothrow_constructible_v<ValueType, const typename OtherOptionalType::value_type&> &&
				std::is_nothrow_assignable_v<ValueType, typename OtherOptionalType::value_type>
            )
        {
            this->template copy_to_helper<dynamic_states>(state, other_state, std::forward<OtherOptionalType>(other));
            return *this;
        }

    private:
        /**
         * Helper m_function to count how many types in a parameter pack are optionals.
         * @tparam OtherValueTypes The types of other values.
         * @tparam Indexes The index sequence for the tuple elements.
         * @return The number of optionals in the parameter pack.
         */
        template <typename... OtherValueTypes, size_t... Indexes>
        static WOJ_NODISCARD
#ifdef HAS_CXX20
            WOJ_CONSTEVAL20
#else
            constexpr
#endif
        size_t helper_count_optionals(std::index_sequence<Indexes...>) noexcept
        {
            using others_tuple = std::tuple<std::remove_cvref_t<OtherValueTypes>...>;

            constexpr auto res = (0 + ... + static_cast<size_t>(is_optional<std::tuple_element_t<Indexes, others_tuple>>::value));
            return res;
        }

        /**
         * Copies values from one optional to other values.
         * @tparam State The state of the source optional.
         * @tparam Index The index of the current value in the tuple.
         * @tparam OthersValueTypes The types of other values to copy.
		 * @tparam OthersStates The states of optionals to copy to.
         * @param other The other value to copy to.
         * @return A reference to the current optional.
         */
        template <optional_state State, size_t Index, typename... OthersValueTypes, optional_state... OthersStates>
        WOJ_ALWAYS_INLINE constexpr void copy_to_impl(auto&& other, meta::value_sequence<OthersStates...>) const
			noexcept
#ifndef NDEBUG
			(
				(
					is_optional_v<std::remove_cvref_t<decltype(other)>> &&
					(
						(
							State == optional_state::has_value &&
							(
								std::is_nothrow_assignable_v<typename decltype(other)::value_type, const ValueType&> ||
								(!std::is_assignable_v<typename decltype(other)::value_type, const ValueType&> && std::is_nothrow_constructible_v<std::remove_cvref_t<decltype(other)>, const ValueType&>)
							) ||
							(
								State == optional_state::no_value ||
								State == optional_state::uninitialized
							)
						)
					) ||
					(
						!is_optional_v<std::remove_cvref_t<decltype(other)>> &&
						std::is_nothrow_assignable_v<std::remove_cvref_t<decltype(other)>, const ValueType&> ||
						(!std::is_assignable_v<std::remove_cvref_t<decltype(other)>, const ValueType&> && std::is_constructible_v<std::remove_cvref_t<decltype(other)>, const ValueType&>)
					)  
				)
			)
#else
            (
				State == optional_state::has_value &&
				(
					std::is_nothrow_assignable_v<typename decltype(other)::value_type, const ValueType&> ||
					(!std::is_assignable_v<typename decltype(other)::value_type, const ValueType&> && std::is_nothrow_constructible_v<std::remove_cvref_t<decltype(other)>, const ValueType&>)
				) ||
				(
					State == optional_state::no_value ||
					State == optional_state::uninitialized
				)
			)
#endif
			requires
	        (
	            (
					is_optional_v<std::remove_cvref_t<decltype(other)>> &&
                    (
	                    (
	                        State == optional_state::has_value &&
							(
								std::is_assignable_v<typename decltype(other)::value_type, const ValueType& > ||
								std::is_constructible_v<std::remove_cvref_t<decltype(other)>, const ValueType&>
							)
						) ||
						(
							State == optional_state::no_value ||
							State == optional_state::uninitialized
						)
                    )
				) ||
		        (
					!is_optional_v<std::remove_cvref_t<decltype(other)>> &&
					State == optional_state::has_value &&
					(
						std::is_assignable_v<std::remove_cvref_t<decltype(other)>, const ValueType&> ||
						std::is_constructible_v<std::remove_cvref_t<decltype(other)>, const ValueType&>
					)           
		        )
		    )
        {
            constexpr size_t number_optionals = this->template helper_count_optionals<std::remove_cvref_t<OthersValueTypes>...>(std::make_index_sequence<Index>{});

            if constexpr (is_optional_v<std::remove_cvref_t<decltype(other)>>)
            {
                if constexpr (number_optionals < sizeof...(OthersStates))
                {
                    constexpr stack::vector<optional_state, sizeof...(OthersStates)> others_states{ std::forward<decltype(OthersStates)>(OthersStates)... };
                    constexpr optional_state other_state = others_states[number_optionals];

                    this->template copy_to<State, other_state>(std::forward<decltype(other)>(other));
                }
                else
                {
                    this->template copy_to<State, optional_state::unknown>(std::forward<decltype(other)>(other));
                }
            }
            else
            {
                this->template copy_to<State>(std::forward<decltype(other)>(other));
            }
        }

        /**
         * Copies values from one optional to other values.
         * @tparam State The state of the source optional.
         * @tparam OthersValueTypes The types of the other values.
		 * @tparam OthersStates The states of the optionals to copy to.
         * @tparam Indexes The index sequence for the tuples.
         * @param others The other values or optionals to copy to.
		 * @param cont The container of the states of the optionals to copy to.
         * @param indexes The index sequence for the tuples.
         * @return A reference to the current optional.
         */
        template <optional_state State, typename... OthersValueTypes, optional_state... OthersStates, size_t... Indexes>
			requires
	        (
	            true && ... &&
	            (
	                (
	                    is_optional_v<std::remove_cvref_t<OthersValueTypes>> &&
	                    (
	                        (
	                            State == optional_state::has_value &&
	                            (
	                                std::is_assignable_v<typename std::remove_cvref_t<OthersValueTypes>::value_type, const ValueType&> ||
	                                std::is_constructible_v<std::remove_cvref_t<OthersValueTypes>, const ValueType&>
	                            )
	                        ) ||
	                        (
	                            State == optional_state::no_value ||
	                            State == optional_state::uninitialized
	                        )
	                    )
	                ) ||
	                (
	                    !is_optional_v<std::remove_cvref_t<OthersValueTypes>> &&
	                    State == optional_state::has_value &&
	                    (
	                        std::is_assignable_v<std::remove_cvref_t<OthersValueTypes>, const ValueType&> ||
	                        std::is_constructible_v<std::remove_cvref_t<OthersValueTypes>, const ValueType&>
	                    )
	                )
	            )
	        )
            WOJ_ALWAYS_INLINE constexpr void copy_to_helper(OthersValueTypes&&... others, meta::value_sequence<OthersStates...> cont, std::index_sequence<Indexes...> indexes) const
            noexcept
#ifndef NDEBUG
            (
                (
                    true && ... &&
                    (
						(
							is_optional_v<std::remove_cvref_t<OthersValueTypes>> &&
							(
								(
									State == optional_state::has_value &&
									(
										std::is_nothrow_assignable_v<typename OthersValueTypes::value_type, const ValueType&> ||
										(!std::is_assignable_v<typename OthersValueTypes::value_type, const ValueType&> && std::is_nothrow_constructible_v<typename OthersValueTypes::value_type, const ValueType&>)
									)
								) ||
								(
									State == optional_state::no_value ||
									State == optional_state::uninitialized
								)
							)
						) ||
						(
							!is_optional_v<std::remove_cvref_t<OthersValueTypes>> &&
							std::is_nothrow_assignable_v<typename OthersValueTypes::value_type, const ValueType&> ||
							(!std::is_assignable_v<typename OthersValueTypes::value_type, const ValueType&> && std::is_nothrow_constructible_v<typename OthersValueTypes::value_type, const ValueType&>)
						)
					)
				)
			)
#else
				(
                    (
						true && ... &&
						(
							(
								State == optional_state::has_value &&
								(
									std::is_nothrow_assignable_v<typename OthersValueTypes::value_type, const ValueType&> ||
									(!std::is_assignable_v<typename OthersValueTypes::value_type, const ValueType&> && std::is_nothrow_constructible_v<typename OthersValueTypes::value_type, const ValueType&>)
								)
							) ||
							(
								State == optional_state::no_value ||
								State == optional_state::uninitialized
							)
                        )
                    )
                )
#endif
        {
            (void(0), ..., copy_to_impl<State, Indexes, OthersValueTypes...>(std::forward<OthersValueTypes>(others), meta::value_sequence<OthersStates...>()));
        }
    public:

        /**
         * Copies values from this optional to multiple other values.
         * @tparam State The state of the source optional (default is unknown).
		 * @tparam OthersStates The states of the optionals to copy to.
         * @param others The other values to copy values to.
         * @return A reference to the current optional.
         */
        template <optional_state State = optional_state::unknown, optional_state... OthersStates>
        WOJ_ALWAYS_INLINE constexpr const optional& copy_to(auto&&... others) const 
			noexcept
#ifndef NDEBUG
			(
				(
					true && ... &&
					(
						(
							is_optional_v<std::remove_cvref_t<decltype(others)>> &&
							(
								(
									State == optional_state::has_value &&
									(
										std::is_nothrow_assignable_v<typename decltype(others)::value_type, const ValueType&> ||
										(!std::is_assignable_v<typename decltype(others)::value_type, const ValueType&> && std::is_nothrow_constructible_v<typename decltype(others)::value_type, const ValueType&>)
									)
								) ||
								(
									State == optional_state::no_value ||
									State == optional_state::uninitialized
								)
							)
						) ||
						(
							!is_optional_v<std::remove_cvref_t<decltype(others)>> &&
							std::is_nothrow_assignable_v<typename decltype(others)::value_type, const ValueType&> ||
							(!std::is_assignable_v<typename decltype(others)::value_type, const ValueType&> && std::is_nothrow_constructible_v<typename decltype(others)::value_type, const ValueType&>)
						)
					)   
				)
			)
#else
			(
				(
					true && ... &&
					(
						(
							State == optional_state::has_value &&
							(
								std::is_nothrow_assignable_v<typename decltype(others)::value_type, const ValueType&> ||
								(!std::is_assignable_v<typename decltype(others)::value_type, const ValueType&> && std::is_nothrow_constructible_v<typename decltype(others)::value_type, const ValueType&>)
								)
							) ||
						(
							State == optional_state::no_value ||
							State == optional_state::uninitialized
						)
					)
				)
            )
#endif
        {
            copy_to_helper<State, decltype(others)...>(std::forward<decltype(others)&&>(others)..., meta::value_sequence<OthersStates...>(), std::make_index_sequence<sizeof...(others)>{});
            return *this;
        }

        /**
         * Copies values from this optional to multiple other values.
         * @tparam State The state of the source optional (default is unknown).
		 * @tparam OthersStates The states of the optionals to copy to.
         * @param others The other values to copy values to.
         * @return A reference to the current optional.
         */
        template <optional_state State = optional_state::unknown, optional_state... OthersStates>
        WOJ_ALWAYS_INLINE constexpr optional& copy_to(auto&&... others) noexcept
#ifndef NDEBUG
        ((State == optional_state::has_value && ((is_optional_v<std::remove_cvref_t<decltype(others)>> || std::is_nothrow_assignable_v<decltype(others), ValueType>) && ...) ||
            ((State == optional_state::no_value || State == optional_state::uninitialized) && (is_optional_v<decltype(others)> && ...))))
#endif
        {
            copy_to_helper<State, decltype(others)...>(std::forward<decltype(others)&&>(others)..., meta::value_sequence<OthersStates...>(), std::make_index_sequence<sizeof...(others)>{});
            return *this;
        }

    private:

        /**
         * Copies values from one optional to other values.
         * @tparam Index The index of the current value in the tuple.
         * @tparam OthersValueTypes The types of other values to copy.
         * @param state The state of the source optional.
		 * @param others_states The states of optionals to copy to.
         * @param other The other value to copy to.
         */
        template <dynamic_states_t = dynamic_states, size_t SizeOthersStates, size_t Index, typename... OthersValueTypes>
        WOJ_ALWAYS_INLINE constexpr void copy_to_impl(const optional_state state, const optional_state(&others_states)[SizeOthersStates], auto&& other) const noexcept
#ifndef NDEBUG
        (false)
#endif
        {
            constexpr size_t number_optionals = helper_count_optionals<std::remove_cvref_t<OthersValueTypes>...>(std::make_index_sequence<Index>{});

            if constexpr (is_optional_v<std::remove_cvref_t<decltype(other)>>)
            {
                if constexpr (number_optionals < SizeOthersStates)
                {
                    copy_to<dynamic_states>(state, others_states[number_optionals], std::forward<decltype(other)>(other));
                }
                else
                {
                    copy_to<dynamic_states>(state, optional_state::unknown, std::forward<decltype(other)>(other));
                }
            }
            else
            {
                copy_to<dynamic_states>(state, optional_state::unknown, std::forward<decltype(other)>(other));
            }
        }

        /**
         * Copies values from one optional to other values.
         * @tparam Index The index of the current value in the tuple.
		 * @tparam OthersValueTypes The types of values to copy.
         * @param state The state of the source optional.
         * @param other The other value to copy to.
         */
        template <dynamic_states_t = dynamic_states, size_t Index, typename... OthersValueTypes>
        WOJ_ALWAYS_INLINE constexpr void copy_to_impl(const optional_state state, auto&& other) const noexcept
#ifndef NDEBUG
        (false)
#endif
        {
            copy_to<dynamic_states>(state, optional_state::unknown, std::forward<decltype(other)>(other));
        }

        /**
         * Copies values from one optional to other values.
         * @tparam OthersValueTypes The types of the other values.
         * @tparam Indexes The index sequence for the tuples.
         * @param state The state of the source optional.
		 * @param others_states The states of optionals to copy to.
         * @param others The other values or optionals to copy to.
		 * @param cont The container of the states of the optionals to copy to.
         * @param indexes The index sequence for the tuples.
         * @return A reference to the current optional.
         */
        template <dynamic_states_t = dynamic_states, size_t SizeOthersStates, typename... OthersValueTypes, size_t... Indexes>
        WOJ_ALWAYS_INLINE constexpr void copy_to_helper(const optional_state state, const optional_state(&others_states)[SizeOthersStates], OthersValueTypes&&... others, std::index_sequence<Indexes...>) const noexcept
#ifndef NDEBUG
        (false)
#endif
        {
            (void(0), ..., copy_to_impl<dynamic_states, SizeOthersStates, Indexes, OthersValueTypes...>(state, others_states, std::forward<decltype(others)>(others)));
        }

        /**
         * Copies values from one optional to other values.
         * @tparam OthersValueTypes The types of the other values.
         * @tparam Indexes The index sequence for the tuples.
         * @param state The state of the source optional.
         * @param others The other values or optionals to copy to.
		 * @param cont The container of the states of the optionals to copy to.
         * @param indexes The index sequence for the tuples.
         * @return A reference to the current optional.
         */
        template <dynamic_states_t = dynamic_states, typename... OthersValueTypes, size_t... Indexes>
        WOJ_ALWAYS_INLINE constexpr void copy_to_helper(const optional_state state, OthersValueTypes&&... others, std::index_sequence<Indexes...>) const noexcept
#ifndef NDEBUG
        (false)
#endif
        {
            (void(0), ..., copy_to_impl<dynamic_states, Indexes, OthersValueTypes...>(state, std::forward<decltype(others)>(others)));
        }

    public:

        /**
         * Copies values from this optional to multiple other values.
         * @param state The state of the source optional (default is unknown).
		 * @param others_states The states of the optionals to copy to.
         * @param others The other values to copy values to.
         * @return A reference to the current optional.
         */
        template <dynamic_states_t, size_t SizeOthersStates>
        WOJ_ALWAYS_INLINE constexpr const optional& copy_to(const optional_state state, const optional_state(&others_states)[SizeOthersStates], auto&&... others) const noexcept
#ifndef NDEBUG
        (false)
#endif
        {
            copy_to_helper<dynamic_states, SizeOthersStates, decltype(others)...>(state, others_states, std::forward<decltype(others)&&>(others)..., std::make_index_sequence<sizeof...(others)>{});
            return *this;
        }

        /**
         * Copies values from this optional to multiple other values.
         * @param state The state of the source optional (default is unknown).
		 * @param others_states The states of the optionals to copy to.
         * @param others The other values to copy values to.
         * @return A reference to the current optional.
         */
        template <dynamic_states_t, size_t SizeOthersStates>
        WOJ_ALWAYS_INLINE constexpr optional& copy_to(const optional_state state, const stack::vector<optional_state, SizeOthersStates>& others_states, auto&&... others) noexcept
#ifndef NDEBUG
        (false)
#endif
        {
            copy_to_helper<dynamic_states, SizeOthersStates, decltype(others)...>(state, others_states.data(), std::forward<decltype(others)&&>(others)..., std::make_index_sequence<sizeof...(others)>{});
            return *this;
        }

        /**
         * Copies values from this optional to multiple other values.
         * @param state The state of the source optional (default is unknown).
		 * @param others_states The states of the optionals to copy to.
         * @param others The other values to copy values to.
         * @return A reference to the current optional.
         */
        template <dynamic_states_t, size_t SizeOthersStates>
        WOJ_ALWAYS_INLINE constexpr const optional& copy_to(const optional_state state, const stack::vector<optional_state, SizeOthersStates>& others_states, auto&&... others) const noexcept
#ifndef NDEBUG
        (false)
#endif
        {
            copy_to_helper<dynamic_states, SizeOthersStates, decltype(others)...>(state, others_states.data(), std::forward<decltype(others)&&>(others)..., std::make_index_sequence<sizeof...(others)>{});
            return *this;
        }

        /**
         * Copies values from this optional to multiple other values.
         * @param state The state of the source optional (default is unknown).
		 * @param others_states The states of the optionals to copy to.
         * @param others The other values to copy values to.
         * @return A reference to the current optional.
         */
        template <dynamic_states_t, size_t SizeOthersStates>
        WOJ_ALWAYS_INLINE constexpr optional& copy_to(const optional_state state, const optional_state(&others_states)[SizeOthersStates], auto&&... others) noexcept
#ifndef NDEBUG
        (false)
#endif
        {

            this->template copy_to_helper<dynamic_states, SizeOthersStates, decltype(others)...>(state, others_states, std::forward<decltype(others)&&>(others)..., std::make_index_sequence<sizeof...(others)>{});
            return *this;
        }

        /**
         * Copies values from this optional to multiple other values.
         * @tparam DynamicStates Used to enable the function.
         * @param state The state of the source optional (default is unknown).
		 * @param others_states UNUSED. The states of the optionals to copy to.
         * @param others The other values to copy values to.
         * @return A reference to the current optional.
         */
        template <dynamic_states_t DynamicStates>
        WOJ_ALWAYS_INLINE constexpr const optional& copy_to(const optional_state state, const empty_t others_states, auto&&... others) const noexcept
#ifndef NDEBUG
        (false)
#endif
        {
            this->template copy_to_helper<dynamic_states, decltype(others)...>(state, std::forward<decltype(others)&&>(others)..., std::make_index_sequence<sizeof...(others)>{});
            return *this;
        }

        /**
         * Copies values from this optional to multiple other values.
         * @tparam DynamicStates Used to enable the function.
         * @param state The state of the source optional (default is unknown).
		 * @param others_states UNUSED. The states of the optionals to copy to.
         * @param others The other values to copy values to.
         * @return A reference to the current optional.
         */
        template <dynamic_states_t DynamicStates>
        WOJ_ALWAYS_INLINE constexpr optional& copy_to(const optional_state state, const empty_t others_states, auto&&... others) noexcept
#ifndef NDEBUG
        (false)
#endif
        {
            this->template copy_to_helper<dynamic_states, decltype(others)...>(state, std::forward<decltype(others)&&>(others)..., std::make_index_sequence<sizeof...(others)>{});
            return *this;
        }

        /**
         * Moves from another value to this optional.
         * @tparam State State of the current optional.
		 * @tparam OtherState UNUSED. State of the current optional to move from.
         * @param other The value to moves from.
         * @return The lvalue reference to optional.
         */
        template <optional_state State = optional_state::unknown, optional_state OtherState = optional_state::unknown>
        constexpr optional& move_from(ValueType&& other) noexcept(
                (State == optional_state::no_value  && std::is_nothrow_copy_constructible_v<ValueType>) || 
                (State == optional_state::has_value && std::is_nothrow_copy_assignable_v   <ValueType>)
            )
        {
            // ----------> SELF: 1 (CEVAL) <----------------
            if constexpr (State == optional_state::has_value)
            {
                m_value = std::move(other);
            }
            // ----------> SELF: 0 (CEVAL) <----------------
            else if constexpr (State == optional_state::no_value || State == optional_state::uninitialized)
            {
                std::construct_at(&m_value, std::move(other));
                m_has_value = true;
            }
            // ----------> SELF: 1 (REVAL) <----------------
            else if (*this)
            {
                m_value = std::move(other);
            }
            // ----------> SELF: 0 (REVAL) <----------------
            else
            {
                std::construct_at(&m_value, std::move(other));
                m_has_value = true;
            }

            return *this;
        }

        /**
         * Moves from another value to this optional.
         * @param state State of the current optional.
		 * @param other_state UNUSED. State of the current optional to move from.
         * @param other The value to moves from.
         * @return The lvalue reference to optional.
         */
        template <dynamic_states_t = dynamic_states>
        constexpr optional& move_from(const optional_state state, const optional_state other_state, ValueType&& other) noexcept(
                std::is_nothrow_move_constructible_v<ValueType> && std::is_nothrow_move_assignable_v<ValueType>
            )
        {
            // ----------> SELF: 1 (CEVAL) <----------------
            if (state == optional_state::has_value)
            {
                m_value = std::move(other);
            }
            // ----------> SELF: 0 (CEVAL) <----------------
            else if (state == optional_state::no_value || state == optional_state::uninitialized)
            {
                std::construct_at(&m_value, std::move(other));
                m_has_value = true;
            }
                // ----------> SELF: 1 (REVAL) <----------------
            else if (*this)
            {
                m_value = std::move(other);
            }
                // ----------> SELF: 0 (REVAL) <----------------
            else
            {
                std::construct_at(&m_value, std::move(other));
                m_has_value = true;
            }

            return *this;
        }

        /**
         * Moves from another optional to this optional.
         * @tparam State State of the current optional.
		 * @tparam OtherState State of the current optional to move from.
         * @param other The optional to move from.
         * @return The lvalue reference to optional.
         */
        template <optional_state State = optional_state::unknown, optional_state OtherState = optional_state::unknown>
            constexpr optional& move_from(optional&& other) noexcept(
                (OtherState == optional_state::has_value && (
                    ( State == optional_state::has_value && std::is_nothrow_move_assignable_v   <ValueType>) ||
                    ((State == optional_state::no_value  || State == optional_state::uninitialized)         && std::is_nothrow_move_constructible_v<ValueType>) ||
                    ( State == optional_state::unknown   && std::is_nothrow_move_constructible_v<ValueType> && std::is_nothrow_move_assignable_v<ValueType>))
                ) ||
                OtherState == optional_state::no_value)
        {
            // ---------------- OTHER: 1 (CEVAL) ----------------
            if constexpr (OtherState == optional_state::has_value)
            {
                // ----------> *OTHER: 1 (CEVAL), SELF: 1 (CEVAL) <----------------
                if constexpr (State == optional_state::has_value)
                {
                    m_value = std::move(other.m_value);
                    other.m_has_value = false;
                }
                // ----------> *OTHER: 1 (CEVAL), SELF: 0 (CEVAL) <----------------
                else if constexpr (State == optional_state::no_value || State == optional_state::uninitialized)
                {
                    std::construct_at(&m_value, std::move(other.m_value));
                    m_has_value = true;
                    other.m_has_value = false;
                }
                // ----------> *OTHER: 1 (CEVAL), SELF: 1 (REVAL) <----------------
                else if (*this)
                {
                    m_value = std::move(other.m_value);
                    other.m_has_value = false;
                }
                // ----------> *OTHER: 1 (CEVAL), SELF: 0 (REVAL) <----------------
                else
                {
                    std::construct_at(&m_value, std::move(other.m_value));
                    m_has_value = true;
                    other.m_has_value = false;
                }
            }
            // ----------------- OTHER: 0 (CEVAL) -----------------
            else if constexpr (OtherState == optional_state::no_value)
            {
                // -----------> *OTHER: 0 (CEVAL), SELF: 1|? (CEVAL) <----------------
                if constexpr (State == optional_state::has_value || State == optional_state::unknown || State == optional_state::uninitialized)
                {
                    m_has_value = false;
                }
                // -----------> *OTHER: 0 (CEVAL), SELF: 0 (CEVAL) <---------------- OMITTED
            }
            // ----------------- OTHER: - (CEVAL) ----------------- OMITTED
            // ----------------- OTHER: ? (CEVAL) -----------------
            else if constexpr (OtherState != optional_state::uninitialized)
            {
                // ------------> OTHER: 1 (REVAL) <----------------
                if (other.m_has_value)
                {
                    // ------>> *OTHER: 1 (REVAL), SELF: 1 (CEVAL) <----------------
                    if constexpr (State == optional_state::has_value)
                    {
                        m_value = std::move(other.m_value);
                        other.m_has_value = false;
                    }
                    // ------>> *OTHER: 1 (REVAL), SELF: 0 (CEVAL) <----------------
                    else if constexpr (State == optional_state::no_value || State == optional_state::uninitialized)
                    {
                        m_has_value = true;
                        std::construct_at(&m_value, std::move(other.m_value));
                        other.m_has_value = false;
                    }
                    // ------>> *OTHER: 1 (REVAL), SELF: 1 (REVAL) <----------------
                    else if (*this)
                    {
                        m_value = std::move(other.m_value);
                        other.m_has_value = false;
                    }
                    // ------>> *OTHER: 1 (REVAL), SELF: 0 (REVAL) <----------------
                    else
                    {
                        m_has_value = true;
                        std::construct_at(&m_value, std::move(other.m_value));
                        other.m_has_value = false;
                    }
                }
                // ------------> OTHER: 0 (REVAL) <----------------
                else
                {
                    // ------>> *OTHER: 0 (REVAL), SELF: 1|? (CEVAL) <----------------
                    if constexpr (State == optional_state::has_value || State == optional_state::unknown || State == optional_state::uninitialized)
                    {
                        m_has_value = false;
                    }
                    // ------>> *OTHER: 0 (REVAL), SELF: 0|- (CEVAL) <---------------- OMITTED
                }
            }

            return *this;
        }

        /**
         * Moves from another optional to this optional.
         * @param state State of the current optional.
		 * @param other_state State of the current optional to move from.
         * @param other The optional to move from.
         * @return The lvalue reference to optional.
         */
        constexpr optional& move_from(const optional_state state, const optional_state other_state, optional&& other) noexcept(std::is_nothrow_move_constructible_v<ValueType>&& std::is_nothrow_move_assignable_v<ValueType>)
        {
            // ---------------- OTHER: 1 (CEVAL) ----------------
            if (other_state == optional_state::has_value)
            {
                // ----------> *OTHER: 1 (CEVAL), SELF: 1 (CEVAL) <----------------
                if (state == optional_state::has_value)
                {
                    m_value = std::move(other.m_value);
                    other.m_has_value = false;
                }
                // ----------> *OTHER: 1 (CEVAL), SELF: 0 (CEVAL) <----------------
                else if (state == optional_state::no_value || state == optional_state::uninitialized)
                {
                    std::construct_at(&m_value, std::move(other.m_value));
                    m_has_value = true;
                    other.m_has_value = false;
                }
                // ----------> *OTHER: 1 (CEVAL), SELF: 1 (REVAL) <----------------
                else if (*this)
                {
                    m_value = std::move(other.m_value);
                    other.m_has_value = false;
                }
                // ----------> *OTHER: 1 (CEVAL), SELF: 0 (REVAL) <----------------
                else
                {
                    std::construct_at(&m_value, std::move(other.m_value));
                    m_has_value = true;
                    other.m_has_value = false;
                }
            }
            // ----------------- OTHER: 0 (CEVAL) -----------------
            else if (other_state == optional_state::no_value)
            {
                // -----------> *OTHER: 0 (CEVAL), SELF: 1|? (CEVAL) <----------------
                if (state == optional_state::has_value || state == optional_state::unknown || state == optional_state::uninitialized)
                {
                    m_has_value = false;
                }
                // -----------> *OTHER: 0 (CEVAL), SELF: 0 (CEVAL) <---------------- OMITTED
            }
            // ----------------- OTHER: - (CEVAL) ----------------- OMITTED
            // ----------------- OTHER: ? (CEVAL) -----------------
            else if (other_state != optional_state::uninitialized)
            {
                // ------------> OTHER: 1 (REVAL) <----------------
                if (other.m_has_value)
                {
                    // ------>> *OTHER: 1 (REVAL), SELF: 1 (CEVAL) <----------------
                    if (state == optional_state::has_value)
                    {
                        m_value = std::move(other.m_value);
                        other.m_has_value = false;
                    }
                    // ------>> *OTHER: 1 (REVAL), SELF: 0 (CEVAL) <----------------
                    else if (state == optional_state::no_value || state == optional_state::uninitialized)
                    {
                        m_has_value = true;
                        std::construct_at(&m_value, std::move(other.m_value));
                        other.m_has_value = false;
                    }
                    // ------>> *OTHER: 1 (REVAL), SELF: 1 (REVAL) <----------------
                    else if (*this)
                    {
                        m_value = std::move(other.m_value);
                        other.m_has_value = false;
                    }
                    // ------>> *OTHER: 1 (REVAL), SELF: 0 (REVAL) <----------------
                    else
                    {
                        m_has_value = true;
                        std::construct_at(&m_value, std::move(other.m_value));
                        other.m_has_value = false;
                    }
                }
                // ------------> OTHER: 0 (REVAL) <----------------
                else
                {
                    // ------>> *OTHER: 0 (REVAL), SELF: 1|? (CEVAL) <----------------
                    if (state == optional_state::has_value || state == optional_state::unknown || state == optional_state::uninitialized)
                    {
                        m_has_value = false;
                    }
                    // ------>> *OTHER: 0 (REVAL), SELF: 0 (CEVAL) <---------------- OMITTED
                }
            }

            return *this;
        }

        /**
         * Moves from another value to new optional.
		 * @tparam OtherState UNUSED. State of the current optional to move from.
         * @param other The value to move from.
         * @return The new optional.
         */
        template <optional_state OtherState = optional_state::unknown>
        constexpr optional moved_from(ValueType&& other) noexcept(std::is_nothrow_move_constructible_v<ValueType>)
        {
            optional temp{ noinit };
            temp.move_from<optional_state::uninitialized, OtherState>(std::move(other));
            return std::move(temp);
        }

        /**
         * Moves from another value to new optional.
		 * @param other_state UNUSED. State of the current optional to move from.
         * @param other The value to move from.
         * @return The new optional.
         */
        static constexpr optional& moved_from(const optional_state other_state, ValueType&& other) noexcept(std::is_nothrow_move_constructible_v<ValueType>)
        {
            optional temp{ noinit };
            temp.move_from(optional_state::uninitialized, other_state, std::move(other));
            return std::move(temp);
        }

        /**
         * Moves from another optional to new optional.
		 * @tparam OtherState State of the current optional to move from.
         * @param other The optional to move from.
         * @return The new optional.
         */
        template <optional_state OtherState = optional_state::unknown>
            constexpr optional moved_from(optional&& other) noexcept(std::is_nothrow_move_constructible_v<ValueType>)
        {
            optional temp{ noinit };
            temp.move_from<optional_state::uninitialized, OtherState>(std::forward<optional>(other));
            return std::move(temp);
        }

        /**
         * Moves from another optional to new optional.
         * @tparam DynamicStates Uses dynamic states when provided.
		 * @param other_state State of the current optional to move from.
         * @param other The optional to move from.
         * @return The new optional.
         */
        template <dynamic_states_t DynamicStates = dynamic_states>
        static constexpr optional& moved_from(const optional_state other_state, optional&& other) noexcept(std::is_nothrow_move_constructible_v<ValueType>)
        {
            optional temp{ noinit };
            temp.move_from(optional_state::uninitialized, other_state, std::forward<optional>(other));
            return std::move(temp);
        }

        /**
         * Moves from optional to another value.
         * @tparam State State of the current optional.
		 * @tparam OtherState UNUSED. State of the current optional to move to.
		 * @param other The value to move to.
         * @return The lvalue reference to optional.
         */
        template <optional_state State = optional_state::unknown, optional_state OtherState = optional_state::unknown, typename OtherValueType> requires (!std::is_same_v<std::remove_cvref_t<OtherValueType>, std::remove_cvref_t<this_type>>)
        constexpr optional& move_to(OtherValueType&& other) noexcept
#ifndef NDEBUG
        (State == optional_state::has_value && std::is_nothrow_assignable_v<std::remove_cvref_t<OtherValueType>, ValueType>)
#endif
        {
            // ---------------- SELF: 1 (CEVAL) ----------------
            if constexpr (State == optional_state::has_value)
            {
                other = std::move(m_value);
                m_has_value = false;
            }

            if constexpr (State == optional_state::no_value || State == optional_state::uninitialized)
            {
#ifndef NDEBUG
                throw bad_optional_access{ 1805ull, "optional.hpp", "move_to" };
#else
                other = std::move(m_value);
                m_has_value = false;
#endif
            }

            if constexpr (State == optional_state::unknown)
            {
                if (*this)
                {
                    other = std::move(m_value);
                    m_has_value = false;
                }
                else
                {
#ifndef NDEBUG
                    throw bad_optional_access{ 1822ull, "optional.hpp", "move_to" };
#else
                    other = std::move(m_value);
                    m_has_value = false;
#endif
                }
            }

            return *this;
        }

        /**
         * Moves from optional to another value.
         * @tparam DynamicStates Uses dynamic states when provided.
         * @param state State of the current optional.
		 * @param other_state UNUSED. State of the current optional to move to.
		 * @param other The value to move to.
         * @return The lvalue reference to optional.
         */
        template <dynamic_states_t DynamicStates = dynamic_states, typename OtherValueType> requires (!std::is_same_v<std::remove_cvref_t<OtherValueType>, std::remove_cvref_t<this_type>>)
        constexpr optional& move_to(const optional_state state, const optional_state other_state, OtherValueType&& other) noexcept
#ifndef NDEBUG
        (false)
#else
        (std::is_nothrow_move_assignable_v<ValueType>)
#endif
        {
            // ---------------- SELF: 1 (CEVAL) ----------------
            if (state == optional_state::has_value)
            {
                other = std::move(m_value);
                m_has_value = false;
            }

            if (state == optional_state::no_value || state == optional_state::uninitialized)
            {
#ifndef NDEBUG
                throw bad_optional_access{ 1858ull, "optional.hpp", "move_to" };
#else
                other = std::move(m_value);
                m_has_value = false;
#endif
            }

            if (state == optional_state::unknown)
            {
                if (*this)
                {
                    other = std::move(m_value);
                    m_has_value = false;
                }
                else
                {
#ifndef NDEBUG
                    throw bad_optional_access{ 1875ull, "optional.hpp", "move_to" };
#else
                    other = std::move(m_value);
                    m_has_value = false;
#endif
                }
            }

            return *this;
        }

        /**
         * Moves from optional to another optional.
         * @tparam State State of the current optional.
		 * @tparam OtherState State of the current optional to move to.
		 * @param other The optional to move to.
         */
        template <optional_state State = optional_state::unknown, optional_state OtherState = optional_state::unknown, typename OtherOptionalType> requires(is_optional_v<std::remove_cvref_t<OtherOptionalType>>)
            constexpr optional& move_to(OtherOptionalType&& other) noexcept
        ((State == optional_state::has_value && (
            (OtherState  == optional_state::has_value && std::is_nothrow_move_assignable_v<ValueType>)   || 
            ((OtherState == optional_state::no_value  || OtherState == optional_state::uninitialized)    && std::is_nothrow_move_constructible_v<ValueType>) ||
            (OtherState  == optional_state::unknown   && std::is_nothrow_move_constructible_v<ValueType> && std::is_nothrow_move_assignable_v<ValueType>)))  ||
        State == optional_state::no_value)
        {
            // ---------------- SELF: 1 (CEVAL) ----------------
            if constexpr (State == optional_state::has_value)
            {
                // ----------> *SELF: 1 (CEVAL), OTHER: 1 (CEVAL) <----------------
                if constexpr (OtherState == optional_state::has_value)
                {
                    other.m_value = std::move(m_value);
                    m_has_value = false;
                }
                // ----------> *SELF: 1 (CEVAL), OTHER: 0 (CEVAL) <----------------
                else if constexpr (OtherState == optional_state::no_value || OtherState == optional_state::uninitialized)
                {
                    std::construct_at(&other.m_value, std::move(m_value));
                    other.m_has_value = true;
                    m_has_value = false;
                }
                    // ----------> *SELF: 1 (CEVAL), OTHER: 1 (REVAL) <----------------
                else if (other.m_has_value)
                {
                    other.m_value = std::move(m_value);
                    m_has_value = false;
                }
                    // ----------> *SELF: 1 (CEVAL), OTHER: 0 (REVAL) <----------------
                else
                {
                    std::construct_at(&other.m_value, std::move(m_value));
                    other.m_has_value = true;
                    m_has_value = false;
                }
            }
            // ----------------- SELF: 0 (CEVAL) -----------------
            else if constexpr (State == optional_state::no_value)
            {
                // -----------> *SELF: 0 (CEVAL), OTHER: 1|? (CEVAL) <----------------
                if constexpr (OtherState == optional_state::has_value || OtherState == optional_state::unknown || OtherState == optional_state::uninitialized)
                {
                    other.m_has_value = false;
                }
                // -----------> *SELF: 0 (CEVAL), OTHER: 0 (CEVAL) <---------------- OMITTED
            }
            // ----------------- SELF: - (CEVAL) ----------------- OMITTED
            // ----------------- SELF: ? (CEVAL) -----------------
            else if constexpr (State != optional_state::uninitialized)
            {
                // ------------> SELF: 1 (REVAL) <----------------
                if (*this)
                {
                    // ------>> *SELF: 1 (REVAL), OTHER: 1 (CEVAL) <----------------
                    if constexpr (OtherState == optional_state::has_value)
                    {
                        other.m_value = std::move(m_value);
                        m_has_value = false;
                    }
                    // ------>> *SELF: 1 (REVAL), OTHER: 0 (CEVAL) <----------------
                else if constexpr (OtherState == optional_state::no_value || OtherState == optional_state::uninitialized)
                {
                    other.m_has_value = true;
                    std::construct_at(&other.m_value, std::move(m_value));
                    m_has_value = false;
                }
                // ------>> *SELF: 1 (REVAL), OTHER: 1 (REVAL) <----------------
                    else if (other.m_has_value)
                    {
                        other.m_value = std::move(m_value);
                        m_has_value = false;
                    }
                    // ------>> *SELF: 1 (REVAL), OTHER: 0 (REVAL) <----------------
                    else
                    {
                        other.m_has_value = true;
                        std::construct_at(&other.m_value, std::move(m_value));
                        m_has_value = false;
                    }
                }
                // ------------> SELF: 0 (REVAL) <----------------
                else
                {
                    // ------>> *SELF: 0 (REVAL), OTHER: 1|? (CEVAL) <----------------
                    if constexpr (OtherState == optional_state::has_value || OtherState == optional_state::unknown || OtherState == optional_state::uninitialized)
                    {
                        other.m_has_value = false;
                    }
                    // ------>> *SELF: 0 (REVAL), OTHER: 0|- (CEVAL) <---------------- OMITTED
                }
            }

            return *this;
        }
        
        /**
         * Moves from optional to another optional.
         * @tparam DynamicStates Uses dynamic states when provided.
         * @param state State of the current optional.
		 * @param other_state State of the current optional to move to.
         * @param other The optional to copy to.
         */
        template <dynamic_states_t DynamicStates = dynamic_states, typename OtherOptionalType> requires(is_optional_v<std::remove_cvref_t<OtherOptionalType>>)
        constexpr optional& move_to(const optional_state state, const optional_state other_state, OtherOptionalType&& other) noexcept(std::is_nothrow_move_constructible_v<ValueType> && std::is_nothrow_move_assignable_v<ValueType>)
        {
            // ---------------- SELF: 1 (CEVAL) ----------------
            if (state == optional_state::has_value)
            {
                // ----------> *SELF: 1 (CEVAL), OTHER: 1 (CEVAL) <----------------
                if (other_state == optional_state::has_value)
                {
                    other.m_value = std::move(m_value);
                    m_has_value = false;
                }
                // ----------> *SELF: 1 (CEVAL), OTHER: 0 (CEVAL) <----------------
                else if (other_state == optional_state::no_value || other_state == optional_state::uninitialized)
                {
                    other.m_has_value = true;
                    std::construct_at(&other.m_value, std::move(m_value));
                    m_has_value = false;
                }
                // ----------> *SELF: 1 (CEVAL), OTHER: 1 (REVAL) <----------------
                else if (other.m_has_value)
                {
                    other.m_value = std::move(m_value);
                    m_has_value = false;
                }
                // ----------> *SELF: 1 (CEVAL), OTHER: 0 (REVAL) <----------------
                else
                {
                    other.m_has_value = true;
                    std::construct_at(&other.m_value, std::move(m_value));
                    m_has_value = false;
                }
            }
            // ----------------- SELF: 0 (CEVAL) -----------------
            else if (state == optional_state::no_value)
            {
                // -----------> *SELF: 0 (CEVAL), OTHER: 1|? (CEVAL) <----------------
                if (other_state == optional_state::has_value || other_state == optional_state::unknown || other_state == optional_state::uninitialized)
                {
                    other.m_has_value = false;
                }
                // -----------> *SELF: 0 (CEVAL), OTHER: 0 (CEVAL) <---------------- OMITTED
            }
            // ----------------- SELF: - (CEVAL) ----------------- OMITTED
            // ----------------- SELF: ? (CEVAL) -----------------
            else if (state != optional_state::uninitialized)
            {
                // ------------> SELF: 1 (REVAL) <----------------
                if (*this)
                {
                    // ------>> *SELF: 1 (REVAL), OTHER: 1 (CEVAL) <----------------
                    if (other_state == optional_state::has_value)
                    {
                        other.m_value = std::move(m_value);
                        m_has_value = false;
                    }
                    // ------>> *SELF: 1 (REVAL), OTHER: 0 (CEVAL) <----------------
                    else if (other_state == optional_state::no_value || other_state == optional_state::uninitialized)
                    {
                        other.m_has_value = true;
                        std::construct_at(&other.m_value, std::move(m_value));
                        m_has_value = false;
                    }
                    // ------>> *SELF: 1 (REVAL), OTHER: 1 (REVAL) <----------------
                    else if (other.m_has_value)
                    {
                        other.m_value = std::move(m_value);
                        m_has_value = false;
                    }
                    // ------>> *SELF: 1 (REVAL), OTHER: 0 (REVAL) <----------------
                    else
                    {
                        other.m_has_value = true;
                        std::construct_at(&other.m_value, std::move(m_value));
                        m_has_value = false;
                    }
                }
                // ------------> SELF: 0 (REVAL) <----------------
                else
                {
                    // ------>> *SELF: 0 (REVAL), OTHER: 1|? (CEVAL) <----------------
                    if (other_state == optional_state::has_value || other_state == optional_state::unknown || other_state == optional_state::uninitialized)
                    {
                        other.m_has_value = false;
                    }
                    // ------>> *SELF: 0 (REVAL), OTHER: 0|- (CEVAL) <---------------- OMITTED
                }
            }
        }

        /**
         * Resets the optional to be empty.
         * @tparam State State of the current optional.
         * @return The lvalue reference to the optional.
         */
        template <optional_state State = optional_state::unknown>
        constexpr optional& reset() noexcept((State == optional_state::has_value && std::is_nothrow_destructible_v<ValueType>) || State == optional_state::no_value)
        {
            if constexpr (State == optional_state::has_value && std::is_destructible_v<ValueType>)
            {
                m_value.~ValueType();
            }

            if constexpr (State == optional_state::unknown && std::is_destructible_v<ValueType>)
            {
                if (*this)
                {
                    m_value.~ValueType();
                }
            }

            if constexpr (State != optional_state::no_value)
            {
                m_has_value = false;
            }

            return *this;
        }

        /**
         * Resets the optional to be empty.
         * @tparam DynamicStates Uses dynamic states when provided.
         * @param state State of the current optional.
         * @return The lvalue reference to the optional.
         */
        template <dynamic_states_t DynamicStates = dynamic_states>
        constexpr optional& reset(const optional_state state) noexcept(std::is_nothrow_destructible_v<ValueType>)
        {
            if (state == optional_state::has_value)
            {
                m_value.~ValueType();
            }

            else if (*this)
            {
                m_value.~ValueType();
            }

            if (state != optional_state::no_value)
            {
                m_has_value = false;
            }

            return *this;
        }

        /**
         * Returns empty optional.
         * @return The new optional.
         */
        static constexpr optional resetted() noexcept(std::is_nothrow_destructible_v<ValueType>)
        {
            return optional{};
        }

        /**
         * Returns a const rvalue reference to the value.
         * @tparam State State of the current optional.
         * @return The const rvalue reference to the value.
         */
        template <optional_state State = optional_state::unknown>
        WOJ_NODISCARD constexpr ValueType& get() noexcept
#ifndef NDEBUG
        (State == optional_state::has_value)
#endif
        {
            if constexpr (State == optional_state::has_value)
            {
                return m_value;
            }
            if constexpr (State == optional_state::no_value || State == optional_state::uninitialized)
            {
#ifndef NDEBUG
                throw bad_optional_access{ 2132ull, "optional.hpp", "get" };
#else
                return m_value;
#endif
            }
            if (*this)
            {
                return m_value;
            }

#ifndef NDEBUG
            throw bad_optional_access{ 2143ull, "optional.hpp", "get" };
#else
            return m_value;
#endif
        }

        /**
         * Returns a const rvalue reference to the value.
         * @tparam State State of the current optional.
         * @return The const rvalue reference to the value.
         */
        template <optional_state State = optional_state::unknown>
        WOJ_NODISCARD std::conditional_t<std::is_arithmetic_v<ValueType>, std::remove_cvref_t<ValueType>, const ValueType&> get() const noexcept
#ifndef NDEBUG
            (State == optional_state::has_value)
#endif
        {
            if constexpr (State == optional_state::has_value)
            {
                return m_value;
            }
            if constexpr (State == optional_state::no_value || State == optional_state::uninitialized)
            {
#ifndef NDEBUG
                throw bad_optional_access{ 2167ull, "optional.hpp", "get" };
#else
                return m_value;
#endif
            }
            if (*this)
            {
                return m_value;
            }

#ifndef NDEBUG
            throw bad_optional_access{ 2178ull, "optional.hpp", "get" };
#else
            return m_value;
#endif
        }

        /**
         * Returns a const lvalue reference to the value.
         * @tparam DynamicStates Uses dynamic states when provided.
         * @param state State of the current optional.
         * @return The const lvalue reference to the value.
         */
        template <dynamic_states_t DynamicStates = dynamic_states>
        WOJ_NODISCARD constexpr ValueType& get(const optional_state state) noexcept
#ifndef NDEBUG
        (false)
#endif
        {
            if (state == optional_state::has_value)
            {
                return m_value;
            }
            if (state == optional_state::no_value || state == optional_state::uninitialized)
            {
#ifndef NDEBUG
                throw bad_optional_access{ 2203ull, "optional.hpp", "get" };
#else
                return m_value;
#endif
            }
            if (*this)
            {
                return m_value;
            }
#ifndef NDEBUG
            throw bad_optional_access{ 2213ull, "optional.hpp", "get" };
#else
            return m_value;
#endif
        }

        /**
         * Returns a const rvalue reference to the value.
         * @tparam DynamicStates Uses dynamic states when provided.
         * @param state State of the current optional.
         * @return The const rvalue reference to the value.
         */
        template <dynamic_states_t DynamicStates = dynamic_states>
        WOJ_NODISCARD std::conditional_t<std::is_arithmetic_v<ValueType>, std::remove_cvref_t<ValueType>, const ValueType&> get(const optional_state state) const noexcept
#ifndef NDEBUG
        (false)
#endif
        {
            if (state == optional_state::has_value)
            {
                return m_value;
            }
            if (state == optional_state::no_value || state == optional_state::uninitialized)
            {
#ifndef NDEBUG
                throw bad_optional_access{ 2238ull, "optional.hpp", "get" };
#else
                return m_value;
#endif
            }
            if (*this)
            {
                return m_value;
            }

#ifndef NDEBUG
            throw bad_optional_access{};
#else
            return m_value;
#endif
        }

        /**
         * Checks if the optional has a value.
         * @tparam State State of the current optional.
         * @return True if the optional has a value, false otherwise.
         */
        template <optional_state State = optional_state::unknown>
        WOJ_NODISCARD constexpr bool has_value() const noexcept
        {
            if constexpr (State == optional_state::has_value)
            {
                return true;
            }
            if constexpr (State == optional_state::no_value)
            {
                return false;
            }

            return m_has_value;
        }

        /**
         * Checks if the optional has a value.
         * @tparam DynamicStates Uses dynamic states when provided.
         * @param state State of the current optional.
         * @return True if the optional has a value, false otherwise.
         */
        template <dynamic_states_t DynamicStates = dynamic_states>
        WOJ_NODISCARD constexpr bool has_value(const optional_state state) const noexcept
        {
            if (state == optional_state::has_value)
            {
                return true;
            }
            if (state == optional_state::no_value)
            {
                return false;
            }

            return m_has_value;
        }

        /**
         * Emplaces the value of the optional by forwarding the arguments.
         * @tparam State State of the current optional.
         * @tparam OtherValueTypes The types of the arguments to forward.
         * @param values The values to forward.
         * @return The lvalue reference to the optional.
         */
        template <optional_state State = optional_state::unknown, typename... OtherValueTypes> requires(std::is_constructible_v<std::remove_cvref_t<ValueType>, OtherValueTypes...>)
        constexpr optional& emplace(OtherValueTypes&&... values) noexcept(std::is_nothrow_constructible_v<std::remove_cvref_t<ValueType>, OtherValueTypes...>)
        {
            if constexpr (State != optional_state::has_value)
            {
                m_has_value = true;
            }

            std::construct_at(&m_value, std::forward<OtherValueTypes>(values)...);

            return *this;
        }

        /**
         * Emplaces the value of the optional by forwarding the arguments.
         * @tparam DynamicStates Uses dynamic states when provided.
         * @tparam OtherValueTypes The types of the arguments to forward.
         * @param state State of the current optional.
         * @param values The values to forward.
         * @return The lvalue reference to the optional.
         */
        template <dynamic_states_t DynamicStates = dynamic_states, typename... OtherValueTypes> requires(std::is_constructible_v<std::remove_cvref_t<ValueType>, OtherValueTypes...>)
        constexpr optional& emplace(const optional_state state, OtherValueTypes&&... values) noexcept(std::is_nothrow_constructible_v<std::remove_cvref_t<ValueType>, OtherValueTypes...>)
        {
            if (state != optional_state::has_value)
            {
                m_has_value = true;
            }

            std::construct_at(&m_value, std::forward<OtherValueTypes>(values)...);

            return *this;
        }

        /**
         * Emplaces the value of new optional by forwarding the arguments.
         * @tparam OtherValueTypes The types of the arguments to forward.
         * @param values The values to forward.
         * @return The new optional.
         */
        template <typename... OtherValueTypes> requires(std::is_constructible_v<std::remove_cvref_t<ValueType>, OtherValueTypes...>)
        static constexpr optional emplaced(OtherValueTypes&&... values) noexcept(std::is_nothrow_constructible_v<std::remove_cvref_t<ValueType>, OtherValueTypes...>)
        {
            optional temp{ noinit };

            temp.template emplace<optional_state::uninitialized>(std::forward<OtherValueTypes>(values)...);

            return std::move(temp);
        }

        /**
         * Applies the m_function to the value of the optional.
         * @tparam State State of the current optional.
         * @tparam FuncType The type of the function to apply.
         * @tparam ArgTypes The types of the arguments to pass to the function.
         * @param func The function to apply.
         * @param args The arguments to pass to the function.
         * @return The reference to the optional.
         */
        template <optional_state State = optional_state::unknown, typename FuncType, typename... ArgTypes> requires (std::is_invocable_v<FuncType, ValueType&, ArgTypes...>)
        constexpr optional& apply(FuncType&& func, ArgTypes&&... args) noexcept
#ifdef NDEBUG
            (std::is_nothrow_invocable_v<FuncType, std::remove_cvref_t<ValueType>, ArgTypes...>&& State == optional_state::has_value)
#else
            (std::is_nothrow_invocable_v<FuncType, std::remove_cvref_t<ValueType>, ArgTypes...>)
#endif
        {
            if constexpr (State == optional_state::has_value)
            {
                func(m_value, std::forward<ArgTypes>(args)...);
            }
            if constexpr (State == optional_state::no_value || State == optional_state::uninitialized)
            {
#ifndef NDEBUG
                throw bad_optional_access{ 2377ull, "optional.hpp", "apply" };
#else
                func(m_value, std::forward<ArgTypes>(args)...);
#endif
            }
            if constexpr (State == optional_state::unknown)
            {
                if (*this)
                {
                    func(m_value, std::forward<ArgTypes>(args)...);
                }
                else
                {
#ifndef NDEBUG
                    throw bad_optional_access{ 2423ull, "optional.hpp", "apply" };
#else
                    func(m_value, std::forward<ArgTypes>(args)...);
#endif
                }
            }

            return *this;
        }

        /**
         * Applies the m_function to the value of the optional.
         * @tparam DynamicStates Uses dynamic states when provided.
         * @tparam FuncType The type of the function to apply.
         * @tparam ArgTypes The types of the arguments to pass to the function.
         * @param state state of the optional.
         * @param func The function to apply.
         * @param args The arguments to pass to the function.
         * @return The reference to the optional.
         */
        template <dynamic_states_t DynamicStates = dynamic_states, typename FuncType, typename... ArgTypes> requires (std::is_invocable_v<FuncType, ValueType&, ArgTypes...>)
        constexpr optional& apply(const optional_state state, FuncType&& func, ArgTypes&&... args) noexcept
#ifndef NDEBUG
            (false)
#else
            (std::is_nothrow_invocable_v<FuncType, std::remove_cvref_t<ValueType>, ArgTypes...>)
#endif
        {
            if (state == optional_state::has_value)
            {
                func(m_value, std::forward<ArgTypes>(args)...);
            }
            if (state == optional_state::no_value || state == optional_state::uninitialized)
            {
#ifndef NDEBUG
                throw bad_optional_access{ 2426ull, "optional.hpp", "apply" };
#else
                func(m_value, std::forward<ArgTypes>(args)...);
#endif
            }
            if (state == optional_state::unknown)
            {
                if (*this)
                {
                    func(m_value, std::forward<ArgTypes>(args)...);
                }
                else
                {
#ifndef NDEBUG
                    throw bad_optional_access{ 2440ull, "optional.hpp", "apply" };
#else
                    func(m_value, std::forward<ArgTypes>(args)...);
#endif
                }
            }

            return *this;
        }

        /**
         * Applies the m_function to the value of the optional to new optional.
         * @tparam State State of the current optional.
         * @tparam FuncType The type of the function to apply.
         * @tparam ArgTypes The types of the arguments to pass to the function.
         * @param func The function to apply.
         * @param args The arguments to pass to the function.
         * @return The new optional.
         */
        template <optional_state State = optional_state::unknown, typename FuncType, typename... ArgTypes> requires (std::is_invocable_v<FuncType, ValueType&, ArgTypes...>)
        constexpr optional applied(FuncType&& func, ArgTypes&&... args) noexcept
#ifndef NDEBUG
            (std::is_nothrow_invocable_v<FuncType, std::remove_cvref_t<ValueType>, ArgTypes...>&& State == optional_state::has_value)
#else
            (std::is_nothrow_invocable_v<FuncType, std::remove_cvref_t<ValueType>, ArgTypes...>)
#endif
        {
            optional temp{ noinit };

            temp.m_value = m_value;
            temp.m_has_value = true;

            if constexpr (State == optional_state::has_value)
            {
                func(temp.m_value, std::forward<ArgTypes>(args)...);
            }
            if constexpr (State == optional_state::no_value || State == optional_state::uninitialized)
            {
#ifndef NDEBUG
                throw bad_optional_access{ 2479ull, "optional.hpp", "apply" };
#else
                func(temp.m_value, std::forward<ArgTypes>(args)...);
#endif
            }
            if constexpr (State == optional_state::unknown)
            {
                if (*this)
                {
                    func(temp.m_value, std::forward<ArgTypes>(args)...);
                }
                else
                {
#ifndef NDEBUG
                    throw bad_optional_access{ 2493ull, "optional.hpp", "apply" };
#else
                    func(temp.m_value, std::forward<ArgTypes>(args)...);
#endif
                }
            }

            return std::move(temp);
        }

        /**
         * Applies the m_function to the value of the optional to new optional.
         * @tparam DynamicStates Uses dynamic states when provided.
         * @tparam FuncType The type of the function to apply.
         * @tparam ArgTypes The types of the arguments to pass to the function.
         * @param state State of the current optional
         * @param func The function to apply.
         * @param args The arguments to pass to the function.
         * @return The new optional.
         */
        template <dynamic_states_t DynamicStates = dynamic_states, typename FuncType, typename... ArgTypes> requires (std::is_invocable_v<FuncType, ValueType&, ArgTypes...>)
        constexpr optional applied(const optional_state state, FuncType&& func, ArgTypes&&... args) noexcept
#ifndef NDEBUG
            (false)
#else
            (std::is_nothrow_invocable_v<FuncType, std::remove_cvref_t<ValueType>, ArgTypes...>)
#endif
        {
            optional temp{ noinit };

            temp.m_value = m_value;
            temp.m_has_value = true;

            if (state == optional_state::has_value)
            {
                func(temp.m_value, std::forward<ArgTypes>(args)...);
            }
            else if (state == optional_state::no_value || state == optional_state::uninitialized)
            {
#ifndef NDEBUG
                throw bad_optional_access{ 2533ull, "optional.hpp", "applied" };
#else
                func(temp.m_value, std::forward<ArgTypes>(args)...);
#endif
            }
            else if (state == optional_state::unknown)
            {
                if (*this)
                {
                    func(temp.m_value, std::forward<ArgTypes>(args)...);
                }
                else
                {
#ifndef NDEBUG
                    throw bad_optional_access{ 2577ull, "optional.hpp", "applied" };
#else
                    func(temp.m_value, std::forward<ArgTypes>(args)...);
#endif
                }
            }

            return std::move(temp);
        }

        /**
         * Returns the optional as a const reference.
         * @return The const reference to the optional.
         */
        WOJ_NODISCARD constexpr const optional& as_const() const noexcept
        {
            return *this;
        }

        /**
         * Returns either has_value if optional has value, no_value otherwise.
         * @tparam State State of the current optional.
         * @return Either has_value or no_value state.
         */
        template <optional_state State = optional_state::unknown>
        WOJ_NODISCARD constexpr optional_state state() const noexcept
        {
            if constexpr (State != optional_state::unknown)
            {
                return State;
            }

            return m_has_value ? optional_state::has_value : optional_state::no_value;
        }

        /**
         * Returns a specified state of the optional.
         * @tparam DynamicStates Uses dynamic states when provided.
         * @param state State of the current optional.
         * @return A specified state of the optional.
         */
        template <dynamic_states_t DynamicStates = dynamic_states>
        WOJ_NODISCARD constexpr optional_state state(const optional_state state) const noexcept
        {
            if (state != optional_state::unknown)
            {
                return state;
            }

            return m_has_value ? optional_state::has_value : optional_state::no_value;
        }

        /**
         * Swaps the values of two optionals.
         * @tparam State State of the current optional.
         * @tparam OtherState State of the other optional.
         * @param other The optional to swap with.
         * @return The reference to the swapped optional.
         */
        template <optional_state State = optional_state::unknown, optional_state OtherState = optional_state::unknown>
        constexpr optional& swap(optional& other)
        noexcept((std::is_move_constructible<ValueType>::value&& std::is_nothrow_move_constructible<ValueType>::value) || (std::is_swappable<ValueType>::value && std::is_nothrow_swappable<ValueType>::value))
        {
            // ---------- SELF: 1 (CSTATE) ----------
            if constexpr (State == optional_state::has_value)
            {
                // -----> SELF: 1 (CSTATE), OTHER: 1 (CSTATE) <---------
                if constexpr (OtherState == optional_state::has_value)
                {
                    std::swap(m_value, other.m_value);
                }
                // -----> SELF: 1 (CSTATE), OTHER: 0 (CSTATE) <---------
                else if constexpr (OtherState == optional_state::no_value || OtherState == optional_state::uninitialized)
                {
                    std::construct_at(std::addressof(other.m_value), std::move(m_value));
                    other.m_has_value = true;
                    m_has_value = false;
                }
                // -----> SELF: 1 (CSTATE), OTHER: 1 (RSTATE) <---------
                else if (other.m_has_value)
                {
                    std::swap(m_value, other.m_value);
                }
                // -----> SELF: 1 (CSTATE), OTHER: 0 (RSTATE) <---------
                else
                {
                    std::construct_at(std::addressof(other.m_value), std::move(m_value));
                    other.m_has_value = true;
                    m_has_value = false;
                }
            }
            // ---------- SELF: 0 (CSTATE) ----------
            else if constexpr (State == optional_state::no_value)
            {
                // -----> SELF: 0 (CSTATE), OTHER: 1 (CSTATE) <---------
                if constexpr (OtherState == optional_state::has_value)
                {
                    std::construct_at(std::addressof(m_value), std::move(other.m_value));
                    other.m_has_value = false;
                    m_has_value = true;
                }
                // -----> SELF: 0 (CSTATE), OTHER: 0 (CSTATE) <--------- OMITTED

                // -----> SELF: 0 (CSTATE), OTHER: ? (CSTATE) <---------
                else if constexpr (OtherState == optional_state::unknown)
                {
                    // >> SELF: 0 (CSTATE), OTHER: 1 (RSTATE) <<--------
                    if (other.m_has_value)
                    {
                        std::construct_at(std::addressof(m_value), std::move(other.m_value));
                        other.m_has_value = false;
                        m_has_value = true;
                    }
                    // >> SELF: 0 (CSTATE), OTHER: 0 (RSTATE) <<-------- OMITTED
                }
            }
            // ---------0 SELF: - (CSTATE) ---------
            else if constexpr (State == optional_state::uninitialized)
            {
                // -----> SELF: - (CSTATE), OTHER: 1 (CSTATE) <---------
                if constexpr (OtherState == optional_state::has_value)
                {
                    std::construct_at(std::addressof(m_value), std::move(other.m_value));
                    other.m_has_value = false;
                    m_has_value = true;
                }
                // -----> SELF: - (CSTATE), OTHER: 0 (CSTATE) <---------
                else if (OtherState == optional_state::no_value)
                {
                    m_has_value = false;
                }
                // -----> SELF: - (CSTATE), OTHER: - (CSTATE) <---------
                else if constexpr (OtherState == optional_state::uninitialized)
                {
                    m_has_value = false;
                    other.m_has_value = false;
                }

                // -----> SELF: 0 (CSTATE), OTHER: ? (CSTATE) <---------
                else if constexpr (OtherState == optional_state::unknown)
                {
                    // >> SELF: 0 (CSTATE), OTHER: 1 (RSTATE) <<--------
                    if (other.m_has_value)
                    {
                        std::construct_at(std::addressof(m_value), std::move(other.m_value));
                        other.m_has_value = false;
                        m_has_value = true;
                    }
                    // >> SELF: 0 (CSTATE), OTHER: 0 (RSTATE) <<-------- OMITTED
                }
            }
            // ---------- SELF: ? (CSTATE) ----------
            else if constexpr (State == optional_state::unknown)
            {
                // -----> SELF: ? (CSTATE), OTHER: 1 (CSTATE) <---------
                if constexpr (OtherState == optional_state::has_value)
                {
                    // >> SELF: 1 (RSTATE), OTHER: 1 (CSTATE) <<--------
                    if (*this)
                    {
                        std::swap(m_value, other.m_value);
                    }
                    // >> SELF: 0 (RSTATE), OTHER: 1 (CSTATE) <<--------
                    else
                    {
                        std::construct_at(std::addressof(m_value), std::move(other.m_value));
                        other.m_has_value = false;
                        m_has_value = true;
                    }
                }
                // -----> SELF: ?, OTHER: 0 (CSTATE) <---------
                else if constexpr (OtherState == optional_state::no_value)
                {
                    // >> SELF: 1 (RSTATE), OTHER: 0 (CSTATE) <<--------
                    if (*this)
                    {
                        std::construct_at(std::addressof(other.m_value), std::move(m_value));
                        other.m_has_value = true;
                        m_has_value = false;
                    }
                    // >> SELF: 0 (RSTATE), OTHER: 0 (CSTATE) <<-------- OMITTED
                }
                // -----> SELF: 1 (RSTATE), OTHER: 1 (RSTATE) <---------
                else if (m_has_value && other.m_has_value)
                {
                    std::swap(m_value, other.m_value);
                }
                // -----> SELF: 1 (RSTATE), OTHER: 0 (RSTATE) <---------
                else if (*this)
                {
                    std::construct_at(std::addressof(other.m_value), std::move(m_value));
                    other.m_has_value = true;
                    m_has_value = false;
                }
                // -----> SELF: 0 (RSTATE), OTHER: 1 (RSTATE) <---------
                else if (other.m_has_value)
                {
                    std::construct_at(std::addressof(m_value), std::move(other.m_value));
                    other.m_has_value = false;
                    m_has_value = true;
                }
                // -----> SELF: 0 (RSTATE), OTHER: 0 (RSTATE) <--------- OMITTED
            }

            return *this;
        }

        /**
         * Swaps the values of two optionals.
         * @tparam DynamicStates Uses dynamic states when provided.
         * @param state State of the current optional.
         * @param other_state State of the other optional.
         * @param other The optional to swap with.
         * @return The reference to the swapped optional.
         */
        template <dynamic_states_t DynamicStates = dynamic_states>
        constexpr optional& swap(const optional_state state, const optional_state other_state, optional& other)
            noexcept((std::is_move_constructible_v<ValueType>&& std::is_nothrow_move_constructible_v<ValueType>) || (std::is_swappable_v<ValueType> && std::is_nothrow_swappable_v<ValueType>))
        {
            // ---------- SELF: 1 (CSTATE) ----------
            if (state == optional_state::has_value)
            {
                // -----> SELF: 1 (CSTATE), OTHER: 1 (CSTATE) <---------
                if (other_state == optional_state::has_value)
                {
                    std::swap(m_value, other.m_value);
                }
                // -----> SELF: 1 (CSTATE), OTHER: 0 (CSTATE) <---------
                else if (other_state == optional_state::no_value)
                {
                    std::construct_at(std::addressof(other.m_value), std::move(m_value));
                    other.m_has_value = true;
                    m_has_value = false;
                }
                // -----> SELF: 1 (CSTATE), OTHER: 1 (RSTATE) <---------
                else if (other.m_has_value)
                {
                    std::swap(m_value, other.m_value);
                }
                // -----> SELF: 1 (CSTATE), OTHER: 0 (RSTATE) <---------
                else
                {
                    std::construct_at(std::addressof(other.m_value), std::move(m_value));
                    other.m_has_value = true;
                    m_has_value = false;
                }
            }
            // ---------- SELF: 0 (CSTATE) ----------
            else if (state == optional_state::no_value)
            {
                // -----> SELF: 0 (CSTATE), OTHER: 1 (CSTATE) <---------
                if (other_state == optional_state::has_value)
                {
                    std::construct_at(std::addressof(m_value), std::move(other.m_value));
                    other.m_has_value = false;
                    m_has_value = true;
                }
                // -----> SELF: 0 (CSTATE), OTHER: 0 (CSTATE) <--------- OMITTED

                // -----> SELF: 0 (CSTATE), OTHER: ? (CSTATE) <---------
                else if (other_state == optional_state::unknown)
                {
                    // >> SELF: 0 (CSTATE), OTHER: 1 (RSTATE) <<--------
                    if (other.m_has_value)
                    {
                        std::construct_at(std::addressof(m_value), std::move(other.m_value));
                        other.m_has_value = false;
                        m_has_value = true;
                    }
                    // >> SELF: 0 (CSTATE), OTHER: 0 (RSTATE) <<-------- OMITTED
                }
            }
            // ---------- SELF: - (CSTATE) ---------- OMITTED
            // ---------- SELF: ? (CSTATE) ----------
            else if (state == optional_state::unknown)
            {
                // -----> SELF: ? (CSTATE), OTHER: 1 (CSTATE) <---------
                if (other_state == optional_state::has_value)
                {
                    // >> SELF: 1 (RSTATE), OTHER: 1 (CSTATE) <<--------
                    if (*this)
                    {
                        std::swap(m_value, other.m_value);
                    }
                    // >> SELF: 0 (RSTATE), OTHER: 1 (CSTATE) <<--------
                    else
                    {
                        std::construct_at(std::addressof(m_value), std::move(other.m_value));
                        other.m_has_value = false;
                        m_has_value = true;
                    }
                }
                // -----> SELF: ?, OTHER: 0 (CSTATE) <---------
                else if (other_state == optional_state::no_value)
                {
                    // >> SELF: 1 (RSTATE), OTHER: 0 (CSTATE) <<--------
                    if (*this)
                    {
                        std::construct_at(std::addressof(other.m_value), std::move(m_value));
                        other.m_has_value = true;
                        m_has_value = false;
                    }
                    // >> SELF: 0 (RSTATE), OTHER: 0 (CSTATE) <<-------- OMITTED
                }
                // -----> SELF: 1 (RSTATE), OTHER: 1 (RSTATE) <---------
                else if (m_has_value && other.m_has_value)
                {
                    std::swap(m_value, other.m_value);
                }
                // -----> SELF: 1 (RSTATE), OTHER: 0 (RSTATE) <---------
                else if (*this)
                {
                    std::construct_at(std::addressof(other.m_value), std::move(m_value));
                    other.m_has_value = true;
                    m_has_value = false;
                }
                // -----> SELF: 0 (RSTATE), OTHER: 1 (RSTATE) <---------
                else if (other.m_has_value)
                {
                    std::construct_at(std::addressof(m_value), std::move(other.m_value));
                    other.m_has_value = false;
                    m_has_value = true;
                }
                // -----> SELF: 0 (RSTATE), OTHER: 0 (RSTATE) <--------- OMITTED
            }
            return *this;
        }
    };
};