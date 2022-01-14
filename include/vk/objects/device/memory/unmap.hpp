#pragma once

#include <core/types/are_exclusively_satsify_predicates.hpp>

#include "../handle.hpp"
#include "handle.hpp"

namespace vk {

	template<typename... Args>
	requires types::are_exclusively_satsify_predicates<
		types::vk::are_contain_one_possibly_guarded_handle_of<vk::device>,
		types::vk::are_contain_one_possibly_guarded_handle_of<vk::device_memory>
	>::for_types_of<Args...>
	void unmap_device_memory(Args&&... args) {
		auto& device = elements::vk::possibly_guarded_handle_of<vk::device>::for_elements_of(args...);
		auto& device_memory = elements::vk::possibly_guarded_handle_of<vk::device_memory>::for_elements_of(args...);

		vkUnmapMemory(
			(VkDevice) vk::get_handle_value(device),
			(VkDeviceMemory) vk::get_handle_value(device_memory)
		);
	}

} // vk