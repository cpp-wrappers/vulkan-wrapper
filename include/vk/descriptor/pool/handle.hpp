#pragma once

#include "vk/handle/base.hpp"

namespace vk {

	struct descriptor_pool;

} // vk

template<>
struct handle<vk::descriptor_pool> : vk::handle_base<vk::non_dispatchable> {};