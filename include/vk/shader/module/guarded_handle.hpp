#pragma once

#include "handle.hpp"
#include "../../device/handle.hpp"
#include "../../shared/guarded_device_child_handle.hpp"

namespace vk {

	template<>
	struct vk::guarded_handle<vk::shader_module> : vk::guarded_device_child_handle_base<vk::shader_module> {
		using base_type = vk::guarded_device_child_handle_base<vk::shader_module>;

		using base_type::base_type;

		void reset(vk::handle<vk::shader_module> v) {
			if(handle().value) {
				vkDestroyShaderModule(
					(VkDevice) device().value,
					(VkShaderModule) handle().value,
					nullptr
				);
			}
			handle() = v;
		}
	};
}