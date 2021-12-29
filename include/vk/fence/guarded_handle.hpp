#pragma once

#include "../shared/guarded_device_child_handle.hpp"
#include "destroy.hpp"
#include "handle.hpp"

namespace vk {

	template<>
	struct vk::guarded_handle<vk::fence> : vk::guarded_device_child_handle_base<vk::fence> {
		using base_type = vk::guarded_device_child_handle_base<vk::fence>;

		using base_type::base_type;

		guarded_handle& operator = (guarded_handle&& other) = default;
	};

}