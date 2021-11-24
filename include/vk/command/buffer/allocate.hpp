#pragma once

#include "handle.hpp"

#include <core/type/range.hpp>

#include "allocate_info.hpp"
#include "../../shared/headers.hpp"

namespace vk {

	class device;
	class command_pool;

	vk::result try_allocate_command_buffers(
		const vk::device& device,
		const vk::command_pool& command_pool,
		vk::command_buffer_level level,
		type::range_of_value_type<vk::command_buffer> auto&& command_buffers
	) {
		vk::command_buffer_allocate_info ai {
			.command_pool = (void*) *(VkCommandPool*)&command_pool, // TODO
			.level = level,
			.count = (uint32) command_buffers.size()
		};

		return {
			(uint32) vkAllocateCommandBuffers(
				*(VkDevice*) &device,
				(VkCommandBufferAllocateInfo*) &ai,
				(VkCommandBuffer*) command_buffers.data()
			)
		};
	}

}