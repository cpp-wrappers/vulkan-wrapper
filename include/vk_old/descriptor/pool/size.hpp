#pragma once

#include "../../descriptor/type.hpp"
#include "../../descriptor/count.hpp"

#include <core/meta/decayed_same_as.hpp>
#include <core/meta/types/are_exclusively_satisfying_predicates.hpp>
#include <core/meta/elements/satisfying_predicate.hpp>

namespace vk {

	struct descriptor_pool_size {
		vk::descriptor_type type;
		vk::descriptor_count descriptor_count { 1 };

		template<typename... Args>
		requires types::are_exclusively_satisfying_predicates<
			types::are_contain_one_decayed<vk::descriptor_type>,
			types::are_may_contain_one_decayed<vk::descriptor_count>
		>::for_types<Args...>
		descriptor_pool_size(Args&&... args) :
			type{ elements::decayed<vk::descriptor_type>(args...) }
		{
			if constexpr (
				types::are_contain_decayed<
					vk::descriptor_count
				>::for_types<Args...>
			) {
				descriptor_count = {
					elements::decayed<vk::descriptor_count>(args...)
				};
			}
		}
	};

} // vk