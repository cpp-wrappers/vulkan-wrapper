#pragma once

#include "device_size.hpp"
#include "headers.hpp"
#include "memory_type_index.hpp"

namespace vk {
	struct memory_requirements {
		vk::device_size size;
		vk::device_size alignment;
		vk::memory_type_indices memory_type_bits;
	};
} // vk

static_assert(sizeof(vk::memory_requirements) == sizeof(VkMemoryRequirements));