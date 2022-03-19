#pragma once

#include <core/integer.hpp>

#include "../../headers.hpp"
#include "../../device_size.hpp"
#include "../../memory_offset.hpp"
#include "../../memory_size.hpp"
#include "handle.hpp"

namespace vk {

	struct mapped_memory_range {
		const uint32 type = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE;
		const void* next;
		handle<vk::device_memory> memory;
		vk::memory_offset offset;
		vk::memory_size size;
	};

} // vk