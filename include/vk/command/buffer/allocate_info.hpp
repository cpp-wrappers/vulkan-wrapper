#pragma once

#include "../../shared/headers.hpp"
#include "level.hpp"

namespace vk {
	struct command_buffer_allocate_info {
		uint32 type = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		const void* next = nullptr;
		void* command_pool;
		vk::command_buffer_level level;
		uint32 count;
	};
}

static_assert(sizeof(vk::command_buffer_allocate_info) == sizeof(VkCommandBufferAllocateInfo));