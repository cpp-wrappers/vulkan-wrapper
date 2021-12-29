#pragma once

#include "handle.hpp"
#include "create.hpp"
#include "../device/handle.hpp"
#include "../shared/guarded_device_child_handle.hpp"

namespace vk {

	template<>
	struct guarded_handle<vk::semaphore> : vk::guarded_device_child_handle_base<vk::semaphore> {
		using base_type = vk::guarded_device_child_handle_base<vk::semaphore>;

		using base_type::base_type;
		guarded_handle& operator = (guarded_handle&&) = default;

		void reset(vk::handle<vk::semaphore> v) {
			if(handle().value) {
				vkDestroySemaphore(
					(VkDevice) device().value,
					(VkSemaphore) handle().value,
					(VkAllocationCallbacks*) nullptr
				);
			}
			handle() = v;
		}
	};
} // vk