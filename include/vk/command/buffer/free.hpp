#pragma once

#include <core/type/range.hpp>

#include "../../shared/headers.hpp"

namespace vk {
	class device;
	class command_pool;
	class command_buffer;

	void free_command_buffers(
		const vk::device& device,
		const vk::command_pool& command_pool,
		type::range_of_value_type<vk::command_buffer> auto&& command_buffers
	) {
		vkFreeCommandBuffers(
			*(VkDevice*) &device,
			*(VkCommandPool*) &command_pool,
			command_buffers.size(),
			(VkCommandBuffer*) command_buffers.data()
		);
	}

}