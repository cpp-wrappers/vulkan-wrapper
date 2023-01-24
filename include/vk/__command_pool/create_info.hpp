#pragma once

#include "../__internal/queue_family_index.hpp"

#include <integer.hpp>
#include <enum_flags.hpp>

namespace vk {

	enum class command_pool_create_flag {
		transient            = 0x00000001,
		reset_command_buffer = 0x00000002,
		_protected           = 0x00000004
	};

	using command_pool_create_flags = enum_flags<vk::command_pool_create_flag>;

	struct command_pool_create_info {
		uint32                        structure_type = 39;
		const void*                   next = nullptr;
		vk::command_pool_create_flags flags;
		vk::queue_family_index        queue_family_index;
	};

} // vk