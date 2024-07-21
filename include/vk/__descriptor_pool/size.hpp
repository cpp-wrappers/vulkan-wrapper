#pragma once

#include "../__internal/descriptor_type.hpp"
#include "../__internal/descriptor_count.hpp"

#include <types.hpp>
#include <tuple.hpp>

namespace vk {

	struct descriptor_pool_size {
		vk::descriptor_type type;
		vk::descriptor_count descriptor_count { 1 };

		template<typename... Args>
		requires types<Args...>::template exclusively_satisfy_predicates<
			is_same_as<vk::descriptor_type>.decayed == 1,
			is_same_as<vk::descriptor_count>.decayed == 1
		>
		descriptor_pool_size(Args&&... args) {
			type = tuple{ args... }.template
				get_decayed_same_as<vk::descriptor_type>();

			descriptor_count = tuple{ args... }.template
				get_decayed_same_as<vk::descriptor_count>();
		}
	};

} // vk