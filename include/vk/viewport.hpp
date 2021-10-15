#pragma once

#include "headers.hpp"

namespace vk {

	struct viewport {
		float x, y, width, height, min_depth, max_depth;
	};
}

static_assert(sizeof(vk::viewport) == sizeof(VkViewport));