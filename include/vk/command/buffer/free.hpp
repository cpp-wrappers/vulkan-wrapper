#pragma once

#include <core/range/of_value_type.hpp>

#include "../../shared/headers.hpp"
#include "../../device/handle.hpp"
#include "../../shared/destroy_or_free.hpp"
#include "handle.hpp"

namespace vk {

	void free_command_buffers(
		vk::handle<vk::device> device,
		vk::handle<vk::command_pool> command_pool,
		range::of_value_type<vk::handle<vk::command_buffer>> auto&& command_buffers
	) {
		vkFreeCommandBuffers(
			(VkDevice) device.value,
			(VkCommandPool) command_pool.value,
			command_buffers.size(),
			(VkCommandBuffer*) command_buffers.data()
		);
	}

	template<>
	struct vk::free_t<vk::command_buffer> {
		void operator() (
			vk::handle<vk::device> device,
			vk::handle<vk::command_pool> command_pool,
			vk::handle<vk::command_buffer> command_buffer
		) const {
			
		}
	};

}