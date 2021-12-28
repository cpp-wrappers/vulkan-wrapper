#pragma once

#include "../../shared/handle.hpp"

namespace vk {

	struct device_memory;

	template<>
	struct vk::handle<vk::device_memory> : vk::handle_base<vk::non_dispatchable> {
	};

	
}