#pragma once

#include "vk/handle/base.hpp"

namespace vk {

	struct surface;

	template<>
	struct vk::handle<vk::surface> : vk::handle_base<vk::non_dispatchable> {};

} // vk