#pragma once

#include "vk/handle/base.hpp"

namespace vk {

	struct semaphore;

	template<>
	struct vk::handle<vk::semaphore> : vk::handle_base<vk::non_dispatchable> {};

} // vk