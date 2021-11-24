#pragma once

#include <core/integer.hpp>
#include <core/flag_enum.hpp>
#include "../../shared/headers.hpp"
#include "usage.hpp"
#include "inheritance_info.hpp"

namespace vk {
	struct command_buffer_begin_info {
		uint32 type = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
		const void* next = nullptr;
		flag_enum<vk::command_buffer_usage> usage;
		const vk::command_buffer_inheritance_info* inheritance_info;
	};
}

static_assert(sizeof(vk::command_buffer_begin_info) == sizeof(VkCommandBufferBeginInfo));