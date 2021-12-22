#pragma once

#include <core/forward.hpp>
#include <core/elements/one_of.hpp>
#include <core/types/count_of_ranges_of_value_type.hpp>
#include <core/elements/range_of_value_type.hpp>
#include <core/exchange.hpp>

#include "../shared/headers.hpp"
#include "../shared/queue_family_index.hpp"
#include "../shared/result.hpp"
#include "../shared/handle.hpp"

namespace vk {

	struct queue;
	struct physical_device;
	struct shader_module;
	struct command_pool;
	struct framebuffer;
	struct image_view;
	struct pipeline_layout;
	struct pipeline;
	struct render_pass;
	struct semaphore;
	struct swapchain;
	struct buffer;
	struct device;

	struct queue_index : wrapper::of_integer<uint32, struct queue_index_t> {};

	template<>
	struct vk::handle<vk::device> : vk::handle_base<vk::dispatchable> {

		inline vk::handle<vk::queue> get_queue(vk::queue_family_index queue_family_index, vk::queue_index queue_index) const;

		template<typename... Args>
		elements::one_of<vk::result, vk::handle<vk::shader_module>>
		try_create_shader_module(Args&&... args) const;

		template<typename... Args>
		vk::handle<vk::shader_module> create_shader_module(Args&&... args) const;

		template<typename... Args>
		vk::handle<vk::command_pool> create_command_pool(Args&&... args) const;

		template<typename... Args>
		elements::one_of<vk::result, vk::handle<vk::framebuffer>>
		try_create_framebuffer(Args&&... args) const;

		template<typename... Args>
		vk::handle<vk::framebuffer> create_framebuffer(Args&&... args) const;

		template<typename... Args>
		elements::one_of<vk::result, vk::handle<vk::image_view>>
		try_create_image_view(Args&&... args) const;

		template<typename... Args>
		vk::handle<vk::image_view> create_image_view(Args&&... args) const;

		template<typename... Args>
		elements::one_of<vk::result, vk::handle<vk::pipeline_layout>>
		try_create_pipeline_layout(Args&&... args) const;

		template<typename... Args>
		vk::handle<vk::pipeline_layout> create_pipeline_layout(Args&&... args) const;

		template<typename... Args>
		elements::one_of<vk::result, vk::handle<vk::pipeline>>
		try_create_graphics_pipeline(Args&&... args) const;

		template<typename... Args>
		vk::handle<vk::pipeline> create_graphics_pipeline(Args&&... args) const;

		template<typename... Args>
		elements::one_of<vk::result, vk::handle<vk::render_pass>>
		try_create_render_pass(Args&&... args) const;

		template<typename... Args>
		vk::handle<vk::render_pass> create_render_pass(Args&&... args) const;

		template<typename... Args>
		elements::one_of<vk::result, vk::handle<vk::semaphore>>
		try_create_semaphore(Args&&... args) const;

		template<typename... Args>
		vk::handle<vk::semaphore> create_semaphore(Args&&... args) const;

		template<typename... Args>
		elements::one_of<vk::result, vk::handle<vk::swapchain>>
		try_create_swapchain(Args&&... args) const;

		template<typename... Args>
		vk::handle<vk::swapchain> create_swapchain(Args&&... args) const;

		template<typename... Args>
		elements::one_of<vk::result, vk::handle<vk::buffer>>
		try_create_buffer(Args&&... args) const;

		template<typename... Args>
		vk::handle<vk::buffer> create_buffer(Args&&... args) const;

		vk::result try_wait_idle() const {
			return {
				(int32) vkDeviceWaitIdle(
					(VkDevice) value
				)
			};
		}
		
	}; // device

} // vk

#include "../queue/handle.hpp"

inline vk::handle<vk::queue>
vk::handle<vk::device>::get_queue(vk::queue_family_index queue_family_index, vk::queue_index queue_index) const {
	VkQueue queue;

	vkGetDeviceQueue(
		(VkDevice) value,
		(uint32) queue_family_index,
		(uint32) queue_index,
		(VkQueue*) &queue
	);

	return { queue };
}

#include "../command/pool/create.hpp"

template<typename... Args>
vk::handle<vk::command_pool>
vk::handle<vk::device>::create_command_pool(Args&&... args) const {
	return vk::create_command_pool(*this, forward<Args>(args)...);
}

#include "../shader/module/create.hpp"

template<typename... Args>
elements::one_of<vk::result, vk::handle<vk::shader_module>>
vk::handle<vk::device>::try_create_shader_module(Args&&... args) const {
	return vk::try_create_shader_module(*this, forward<Args>(args)...);
}

template<typename... Args>
vk::handle<vk::shader_module>
vk::handle<vk::device>::create_shader_module(Args&&... args) const {
	return vk::create_shader_module(*this, forward<Args>(args)...);
}

#include "../framebuffer/create.hpp"

template<typename... Args>
elements::one_of<vk::result, vk::handle<vk::framebuffer>>
vk::handle<vk::device>::try_create_framebuffer(Args&&... args) const {
	return vk::try_create_framebuffer(*this, forward<Args>(args)...);
}

template<typename... Args>
vk::handle<vk::framebuffer>
vk::handle<vk::device>::create_framebuffer(Args&&... args) const {
	return vk::create_framebuffer(*this, forward<Args>(args)...);
}

#include "../image/view/create.hpp"

template<typename... Args>
elements::one_of<vk::result, vk::handle<vk::image_view>>
vk::handle<vk::device>::try_create_image_view(Args&&... args) const {
	return vk::try_create_image_view(*this, forward<Args>(args)...);
}

template<typename... Args>
vk::handle<vk::image_view>
vk::handle<vk::device>::create_image_view(Args&&... args) const {
	return vk::create_image_view(*this, forward<Args>(args)...);
}

#include "../pipeline/layout/create.hpp"

template<typename... Args>
elements::one_of<vk::result, vk::handle<vk::pipeline_layout>>
vk::handle<vk::device>::try_create_pipeline_layout(Args&&... args) const {
	return vk::try_create_pipeline_layout(*this, forward<Args>(args)...);
}

template<typename... Args>
vk::handle<vk::pipeline_layout>
vk::handle<vk::device>::create_pipeline_layout(Args&&... args) const {
	return vk::create_pipeline_layout(*this, forward<Args>(args)...);
}

#include "../pipeline/create.hpp"

template<typename... Args>
elements::one_of<vk::result, vk::handle<vk::pipeline>>
vk::handle<vk::device>::try_create_graphics_pipeline(Args&&... args) const {
	return vk::try_create_graphics_pipeline(*this, forward<Args>(args)...);
}

template<typename... Args>
vk::handle<vk::pipeline>
vk::handle<vk::device>::create_graphics_pipeline(Args&&... args) const {
	return vk::create_graphics_pipeline(*this, forward<Args>(args)...);
}

#include "../render_pass/create.hpp"

template<typename... Args>
elements::one_of<vk::result, vk::handle<vk::render_pass>>
vk::handle<vk::device>::try_create_render_pass(Args&&... args) const {
	return vk::try_create_render_pass(*this, forward<Args>(args)...);
}

template<typename... Args>
vk::handle<vk::render_pass>
vk::handle<vk::device>::create_render_pass(Args&&... args) const {
	return vk::create_render_pass(*this, forward<Args>(args)...);
}

#include "../semaphore/create.hpp"

template<typename... Args>
elements::one_of<vk::result, vk::handle<vk::semaphore>>
vk::handle<vk::device>::try_create_semaphore(Args&&... args) const {
	return vk::try_create_semaphore(*this, forward<Args>(args)...);
}

template<typename... Args>
vk::handle<vk::semaphore>
vk::handle<vk::device>::create_semaphore(Args&&... args) const {
	return vk::create_semaphore(*this, forward<Args>(args)...);
}

#include "../swapchain/create.hpp"

template<typename... Args>
elements::one_of<vk::result, vk::handle<vk::swapchain>>
vk::handle<vk::device>::try_create_swapchain(Args&&... args) const {
	return vk::try_create_swapchain(*this, forward<Args>(args)...);
}

template<typename... Args>
vk::handle<vk::swapchain>
vk::handle<vk::device>::create_swapchain(Args&&... args) const {
	return vk::create_swapchain(*this, forward<Args>(args)...);
}

#include "../buffer/create.hpp"

template<typename... Args>
elements::one_of<vk::result, vk::handle<vk::buffer>>
vk::handle<vk::device>::try_create_buffer(Args&&... args) const {
	return vk::try_create_buffer(*this, forward<Args>(args)...);
}

template<typename... Args>
vk::handle<vk::buffer> vk::handle<vk::device>::create_buffer(Args&&... args) const {
	return vk::create_buffer(*this, forward<Args>(args)...);
}