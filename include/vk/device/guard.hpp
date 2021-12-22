#pragma once

#include <core/exchange.hpp>

#include "handle.hpp"
#include "../shared/guarded.hpp"

namespace vk {

	template<>
	class guarded<vk::device> {
		vk::handle<vk::device> device;
	public:

		guarded(vk::handle<vk::device> device)
			: device{ device }
		{}

		guarded(guarded&& other)
			: device{ exchange(other.device.value, nullptr) }
		{}

		~guarded() {
			if(device.value) {
				vkDestroyDevice(
					(VkDevice) exchange(device.value, nullptr),
					nullptr
				);
			}
		}

		const vk::handle<vk::device>& object() const {
			return device;
		}
		
		template<typename... Args>
		vk::handle<vk::shader_module> create_shader_module(Args... args) const {
			return device.create_shader_module<Args...>(forward<Args>(args)...);
		}

		template<typename... Args>
		vk::guarded<vk::shader_module> create_guarded_shader_module(Args&&... args) const;

		template<typename... Args>
		vk::guarded<vk::command_pool> create_guarded_command_pool(Args&&... args) const;

		template<typename... Args>
		vk::guarded<vk::framebuffer> create_guarded_framebuffer(Args&&... args) const;

		template<typename... Args>
		vk::guarded<vk::image_view> create_guarded_image_view(Args&&... args) const;

		template<typename... Args>
		vk::guarded<vk::pipeline_layout> create_guarded_pipeline_layout(Args&&... args) const;

		template<typename... Args>
		vk::guarded<vk::pipeline> create_guarded_graphics_pipeline(Args&&... args) const;

		template<typename... Args>
		vk::guarded<vk::render_pass> create_guarded_render_pass(Args&&... args) const;

		template<typename... Args>
		vk::guarded<vk::semaphore> create_guarded_semaphore(Args&&... args) const;

		template<typename... Args>
		vk::guarded<vk::swapchain> create_guarded_swapchain(Args&&... args) const;

		vk::handle<vk::queue> get_queue(vk::queue_family_index queue_family_index, vk::queue_index queue_index) const {
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

#include "../shader/module/guard.hpp"

template<typename... Args>
vk::guarded<vk::shader_module> vk::guarded<vk::device>::create_guarded_shader_module(Args&&... args) const {
	return { device.create_shader_module(forward<Args>(args)...), this->device };
}

#include "../command/pool/guard.hpp"

template<typename... Args>
vk::guarded<vk::command_pool> vk::guarded<vk::device>::create_guarded_command_pool(Args&&... args) const {
	return { device.create_command_pool(forward<Args>(args)...), this->device };
}

#include "../framebuffer/guard.hpp"

template<typename... Args>
vk::guarded<vk::framebuffer> vk::guarded<vk::device>::create_guarded_framebuffer(Args&&... args) const {
	return { device.create_framebuffer(forward<Args>(args)...), this->device };
}

#include "../image/view/guard.hpp"

template<typename... Args>
vk::guarded<vk::image_view> vk::guarded<vk::device>::create_guarded_image_view(Args&&... args) const {
	return { device.create_image_view(forward<Args>(args)...), this->device };
}

#include "../pipeline/layout/guard.hpp"

template<typename... Args>
vk::guarded<vk::pipeline_layout> vk::guarded<vk::device>::create_guarded_pipeline_layout(Args&&... args) const {
	return { device.create_pipeline_layout(forward<Args>(args)...), this->device };
}

#include "../pipeline/guard.hpp"

template<typename... Args>
vk::guarded<vk::pipeline> vk::guarded<vk::device>::create_guarded_graphics_pipeline(Args&&... args) const {
	return { device.create_graphics_pipeline(forward<Args>(args)...), this->device };
}

#include "../render_pass/guard.hpp"

template<typename... Args>
vk::guarded<vk::render_pass> vk::guarded<vk::device>::create_guarded_render_pass(Args&&... args) const {
	return { device.create_render_pass(forward<Args>(args)...), this->device };
}

#include "../semaphore/guard.hpp"

template<typename... Args>
vk::guarded<vk::semaphore> vk::guarded<vk::device>::create_guarded_semaphore(Args&&... args) const {
	return { device.create_semaphore(forward<Args>(args)...), this->device };
}

#include "../swapchain/guard.hpp"

template<typename... Args>
vk::guarded<vk::swapchain> vk::guarded<vk::device>::create_guarded_swapchain(Args&&... args) const {
	return { device.create_swapchain(forward<Args>(args)...), this->device };
}