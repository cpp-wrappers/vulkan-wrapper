#pragma once

#include <core/type/range.hpp>

#include "../../shared/headers.hpp"
#include "handle.hpp"
#include "../../device/handle.hpp"

namespace vk {

	void free_command_buffers(
		vk::device device,
		vk::command_pool command_pool,
		type::range_of_value_type<vk::command_buffer> auto&& command_buffers
	) {
		vkFreeCommandBuffers(
			(VkDevice) device.handle,
			(VkCommandPool) command_pool.handle,
			command_buffers.size(),
			(VkCommandBuffer*) command_buffers.data()
		);
	}

}