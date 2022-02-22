#pragma once

#include "vk/handle/base.hpp"

namespace vk {

	struct buffer_view;

	template<>
	struct vk::handle<vk::buffer_view> : vk::handle_base<vk::non_dispatchable> {

	};

} // vk