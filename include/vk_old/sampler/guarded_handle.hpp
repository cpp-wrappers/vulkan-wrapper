#pragma once

#include "handle.hpp"
#include "destroy.hpp"

#include "../handle/guarded/device_child_base.hpp"

template<>
struct guarded_handle<vk::sampler> : vk::guarded_device_child_handle_base<vk::sampler> {
	using base_type = vk::guarded_device_child_handle_base<vk::sampler>;
	using base_type::base_type;
};