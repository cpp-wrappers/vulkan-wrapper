#pragma once

#include "../__semaphore/handle.hpp"

namespace vk {

	struct signal_semaphore : handle<vk::semaphore> {};

} // vk