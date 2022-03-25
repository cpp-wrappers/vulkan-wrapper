#pragma once

#include "handle.hpp"

#include "vk/handle/guarded/device_child_base.hpp"

template<>
struct guarded_handle<vk::buffer_view> :
	vk::guarded_device_child_handle_base<vk::buffer_view>
{
	using base_type = vk::guarded_device_child_handle_base<vk::buffer_view>;
	using base_type::base_type;
};