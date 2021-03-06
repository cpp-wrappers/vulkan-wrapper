#pragma once

#include "../semaphore/handle.hpp"
#include "../swapchain/handle.hpp"

namespace vk {

	struct present_info {
		uint32                       structure_type = 1000001001;
		const void*                  next = nullptr;
		uint32                       wait_semaphore_count = 0;
		const handle<vk::semaphore>* wait_semaphores = nullptr;
		uint32                       swapchain_count = 0;
		const handle<vk::swapchain>* swapchains = nullptr;
		const vk::image_index*       image_indices = nullptr;
		const vk::result*            results = nullptr;
	};

} // vk