#pragma once

#include "../__shader_module/stage.hpp"
#include "../__internal/size.hpp"
#include "../__internal/offset.hpp"

#include <types.hpp>
#include <tuple.hpp>

namespace vk {

	struct push_constant_range {
		vk::shader_stages stages;
		vk::offset<1> offset;
		vk::size size;

		template<typename... Args>
		requires types<Args...>::template exclusively_satisfy_predicates<
			count_of_decayed_same_as<vk::shader_stages> == 1,
			count_of_decayed_same_as<vk::offset<1>> <= 1,
			count_of_decayed_same_as<vk::size> == 1
		>
		push_constant_range(Args&&... args) {
			stages = tuple{ args... }.template
				get_decayed_same_as<vk::shader_stages>();

			if constexpr(types<Args...>::template
				count_of_decayed_same_as<vk::offset<1>> > 0
			) {
				offset = tuple{ args... }.template
					get_decayed_same_as<vk::offset<1>>();
			}
			size = tuple{ args... }.template
				get_decayed_same_as<vk::size>();
		}
	};

} // vk