#pragma once

#include "headers.hpp"

namespace vk {

	struct viewport {
		float x = 0;
		float y = 0;
		float width;
		float height;
		float min_depth = 0;
		float max_depth = 1;
	};
}

static_assert(sizeof(vk::viewport) == sizeof(VkViewport));