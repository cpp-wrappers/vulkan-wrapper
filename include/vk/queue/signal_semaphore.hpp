#pragma once

#include "../semaphore/handle.hpp"

#include <core/wrapper/of.hpp>

namespace vk {

	struct signal_semaphore :
		wrapper::of<handle<vk::semaphore>, struct signal_semaphore_t>
	{};

} // vk