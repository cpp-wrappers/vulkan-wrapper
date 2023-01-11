#pragma once

#include "handle.hpp"

#include "../queue/handle.hpp"
#include "../function.hpp"

#include <core/meta/decayed_same_as.hpp>

extern "C" VK_ATTR void VK_CALL vkGetDeviceQueue(
	handle<vk::device>     device,
	vk::queue_family_index queue_family_index,
	vk::queue_index        queue_index,
	handle<vk::queue>*     queue
);

namespace vk {

	template<typename... Args>
	requires types::are_exclusively_satisfying_predicates<
		types::are_contain_one_decayed<handle<vk::device>>,
		types::are_contain_one_decayed<vk::queue_family_index>,
		types::are_contain_one_decayed<vk::queue_index>
	>::for_types<Args...>
	handle<vk::queue>
	get_device_queue(Args&&... args) {
		auto device = elements::decayed<handle<vk::device>>(args...);
		auto queue_family_index {
			elements::decayed<vk::queue_family_index>(args...)
		};
		auto queue_index {
			elements::decayed<vk::queue_index>(args...)
		};

		handle<vk::queue> queue;

		vkGetDeviceQueue(device, queue_family_index, queue_index, &queue);

		return { queue };
	}

} // vk

template<typename... Args>
handle<vk::queue>
handle<vk::device>::get_queue(Args&&... args) const {
	return vk::get_device_queue(*this, forward<Args>(args)...);
}