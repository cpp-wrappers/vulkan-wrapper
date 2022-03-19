#pragma once

#include "vk/handle/base.hpp"

namespace vk {

	struct descriptor_set;

} // vk

template<>
struct handle<vk::descriptor_set> : vk::handle_base<vk::non_dispatchable> {};