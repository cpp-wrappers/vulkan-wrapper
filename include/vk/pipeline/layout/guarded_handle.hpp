#pragma once

#include "handle.hpp"
#include "destroy.hpp"

#include "../../device/handle.hpp"
#include "../../handle/guarded/device_child_base.hpp"

template<>
struct guarded_handle<vk::pipeline_layout> :
	vk::guarded_device_child_handle_base<vk::pipeline_layout>
{
	using base_type = vk::guarded_device_child_handle_base<vk::pipeline_layout>;
	using base_type::base_type;
};