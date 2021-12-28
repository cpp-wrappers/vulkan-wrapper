#pragma once

#include <core/integer.hpp>

#include "../../shared/headers.hpp"
#include "../../shared/device_size.hpp"

namespace vk {

	struct memory_type_index : wrapper::of_integer<uint32, struct memory_type_index_t> {};

	struct memory_allocate_info {
		const uint32 type = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
		const void* next = nullptr;
		vk::device_size size;
		vk::memory_type_index memory_type_index;
	};
}

static_assert(sizeof(vk::memory_allocate_info) == sizeof(VkMemoryAllocateInfo));