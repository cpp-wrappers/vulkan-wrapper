#pragma once

#include "../../object/handle/base.hpp"

namespace vk {

	struct image;

	template<>
	struct vk::handle<vk::image> : vk::handle_base<vk::non_dispatchable> {
	};
}