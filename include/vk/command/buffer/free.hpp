#pragma once

#include <core/range/of_value_type.hpp>

#include "../../shared/headers.hpp"
#include "handle.hpp"
#include "../../device/handle.hpp"

namespace vk {

	void free_command_buffers(
		vk::handle<vk::device> device,
		vk::handle<vk::command_pool> command_pool,
		range::of_value_type<vk::handle<vk::command_buffer>> auto&& command_buffers
	) {
		vkFreeCommandBuffers(
			(VkDevice) device.value,
			(VkCommandPool) command_pool.value,
			command_buffers.size(),
			(VkCommandBuffer*) command_buffers.data()
		);
	}

}