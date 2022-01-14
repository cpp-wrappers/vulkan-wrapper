#pragma once

#include "../../object/handle/base.hpp"

namespace vk {

	struct render_pass;

	template<>
	struct vk::handle<vk::render_pass> : vk::handle_base<vk::non_dispatchable> {};

} // vk