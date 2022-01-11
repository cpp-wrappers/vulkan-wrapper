#pragma once

#include "../../../object/handle/guarded/device_child_base.hpp"
#include "handle.hpp"

namespace vk {

	template<>
	struct vk::guarded_handle<vk::buffer_view> : vk::guarded_device_child_handle_base<vk::buffer_view> {
		using base_type = vk::guarded_device_child_handle_base<vk::buffer_view>;

		using base_type::base_type;
	};
}