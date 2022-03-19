#pragma once

#include "vk/handle/base.hpp"

namespace vk {

	struct fence;

} // vk

template<>
struct handle<vk::fence> : vk::handle_base<vk::non_dispatchable> {};