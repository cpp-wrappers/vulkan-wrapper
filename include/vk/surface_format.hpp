#pragma once

#include "format.hpp"
#include "color_space.hpp"
#include <vulkan/vulkan_core.h>

namespace vk {

struct surface_format {
	vk::format format;
	vk::color_space color_space;
};

} // vk

static_assert(sizeof(vk::surface_format) == sizeof(VkSurfaceFormatKHR));