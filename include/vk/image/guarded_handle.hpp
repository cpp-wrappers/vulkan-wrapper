#pragma once

#include "../shared/guarded_device_child_handle.hpp"
#include "destroy.hpp"

namespace vk {

	template<>
	struct vk::guarded_handle<vk::image> : vk::guarded_device_child_handle_base<vk::image> {
		using base_type = vk::guarded_device_child_handle_base<vk::image>;

		using base_type::base_type;

	};

}