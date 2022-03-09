#pragma once

#include "allocate_flag.hpp"

#include "vk/headers.hpp"

namespace vk {

	struct memory_allocate_flags_info {
		const uint32 __type = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO;
		const void* next;
		vk::memory_allocate_flags flags;
		uint32 device_mask;
	};

} // vk

static_assert(sizeof(vk::memory_allocate_flags_info) == sizeof(VkMemoryAllocateFlagsInfo));