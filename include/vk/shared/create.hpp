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

#include "handle.hpp"
#include "result.hpp"
#include "guarded_handle.hpp"

namespace vk {

	template<typename ObjectType>
	struct try_create_t;

	template<typename ObjectType>
	constexpr inline vk::try_create_t<ObjectType> try_create = vk::try_create_t<ObjectType>{};

	template<typename ObjectType, typename... Args>
	vk::handle<ObjectType>
	create(Args&&... args) {
		auto result = vk::try_create<ObjectType>(forward<Args>(args)...);
		if(result.template is_current<vk::result>()) throw result.template get<vk::result>();
		return result.template get<vk::handle<ObjectType>>();
	}

}