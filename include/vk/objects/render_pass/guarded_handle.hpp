#pragma once

#include "../../object/handle/guarded/device_child_base.hpp"
#include "../device/handle.hpp"
#include "handle.hpp"
#include "destroy.hpp"

namespace vk {

	template<>
	struct vk::guarded_handle<vk::render_pass> : vk::guarded_device_child_handle_base<vk::render_pass> {
		using base_type = vk::guarded_device_child_handle_base<vk::render_pass>;

		using base_type::base_type;
	};
}