#pragma once

#include <core/meta/type/negated_predicate.hpp>
#include <core/meta/types/are_exclusively_satsify_predicates.hpp>
#include <core/meta/types/are_contain_range_of_value_type.hpp>
#include <core/meta/types/count_of_ranges_of_value_type.hpp>
#include <core/meta/elements/one_of.hpp>
#include <core/meta/elements/range_of_value_type.hpp>

namespace vk {
	
	template<typename ObjectType>
	inline constexpr bool is_allocatable = false;

	template<typename ObjectType>
	inline constexpr bool is_creatable = !is_allocatable<ObjectType>;

	template<typename ObjectType>
	requires(vk::is_creatable<ObjectType>)
	struct create_t;

	template<typename ObjectType>
	constexpr inline vk::create_t<ObjectType> create = vk::create_t<ObjectType>{};

	template<typename ObjectType>
	requires(vk::is_allocatable<ObjectType>)
	struct allocate_t;

	template<typename ObjectType>
	constexpr inline vk::allocate_t<ObjectType> allocate = vk::allocate_t<ObjectType>{};

} // vk