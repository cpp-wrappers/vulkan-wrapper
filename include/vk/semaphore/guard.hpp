#pragma once

#include "handle.hpp"
#include "../device/handle.hpp"

namespace vk {
	class semaphore_guard {
		vk::semaphore semaphore;
		vk::device device;
	public:

		semaphore_guard(vk::semaphore semaphore, vk::device device)
			: semaphore{ semaphore }, device{ device }
		{}

		~semaphore_guard() {
			if(semaphore.handle) {
				vkDestroySemaphore(
					(VkDevice) device.handle,
					(VkSemaphore) exchange(semaphore.handle, 0),
					nullptr
				);
			}
		}
	};
}