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
			count_of_decayed_same_as<vk::descriptor_type> == 1,
			count_of_decayed_same_as<vk::descriptor_count> <= 1
		>
		descriptor_pool_size(Args&&... args) :
			type {
				tuple{ args... }.template
					get_decayed_same_as<vk::descriptor_type>()
			}
		{
			if constexpr (types<Args...>::template
				count_of_decayed_same_as<vk::descriptor_count> > 0
			) {
				descriptor_count = tuple{ args... }.template
					get_decayed_same_as<vk::descriptor_count>();
			}
		}
	};

} // vk