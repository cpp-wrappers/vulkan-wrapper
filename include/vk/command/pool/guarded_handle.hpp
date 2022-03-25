#pragma once

#include "handle.hpp"
#include "destroy.hpp"

#include "vk/handle/guarded/device_child_base.hpp"

template<>
struct guarded_handle<vk::command_pool> :
	vk::guarded_device_child_handle_base<vk::command_pool>
{
	using base_type = vk::guarded_device_child_handle_base<vk::command_pool>;
	using base_type::base_type;

	template<typename... Args>
	void allocate_command_buffers(Args&&... args) {
		return handle().allocate_command_buffers(
			device(),
			handle(),
			forward<Args>(args)...
		);
	}

	template<typename ObjectType, typename... Args>
	guarded_handle<ObjectType> allocate_guarded(Args&&... args) const {
		return {
			device(),
			handle(),
			vk::allocate<ObjectType>(device(), handle(), forward<Args>(args)...)
		};
	}

	template<range::of<::handle<vk::command_buffer>> CommandBuffers>
	void free_command_buffers(CommandBuffers&& command_buffers) {
		handle().free_command_buffers(
			device(),
			forward<CommandBuffers>(command_buffers)
		);
	}

};

#include "../buffer/guarded_handle.hpp"