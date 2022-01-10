#pragma once

#include "../../object/handle/guarded/device_child_base.hpp"
#include "../device/handle.hpp"
#include "handle.hpp"
#include "destroy.hpp"

namespace vk {

	template<>
	struct guarded_handle<vk::semaphore> : vk::guarded_device_child_handle_base<vk::semaphore> {
		using base_type = vk::guarded_device_child_handle_base<vk::semaphore>;

		using base_type::base_type;
		guarded_handle& operator = (guarded_handle&&) = default;
	};
} // vk