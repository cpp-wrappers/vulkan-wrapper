#pragma once

#include <core/forward.hpp>
#include <core/exchange.hpp>
#include <core/range/of_value_type.hpp>
#include <core/meta/elements/one_of.hpp>

#include "vk/handle/base.hpp"
#include "vk/handle/get_value.hpp"
#include "vk/handle/possibly_guarded_handle_of.hpp"
#include "vk/create_or_allocate.hpp"
#include "vk/headers.hpp"
#include "vk/queue_family_index.hpp"
#include "vk/result.hpp"
#include "vk/memory_requirements.hpp"
#include "vk/timeout.hpp"

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
	struct image;
	struct deferred_operation;
	struct acceleration_structure;

	struct queue_index : wrapper::of_integer<uint32, struct queue_index_t> {};
	struct wait_all : wrapper::of<bool, struct wait_all_t> {};

	template<>
	struct vk::handle<vk::device> : vk::handle_base<vk::dispatchable> {

		inline vk::handle<vk::queue> get_queue(vk::queue_family_index queue_family_index, vk::queue_index queue_index) const;

		template<typename ObjectType, typename... Args>
		vk::expected<vk::handle<ObjectType>>
		create(Args&&... args) const {
			return vk::create<ObjectType>(*this, forward<Args>(args)...);
		}

		template<typename ObjectType, typename... Args>
		vk::expected<vk::handle<ObjectType>>
		allocate(Args&&... args) const {
			return vk::allocate<ObjectType>(*this, forward<Args>(args)...);
		}

		vk::memory_requirements
		get_buffer_memory_requirements(vk::possibly_guarded_handle_of<vk::buffer> auto& buffer) const {
			vk::memory_requirements memory_requirements;
			vkGetBufferMemoryRequirements(
				(VkDevice) vk::get_handle_value(*this),
				(VkBuffer) vk::get_handle_value(buffer),
				(VkMemoryRequirements*) &memory_requirements
			);
			return memory_requirements;
		}

		vk::memory_requirements
		get_image_memory_requirements(vk::possibly_guarded_handle_of<vk::image> auto& image) const {
			vk::memory_requirements memory_requirements;
			vkGetImageMemoryRequirements(
				(VkDevice) vk::get_handle_value(*this),
				(VkImage) vk::get_handle_value(image),
				(VkMemoryRequirements*) &memory_requirements
			);
			return memory_requirements;
		}

		vk::result try_map_memory(
			vk::possibly_guarded_handle_of<vk::device_memory> auto& memory,
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

		vk::result try_wait_idle() const {
			return {
				(int32) vkDeviceWaitIdle(
					(VkDevice) value
				)
			};
		}

		template<typename... Args>
		void update_descriptor_sets(Args&&... args) const;

		template<typename... Args>
		void update_descriptor_set(Args&&... args) const;
		
	}; // device

} // vk

#include "memory/allocate.hpp"
#include "vk/command/pool/create.hpp"
#include "vk/shader/module/create.hpp"
#include "vk/framebuffer/create.hpp"
#include "vk/image/create.hpp"
#include "vk/image/view/create.hpp"
#include "vk/pipeline/layout/create.hpp"
#include "vk/pipeline/create.hpp"
#include "vk/render_pass/create.hpp"
#include "vk/semaphore/create.hpp"
#include "vk/swapchain/create.hpp"
#include "vk/buffer/create.hpp"
#include "vk/buffer/view/create.hpp"
#include "vk/fence/create.hpp"
#include "vk/sampler/create.hpp"
#include "vk/descriptor/set/layout/create.hpp"
#include "vk/descriptor/pool/create.hpp"
#include "vk/deferred_operation/create.hpp"
#include "vk/acceleration_structure/create.hpp"

#include "vk/queue/handle.hpp"

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

#include "vk/descriptor/set/update.hpp"

template<typename... Args>
void vk::handle<vk::device>::update_descriptor_sets(Args&&... args) const {
	vk::update_descriptor_sets(*this, forward<Args>(args)...);
}

template<typename... Args>
void vk::handle<vk::device>::update_descriptor_set(Args&&... args) const {
	vk::update_descriptor_set(*this, forward<Args>(args)...);
}