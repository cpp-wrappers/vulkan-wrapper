#pragma once

#include "handle.hpp"
#include "destroy.hpp"
#include "../../shared/guarded_device_child_handle.hpp"

namespace vk {

	template<>
	struct vk::guarded_handle<vk::command_pool> : vk::guarded_device_child_handle_base<vk::command_pool> {
		using base_type = vk::guarded_device_child_handle_base<vk::command_pool>;

		using base_type::base_type;

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

		template<typename ObjectType, typename... Args>
		vk::guarded_handle<ObjectType> allocate_guarded(Args&&... args) const {
			return { device(), handle(), vk::allocate<ObjectType>(device(), handle(), forward<Args>(args)...) };
		}

		template<range::of_value_type<vk::handle<vk::command_buffer>> CommandBuffers>
		void free_command_buffers(CommandBuffers&& command_buffers) {
			handle().free_command_buffers(device(), forward<CommandBuffers>(command_buffers));
		}
	};
}

#include "../buffer/guarded_handle.hpp"