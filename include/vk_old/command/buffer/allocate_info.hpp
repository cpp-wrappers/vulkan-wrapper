#pragma once

#include "level.hpp"

#include "../../command/pool/handle.hpp"

#include <core/handle.hpp>

namespace vk {

	struct command_buffer_allocate_info {
		uint32 structure_type = 40;
		const void* next;
		handle<vk::command_pool> command_pool;
		vk::command_buffer_level level;
		uint32 count;
	};

} // vk