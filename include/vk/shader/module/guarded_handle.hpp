#pragma once

#include "handle.hpp"
#include "destroy.hpp"

#include "vk/handle/guarded/device_child_base.hpp"

template<>
struct guarded_handle<vk::shader_module> : vk::guarded_device_child_handle_base<vk::shader_module> {
	using base_type = vk::guarded_device_child_handle_base<vk::shader_module>;
	using base_type::base_type;
};