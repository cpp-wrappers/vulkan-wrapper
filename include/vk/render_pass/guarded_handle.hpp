#pragma once

#include "handle.hpp"
#include "../device/handle.hpp"
#include "../shared/guarded_device_child_handle.hpp"

namespace vk {

	template<>
	struct vk::guarded_handle<vk::render_pass> : vk::guarded_device_child_handle_base<vk::render_pass> {
		using base_type = vk::guarded_device_child_handle_base<vk::render_pass>;

		using base_type::base_type;

		~guarded_handle() {
			if(handle().value) {
				vkDestroyRenderPass(
					(VkDevice) device().value,
					(VkRenderPass) exchange(handle().value, 0),
					nullptr
				);
			}
		}
	};
}