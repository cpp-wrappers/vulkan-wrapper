#pragma once

#include "vk/handle/base.hpp"

namespace vk {

	struct acceleration_structure;

} // vk

template<>
struct handle<vk::acceleration_structure> : vk::handle_base<vk::non_dispatchable> {};