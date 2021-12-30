#pragma once

#include "../shared/device_size.hpp"
#include "../shared/headers.hpp"
#include "../shared/memory_type_index.hpp"

namespace vk {
	struct memory_requirements {
		vk::device_size size;
		vk::device_size alignment;
		vk::memory_type_indices memory_type_bits;
	};
} // vk

static_assert(sizeof(vk::memory_requirements) == sizeof(VkMemoryRequirements));