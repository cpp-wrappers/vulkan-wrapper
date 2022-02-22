#pragma once

#include "vk/handle/base.hpp"

namespace vk {

	struct acceleration_structure;

	template<>
	struct vk::handle<vk::acceleration_structure> : vk::handle_base<vk::dispatchable> {
	};

}