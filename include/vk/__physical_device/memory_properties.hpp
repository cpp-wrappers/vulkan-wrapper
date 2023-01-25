#pragma once

#include "../memory_type.hpp"
#include "../memory_heap.hpp"

namespace vk {

	struct physical_device_memory_properties {
		uint32 memory_type_count;
		vk::memory_type memory_types[32];
		uint32 memory_heap_count;
		vk::memory_heap memory_heaps[16];
	};

} // vk