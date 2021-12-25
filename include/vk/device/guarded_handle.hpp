#pragma once

#include <core/exchange.hpp>

#include "handle.hpp"
#include "../shared/guarded_handle.hpp"

namespace vk {

	template<>
	class guarded_handle<vk::device> {
		vk::handle<vk::device> device;
	public:

		guarded_handle(vk::handle<vk::device> device)
			: device{ device }
		{}

		guarded_handle(guarded_handle&& other)
			: device{ exchange(other.device.value, nullptr) }
		{}

		~guarded_handle() {
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
		vk::guarded_handle<vk::shader_module> create_guarded_shader_module(Args&&... args) const;

		template<typename... Args>
		vk::guarded_handle<vk::command_pool> create_guarded_command_pool(Args&&... args) const;

		template<typename... Args>
		vk::guarded_handle<vk::framebuffer> create_guarded_framebuffer(Args&&... args) const;

		template<typename... Args>
		vk::guarded_handle<vk::image_view> create_guarded_image_view(Args&&... args) const;

		template<typename... Args>
		vk::guarded_handle<vk::pipeline_layout> create_guarded_pipeline_layout(Args&&... args) const;

		template<typename... Args>
		vk::guarded_handle<vk::pipeline> create_guarded_graphics_pipeline(Args&&... args) const;

		template<typename... Args>
		vk::guarded_handle<vk::render_pass> create_guarded_render_pass(Args&&... args) const;

		template<typename... Args>
		vk::guarded_handle<vk::semaphore> create_guarded_semaphore(Args&&... args) const;

		template<typename... Args>
		vk::guarded_handle<vk::swapchain> create_guarded_swapchain(Args&&... args) const;

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

#include "../shader/module/guarded_handle.hpp"

template<typename... Args>
vk::guarded_handle<vk::shader_module> vk::guarded_handle<vk::device>::create_guarded_shader_module(Args&&... args) const {
	return { device.create_shader_module(forward<Args>(args)...), this->device };
}

#include "../command/pool/guarded_handle.hpp"

template<typename... Args>
vk::guarded_handle<vk::command_pool> vk::guarded_handle<vk::device>::create_guarded_command_pool(Args&&... args) const {
	return { device.create_command_pool(forward<Args>(args)...), this->device };
}

#include "../framebuffer/guarded_handle.hpp"

template<typename... Args>
vk::guarded_handle<vk::framebuffer> vk::guarded_handle<vk::device>::create_guarded_framebuffer(Args&&... args) const {
	return { device.create_framebuffer(forward<Args>(args)...), this->device };
}

#include "../image/view/guarded_handle.hpp"

template<typename... Args>
vk::guarded_handle<vk::image_view> vk::guarded_handle<vk::device>::create_guarded_image_view(Args&&... args) const {
	return { device.create_image_view(forward<Args>(args)...), this->device };
}

#include "../pipeline/layout/guarded_handle.hpp"

template<typename... Args>
vk::guarded_handle<vk::pipeline_layout> vk::guarded_handle<vk::device>::create_guarded_pipeline_layout(Args&&... args) const {
	return { device.create_pipeline_layout(forward<Args>(args)...), this->device };
}

#include "../pipeline/guarded_handle.hpp"

template<typename... Args>
vk::guarded_handle<vk::pipeline> vk::guarded_handle<vk::device>::create_guarded_graphics_pipeline(Args&&... args) const {
	return { device.create_graphics_pipeline(forward<Args>(args)...), this->device };
}

#include "../render_pass/guarded_handle.hpp"

template<typename... Args>
vk::guarded_handle<vk::render_pass> vk::guarded_handle<vk::device>::create_guarded_render_pass(Args&&... args) const {
	return { device.create_render_pass(forward<Args>(args)...), this->device };
}

#include "../semaphore/guarded_handle.hpp"

template<typename... Args>
vk::guarded_handle<vk::semaphore> vk::guarded_handle<vk::device>::create_guarded_semaphore(Args&&... args) const {
	return { device.create_semaphore(forward<Args>(args)...), this->device };
}

#include "../swapchain/guarded_swapchain.hpp"

template<typename... Args>
vk::guarded_handle<vk::swapchain> vk::guarded_handle<vk::device>::create_guarded_swapchain(Args&&... args) const {
	return { device.create_swapchain(forward<Args>(args)...), this->device };
}