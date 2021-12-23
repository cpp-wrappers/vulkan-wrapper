#pragma once

#include "handle.hpp"
#include "create.hpp"
#include "../../shared/guarded_handle.hpp"

namespace vk {

	template<>
	class guarded_handle<vk::command_pool> {
		vk::handle<vk::command_pool> command_pool;
		vk::handle<vk::device> device;
	public:

		guarded_handle(vk::handle<vk::command_pool> command_pool, vk::handle<vk::device> device)
			: command_pool{ command_pool }, device{ device }
		{}

		~guarded_handle() {
			if(command_pool.value) {
				vkDestroyCommandPool(
					(VkDevice) device.value,
					(VkCommandPool) exchange(command_pool.value, 0),
					nullptr
				);
			}
		}

		template<range::of_value_type<vk::handle<vk::command_buffer>> CommandBuffers>
		vk::result try_allocate_command_buffers(
			vk::command_buffer_level level,
			CommandBuffers&& command_buffers
		) {
			return command_pool.try_allocate_command_buffers(device, level, forward<CommandBuffers>(command_buffers));
		}

		template<range::of_value_type<vk::handle<vk::command_buffer>> CommandBuffers>
		void allocate_command_buffers(
			vk::command_buffer_level level,
			CommandBuffers&& command_buffers
		) {
			command_pool.allocate_command_buffers(device, level, forward<CommandBuffers>(command_buffers));
		}

		template<range::of_value_type<vk::handle<vk::command_buffer>> CommandBuffers>
		void free_command_buffers(CommandBuffers&& command_buffers) {
			command_pool.free_command_buffers(device, forward<CommandBuffers>(command_buffers));
		}
	};
}