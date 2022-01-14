#pragma once

#include <core/integer.hpp>
#include <core/flag_enum.hpp>

#include "../../../shared/headers.hpp"
#include "../../../shared/queue_family_index.hpp"

namespace vk {

	enum class command_pool_create_flag {
		transient = VK_COMMAND_POOL_CREATE_TRANSIENT_BIT,
		reset_command_buffer = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT,
		рrotected = VK_COMMAND_POOL_CREATE_PROTECTED_BIT
	};

	using command_pool_create_flags = flag_enum<vk::command_pool_create_flag>;

	struct command_pool_create_info {
		const uint32 type = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
		const void* const next;
		vk::command_pool_create_flags flags;
		vk::queue_family_index queue_family_index;
	};

} // vk

static_assert(sizeof(vk::command_pool_create_info) == sizeof(VkCommandPoolCreateInfo));