#pragma once

#include "handle.hpp"
#include "../../device/handle.hpp"

namespace vk {

	class device;

	class shader_module_guard {
		vk::shader_module shader_module;
		vk::device device;
	public:

		shader_module_guard(vk::shader_module shader_module, vk::device device)
			: shader_module{ shader_module }, device{ device }
		{}

		shader_module_guard(shader_module_guard&& other)
			: shader_module{ exchange(other.shader_module.handle, 0) }
		{}

		~shader_module_guard() {
			if(shader_module.handle) {
				vkDestroyShaderModule(
					(VkDevice) device.handle,
					(VkShaderModule) exchange(shader_module.handle, 0),
					nullptr
				);
			}
		}

		vk::shader_module object() const {
			return shader_module;
		}
	};
}