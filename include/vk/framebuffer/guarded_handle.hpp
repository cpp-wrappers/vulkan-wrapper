#pragma once

#include "handle.hpp"
#include "destroy.hpp"

#include "vk/handle/guarded/device_child_base.hpp"

namespace vk {
	
	template<>
	struct guarded_handle<vk::framebuffer> : vk::guarded_device_child_handle_base<vk::framebuffer> {
		using base_type = vk::guarded_device_child_handle_base<vk::framebuffer>;

		using base_type::base_type;

		guarded_handle& operator = (guarded_handle&& other) = default;
	};

} // vk