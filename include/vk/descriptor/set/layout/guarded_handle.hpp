#pragma once

#include "destroy.hpp"

#include "vk/handle/guarded/device_child_base.hpp"

template<>
struct guarded_handle<vk::descriptor_set_layout> : vk::guarded_device_child_handle_base<vk::descriptor_set_layout> {
	using base_type = vk::guarded_device_child_handle_base<vk::descriptor_set_layout>;

	using base_type::base_type;
};