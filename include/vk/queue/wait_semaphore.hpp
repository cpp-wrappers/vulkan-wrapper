#pragma once

#include "../semaphore/handle.hpp"

#include <core/wrapper/of.hpp>

namespace vk {

	struct wait_semaphore :
		wrapper::of<handle<vk::semaphore>, struct wait_semaphore_t>
	{};

} // vk