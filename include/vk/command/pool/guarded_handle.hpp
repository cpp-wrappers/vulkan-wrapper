#pragma once

#include "handle.hpp"
#include "create.hpp"
#include "../../shared/guarded_device_child_handle.hpp"

namespace vk {

	template<>
	struct vk::guarded_handle<vk::command_pool> : vk::guarded_device_child_handle_base<vk::command_pool> {
		using base_type = vk::guarded_device_child_handle_base<vk::command_pool>;

		using base_type::base_type;

		void reset(vk::handle<vk::command_pool> v) {
			if(handle().value) {
				vkDestroyCommandPool(
					(VkDevice) device().value,
					(VkCommandPool) handle().value,
					nullptr
				);
			}
			handle() = v;
		}

		template<range::of_value_type<vk::handle<vk::command_buffer>> CommandBuffers>
		vk::result try_allocate_command_buffers(
			vk::command_buffer_level level,
			CommandBuffers&& command_buffers
		) {
			return handle().try_allocate_command_buffers(device(), level, forward<CommandBuffers>(command_buffers));
		}

		template<range::of_value_type<vk::handle<vk::command_buffer>> CommandBuffers>
		void allocate_command_buffers(
			vk::command_buffer_level level,
			CommandBuffers&& command_buffers
		) {
			handle().allocate_command_buffers(device(), level, forward<CommandBuffers>(command_buffers));
		}

		template<range::of_value_type<vk::handle<vk::command_buffer>> CommandBuffers>
		void free_command_buffers(CommandBuffers&& command_buffers) {
			handle().free_command_buffers(device(), forward<CommandBuffers>(command_buffers));
		}
	};
}