#pragma once

#include "vk/handle/base.hpp"

namespace vk {

	struct descriptor_set_layout;

} // vk

template<>
struct handle<vk::descriptor_set_layout> : vk::handle_base<vk::non_dispatchable> {};