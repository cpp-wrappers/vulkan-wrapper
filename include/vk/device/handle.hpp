#pragma once

#include <core/forward.hpp>
#include <core/elements/one_of.hpp>
#include <core/types/count_of_ranges_of_value_type.hpp>
#include <core/elements/range_of_value_type.hpp>
#include <core/range/of_value_type.hpp>
#include <core/exchange.hpp>

#include "../shared/headers.hpp"
#include "../shared/queue_family_index.hpp"
#include "../shared/result.hpp"
#include "../shared/handle.hpp"
#include "../shared/memory_requirements.hpp"
#include "../shared/guarded_handle.hpp"
#include "../shared/timeout.hpp"
#include "../shared/create_or_allocate.hpp"
#include "mapped_memory_range.hpp"

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

		template<typename ObjectType, typename... Args>
		elements::one_of<vk::result, vk::handle<ObjectType>>
		try_create(Args&&... args) const {
			return vk::try_create<ObjectType>(*this, forward<Args>(args)...);
		}

		template<typename ObjectType, typename... Args>
		vk::handle<ObjectType>
		create(Args&&... args) const {
			return vk::create<ObjectType>(*this, forward<Args>(args)...);
		}

		template<typename ObjectType, typename... Args>
		elements::one_of<vk::result, vk::handle<ObjectType>>
		try_allocate(Args&&... args) const {
			return vk::try_allocate<ObjectType>(*this, forward<Args>(args)...);
		}

		template<typename ObjectType, typename... Args>
		vk::handle<ObjectType>
		allocate(Args&&... args) const {
			return vk::allocate<ObjectType>(*this, forward<Args>(args)...);
		}

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

		vk::result try_wait_idle() const {
			return {
				(int32) vkDeviceWaitIdle(
					(VkDevice) value
				)
			};
		}

		vk::result try_wait_for_fences(
			range::of_value_type<vk::handle<vk::fence>> auto&& fences,
			bool wait_all,
			vk::timeout timeout
		) const {
			return {
				(int32) vkWaitForFences(
					(VkDevice) vk::get_handle_value(*this),
					(uint32) fences.size(),
					(VkFence*) fences.data(),
					uint32{ wait_all },
					(uint64) timeout
				)
			};
		}

		template<range::of_value_type<vk::handle<vk::fence>> Fences>
		void wait_for_fences(
			Fences&& fences,
			bool wait_all,
			vk::timeout timeout
		) const {
			vk::result result = try_wait_for_fences(forward<Fences>(fences), wait_all, timeout);
			if(!result.success()) throw result;
		}

		vk::result try_reset_fences(range::of_value_type<vk::handle<vk::fence>> auto&& fences) const {
			return {
				(int) vkResetFences(
					(VkDevice) vk::get_handle_value(*this),
					(uint32) fences.size(),
					(VkFence*) fences.data()
				)
			};
		}

		template<range::of_value_type<vk::handle<vk::fence>> Fences>
		void reset_fences(Fences&& fences) const {
			auto result = try_reset_fences(forward<Fences>(fences));
			if(!result.success()) throw result;
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
#include "../shader/module/create.hpp"
#include "../framebuffer/create.hpp"
#include "../image/view/create.hpp"
#include "../pipeline/layout/create.hpp"
#include "../pipeline/graphics/create.hpp"
#include "../render_pass/create.hpp"
#include "../semaphore/create.hpp"
#include "../swapchain/create.hpp"
#include "../buffer/create.hpp"
#include "memory/allocate.hpp"
#include "../fence/create.hpp"