#pragma once

#include "vk/handle/base.hpp"

namespace vk {

	struct sampler;

	template<>
	struct vk::handle<vk::sampler> : vk::handle_base<vk::non_dispatchable> {};

} // vk