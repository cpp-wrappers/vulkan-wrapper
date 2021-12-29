#pragma once

#include "handle.hpp"
#include "destroy.hpp"
#include "../../shared/guarded_device_child_handle.hpp"

namespace vk {

	template<>
	struct vk::guarded_handle<vk::shader_module> : vk::guarded_device_child_handle_base<vk::shader_module> {
		using base_type = vk::guarded_device_child_handle_base<vk::shader_module>;

		using base_type::base_type;
	};
}