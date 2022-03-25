#pragma once

#include "../handle/base.hpp"
#include "../handle/get_value.hpp"
#include "../create_or_allocate.hpp"
#include "../headers.hpp"
#include "../queue_family_index.hpp"
#include "../result.hpp"
#include "../memory_requirements.hpp"
#include "../timeout.hpp"

#include <core/forward.hpp>
#include <core/exchange.hpp>
#include <core/range/of_value_type_same_as.hpp>
#include <core/meta/elements/one_of.hpp>
#include <core/handle/possibly_guarded_of.hpp>

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

}

template<>
struct handle<vk::device> : vk::handle_base<vk::dispatchable> {

	handle<vk::queue> inline
	get_queue(
		vk::queue_family_index queue_family_index,
		vk::queue_index queue_index
	) const;

	template<typename ObjectType, typename... Args>
	vk::expected<handle<ObjectType>>
	create(Args&&... args) const {
		return vk::create<ObjectType>(*this, forward<Args>(args)...);
	}

	template<typename ObjectType, typename... Args>
	vk::expected<handle<ObjectType>>
	allocate(Args&&... args) const {
		return vk::allocate<ObjectType>(*this, forward<Args>(args)...);
	}

	vk::result try_map_memory(
		possibly_guarded_handle_of<vk::device_memory> auto& memory,
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
		
}; // handle<device>

#include "memory/allocate.hpp"
#include "../command/pool/create.hpp"
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
#include "../descriptor/set/layout/create.hpp"
#include "../descriptor/pool/create.hpp"
#include "../deferred_operation/create.hpp"
#include "../acceleration_structure/create.hpp"

#include "../queue/handle.hpp"

handle<vk::queue> inline
handle<vk::device>::get_queue(
	vk::queue_family_index queue_family_index,
	vk::queue_index queue_index
) const {
	VkQueue queue;

	vkGetDeviceQueue(
		(VkDevice) value,
		(uint32) queue_family_index,
		(uint32) queue_index,
		(VkQueue*) &queue
	);

	return { queue };
}

#include "../descriptor/set/update.hpp"

template<typename... Args>
void handle<vk::device>::update_descriptor_sets(Args&&... args) const {
	vk::update_descriptor_sets(*this, forward<Args>(args)...);
}

template<typename... Args>
void handle<vk::device>::update_descriptor_set(Args&&... args) const {
	vk::update_descriptor_set(*this, forward<Args>(args)...);
}