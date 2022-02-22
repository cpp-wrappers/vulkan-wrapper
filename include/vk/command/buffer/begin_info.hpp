#pragma once

#include "usage.hpp"
#include "inheritance_info.hpp"

#include <core/flag_enum.hpp>

#include "vk/headers.hpp"

namespace vk {

	struct command_buffer_begin_info {
		const uint32 type = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
		const void* const next;
		vk::command_buffer_usages usages;
		const vk::command_buffer_inheritance_info* inheritance_info;
	};

} // vk

static_assert(sizeof(vk::command_buffer_begin_info) == sizeof(VkCommandBufferBeginInfo));