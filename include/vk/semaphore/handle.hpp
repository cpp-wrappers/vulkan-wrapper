#pragma once

#include "../shared/handle.hpp"

namespace vk {

	struct semaphore;

	template<>
	struct vk::handle<vk::semaphore> : vk::handle_base<vk::non_dispatchable> {
	}; // semaphore
} // vk