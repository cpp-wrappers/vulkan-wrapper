#pragma once

#include "handle.hpp"
#include "../../device/handle.hpp"
#include "../../shared/guarded.hpp"

namespace vk {

	template<>
	class vk::guarded<vk::shader_module> {
		vk::shader_module shader_module;
		vk::device device;
	public:

		guarded(vk::shader_module shader_module, vk::device device)
			: shader_module{ shader_module }, device{ device }
		{}

		guarded(guarded&& other)
			: shader_module{ exchange(other.shader_module.handle, 0) }
		{}

		~guarded() {
			if(shader_module.handle) {
				vkDestroyShaderModule(
					(VkDevice) device.handle,
					(VkShaderModule) exchange(shader_module.handle, 0),
					nullptr
				);
			}
		}

		const vk::shader_module& object() const {
			return shader_module;
		}
	};
}