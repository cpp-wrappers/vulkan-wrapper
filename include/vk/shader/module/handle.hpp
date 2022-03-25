#pragma once

#include "../../handle/base.hpp"

namespace vk {

	struct shader_module;

} // vk

template<>
struct handle<vk::shader_module> : vk::handle_base<vk::non_dispatchable> {};