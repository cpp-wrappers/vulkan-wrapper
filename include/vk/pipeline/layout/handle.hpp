#pragma once

#include "../../handle/base.hpp"

namespace vk {

	struct pipeline_layout;

} // vk

template<>
struct handle<vk::pipeline_layout> :
	vk::handle_base<vk::non_dispatchable>
{};