#pragma once

#include "handle.hpp"

#include "../handle.hpp"
#include "../../function.hpp"

#include <core/meta/types/are_exclusively_satisfying_predicates.hpp>

extern "C" VK_ATTR void VK_CALL vkUnmapMemory(
	handle<vk::device> device,
	handle<vk::device_memory> memory
);

namespace vk {

	template<typename... Args>
	requires types::are_exclusively_satisfying_predicates<
		types::are_contain_one_decayed<handle<vk::device>>,
		types::are_contain_one_decayed<handle<vk::device_memory>>
	>::for_types<Args...>
	void unmap_memory(Args&&... args) {
		auto device = elements::decayed<handle<vk::device>>(args...);

		auto device_memory {
			elements::decayed<handle<vk::device_memory>>(args...)
		};

		vkUnmapMemory(
			device,
			device_memory
		);
	}

} // vk

void inline
handle<vk::device>::unmap_memory(
	handle<vk::device_memory> device_memory
) const {
	vk::unmap_memory(*this, device_memory);
}