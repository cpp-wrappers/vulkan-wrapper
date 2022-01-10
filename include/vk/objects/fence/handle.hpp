#pragma once

#include "../../object/handle/base.hpp"

namespace vk {

	struct fence;

	template<>
	struct vk::handle<vk::fence> : vk::handle_base<vk::non_dispatchable> {
	};
}