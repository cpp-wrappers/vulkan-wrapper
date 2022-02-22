#pragma once

#include "vk/handle/base.hpp"

namespace vk {

	struct framebuffer;

	template<>
	struct vk::handle<vk::framebuffer> : vk::handle_base<vk::non_dispatchable> {};

} // vk