#pragma once

#include "handle.hpp"
#include "../shared/guarded_device_child_handle.hpp"
#include "../device/handle.hpp"

namespace vk {

	template<>
	struct vk::guarded_handle<vk::buffer> : vk::guarded_device_child_handle_base<vk::buffer> {
		using base_type = vk::guarded_device_child_handle_base<vk::buffer>;

		using base_type::base_type;

		~guarded_handle() {
			if(handle().value) {
				vkDestroyBuffer(
					(VkDevice) device().value,
					(VkBuffer) exchange(handle().value, 0),
					(VkAllocationCallbacks*) nullptr
				);
			}
		}
	};

}