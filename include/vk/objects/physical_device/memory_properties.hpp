#pragma once

#include "../../shared/headers.hpp"
#include "../../shared/memory_type.hpp"
#include "../../shared/memory_heap.hpp"

namespace vk {

	struct physical_device_memory_properties {
		uint32 memory_type_count;
		vk::memory_type memory_types[VK_MAX_MEMORY_TYPES];
		uint32 memory_heap_count;
		vk::memory_heap memory_heaps[VK_MAX_MEMORY_HEAPS];
	};

} // vk

static_assert(sizeof(vk::physical_device_memory_properties) == sizeof(VkPhysicalDeviceMemoryProperties));