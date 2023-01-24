#pragma once

#include <integer.hpp>

namespace vk {

	struct semaphore_create_info {
		uint32      structure_type = 9;
		const void* next;
		uint32      flags = 0;
	};

} // vk