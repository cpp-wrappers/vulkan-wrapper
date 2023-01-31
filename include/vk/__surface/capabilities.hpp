#pragma once

#include "./transform.hpp"
#include "./composite_alpha.hpp"
#include "./min_max_image_count.hpp"
#include "../__internal/extent.hpp"
#include "../__image/usage.hpp"
 
#include <enum_flags.hpp>

namespace vk {

	struct surface_capabilities {
		vk::min_image_count min_image_count;
		vk::max_image_count max_image_count;
		vk::extent<2> current_extent;
		vk::extent<2> min_image_extent;
		vk::extent<2> max_image_extent;
		uint32 max_image_array_layers;
		enum_flags<vk::surface_transform> supported_transforms;
		vk::surface_transform current_transform;
		enum_flags<vk::composite_alpha> supported_composite_alpha;
		vk::image_usages supported_usages;
	};

} // vk