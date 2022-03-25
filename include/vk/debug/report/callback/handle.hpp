#pragma once

#include "vk/handle/base.hpp"

namespace vk {

	struct debug_report_callback;

} // vk

template<>
struct handle<vk::debug_report_callback> :
	vk::handle_base<vk::non_dispatchable>
{};