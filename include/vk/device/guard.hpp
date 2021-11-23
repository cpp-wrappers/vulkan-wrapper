#pragma once

#include "handle.hpp"

namespace vk {
	class device_guard {
		vk::device device;
	public:

		device_guard(vk::device device)
			: device{ device }
		{}

		~device_guard() {
			if(device.handle) {
				vkDestroyDevice(
					(VkDevice) exchange(device.handle, nullptr),
					nullptr
				);
			}
		}

		vk::device object() const {
			return device;
		}
		
		template<typename... Args>
		vk::shader_module create_shader_module(Args... args) const {
			return device.create_shader_module<Args...>(forward<Args>(args)...);
		}
	};
}