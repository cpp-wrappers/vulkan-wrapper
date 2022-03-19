#pragma once

#include "handle.hpp"
#include "destroy.hpp"

#include "vk/handle/guarded/device_child_base.hpp"
#include "vk/device/handle.hpp"

template<>
struct guarded_handle<vk::pipeline> : vk::guarded_device_child_handle_base<vk::pipeline> {
	using base_type = vk::guarded_device_child_handle_base<vk::pipeline>;

	using base_type::base_type;
};