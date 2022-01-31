#pragma once

#include <core/integer.hpp>

#include "../../headers.hpp"
#include "../../memory_size.hpp"
#include "../../memory_type_index.hpp"

namespace vk {

	struct memory_allocate_info {
		const uint32 type = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
		const void* const next = nullptr;
		vk::memory_size size;
		vk::memory_type_index memory_type_index;
	};

} // vk

static_assert(sizeof(vk::memory_allocate_info) == sizeof(VkMemoryAllocateInfo));