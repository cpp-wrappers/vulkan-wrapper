#pragma once

#include "vk/handle/base.hpp"

namespace vk {

	struct deferred_operation;

} // vk

template<>
struct handle<vk::deferred_operation> : vk::handle_base<vk::non_dispatchable> {};