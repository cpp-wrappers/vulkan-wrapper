#pragma once

#include "handle.hpp"
#include "../../device/handle.hpp"
#include "../../shared/guarded_handle.hpp"

namespace vk {

	template<>
	class vk::guarded_handle<vk::shader_module> {
		vk::handle<vk::shader_module> shader_module;
		vk::handle<vk::device> device;
	public:

		guarded_handle(vk::handle<vk::shader_module> shader_module, vk::handle<vk::device> device)
			: shader_module{ shader_module }, device{ device }
		{}

		guarded_handle(guarded_handle&& other)
			: shader_module{ exchange(other.shader_module.value, 0) }
		{}

		~guarded_handle() {
			if(shader_module.value) {
				vkDestroyShaderModule(
					(VkDevice) device.value,
					(VkShaderModule) exchange(shader_module.value, 0),
					nullptr
				);
			}
		}

		const vk::handle<vk::shader_module>& object() const {
			return shader_module;
		}
	};
}