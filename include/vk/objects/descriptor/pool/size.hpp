#pragma once

#include <core/types/are_exclusively_satsify_predicates.hpp>
#include <core/types/are_contain_one_type.hpp>
#include <core/elements/of_type.hpp>
#include <core/elements/satisfying_predicate.hpp>

#include "../type.hpp"
#include "../count.hpp"

namespace vk {

	struct descriptor_pool_size {
		vk::descriptor_type type;
		vk::descriptor_count descriptor_count;

		template<typename... Args>
		requires types::are_exclusively_satsify_predicates<
			types::are_contain_one_type<vk::descriptor_type>,
			types::count_of_satisfying_predicate<is_integer>::equals<1>
		>::for_types_of<decay<Args>...>
		descriptor_pool_size(Args&&... args)
		:
			type{ elements::of_type<vk::descriptor_type>(args...) },
			descriptor_count{ (uint32) elements::satisfying_predicate<is_integer>(args...) }
		{}
	};

} // vk