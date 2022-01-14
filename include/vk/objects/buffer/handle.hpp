#pragma once

#include "../../object/handle/base.hpp"

namespace vk {

	struct buffer;

	template<>
	struct vk::handle<vk::buffer> : vk::handle_base<vk::non_dispatchable> {
	};

} // vk