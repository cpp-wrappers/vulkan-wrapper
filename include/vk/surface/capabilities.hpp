#pragma once

#include "transform.hpp"

#include <core/flag_enum.hpp>

#include "vk/headers.hpp"
#include "vk/extent.hpp"
#include "vk/surface/composite_alpha.hpp"
#include "vk/image/usage.hpp"
#include "vk/surface/min_image_count.hpp"

namespace vk {

	struct surface_capabilities {
		vk::min_image_count min_image_count;
		uint32 max_image_count;
		vk::extent<2> current_extent;
		vk::extent<2> min_image_extent;
		vk::extent<2> max_image_extent;
		uint32 max_image_array_layers;
		flag_enum<vk::surface_transform> supported_transforms;
		vk::surface_transform current_transform;
		flag_enum<vk::composite_alpha> supported_composite_alpha;
		vk::image_usages supported_usages;
	};

} // vk

static_assert(sizeof(vk::surface_capabilities) == sizeof(VkSurfaceCapabilitiesKHR));