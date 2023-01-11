#pragma once

#include <core/integer.hpp>

#include "../../memory_size.hpp"
#include "../../memory_type_index.hpp"

namespace vk {

	struct memory_allocate_info {
		const uint32 structure_type = 5;
		const void* next = nullptr;
		vk::memory_size size;
		vk::memory_type_index memory_type_index;
	};

} // vk