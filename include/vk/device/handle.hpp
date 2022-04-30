#pragma once

#include "../handle/base.hpp"
#include "../create_or_allocate.hpp"
#include "../queue_family_index.hpp"
#include "../result.hpp"
#include "../memory_requirements.hpp"
#include "../timeout.hpp"
#include "../function.hpp"
#include "../unexpected_handler.hpp"
#include "../count.hpp"
#include "../swapchain/image_index.hpp"
#include "../memory_offset.hpp"

#include <core/handle.hpp>
#include <core/range_of_value_type_same_as.hpp>

namespace vk {

	struct queue;
	struct physical_device;
	struct shader_module;
	struct command_pool;
	struct command_buffer;
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
	struct image;
	struct deferred_operation;
	struct acceleration_structure;

	struct queue_index { uint32 _; };
	struct wait_all { bool _; };

	template<>
	inline constexpr bool is_creatable<vk::device> = true;

} // vk

template<>
struct handle<vk::device> : vk::handle_base<vk::dispatchable> {

	template<typename ObjectType, typename... Args>
	handle<ObjectType>
	create(Args&&... args) const {
		auto result = vk::create<ObjectType>(*this, forward<Args>(args)...);
		if(result.is_unexpected()) {
			vk::unexpected_handler(result.get_unexpected());
		}
		return result.get_expected();
	}

	template<typename ObjectType, typename... Args>
	handle<ObjectType>
	allocate(Args&&... args) const {
		auto result = vk::allocate<ObjectType>(*this, forward<Args>(args)...);
		if(result.is_unexpected()) {
			vk::unexpected_handler(result.get_unexpected());
		}
		return result.get_expected();
	}

	template<typename... Args>
	handle<vk::queue>
	get_queue(Args&&... args) const;

	vk::result inline try_wait_idle() const;

	void inline wait_idle() const;

	template<typename... Args>
	void update_descriptor_sets(Args&&... args) const;

	template<typename... Args>
	void update_descriptor_set(Args&&... args) const;

	vk::memory_requirements inline
	get_memory_requirements(handle<vk::buffer>) const;

	vk::memory_requirements inline
	get_memory_requirements(handle<vk::image>) const;

	void inline
	bind_memory(
		handle<vk::buffer> buffer,
		handle<vk::device_memory> memory,
		vk::memory_offset offset = {}
	) const;

	void inline
	bind_memory(
		handle<vk::image> image, handle<vk::device_memory> memory
	) const;

	template<typename... Args>
	void map_memory(Args&&... args) const;

	void inline
	unmap_memory(handle<vk::device_memory> device_memory) const;

	template<typename... Args>
	void flush_mapped_memory_range(Args&&... args) const;

	template<typename... Args>
	void wait_for_fence(Args&&... args) const;

	void inline reset_fence(handle<vk::fence> fence) const;

	template<typename... Args>
	vk::count get_swapchain_images(Args&&...) const;

	vk::count inline
	get_swapchain_image_count(handle<vk::swapchain> swapchain) const;

	template<typename... Args>
	vk::expected<vk::image_index>
	try_acquire_next_image(Args&&... args) const;

	decltype(auto)
	view_swapchain_images(
		handle<vk::swapchain> swapchain, vk::count count, auto&& f
	) const;

	template<typename F>
	decltype(auto)
	view_swapchain_images(handle<vk::swapchain> swapchain, F&& f) const;

	template<typename F>
	void
	for_each_swapchain_image(handle<vk::swapchain> swapchain, F&& f) const;

	template<range_of<handle<vk::command_buffer>> CommandBuffers>
	void free_command_buffers(
		handle<vk::command_pool> command_pool, CommandBuffers&& command_buffers
	) const;

}; // handle<device>

#include "memory/allocate.hpp"
#include "../command/pool/create.hpp"
#include "../command/buffer/allocate.hpp"
#include "../shader/module/create.hpp"
#include "../framebuffer/create.hpp"
#include "../image/create.hpp"
#include "../image/view/create.hpp"
#include "../pipeline/layout/create.hpp"
#include "../pipeline/create.hpp"
#include "../render_pass/create.hpp"
#include "../semaphore/create.hpp"
#include "../swapchain/create.hpp"
#include "../buffer/create.hpp"
#include "../buffer/view/create.hpp"
#include "../fence/create.hpp"
#include "../sampler/create.hpp"
#include "../descriptor/set/allocate.hpp"
#include "../descriptor/set/layout/create.hpp"
#include "../descriptor/pool/create.hpp"
#include "../deferred_operation/create.hpp"
#include "../acceleration_structure/create.hpp"

#include "get_queue.hpp"
#include "wait_idle.hpp"
#include "../descriptor/set/update.hpp"
#include "../buffer/get_memory_requirements.hpp"
#include "../image/get_memory_requirements.hpp"
#include "../buffer/bind_memory.hpp"
#include "../image/bind_memory.hpp"
#include "memory/map.hpp"
#include "memory/flush_mapped_range.hpp"
#include "memory/unmap.hpp"
#include "../fence/wait.hpp"
#include "../fence/reset.hpp"
#include "../swapchain/get_images.hpp"
#include "../swapchain/get_image_count.hpp"
#include "../swapchain/acquire_next_image.hpp"
#include "../swapchain/view_images.hpp"
#include "../swapchain/for_each_image.hpp"
#include "../command/buffer/free.hpp"