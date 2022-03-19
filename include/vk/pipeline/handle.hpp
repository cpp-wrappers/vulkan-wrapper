#pragma once

#include "vk/handle/base.hpp"

namespace vk {

	struct pipeline;

} // vk

template<>
struct handle<vk::pipeline> : vk::handle_base<vk::non_dispatchable> {};