#pragma once

#include <core/forward.hpp>
#include <core/elements/one_of.hpp>
#include <core/types/count_of_ranges_of_value_type.hpp>
#include <core/elements/range_of_value_type.hpp>
#include <core/range/of_value_type.hpp>
#include <core/exchange.hpp>

#include "mapped_memory_range.hpp"
#include "../shared/headers.hpp"
#include "../shared/queue_family_index.hpp"
#include "../shared/result.hpp"
#include "../shared/handle.hpp"
#include "../shared/memory_requirements.hpp"
#include "../shared/guarded_handle.hpp"

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
	struct device_memory;
	struct fence;

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

		template<typename... Args>
		elements::one_of<vk::result, vk::handle<vk::buffer>>
		try_create_buffer(Args&&... args) const;

		template<typename... Args>
		vk::handle<vk::buffer> create_buffer(Args&&... args) const;

		vk::memory_requirements
		get_buffer_memory_requirements(vk::ordinary_or_guarded_handle<vk::buffer> auto& buffer) const {
			vk::memory_requirements memory_requirements;
			vkGetBufferMemoryRequirements(
				(VkDevice) vk::get_handle_value(*this),
				(VkBuffer) vk::get_handle_value(buffer),
				(VkMemoryRequirements*) &memory_requirements
			);
			return memory_requirements;
		}

		vk::result
		try_bind_buffer_memory(
			vk::ordinary_or_guarded_handle<vk::buffer> auto& buffer,
			vk::ordinary_or_guarded_handle<vk::device_memory> auto& memory,
			vk::device_size offset = { 0u }
		) {
			return {
				(int32) vkBindBufferMemory(
					(VkDevice) vk::get_handle_value(*this),
					(VkBuffer) vk::get_handle_value(buffer),
					(VkDeviceMemory) vk::get_handle_value(memory),
					(VkDeviceSize) offset
				)
			};
		}

		void bind_buffer_memory(
			vk::ordinary_or_guarded_handle<vk::buffer> auto& buffer,
			vk::ordinary_or_guarded_handle<vk::device_memory> auto& memory,
			vk::device_size offset = { 0u }
		) {
			vk::result result = try_bind_buffer_memory(buffer, memory, offset);
			if(!result.success()) throw result;
		}

		vk::result try_map_memory(
			vk::ordinary_or_guarded_handle<vk::device_memory> auto& memory,
			vk::device_size offset,
			vk::device_size size,
			void** data
		) {
			return {
				(int32) vkMapMemory(
					(VkDevice) vk::get_handle_value(*this),
					(VkDeviceMemory) vk::get_handle_value(memory),
					(VkDeviceSize) offset,
					(VkDeviceSize) size,
					(VkMemoryMapFlags) 0,
					(void**) data
				)
			};
		}

		void map_memory(
			vk::ordinary_or_guarded_handle<vk::device_memory> auto& memory,
			vk::device_size offset,
			vk::device_size size,
			void** data
		) {
			vk::result result = try_map_memory(memory, offset, size, data);
			if(!result.success()) throw result;
		}

		vk::result try_flush_mapped_memory_ranges(range::of_value_type<vk::mapped_memory_range> auto&& ranges) const {
			return {
				(int32) vkFlushMappedMemoryRanges(
					(VkDevice) vk::get_handle_value(*this),
					(uint32) ranges.size(),
					(VkMappedMemoryRange*) ranges.data()
				)
			};
		}

		void unmap_memory(vk::ordinary_or_guarded_handle<vk::device_memory> auto& memory) const {
			vkUnmapMemory(
				(VkDevice) vk::get_handle_value(*this),
				(VkDeviceMemory) vk::get_handle_value(memory)
			);
		}

		template<range::of_value_type<vk::mapped_memory_range> MappedMemoryRanges>
		void flush_mapped_memory_ranges(MappedMemoryRanges&& ranges) const {
			vk::result result = try_flush_mapped_memory_ranges(forward<MappedMemoryRanges>(ranges));
			if(!result.success()) throw result;
		}

		template<typename... Args>
		elements::one_of<vk::result, vk::handle<vk::device_memory>>
		try_allocate_memory(Args&&... args) const;

		template<typename... Args>
		vk::handle<vk::device_memory> allocate_memory(Args&&... args) const;

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

#include "memory/allocate.hpp"

template<typename... Args>
elements::one_of<vk::result, vk::handle<vk::device_memory>>
vk::handle<vk::device>::try_allocate_memory(Args&&... args) const {
	return vk::try_allocate_memory(*this, forward<Args>(args)...);
}

template<typename... Args>
vk::handle<vk::device_memory> vk::handle<vk::device>::allocate_memory(Args&&... args) const {
	return vk::allocate_memory(*this, forward<Args>(args)...);
}
