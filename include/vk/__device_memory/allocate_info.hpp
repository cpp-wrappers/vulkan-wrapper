#pragma once

#include "../__internal/memory_size.hpp"
#include "../__internal/memory_type_index.hpp"

#include <integer.hpp>

namespace vk {

	struct memory_allocate_info {
		const uint32 structure_type = 5;
		const void* next = nullptr;
		vk::memory_size size;
		vk::memory_type_index memory_type_index;
	};

} // vk