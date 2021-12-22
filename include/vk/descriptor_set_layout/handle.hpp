#pragma once

#include "../shared/handle.hpp"

namespace vk {

	struct descriptor_set_layout;

	template<>
	struct vk::handle<vk::descriptor_set_layout> : vk::handle_base<vk::non_dispatchable> {
	};

} // vk