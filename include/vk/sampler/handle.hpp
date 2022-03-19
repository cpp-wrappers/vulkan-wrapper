#pragma once

#include "vk/handle/base.hpp"

namespace vk {

	struct sampler;

} // vk

template<>
struct handle<vk::sampler> : vk::handle_base<vk::non_dispatchable> {};