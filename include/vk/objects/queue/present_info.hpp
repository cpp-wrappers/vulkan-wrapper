#pragma once

#include <core/integer.hpp>
#include "../../shared/headers.hpp"
#include "../../object/handle/base.hpp"

namespace vk {

	struct semaphore;
	struct swapchain;
	struct image_index;
	struct result;

	struct present_info {
		const uint32 type = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
		const void* const next;
		uint32 wait_semaphore_count;
		const vk::handle<vk::semaphore>* wait_semaphores;
		uint32 swapchain_count;
		const vk::handle<vk::swapchain>* swapchains;
		const vk::image_index* image_indices;
		const vk::result* results;
	};

} // vk

static_assert(sizeof(vk::present_info) == sizeof(VkPresentInfoKHR));