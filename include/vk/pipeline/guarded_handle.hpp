#pragma once

#include "handle.hpp"
#include "destroy.hpp"
#include "../device/handle.hpp"
#include "../shared/guarded_device_child_handle.hpp"

namespace vk {

	template<>
	struct guarded_handle<vk::pipeline> : vk::guarded_device_child_handle_base<vk::pipeline> {
		using base_type = vk::guarded_device_child_handle_base<vk::pipeline>;

		using base_type::base_type;
	};
}