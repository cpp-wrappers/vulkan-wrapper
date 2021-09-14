#pragma once

#include <core/flag_enum.hpp>

#include "headers.hpp"
#include "extent.hpp"
#include "surface_transform.hpp"
#include "composite_alpha.hpp"
#include "image/usage.hpp"

namespace vk {

struct surface_capabilities {
	uint32_t min_image_count;
	uint32_t max_image_count;
	vk::extent<2> current_extent;
	vk::extent<2> min_image_extent;
	vk::extent<2> max_image_extent;
	uint32_t max_image_array_layers;
	flag_enum<vk::surface_transform> supported_transforms;
	vk::surface_transform current_transform;
	flag_enum<vk::composite_alpha> supported_composite_alpha;
	flag_enum<vk::image_usage> supported_usage_flags;
};

} // vk

static_assert(sizeof(vk::surface_capabilities) == sizeof(VkSurfaceCapabilitiesKHR));