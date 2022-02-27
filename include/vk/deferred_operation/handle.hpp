#pragma once

#include "vk/handle/base.hpp"

namespace vk {

	struct deferred_operation;

	template<>
	struct vk::handle<vk::deferred_operation> : vk::handle_base<vk::non_dispatchable> {
	};

}