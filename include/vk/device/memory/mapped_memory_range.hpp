#pragma once

#include <core/integer.hpp>

#include "../shared/headers.hpp"
#include "../shared/device_size.hpp"
#include "memory/handle.hpp"

namespace vk {

	struct mapped_memory_range {
		const uint32 type = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE;
		const void* next;
		vk::handle<vk::device_memory> memory;
		vk::device_size offset;
		vk::device_size size;
	};
}