#pragma once

#include "handle.hpp"
#include "destroy.hpp"
#include "../../shared/guarded_device_child_handle.hpp"

namespace vk {

	template<>
	struct guarded_handle<vk::image_view> : vk::guarded_device_child_handle_base<vk::image_view> {
		using base_type = vk::guarded_device_child_handle_base<vk::image_view>;

		using base_type::base_type;
		guarded_handle& operator = (guarded_handle&&) = default;
	};
}