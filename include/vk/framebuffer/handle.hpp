#pragma once

#include "vk/handle/base.hpp"

namespace vk {

	struct framebuffer;

} // vk

template<>
struct handle<vk::framebuffer> : vk::handle_base<vk::non_dispatchable> {};