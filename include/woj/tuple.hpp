#pragma once

#include <type_traits>
#include "woj/base.hpp"

namespace woj
{
    class bad_tuple_access : public exception
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


        template <size_t Index>
        constexpr none_t get() const
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

        constexpr none_t get(const size_t) const
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

        constexpr size_t size() const
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
            FirstType m_data[1];
        };

        constexpr single() 
            noexcept 
            (
                std::is_nothrow_default_constructible_v<FirstType>
            )
            : m_data{} {}

        constexpr single(const FirstType &first)
            noexcept 
            (
                std::is_nothrow_copy_constructible_v<FirstType>
            )
            : m_data{ first } {}

        constexpr single(FirstType &&first)
            noexcept 
            (
                std::is_nothrow_move_constructible_v<FirstType>
            )
            : m_data{ std::move(first) } {}

        constexpr single(const single &other)
            noexcept 
            (
                std::is_nothrow_copy_constructible_v<FirstType>
            )
            : m_data{ other.m_data } {}

        constexpr single(single &&other)
            noexcept 
            (
                std::is_nothrow_move_constructible_v<FirstType>
            )
            : m_data{ std::move(other.m_data) } {}

        template <typename... Args>
        constexpr single(in_place_t, Args &&...args)
            noexcept 
            (
                std::is_nothrow_copy_constructible_v<FirstType>
            )
            : m_data{ std::forward<Args>(args)... } {}

        constexpr single &operator=(const single &other)
            noexcept
            (
                std::is_nothrow_copy_assignable_v<FirstType>
            )
        {
            m_data = other.m_data;
            return *this;
        }

        constexpr single &operator=(single &&other)
            noexcept
            (
                std::is_nothrow_move_assignable_v<FirstType>
            )
        {
            m_data = std::move(other.m_data);
            return *this;
        }

        constexpr ~single()
            noexcept
            (
                std::is_nothrow_destructible_v<FirstType>
            ) = default;

        constexpr bool operator==(const single &other) const

            noexcept
        {
            return m_data == other.m_data;
        }

        constexpr std::strong_ordering operator<=>(const single &other) const
            noexcept
        {
            return m_data <=> other.m_data;
        }

        constexpr FirstType operator[](const size_t index) const
            noexcept
#ifndef NDEBUG
            (
                false
            )
#endif
        {
#ifndef NDEBUG
            if (!index)
                return m_data[index];
            throw bad_tuple_access{ __LINE__, "Single access out of bounds.", __FILE__, __func__ };
#else
            return m_data[index];
#endif
        }

        constexpr FirstType get(const size_t index) const
            noexcept
#ifndef NDEBUG
            (
                false
            )
#endif
        {
            return operator[](index);
        }

        constexpr size_t size() const
            noexcept
        {
            return 1;
        }

        constexpr explicit operator bool() const
            noexcept
        {
            return true;
        }
    };

    template <typename FirstType, typename SecondType>
    class pair
    {
    public:
        union
        {
            FirstType m_data[2];
        };

        constexpr pair() 
            noexcept 
            (
                std::is_nothrow_default_constructible_v<FirstType> &&
                std::is_nothrow_default_constructible_v<SecondType>
            )
            : m_data{} {}

        constexpr pair(const FirstType &first, const SecondType &second)
            noexcept 
            (
                std::is_nothrow_copy_constructible_v<FirstType> &&
                std::is_nothrow_copy_constructible_v<SecondType>
            )
            : m_data{ first, second } {}

        constexpr pair(FirstType &&first, SecondType &&second)
            noexcept 
            (
                std::is_nothrow_move_constructible_v<FirstType> &&
                std::is_nothrow_move_constructible_v<SecondType>
            )
            : m_data{ std::move(first), std::move(second) } {}

        constexpr pair(const pair &other)
            noexcept 
            (
                std::is_nothrow_copy_constructible_v<FirstType> &&
                std::is_nothrow_copy_constructible_v<SecondType>
            )
            : m_data{ other.m_data } {}

        constexpr pair(pair &&other)
            noexcept 
            (
                std::is_nothrow_move_constructible_v<FirstType> &&
                std::is_nothrow_move_constructible_v<SecondType>
            )
            : m_data{ std::move(other.m_data) } {}

        constexpr pair &operator=(const pair &other)
            noexcept
            (
                std::is_nothrow_copy_assignable_v<FirstType> &&
                std::is_nothrow_copy_assignable_v<SecondType>
            )
        {
            m_data = other.m_data;
            return *this;
        }

        constexpr pair &operator=(pair &&other)
            noexcept
            (
                std::is_nothrow_move_assignable_v<FirstType> &&
                std::is_nothrow_move_assignable_v<SecondType>
            )
        {
            m_data = std::move(other.m_data);
            return *this;
        }

        constexpr ~pair()
            noexcept
            (
                std::is_nothrow_destructible_v<FirstType> &&
                std::is_nothrow_destructible_v<SecondType>
            ) = default;

        constexpr bool operator==(const pair &other) const
            noexcept
        {
            return m_data[0] == other.m_data[0] && m_data[1] == other.m_data[1];
        }

        constexpr std::strong_ordering operator<=>(const pair &other) const
            noexcept
        {
            if (m_data[0] != other.m_data[0])
                return m_data[0] <=> other.m_data[0];
            return m_data[1] <=> other.m_data[1];
        }

        constexpr FirstType operator[](const size_t index) const
            noexcept
#ifndef NDEBUG
            (
                false
            )
#endif
        {
#ifndef NDEBUG
            if (index < 2)
                return m_data[index];
            throw bad_tuple_access{ __LINE__, "Pair access out of bounds.", __FILE__, __func__ };
#else
            return m_data[index];
#endif
        }

        constexpr FirstType get(const size_t index) const
            noexcept
#ifndef NDEBUG
            (
                false
            )
#endif
        {
            return operator[](index);
        }

        constexpr size_t size() const
            noexcept
        {
            return 2;
        }

        constexpr explicit operator bool() const
            noexcept
        {
            return true;
        }
    };

} // namespace woj
