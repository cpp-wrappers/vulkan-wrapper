#pragma once

#include "memory_property.hpp"

namespace vk {

	struct memory_type {
		vk::memory_properties properties;
		uint32 head_index;
	};
} // vk

static_assert(sizeof(vk::memory_type) == sizeof(VkMemoryType));