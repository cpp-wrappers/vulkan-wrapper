#pragma once

#include "handle.hpp"
#include "destroy.hpp"
#include "../../../shared/guarded_instance_child_handle.hpp"

namespace vk {

	template<>
	struct vk::guarded_handle<vk::debug_report_callback> : vk::guarded_instance_child_handle_base<vk::debug_report_callback> {
		using base_type = vk::guarded_instance_child_handle_base<vk::debug_report_callback>;

		using base_type::base_type;
	};
}