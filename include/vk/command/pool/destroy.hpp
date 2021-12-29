#pragma once

#include "../../shared/destroy_or_free.hpp"
#include "handle.hpp"
#include "../../device/handle.hpp"

namespace vk {

	template<>
	struct vk::destroy_t<vk::command_pool> {
		void operator() (vk::handle<vk::device> device, vk::handle<vk::command_pool> command_pool) const {
			vkDestroyCommandPool(
				(VkDevice) device.value,
				(VkCommandPool) command_pool.value,
				nullptr
			);
		}
	};

}