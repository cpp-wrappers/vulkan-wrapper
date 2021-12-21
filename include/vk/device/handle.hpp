#pragma once

#include <core/forward.hpp>
#include <core/elements/one_of.hpp>
#include <core/types/count_of_ranges_of_value_type.hpp>
#include <core/elements/range_of_value_type.hpp>
#include <core/exchange.hpp>

#include "../shared/headers.hpp"
#include "../shared/queue_family_index.hpp"
#include "../shared/result.hpp"

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

	struct queue_index : wrapper::of_integer<uint32, struct queue_index_t> {};

	struct device {
		void* handle;

		inline vk::queue get_queue(vk::queue_family_index queue_family_index, vk::queue_index queue_index) const;

		template<typename... Args>
		elements::one_of<vk::result, vk::shader_module>
		try_create_shader_module(Args&&... args) const;

		template<typename... Args>
		vk::shader_module create_shader_module(Args&&... args) const;

		template<typename... Args>
		vk::command_pool create_command_pool(Args&&... args) const;

		template<typename... Args>
		elements::one_of<vk::result, vk::framebuffer>
		try_create_framebuffer(Args&&... args) const;

		template<typename... Args>
		vk::framebuffer create_framebuffer(Args&&... args) const;

		template<typename... Args>
		elements::one_of<vk::result, vk::image_view>
		try_create_image_view(Args&&... args) const;

		template<typename... Args>
		vk::image_view create_image_view(Args&&... args) const;

		template<typename... Args>
		elements::one_of<vk::result, vk::pipeline_layout>
		try_create_pipeline_layout(Args&&... args) const;

		template<typename... Args>
		vk::pipeline_layout create_pipeline_layout(Args&&... args) const;

		template<typename... Args>
		elements::one_of<vk::result, vk::pipeline>
		try_create_graphics_pipeline(Args&&... args) const;

		template<typename... Args>
		vk::pipeline create_graphics_pipeline(Args&&... args) const;

		template<typename... Args>
		elements::one_of<vk::result, vk::render_pass>
		try_create_render_pass(Args&&... args) const;

		template<typename... Args>
		vk::render_pass create_render_pass(Args&&... args) const;

		template<typename... Args>
		elements::one_of<vk::result, vk::semaphore>
		try_create_semaphore(Args&&... args) const;

		template<typename... Args>
		semaphore create_semaphore(Args&&... args) const;

		vk::result try_wait_idle() const {
			return {
				(int32) vkDeviceWaitIdle(
					(VkDevice) handle
				)
			};
		}
		
	}; // device

} // vk

#include "../queue/handle.hpp"

inline vk::queue vk::device::get_queue(vk::queue_family_index queue_family_index, vk::queue_index queue_index) const {
	VkQueue queue;

	vkGetDeviceQueue(
		(VkDevice) handle,
		(uint32) queue_family_index,
		(uint32) queue_index,
		(VkQueue*) &queue
	);

	return { queue };
}

#include "../command/pool/create.hpp"

template<typename... Args>
vk::command_pool
vk::device::create_command_pool(Args&&... args) const {
	return vk::create_command_pool(*this, forward<Args>(args)...);
}

#include "../shader/module/create.hpp"

template<typename... Args>
elements::one_of<vk::result, vk::shader_module>
vk::device::try_create_shader_module(Args&&... args) const {
	return vk::try_create_shader_module(*this, args...);
}

template<typename... Args>
vk::shader_module
vk::device::create_shader_module(Args&&... args) const {
	auto result = try_create_shader_module(forward<Args>(args)...);
	if(result.template is_current<vk::result>()) throw result.template get<vk::result>();
	return result.template get<vk::shader_module>();
}

#include "../framebuffer/create.hpp"

template<typename... Args>
elements::one_of<vk::result, vk::framebuffer>
vk::device::try_create_framebuffer(Args&&... args) const {
	return vk::try_create_framebuffer(*this, args...);
}

template<typename... Args>
vk::framebuffer
vk::device::create_framebuffer(Args&&... args) const {
	auto result = try_create_framebuffer(forward<Args>(args)...);
	if(result.template is_current<vk::result>()) throw result.template get<vk::result>();
	return result.template get<vk::framebuffer>();
}

#include "../image/view/create.hpp"

template<typename... Args>
elements::one_of<vk::result, vk::image_view>
vk::device::try_create_image_view(Args&&... args) const {
	return vk::try_create_image_view(*this, args...);
}

template<typename... Args>
vk::image_view
vk::device::create_image_view(Args&&... args) const {
	auto result = try_create_image_view(forward<Args>(args)...);
	if(result.template is_current<vk::result>()) throw result.template get<vk::result>();
	return result.template get<vk::image_view>();
}

#include "../pipeline/layout/create.hpp"

template<typename... Args>
elements::one_of<vk::result, vk::pipeline_layout>
vk::device::try_create_pipeline_layout(Args&&... args) const {
	return vk::try_create_pipeline_layout(*this, args...);
}

template<typename... Args>
vk::pipeline_layout
vk::device::create_pipeline_layout(Args&&... args) const {
	auto result = try_create_pipeline_layout(forward<Args>(args)...);
	if(result.template is_current<vk::result>()) throw result.template get<vk::result>();
	return result.template get<vk::pipeline_layout>();
}

#include "../pipeline/create.hpp"

template<typename... Args>
elements::one_of<vk::result, vk::pipeline>
vk::device::try_create_graphics_pipeline(Args&&... args) const {
	return vk::try_create_graphics_pipeline(*this, args...);
}

template<typename... Args>
vk::pipeline
vk::device::create_graphics_pipeline(Args&&... args) const {
	auto result = try_create_graphics_pipeline(forward<Args>(args)...);
	if(result.template is_current<vk::result>()) throw result.template get<vk::result>();
	return result.template get<vk::pipeline>();
}

#include "../render_pass/create.hpp"

template<typename... Args>
elements::one_of<vk::result, vk::render_pass>
vk::device::try_create_render_pass(Args&&... args) const {
	return vk::try_create_render_pass(*this, args...);
}

template<typename... Args>
vk::render_pass
vk::device::create_render_pass(Args&&... args) const {
	auto result = try_create_render_pass(forward<Args>(args)...);
	if(result.template is_current<vk::result>()) throw result.template get<vk::result>();
	return result.template get<vk::render_pass>();
}

#include "../semaphore/create.hpp"

template<typename... Args>
elements::one_of<vk::result, vk::semaphore>
vk::device::try_create_semaphore(Args&&... args) const {
	return vk::try_create_semaphore(*this, args...);
}

template<typename... Args>
vk::semaphore
vk::device::create_semaphore(Args&&... args) const {
	auto result = try_create_semaphore(forward<Args>(args)...);
	if(result.template is_current<vk::result>()) throw result.template get<vk::result>();
	return result.template get<vk::semaphore>();
}