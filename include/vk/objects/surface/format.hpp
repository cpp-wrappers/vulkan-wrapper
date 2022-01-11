#pragma once

#include "../../shared/format.hpp"
#include "../image/color_space.hpp"

namespace vk {

	struct surface_format {
		vk::format format;
		vk::color_space color_space;
	};

} // vk

static_assert(sizeof(vk::surface_format) == sizeof(VkSurfaceFormatKHR));