#pragma once

#include "allocate_flag.hpp"

namespace vk {

	struct memory_allocate_flags_info {
		uint32 structure_type = 1000060000;
		const void* next;
		vk::memory_allocate_flags flags;
		uint32 device_mask;
	};

} // vk