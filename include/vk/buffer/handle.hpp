#pragma once

#include "vk/handle/base.hpp"

namespace vk {

	struct buffer;

} // vk

template<>
struct handle<vk::buffer> : vk::handle_base<vk::non_dispatchable> {};