#pragma once

#include "handle.hpp"

#include <core/type/range.hpp>

#include "allocate_info.hpp"
#include "../../shared/headers.hpp"
#include "../../device/handle.hpp"

namespace vk {

	vk::result try_allocate_command_buffers(
		vk::device device,
		vk::command_pool command_pool,
		vk::command_buffer_level level,
		type::range_of_value_type<vk::command_buffer> auto&& command_buffers
	) {
		vk::command_buffer_allocate_info ai {
			.command_pool = command_pool,
			.level = level,
			.count = (uint32) command_buffers.size()
		};

		return {
			(int32) vkAllocateCommandBuffers(
				(VkDevice) device.handle,
				(VkCommandBufferAllocateInfo*) &ai,
				(VkCommandBuffer*) command_buffers.data()
			)
		};
	}

}