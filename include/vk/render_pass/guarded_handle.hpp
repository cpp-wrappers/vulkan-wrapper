#pragma once

#include "handle.hpp"
#include "destroy.hpp"

#include "vk/handle/guarded/device_child_base.hpp"
#include "vk/device/handle.hpp"

namespace vk {

	template<>
	struct vk::guarded_handle<vk::render_pass> : vk::guarded_device_child_handle_base<vk::render_pass> {
		using base_type = vk::guarded_device_child_handle_base<vk::render_pass>;

		using base_type::base_type;
	};

} // vk