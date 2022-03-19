#pragma once

#include "vk/handle/base.hpp"

namespace vk {

	struct semaphore;

} // vk

template<>
struct handle<vk::semaphore> : vk::handle_base<vk::non_dispatchable> {};