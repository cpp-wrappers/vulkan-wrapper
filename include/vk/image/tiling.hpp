#pragma once

#include "vk/headers.hpp"

namespace vk {

	enum class image_tiling {
		optimal = VK_IMAGE_TILING_OPTIMAL,
		linear = VK_IMAGE_TILING_LINEAR
	};

} // vk