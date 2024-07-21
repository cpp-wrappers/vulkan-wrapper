#pragma once

#include "../__internal/access.hpp"

#include <integer.hpp>
#include <types.hpp>
#include <tuple.hpp>

namespace vk {

	struct memory_barrier {
		uint32 type = 46;
		const void* next = nullptr;
		vk::src_access src_access_mask;
		vk::dst_access dst_access_mask;

		template<typename... Args>
		requires types<Args...>::template exclusively_satisfy_predicates<
			is_same_as<vk::src_access>.decayed == 1,
			is_same_as<vk::dst_access>.decayed == 1
		>
		memory_barrier(Args&&... args) {
			src_access_mask = tuple { args... }.template
				get_decayed_same_as<vk::src_access>();
			dst_access_mask = tuple { args... }.template
				get_decayed_same_as<vk::dst_access>();
		}
	};

}