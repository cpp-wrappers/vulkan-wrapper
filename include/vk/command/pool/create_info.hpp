#pragma once

#include <core/integer.hpp>
#include <core/flag_enum.hpp>

#include "../../shared/headers.hpp"
#include "../../shared/queue_family_index.hpp"

namespace vk {

	enum class command_pool_create_flag {
		transient = VK_COMMAND_POOL_CREATE_TRANSIENT_BIT,
		reset_command_buffer = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT,
		рrotected = VK_COMMAND_POOL_CREATE_PROTECTED_BIT
	};

	struct command_pool_create_info {
		const uint32 type = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
		const void* next = nullptr;
		flag_enum<command_pool_create_flag> flags{};
		vk::queue_family_index queue_family_index;
	};

}

static_assert(sizeof(vk::command_pool_create_info) == sizeof(VkCommandPoolCreateInfo));