#pragma once

#include "../../shared/destroy.hpp"
#include "handle.hpp"
#include "../../device/handle.hpp"

namespace vk {

	template<>
	struct vk::destroy_t<vk::shader_module> {

		void operator () (vk::handle<vk::device> device, vk::handle<vk::shader_module> shader_module) const {
			vkDestroyShaderModule(
				(VkDevice) device.value,
				(VkShaderModule) shader_module.value,
				nullptr
			);
		}

	};

}