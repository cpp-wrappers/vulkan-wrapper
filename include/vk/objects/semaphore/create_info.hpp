#pragma once

#include <core/integer.hpp>

#include "../../shared/headers.hpp"

namespace vk {

	struct semaphore_create_info {
		const uint32 type = (uint32) VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
		const void* next;
		uint32 flags = 0;
	};

}

static_assert(sizeof(vk::semaphore_create_info) == sizeof(VkSemaphoreCreateInfo));