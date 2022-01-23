#pragma once

#include "handle.hpp"
#include "destroy.hpp"
#include "../handle/guarded/device_child_base.hpp"

namespace vk {

	template<>
	struct vk::guarded_handle<vk::buffer> : vk::guarded_device_child_handle_base<vk::buffer> {
		using base_type = vk::guarded_device_child_handle_base<vk::buffer>;

		using base_type::base_type;

		template<typename... Args> vk::result try_bind_memory(Args&&...) const;
		template<typename... Args> void bind_memory(Args&&...) const;
	};

} // vk

#include "bind_memory.hpp"

template<typename... Args>
vk::result vk::guarded_handle<vk::buffer>::try_bind_memory(Args&&... args) const {
	return vk::try_bind_buffer_memory(device(), handle(), forward<Args>(args)...);
}

template<typename... Args>
void vk::guarded_handle<vk::buffer>::bind_memory(Args&&... args) const {
	vk::bind_buffer_memory(device(), handle(), forward<Args>(args)...);
}