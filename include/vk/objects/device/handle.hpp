#pragma once

#include <core/forward.hpp>
#include <core/elements/one_of.hpp>
#include <core/types/count_of_ranges_of_value_type.hpp>
#include <core/types/are_contain_type.hpp>
#include <core/elements/range_of_value_type.hpp>
#include <core/range/of_value_type.hpp>
#include <core/exchange.hpp>

#include "../../shared/headers.hpp"
#include "../../shared/queue_family_index.hpp"
#include "../../shared/result.hpp"
#include "../../shared/memory_requirements.hpp"
#include "../../shared/timeout.hpp"
#include "../../object/handle/base.hpp"
#include "../../object/handle/get_value.hpp"
#include "../../object/create_or_allocate.hpp"

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
#include "../image/create.hpp"
#include "../image/view/create.hpp"
#include "../pipeline/layout/create.hpp"
#include "../pipeline/graphics/create.hpp"
#include "../render_pass/create.hpp"
#include "../semaphore/create.hpp"
#include "../swapchain/create.hpp"
#include "../buffer/create.hpp"
#include "../fence/create.hpp"
#include "../sampler/create.hpp"
#include "../descriptor/set_layout/create.hpp"
#include "../descriptor/pool/create.hpp"
#include "memory/allocate.hpp"