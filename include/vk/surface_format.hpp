#pragma once

#include "image/format.hpp"
#include "color_space.hpp"

namespace vk {

struct surface_format {
	vk::format format;
	vk::color_space color_space;
};

} // vk

static_assert(sizeof(vk::surface_format) == sizeof(VkSurfaceFormatKHR));