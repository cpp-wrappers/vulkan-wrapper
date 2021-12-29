#pragma once

#include "handle.hpp"

#include "allocate_info.hpp"
#include "handle.hpp"
#include "../../shared/create_or_allocate.hpp"
#include "../../device/handle.hpp"

namespace vk {

	vk::result try_allocate_command_buffers(
		vk::handle<vk::device> device,
		vk::handle<vk::command_pool> command_pool,
		vk::command_buffer_level level,
		range::of_value_type<vk::handle<vk::command_buffer>> auto&& command_buffers
	) {
		vk::command_buffer_allocate_info ai {
			.command_pool = command_pool,
			.level = level,
			.count = (uint32) command_buffers.size()
		};

		return {
			(int32) vkAllocateCommandBuffers(
				(VkDevice) device.value,
				(VkCommandBufferAllocateInfo*) &ai,
				(VkCommandBuffer*) command_buffers.data()
			)
		};
	}

	template<>
	struct vk::try_allocate_t<vk::command_buffer> {

		elements::one_of<vk::result, vk::handle<vk::command_buffer>>
		operator () (
			vk::handle<vk::device> device,
			vk::handle<vk::command_pool> command_pool,
			vk::command_buffer_level level
		) const {
			vk::command_buffer_allocate_info ai {
				.command_pool = command_pool,
				.level = level,
				.count = 1
			};

			VkCommandBuffer command_buffer;

			vk::result result {
				(int32) vkAllocateCommandBuffers(
					(VkDevice) device.value,
					(VkCommandBufferAllocateInfo*) &ai,
					(VkCommandBuffer*) &command_buffer
				)
			};

			if(result.success()) return vk::handle<vk::command_buffer>{ command_buffer };

			return result;
		}
	};

}