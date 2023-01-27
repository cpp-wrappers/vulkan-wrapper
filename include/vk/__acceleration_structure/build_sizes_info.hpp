#pragma once

#include "../__internal/memory_size.hpp"

namespace vk {

	struct acceleration_structure_build_sizes_info {
		uint32 structure_type = 1000150020;
		const void* next = nullptr;
		vk::memory_size acceleration_structure_size;
		vk::memory_size update_scratch_size;
		vk::memory_size build_scratch_size;
	};

	namespace as {
		using build_sizes_info = vk::acceleration_structure_build_sizes_info;
	}

} // vk