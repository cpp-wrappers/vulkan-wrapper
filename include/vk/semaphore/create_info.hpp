#pragma once

#include <core/integer.hpp>

#include "../headers.hpp"

namespace vk {

	struct semaphore_create_info {
		const uint32 type = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
		const void* const next;
		uint32 flags = 0;
	};

} // vk

static_assert(sizeof(vk::semaphore_create_info) == sizeof(VkSemaphoreCreateInfo));