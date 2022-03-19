#pragma once

#include "vk/handle/base.hpp"

namespace vk {

	struct buffer_view;

} // vk

template<>
struct handle<vk::buffer_view> : vk::handle_base<vk::non_dispatchable> {};