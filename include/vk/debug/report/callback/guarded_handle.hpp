#pragma once

#include "handle.hpp"
#include "destroy.hpp"

#include "vk/handle/guarded/instance_child_base.hpp"


template<>
struct guarded_handle<vk::debug_report_callback> : vk::guarded_instance_child_handle_base<vk::debug_report_callback> {
	using base_type = vk::guarded_instance_child_handle_base<vk::debug_report_callback>;

	using base_type::base_type;
};