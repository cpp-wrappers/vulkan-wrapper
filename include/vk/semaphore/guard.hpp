#pragma once

#include "handle.hpp"
#include "create.hpp"
#include "../device/handle.hpp"
#include "../shared/guarded.hpp"

namespace vk {

	template<>
	class guarded<vk::semaphore> {
		vk::semaphore semaphore;
		vk::device device;
	public:

		guarded(vk::semaphore semaphore, vk::device device)
			: semaphore{ semaphore }, device{ device }
		{}

		template<typename... Args>
		guarded(vk::device device, Args&&... args)
			: semaphore{ vk::create_semaphore(device, forward<Args>(args)...)  }, device{ device }
		{}

		guarded(guarded&& other)
			: semaphore{ exchange(other.semaphore.handle, 0) }, device{ other.device }
		{}

		~guarded() {
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