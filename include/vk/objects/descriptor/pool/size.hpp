#pragma once

#include "../type.hpp"
#include "../count.hpp"

#include <core/meta/decayed_same_as.hpp>
#include <core/meta/types/are_exclusively_satsify_predicates.hpp>
#include <core/meta/elements/satisfying_predicate.hpp>

namespace vk {

	struct descriptor_pool_size {
		vk::descriptor_type type;
		vk::descriptor_count descriptor_count;

		template<typename... Args>
		requires types::are_exclusively_satsify_predicates<
			types::are_contain_one_decayed_same_as<vk::descriptor_type>,
			types::count_of_satisfying_predicate<type::modified_predicate<is_integer, type::decay>>::equals<1>
		>::for_types<Args...>
		descriptor_pool_size(Args&&... args)
		:
			type{ elements::decayed_same_as<vk::descriptor_type>(args...) },
			descriptor_count{ (uint32) elements::satisfying_predicate<type::modified_predicate<is_integer, type::decay>>(args...) }
		{}
	};

} // vk