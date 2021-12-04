#pragma once

#include <core/integer.hpp>
#include "../shared/headers.hpp"

namespace vk {

	class semaphore;
	class swapchain;
	class image_index;
	class result;

	struct present_info {
		const uint32 type = (uint32)VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
		const void* next;
		uint32 wait_semaphore_count;
		const vk::semaphore* wait_semaphores;
		uint32 swapchain_count;
		const vk::swapchain* swapchains;
		const vk::image_index* image_indices;
		const vk::result* results;
	};
}

static_assert(sizeof(vk::present_info) == sizeof(VkPresentInfoKHR));