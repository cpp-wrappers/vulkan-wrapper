#pragma once

#include "../device/handle.hpp"
#include "../shared/guarded_device_child_handle.hpp"
#include "handle.hpp"
#include "destroy.hpp"

namespace vk {

	template<>
	struct vk::guarded_handle<vk::render_pass> : vk::guarded_device_child_handle_base<vk::render_pass> {
		using base_type = vk::guarded_device_child_handle_base<vk::render_pass>;

		using base_type::base_type;
	};
}