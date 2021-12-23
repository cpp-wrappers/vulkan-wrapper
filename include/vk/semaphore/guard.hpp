#pragma once

#include "handle.hpp"
#include "create.hpp"
#include "../device/handle.hpp"
#include "../shared/guarded_handle.hpp"

namespace vk {

	template<>
	class guarded_handle<vk::semaphore> {
		vk::handle<vk::semaphore> semaphore;
		vk::handle<vk::device> device;
	public:

		guarded_handle(vk::handle<vk::semaphore> semaphore, vk::handle<vk::device> device)
			: semaphore{ semaphore }, device{ device }
		{}

		guarded_handle(guarded_handle&& other)
			: semaphore{ exchange(other.semaphore.value, 0) }, device{ other.device }
		{}

		~guarded_handle() {
			if(semaphore.value) {
				vkDestroySemaphore(
					(VkDevice) device.value,
					(VkSemaphore) exchange(semaphore.value, 0),
					(VkAllocationCallbacks*) nullptr
				);
			}
		}

		const vk::handle<vk::semaphore>& object() const {
			return semaphore;
		}
	};
} // vk