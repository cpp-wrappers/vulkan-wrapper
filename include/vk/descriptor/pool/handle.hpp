#pragma once

#include "../../handle/base.hpp"

namespace vk {

	struct descriptor_pool;

	template<>
	struct vk::handle<vk::descriptor_pool> : vk::handle_base<vk::non_dispatchable> {
		
	};

} // vk