#pragma once

#include "aspect.hpp"

namespace vk {

	struct image_subresource_layers {
		vk::image_aspects aspects;
		uint32 mip_level;
		uint32 base_array_layer;
		uint32 layer_count;
	};

} // vk

#include "../headers.hpp"

static_assert(sizeof(vk::image_subresource_layers) == sizeof(VkImageSubresourceLayers));