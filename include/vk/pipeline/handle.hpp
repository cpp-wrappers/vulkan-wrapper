#pragma once

#include "../shared/handle.hpp"

namespace vk {

	struct pipeline;

	template<>
	struct vk::handle<vk::pipeline> : vk::handle_base<vk::non_dispatchable> {
	};
}