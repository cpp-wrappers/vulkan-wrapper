#pragma once

#include "vk/handle/base.hpp"

namespace vk {

	struct pipeline;

	template<>
	struct vk::handle<vk::pipeline> : vk::handle_base<vk::non_dispatchable> {};

} // vk