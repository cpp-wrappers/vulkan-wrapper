#pragma once

#include <core/types/are_exclusively_satsify_predicates.hpp>
#include <core/elements/range_of_value_type.hpp>
#include <core/types/are_contain_range_of_value_type.hpp>
#include <core/type/negated_predicate.hpp>
#include <core/types/count_of_ranges_of_value_type.hpp>
#include <core/elements/pass_satisfying_type_predicate.hpp>
#include <core/types/count_of_type.hpp>
#include <core/elements/of_type.hpp>
#include <core/elements/for_each_of_type.hpp>
#include <core/elements/one_of.hpp>

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
}