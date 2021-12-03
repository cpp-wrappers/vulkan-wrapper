#pragma once

#include "handle.hpp"
#include "create.hpp"

namespace vk {
	class command_pool_guard;

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

		const vk::device& object() const {
			return device;
		}
		
		template<typename... Args>
		vk::shader_module create_shader_module(Args... args) const {
			return device.create_shader_module<Args...>(forward<Args>(args)...);
		}

		template<typename... Args>
		vk::command_pool_guard create_guarded_command_pool(Args&&... args) const;

		vk::queue get_queue(vk::queue_family_index queue_family_index, vk::queue_index queue_index) const {
			return device.get_queue(queue_family_index, queue_index);
		}

		vk::result try_wait_idle() const {
			return device.try_wait_idle();
		}

		void wait_idle() const {
			auto result = try_wait_idle();
			if(!result.success()) throw result;
		}
	}; //device_guard
} // vk

#include "../command/pool/guard.hpp"

template<typename... Args>
vk::command_pool_guard vk::device_guard::create_guarded_command_pool(Args&&... args) const {
	return { device.create_command_pool(forward<Args>(args)...), this->device };
}