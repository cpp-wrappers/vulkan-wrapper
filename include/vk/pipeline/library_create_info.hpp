#pragma once

#include "handle.hpp"

#include "vk/headers.hpp"

namespace vk {

	struct pipeline_library_create_info {
		uint32 structure_type = VK_STRUCTURE_TYPE_PIPELINE_LIBRARY_CREATE_INFO_KHR;
		const void* next;
		uint32 library_count;
		const handle<vk::pipeline>* libraries;
	};

} // vk

static_assert(sizeof(vk::pipeline_library_create_info) == sizeof(VkPipelineLibraryCreateInfoKHR));