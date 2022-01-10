#pragma once

#include "../guarded_handle.hpp"
#include "destroy.hpp"

namespace vk {

	template<>
	struct guarded_handle<vk::graphics_pipeline> : vk::guarded_device_child_handle_base<vk::graphics_pipeline> {
		using base_type = vk::guarded_device_child_handle_base<vk::graphics_pipeline>;

		using base_type::base_type;
	};

}