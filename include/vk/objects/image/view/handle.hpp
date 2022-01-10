#pragma once

#include "../../../object/handle/base.hpp"

namespace vk {

	struct image_view;

	template<>
	struct vk::handle<vk::image_view> : vk::handle_base<vk::non_dispatchable> {
	};

}