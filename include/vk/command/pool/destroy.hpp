#pragma once

#include "../../headers.hpp"
#include <vulkan/vulkan_core.h>

namespace vk {

	struct device;
	struct command_pool;
	
	void inline destroy_command_pool(vk::device& device, vk::command_pool& command_pool) {
		vkDestroyCommandPool(
			(VkDevice) &device,
			(VkCommandPool) &command_pool,
			nullptr
		);
	}
}