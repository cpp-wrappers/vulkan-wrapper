#pragma once

#include "handle.hpp"
#include "create.hpp"
#include "../../shared/guarded.hpp"

namespace vk {

	template<>
	class guarded<vk::command_pool> {
		vk::command_pool command_pool;
		vk::device device;
	public:

		guarded(vk::command_pool command_pool, vk::device device)
			: command_pool{ command_pool }, device{ device }
		{}

		~guarded() {
			if(command_pool.handle) {
				vkDestroyCommandPool(
					(VkDevice) device.handle,
					(VkCommandPool) exchange(command_pool.handle, 0),
					nullptr
				);
			}
		}

		template<range::of_value_type<vk::command_buffer> CommandBuffers>
		vk::result try_allocate_command_buffers(
			vk::command_buffer_level level,
			CommandBuffers&& command_buffers
		) {
			return command_pool.try_allocate_command_buffers(device, level, forward<CommandBuffers>(command_buffers));
		}

		template<range::of_value_type<vk::command_buffer> CommandBuffers>
		void allocate_command_buffers(
			vk::command_buffer_level level,
			CommandBuffers&& command_buffers
		) {
			command_pool.allocate_command_buffers(device, level, forward<CommandBuffers>(command_buffers));
		}

		template<range::of_value_type<vk::command_buffer> CommandBuffers>
		void free_command_buffers(CommandBuffers&& command_buffers) {
			command_pool.free_command_buffers(device, forward<CommandBuffers>(command_buffers));
		}
	};
}