#pragma once

#include "handle.hpp"
#include "create.hpp"

namespace vk {
	class device_guard {
		vk::device device;
	public:

		device_guard(vk::device device)
			: device{ device }
		{}
		
		template<typename... Args>
		device_guard(Args&&... args)
			: device{ vk::create_device(forward<Args>(args)...) }
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

		vk::queue get_queue(vk::queue_family_index queue_family_index, vk::queue_index queue_index) const {
			return device.get_queue(queue_family_index, queue_index);
		}
	}; //device_guard
} // vk