#pragma once

#include <core/exchange.hpp>

#include "handle.hpp"
#include "../shared/guarded_handle.hpp"

namespace vk {

	template<>
	struct guarded_handle<vk::device> : vk::guarded_handle_base<vk::device> {
		using base_type = vk::guarded_handle_base<vk::device>;
		using base_type::base_type;

		void reset(vk::handle<vk::device> v) {
			if(handle().value) {
				vkDestroyDevice(
					(VkDevice) handle().value,
					nullptr
				);
			}
			handle() = v;
		}
		
		template<typename... Args>
		vk::handle<vk::shader_module> create_shader_module(Args... args) const {
			return handle().create_shader_module<Args...>(forward<Args>(args)...);
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

		template<typename... Args>
		vk::guarded_handle<vk::buffer> create_guarded_buffer(Args&&... args) const;

		template<typename... Args>
		vk::guarded_handle<vk::fence> create_guarded_fence(Args&&... args) const;

		vk::memory_requirements
		get_buffer_memory_requirements(vk::ordinary_or_guarded_handle<vk::buffer> auto& buffer) const {
			return handle().get_buffer_memory_requirements(buffer);
		}

		template<typename... Args>
		vk::guarded_handle<vk::device_memory> allocate_guarded_memory(Args&&... args) const;

		vk::handle<vk::queue> get_queue(vk::queue_family_index queue_family_index, vk::queue_index queue_index) const {
			return handle().get_queue(queue_family_index, queue_index);
		}

		vk::result try_wait_idle() const {
			return handle().try_wait_idle();
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
	return { handle().create_shader_module(forward<Args>(args)...), handle() };
}

#include "../command/pool/guarded_handle.hpp"

template<typename... Args>
vk::guarded_handle<vk::command_pool> vk::guarded_handle<vk::device>::create_guarded_command_pool(Args&&... args) const {
	return { handle().create_command_pool(forward<Args>(args)...), handle() };
}

#include "../framebuffer/guarded_handle.hpp"

template<typename... Args>
vk::guarded_handle<vk::framebuffer> vk::guarded_handle<vk::device>::create_guarded_framebuffer(Args&&... args) const {
	return { handle().create_framebuffer(forward<Args>(args)...), handle() };
}

#include "../image/view/guarded_handle.hpp"

template<typename... Args>
vk::guarded_handle<vk::image_view> vk::guarded_handle<vk::device>::create_guarded_image_view(Args&&... args) const {
	return { handle().create_image_view(forward<Args>(args)...), handle() };
}

#include "../pipeline/layout/guarded_handle.hpp"

template<typename... Args>
vk::guarded_handle<vk::pipeline_layout> vk::guarded_handle<vk::device>::create_guarded_pipeline_layout(Args&&... args) const {
	return { handle().create_pipeline_layout(forward<Args>(args)...), handle() };
}

#include "../pipeline/guarded_handle.hpp"

template<typename... Args>
vk::guarded_handle<vk::pipeline> vk::guarded_handle<vk::device>::create_guarded_graphics_pipeline(Args&&... args) const {
	return { handle().create_graphics_pipeline(forward<Args>(args)...), handle() };
}

#include "../render_pass/guarded_handle.hpp"

template<typename... Args>
vk::guarded_handle<vk::render_pass> vk::guarded_handle<vk::device>::create_guarded_render_pass(Args&&... args) const {
	return { handle().create_render_pass(forward<Args>(args)...), handle() };
}

#include "../semaphore/guarded_handle.hpp"

template<typename... Args>
vk::guarded_handle<vk::semaphore> vk::guarded_handle<vk::device>::create_guarded_semaphore(Args&&... args) const {
	return { handle().create_semaphore(forward<Args>(args)...), handle() };
}

#include "../swapchain/guarded_handle.hpp"

template<typename... Args>
vk::guarded_handle<vk::swapchain> vk::guarded_handle<vk::device>::create_guarded_swapchain(Args&&... args) const {
	return { handle().create_swapchain(forward<Args>(args)...), handle() };
}

#include "../buffer/guarded_handle.hpp"

template<typename... Args>
vk::guarded_handle<vk::buffer> vk::guarded_handle<vk::device>::create_guarded_buffer(Args&&... args) const {
	return { handle().create_buffer(forward<Args>(args)...), handle() };
}

#include "../fence/guarded_handle.hpp"

template<typename... Args>
vk::guarded_handle<vk::fence> vk::guarded_handle<vk::device>::create_guarded_fence(Args&&... args) const {
	return { handle().create_fence(forward<Args>(args)...), handle() };
}