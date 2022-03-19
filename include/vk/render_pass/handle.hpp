#pragma once

#include "vk/handle/base.hpp"

namespace vk {

	struct render_pass;

} // vk

template<>
struct handle<vk::render_pass> : vk::handle_base<vk::non_dispatchable> {};