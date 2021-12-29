#pragma once

#include "../shared/destroy.hpp"
#include "handle.hpp"
#include "../device/handle.hpp"

namespace vk {

	template<>
	struct vk::destroy_t<vk::semaphore> {
		void operator() (vk::handle<vk::device> device, vk::handle<vk::semaphore> semaphore) const {
			vkDestroySemaphore(
				(VkDevice) device.value,
				(VkSemaphore) semaphore.value,
				nullptr
			);
		}
	};

}