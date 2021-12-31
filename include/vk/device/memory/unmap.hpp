#pragma once

#include <core/types/are_exclusively_satsify_predicates.hpp>

#include "../../shared/guarded_handle.hpp"
#include "../handle.hpp"
#include "handle.hpp"

namespace vk {

	template<typename... Args>
	requires(
		types::are_exclusively_satsify_predicates<
			types::vk::contain_one<vk::device>,
			types::vk::contain_one<vk::device_memory>
		>::for_types_of<Args...>
	)
	void unmap_device_memory(Args&&... args) {
		auto& device = elements::vk::of_type<vk::device>::for_elements_of(args...);
		auto& device_memory = elements::vk::of_type<vk::device_memory>::for_elements_of(args...);

		vkUnmapMemory(
			(VkDevice) vk::get_handle_value(device),
			(VkDeviceMemory) vk::get_handle_value(device_memory)
		);
	}
}