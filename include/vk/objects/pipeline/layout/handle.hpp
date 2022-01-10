#pragma once

#include "../../../object/handle/base.hpp"

namespace vk {

	struct pipeline_layout;

	template<>
	struct vk::handle<vk::pipeline_layout> : vk::handle_base<vk::non_dispatchable> {
	};

}