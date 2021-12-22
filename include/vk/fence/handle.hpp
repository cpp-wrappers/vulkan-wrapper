#pragma once

#include "../shared/handle.hpp"

namespace vk {

	struct fence;

	template<>
	struct vk::handle<vk::fence> : vk::handle_base<vk::non_dispatchable> {
	};
}