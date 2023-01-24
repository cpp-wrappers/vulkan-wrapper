#pragma once

#include "image_index.hpp"
#include "../result.hpp"

#include <core/integer.hpp>

namespace vk {

	struct semaphore;
	struct swapchain;

	struct present_info {
		uint32 structure_type = 1000001001;
		const void* next = nullptr;
		uint32 wait_semaphore_count = 0;
		const vk::semaphore* wait_semaphores = nullptr;
		uint32 swapchain_count = 0;
		const vk::swapchain* swapchains = nullptr;
		const vk::image_index* image_indices = nullptr;
		vk::result* results = nullptr;
	};

} // vk