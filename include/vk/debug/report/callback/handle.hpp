#pragma once

#include "../../../handle/base.hpp"

namespace vk {

	struct debug_report_callback;
	
	template<>
	struct vk::handle<vk::debug_report_callback> : vk::handle_base<vk::non_dispatchable> {
	};
	
} // vk