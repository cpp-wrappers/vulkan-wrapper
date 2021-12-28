#pragma once

#include "../shared/device_size.hpp"
#include "../shared/headers.hpp"

namespace vk {
	struct memory_requirements {
		vk::device_size size;
		vk::device_size alignment;
		uint32 memory_type_bits;
	};
} // vk

static_assert(sizeof(vk::memory_requirements) == sizeof(VkMemoryRequirements));