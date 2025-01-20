#pragma once
#include <type_traits>
#include <algorithm>
#include "../base.hpp"

namespace woj::meta
{
	template <typename FindType, typename... CheckTypes>
	struct is_any_of
	{
		static constexpr bool value = (std::is_same_v<FindType, CheckTypes> || ...);
	};

	template <typename FindType, typename... CheckTypes>
	constexpr bool is_any_of_v = is_any_of<FindType, CheckTypes...>::value;

	template <typename FindType, typename... CheckTypes>
	struct is_not_any_of
	{
		static constexpr bool value = (!std::is_same_v<FindType, CheckTypes> && ...);
	};

	template <typename FindType, typename... CheckTypes>
	constexpr bool is_not_any_of_v = is_not_any_of<FindType, CheckTypes...>::value;

	template <typename FindType, typename... CheckTypes>
	struct is_none_of
	{
		static constexpr bool value = is_not_any_of_v<FindType, CheckTypes...>;
	};

	template <typename FindType, typename... CheckTypes>
	constexpr bool is_none_of_v = is_none_of<FindType, CheckTypes...>::value;

	template <typename FindType, typename... CheckTypes>
	struct is_not_none_of
	{
		static constexpr bool value = is_any_of_v<FindType, CheckTypes...>;
	};

	template <typename FindType, typename... CheckTypes>
	constexpr bool is_not_none_of_v = is_not_none_of<FindType, CheckTypes...>::value;

	template <typename FindType, typename... CheckTypes>
	struct is_all_of
	{
		static constexpr bool value = (std::is_same_v<FindType, CheckTypes> && ...);
	};

	template <typename FindType, typename... CheckTypes>
	constexpr bool is_all_of_v = is_all_of<FindType, CheckTypes...>::value;

	template <typename FindType, typename... CheckTypes>
	struct is_not_all_of
	{
		static constexpr bool value = !is_all_of_v<FindType, CheckTypes...>;
	};

	template <typename FindType, typename... CheckTypes>
	constexpr bool is_not_all_of_v = is_not_all_of<FindType, CheckTypes...>::value;

	template <typename FindType, typename... CheckTypes>
	struct find_first_of;

	template <typename FindType>
	struct find_first_of<FindType>
	{
		static constexpr size_t value = static_cast<size_t>(-1);
	};

	template <typename FindType, typename First, typename... Rest>
	struct find_first_of<FindType, First, Rest...>
	{
		static constexpr size_t value =
			std::is_same_v<FindType, First>
			? 0
			: (find_first_of<FindType, Rest...>::value == static_cast<size_t>(-1)
				? static_cast<size_t>(-1)
				: 1 + find_first_of<FindType, Rest...>::value);

	};

	template <typename FindType, typename... CheckTypes>
	struct count_of;

	template <typename FindType>
	struct count_of<FindType>
	{
		static constexpr size_t value = 0;
	};

	template <typename FindType, typename... CheckTypes>
	struct count_of
	{
		static constexpr size_t value = (0 + ... + std::is_same_v<FindType, CheckTypes>);
	};

	template <typename FindType, typename... CheckTypes>
	constexpr size_t count_of_v = count_of<FindType, CheckTypes...>::value;
}
