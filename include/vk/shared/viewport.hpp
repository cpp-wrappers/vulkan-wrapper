#pragma once

#include "headers.hpp"

namespace vk {

	struct viewport {
		float x = 0, y = 0, width, height, min_depth = 0, max_depth = 1;
	};
}

static_assert(sizeof(vk::viewport) == sizeof(VkViewport));