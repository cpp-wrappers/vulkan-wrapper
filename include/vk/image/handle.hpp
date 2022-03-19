#pragma once

#include "vk/handle/base.hpp"

namespace vk {

	struct image;

} // vk

template<>
struct handle<vk::image> : vk::handle_base<vk::non_dispatchable> {};