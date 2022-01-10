#pragma once

#include <core/integer.hpp>

#include "../shared/headers.hpp"
#include "../shared/result.hpp"
#include "image_index.hpp"

namespace vk {

	struct semaphore;
	struct swapchain;

	struct present_info {
		const uint32 type = (uint32) VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
		const void* next;
		uint32 wait_semaphore_count;
		const vk::semaphore* wait_semaphores;
		uint32 swapchain_count;
		const vk::swapchain* swapchains;
		const vk::image_index* image_indices;
		vk::result* results;
	};

}

static_assert(sizeof(vk::present_info) == sizeof(VkPresentInfoKHR));