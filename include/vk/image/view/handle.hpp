#pragma once

#include "vk/handle/base.hpp"

namespace vk {

	struct image_view;

} // vk

template<>
struct handle<vk::image_view> : vk::handle_base<vk::non_dispatchable> {};