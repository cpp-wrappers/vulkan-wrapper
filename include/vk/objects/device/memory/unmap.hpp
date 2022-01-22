#pragma once

#include "handle.hpp"
#include "../handle.hpp"

#include <core/meta/types/are_exclusively_satsify_predicates.hpp>

namespace vk {

	template<typename... Args>
	requires types::are_exclusively_satsify_predicates<
		types::vk::are_contain_one_possibly_guarded_handle_of<vk::device>,
		types::vk::are_contain_one_possibly_guarded_handle_of<vk::device_memory>
	>::for_types<Args...>
	void unmap_device_memory(Args&&... args) {
		auto& device = elements::vk::possibly_guarded_handle_of<vk::device>(args...);
		auto& device_memory = elements::vk::possibly_guarded_handle_of<vk::device_memory>(args...);

		vkUnmapMemory(
			(VkDevice) vk::get_handle_value(device),
			(VkDeviceMemory) vk::get_handle_value(device_memory)
		);
	}

} // vk