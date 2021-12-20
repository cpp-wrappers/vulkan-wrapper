#pragma once

#include "handle.hpp"
#include "create.hpp"
#include "../device/handle.hpp"

namespace vk {
	class semaphore_guard {
		vk::semaphore semaphore;
		vk::device device;
	public:

		semaphore_guard(vk::semaphore semaphore, vk::device device)
			: semaphore{ semaphore }, device{ device }
		{}

		template<typename... Args>
		semaphore_guard(vk::device device, Args&&... args)
			: semaphore{ vk::create_semaphore(device, forward<Args>(args)...)  }, device{ device }
		{}

		semaphore_guard(semaphore_guard&& other)
			: semaphore{ exchange(other.semaphore.handle, 0) }, device{ other.device }
		{}

		~semaphore_guard() {
			if(semaphore.handle) {
				vkDestroySemaphore(
					(VkDevice) device.handle,
					(VkSemaphore) exchange(semaphore.handle, 0),
					(VkAllocationCallbacks*) nullptr
				);
			}
		}

		const vk::semaphore& object() const {
			return semaphore;
		}
	};
} // vk