#pragma once

#include "headers.hpp"
#include "device_size.hpp"
#include "memory_type_index.hpp"
#include "memory_size.hpp"

namespace vk {
	struct memory_requirements {
		vk::memory_size size;
		vk::device_size alignment;
		vk::memory_type_indices memory_type_indices;
	};
} // vk

static_assert(sizeof(vk::memory_requirements) == sizeof(VkMemoryRequirements));