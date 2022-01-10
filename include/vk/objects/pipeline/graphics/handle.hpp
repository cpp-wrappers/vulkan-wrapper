#pragma once

#include "../handle.hpp"

namespace vk {

	struct graphics_pipeline;

	template<>
	struct vk::handle<vk::graphics_pipeline> : vk::handle<vk::pipeline> {
	};

}