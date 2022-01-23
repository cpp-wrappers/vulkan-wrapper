#pragma once

#include "../handle/guarded/device_child_base.hpp"
#include "../device/handle.hpp"
#include "handle.hpp"
#include "destroy.hpp"

namespace vk {

	template<>
	struct guarded_handle<vk::pipeline> : vk::guarded_device_child_handle_base<vk::pipeline> {
		using base_type = vk::guarded_device_child_handle_base<vk::pipeline>;

		using base_type::base_type;
	};

} // vk