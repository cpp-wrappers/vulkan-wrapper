#pragma once

#include "../../../object/handle/guarded/device_child_base.hpp"
#include "handle.hpp"
#include "destroy.hpp"

namespace vk {

	template<>
	struct vk::guarded_handle<vk::command_pool> : vk::guarded_device_child_handle_base<vk::command_pool> {
		using base_type = vk::guarded_device_child_handle_base<vk::command_pool>;

		using base_type::base_type;

		template<typename... Args>
		void allocate_command_buffers(Args&&... args) {
			return handle().allocate_command_buffers(device(), handle(), forward<Args>(args)...);
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

} // vk

#include "../buffer/guarded_handle.hpp"