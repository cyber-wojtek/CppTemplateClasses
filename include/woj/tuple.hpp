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
            : exception{ static_cast<uint64_t>(-1), "Bad optional access.", nullptr, nullptr } {}

        constexpr bad_tuple_access(const size_t line, const char* message, const char* const file, const char* const function) 
            noexcept
            : exception{ line, message, file, function } {}
    };

    class nulluple
    {
        constexpr nulluple() 
            noexcept = default;

        constexpr nulluple(const nulluple &) 
            noexcept = default;

        constexpr nulluple(nulluple &&) 
            noexcept = default;

        constexpr nulluple(const noinit_t) 
            noexcept {}

        constexpr nulluple &operator=(const nulluple &) 
            noexcept = default;

        constexpr nulluple &operator=(nulluple &&)
            noexcept = default;

        constexpr ~nulluple()
            noexcept = default;

        constexpr bool operator==(const nulluple &) const
            noexcept
        {
            return true;
        }

        constexpr std::strong_ordering operator<=>(const nulluple &) const
            noexcept
        {
            return std::strong_ordering::equal;
        }

        constexpr none_t operator[](const size_t) const
            noexcept
#ifndef NDEBUG
            (
                false
            )
#endif
        {
#ifndef NDEBUG
            throw bad_tuple_access{ __LINE__, "Accessing nulluple.", __FILE__, __func__ };
#endif
            return none;
        }

        constexpr nulluple &copy_from(const nulluple &) 
            noexcept
        {
            return *this;
        }

        template <typename OtherNullupleType>
            requires
            (
                std::is_same_v<std::remove_cvref_t<OtherNullupleType>, nulluple>
            )
        constexpr nulluple &copy_to(OtherNullupleType&&) const
            noexcept
        {
            return *this;
        }

        template <typename OtherNullupleType>
            requires
            (
                std::is_same_v<std::remove_cvref_t<OtherNullupleType>, nulluple>
            )
        constexpr nulluple &copy_to(OtherNullupleType&&)
            noexcept
        {
            return *this;
        }

		constexpr nulluple& move_from(nulluple &&) const
			noexcept
		{
			return *this;
		}

		template <typename OtherNullupleType>
			requires
		(
			std::is_same_v<std::remove_cvref_t<OtherNullupleType>, nulluple>
			)
		constexpr nulluple& move_to(OtherNullupleType&&) const
			noexcept
		{
			return *this;
		}


        template <size_t Index>
        static constexpr none_t get()
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

        static constexpr none_t get(const size_t)
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

        static constexpr size_t size()
	        noexcept
        {
            return 0;
        }

        constexpr explicit operator bool() const
            noexcept
        {
            return false;
        }

        constexpr nulluple &swap(nulluple &) 
            noexcept 
        {
            return *this;
        }

        constexpr nulluple &swap(nulluple &&) 
            noexcept
        {
            return *this;
        }
    };

    template <typename FirstType>
    class single
    {
    public:
        union 
        {
            FirstType first;
        };

        constexpr single() 
            noexcept 
            (
                std::is_nothrow_default_constructible_v<FirstType>
            )
            : first{} {}

		template <typename OtherFirstType>
			requires
			(
				std::is_constructible_v<FirstType, const OtherFirstType &>   
            )
		explicit constexpr single(const OtherFirstType &first)
            noexcept 
            (
                std::is_nothrow_copy_constructible_v<FirstType>
            )
            : first{ first } {}

		template <typename OtherFirstType>
			requires
			(
				std::is_constructible_v<FirstType, OtherFirstType&&> &&
				std::is_rvalue_reference_v<OtherFirstType>
            )
		explicit constexpr single(OtherFirstType&& first)
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

        constexpr single(single &&other)
            noexcept 
            (
                std::is_nothrow_move_constructible_v<FirstType>
            )
            : first{ std::move(other.first) } {}

        template <typename ...ArgsTypes>
        explicit constexpr single(in_place_t, ArgsTypes &&...args)
            noexcept 
            (
                std::is_nothrow_copy_constructible_v<FirstType>
            )
            : first{ std::forward<ArgsTypes>(args)... } {}

		constexpr single& operator=(const FirstType& other)
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
				first = other;
			}
			else
			{
				std::destroy_at(std::addressof(first));
				std::construct_at(std::addressof(first), other);
			}

			return *this;
		}

		constexpr single& operator=(FirstType&& other)
			noexcept
			(
				std::is_nothrow_move_assignable_v<FirstType> ||
				(
					!std::is_move_assignable_v<FirstType> &&
					std::is_nothrow_move_constructible_v<FirstType> &&
					std::is_nothrow_destructible_v<FirstType>
				)
			)
		{
			if constexpr (std::is_move_assignable_v<FirstType>)
			{
				first = std::move(other);
			}
			else
			{
				std::destroy_at(std::addressof(first));
				std::construct_at(std::addressof(first), std::move(other));
			}

			return *this;
		}
        

        constexpr single &operator=(const single &other)
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

        constexpr single &operator=(single &&other)
            noexcept
            (
                std::is_nothrow_move_assignable_v<FirstType> ||
				(
					!std::is_move_assignable_v<FirstType> &&
					std::is_move_constructible_v<FirstType> &&
					std::is_nothrow_destructible_v<FirstType>
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
            first = std::move(other.first);
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

		constexpr  const FirstType& operator[](const size_t index) const
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

        constexpr FirstType &get(const size_t index) const
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

		constexpr single &swap(single &other)
			noexcept
			(
				std::is_nothrow_swappable_v<FirstType>
			)
		{
			std::swap(first, other.first);
			return *this;
		}

		constexpr single &swap(single &&other)
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
		union
		{
			FirstType first;
			SecondType second;
		};
		constexpr pair()
			noexcept
			(
				std::is_nothrow_default_constructible_v<FirstType>&&
				std::is_nothrow_default_constructible_v<SecondType>
			)
			: first{}, second{} {
		}

		template <typename OtherFirstType, typename OtherSecondType>
			requires
			(
				std::is_constructible_v<FirstType, OtherFirstType &&> &&
				std::is_constructible_v<SecondType, OtherSecondType &&>
			)
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

        constexpr pair(pair &&other)
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
			: first{ std::forward<ArgsTypes>(args)... }, second{ std::forward<ArgsTypes>(args)... } {
		}

		constexpr pair& operator=(const pair &other)
			noexcept
			(
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
						!std::is_copy_assignable_v<SecondType>&&
						std::is_nothrow_copy_constructible_v<SecondType>&&
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
         
		constexpr pair &operator=(pair &&other)
			noexcept
			(
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
			if constexpr (std::is_move_assignable_v<SecondType>)
			{
				second = std::move(other.second);
			}
			else
			{
				std::destroy_at(std::addressof(second));
				std::construct_at(std::addressof(second), std::move(other.second));
			}
			return *this;
		}

		constexpr ~pair()
			noexcept
			(
				std::is_nothrow_destructible_v<FirstType>&&
				std::is_nothrow_destructible_v<SecondType>
			) = default;

		constexpr bool operator==(const pair& other) const
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

        constexpr std::strong_ordering operator<=>(const pair& other) const
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

		constexpr pair &swap(pair &other)
			noexcept
			(
				std::is_nothrow_swappable_v<FirstType> &&
				std::is_nothrow_swappable_v<SecondType>
			)
		{
			std::swap(first, other.first);
			std::swap(second, other.second);
			return *this;
		}

		constexpr pair &swap(pair &&other)
			noexcept
			(
				std::is_nothrow_swappable_v<FirstType>&&
				std::is_nothrow_swappable_v<SecondType>
			)
		{
			std::swap(first, other.first);
			std::swap(second, other.second);
			return *this;
		}
	};

} // namespace woj
