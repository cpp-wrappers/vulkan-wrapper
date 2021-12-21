#pragma once

#include <core/exchange.hpp>

#include "handle.hpp"
#include "create.hpp"
#include "../shared/guarded.hpp"

namespace vk {
	class command_pool_guard;
	class framebuffer_guard;
	class image_view_guard;
	class pipeline_layout_guard;
	class pipeline_guard;
	class render_pass_guard;
	class semaphore_guard;

	template<>
	class guarded<vk::device> {
		vk::device device;
	public:

		guarded(vk::device device)
			: device{ device }
		{}

		guarded(guarded&& other)
			: device{ exchange(other.device.handle, nullptr) }
		{}

		~guarded() {
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
		vk::guarded<command_pool> create_guarded_command_pool(Args&&... args) const;

		template<typename... Args>
		vk::guarded<framebuffer> create_guarded_framebuffer(Args&&... args) const;

		template<typename... Args>
		vk::guarded<image_view> create_guarded_image_view(Args&&... args) const;

		template<typename... Args>
		vk::guarded<vk::pipeline_layout> create_guarded_pipeline_layout(Args&&... args) const;

		template<typename... Args>
		vk::guarded<pipeline> create_guarded_graphics_pipeline(Args&&... args) const;

		template<typename... Args>
		vk::guarded<vk::render_pass> create_guarded_render_pass(Args&&... args) const;

		template<typename... Args>
		vk::guarded<semaphore> create_guarded_semaphore(Args&&... args) const;

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