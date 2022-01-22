#pragma once

#include "level.hpp"
#include "../pool/handle.hpp"
#include "../../../shared/headers.hpp"

namespace vk {

	struct command_buffer_allocate_info {
		const uint32 type = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		const void* const next;
		vk::handle<vk::command_pool> command_pool;
		vk::command_buffer_level level;
		uint32 count;
	};

} // vk

static_assert(sizeof(vk::command_buffer_allocate_info) == sizeof(VkCommandBufferAllocateInfo));