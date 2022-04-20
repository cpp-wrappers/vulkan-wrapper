#pragma once

#include "../semaphore/handle.hpp"

namespace vk {

	struct wait_semaphore : handle<vk::semaphore> {};

} // vk