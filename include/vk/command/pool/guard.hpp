#pragma once

#include "handle.hpp"
#include "create.hpp"

namespace vk {
	class command_pool_guard {
		vk::command_pool command_pool;
		vk::device device;
	public:

		command_pool_guard(vk::command_pool command_pool, vk::device device)
			: command_pool{ command_pool }, device{ device }
		{}

		template<typename... Args>
		command_pool_guard(vk::device device, Args&&... args)
			: command_pool{ vk::create_command_pool(device, forward<Args>(args)...) }, device{ device }
		{}

		~command_pool_guard() {
			if(command_pool.handle) {
				vkDestroyCommandPool(
					(VkDevice) device.handle,
					(VkCommandPool) exchange(command_pool.handle, 0),
					nullptr
				);
			}
		}

		template<type::range_of_value_type<vk::command_buffer> CommandBuffers>
		vk::result try_allocate_command_buffers(
			vk::command_buffer_level level,
			CommandBuffers&& command_buffers
		) {
			return command_pool.try_allocate_command_buffers(device, level, forward<CommandBuffers>(command_buffers));
		}

		template<type::range_of_value_type<vk::command_buffer> CommandBuffers>
		void allocate_command_buffers(
			vk::command_buffer_level level,
			CommandBuffers&& command_buffers
		) {
			command_pool.allocate_command_buffers(device, level, forward<CommandBuffers>(command_buffers));
		}

		template<type::range_of_value_type<vk::command_buffer> CommandBuffers>
		void free_command_buffers(CommandBuffers&& command_buffers) {
			command_pool.free_command_buffers(device, forward<CommandBuffers>(command_buffers));
		}
	};
}