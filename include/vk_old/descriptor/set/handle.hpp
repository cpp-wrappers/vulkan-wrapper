#pragma once

#include "../../handle/base.hpp"

#include <core/handle.hpp>

namespace vk {

	struct descriptor_set;

} // vk

template<>
struct handle<vk::descriptor_set> : vk::handle_base<vk::non_dispatchable> {};