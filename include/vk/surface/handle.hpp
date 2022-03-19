#pragma once

#include "vk/handle/base.hpp"

namespace vk {

	struct surface;

} // vk

template<>
struct handle<vk::surface> : vk::handle_base<vk::non_dispatchable> {};