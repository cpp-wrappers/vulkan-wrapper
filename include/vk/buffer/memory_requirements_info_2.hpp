#pragma once

#include "handle.hpp"

#include "vk/headers.hpp"

namespace vk {

	struct buffer_memory_requirements_info_2 {
		uint32 structure_type = VK_STRUCTURE_TYPE_BUFFER_MEMORY_REQUIREMENTS_INFO_2;
		const void* next;
		handle<vk::buffer> buffer;
	};

} // vk

static_assert(sizeof(vk::buffer_memory_requirements_info_2) == sizeof(VkBufferMemoryRequirementsInfo2));