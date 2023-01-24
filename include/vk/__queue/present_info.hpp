#pragma once

#include "../__semaphore/handle.hpp"
#include "../__swapchain/handle.hpp"
#include "../__swapchain/image_index.hpp"
#include "../__internal/result.hpp"

namespace vk {

	struct present_info {
		uint32 structure_type = 1000001001;
		const void* next = nullptr;
		uint32 wait_semaphore_count = 0;
		const handle<vk::semaphore>::underlying_type* wait_semaphores = nullptr;
		uint32 swapchain_count = 0;
		const handle<vk::swapchain>::underlying_type* swapchains = nullptr;
		const vk::image_index* image_indices = nullptr;
		const vk::result*            results = nullptr;
	};

} // vk