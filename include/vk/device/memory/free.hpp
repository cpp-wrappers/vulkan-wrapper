#pragma once

#include "../../shared/destroy_or_free.hpp"
#include "../handle.hpp"
#include "handle.hpp"

namespace vk {

	template<>
	struct vk::free_t<vk::device_memory> {

		void operator () (vk::handle<vk::device> device, vk::handle<vk::device_memory> device_memory) const {
			vkFreeMemory(
				(VkDevice) vk::get_handle_value(device),
				(VkDeviceMemory) vk::get_handle_value(device_memory),
				(VkAllocationCallbacks*) nullptr
			);
		} 

	};

}