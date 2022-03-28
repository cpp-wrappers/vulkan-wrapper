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
		types::are_contain_one_possibly_guarded_handle_of<vk::device>,
		types::are_contain_one_possibly_guarded_handle_of<vk::device_memory>
	>::for_types<Args...>
	void unmap_device_memory(Args&&... args) {
		auto& device = elements::possibly_guarded_handle_of<
			vk::device
		>(args...);

		auto& device_memory = elements::possibly_guarded_handle_of<
			vk::device_memory
		>(args...);

		vkUnmapMemory(
			vk::get_handle(device),
			vk::get_handle(device_memory)
		);
	}

} // vk