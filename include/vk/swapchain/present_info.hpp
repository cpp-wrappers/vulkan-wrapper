#pragma once

#include "image_index.hpp"

#include <core/integer.hpp>

#include "vk/headers.hpp"
#include "vk/result.hpp"

namespace vk {

	struct semaphore;
	struct swapchain;

	struct present_info {
		const uint32 type = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
		const void* const next;
		uint32 wait_semaphore_count;
		const vk::semaphore* wait_semaphores;
		uint32 swapchain_count;
		const vk::swapchain* swapchains;
		const vk::image_index* image_indices;
		vk::result* results;
	};

} // vk

static_assert(sizeof(vk::present_info) == sizeof(VkPresentInfoKHR));