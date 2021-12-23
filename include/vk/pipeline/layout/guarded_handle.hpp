#pragma once

#include "handle.hpp"
#include "../../device/handle.hpp"
#include "../../shared/guarded_device_child_handle.hpp"

namespace vk {

	template<>
	struct vk::guarded_handle<vk::pipeline_layout> : vk::guarded_device_child_handle_base<vk::pipeline_layout> {
		using base_type = vk::guarded_device_child_handle_base<vk::pipeline_layout>;

		using base_type::base_type;

		~guarded_handle() {
			if(handle().value) {
				vkDestroyPipelineLayout(
					(VkDevice) device().value,
					(VkPipelineLayout) exchange(handle().value, 0),
					(VkAllocationCallbacks*) nullptr
				);
			}
		}
	};
}