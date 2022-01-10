#pragma once

#include <core/flag_enum.hpp>

#include "../../shared/headers.hpp"

namespace vk {

	enum class image_aspect {
		color = VK_IMAGE_ASPECT_COLOR_BIT,
		depth = VK_IMAGE_ASPECT_DEPTH_BIT,
		stencil = VK_IMAGE_ASPECT_STENCIL_BIT,
		metadata = VK_IMAGE_ASPECT_METADATA_BIT,
		plane_0 = VK_IMAGE_ASPECT_PLANE_0_BIT,
		plane_1 = VK_IMAGE_ASPECT_PLANE_1_BIT,
		plane_2 = VK_IMAGE_ASPECT_PLANE_2_BIT,
		memory_plane_0 = VK_IMAGE_ASPECT_MEMORY_PLANE_0_BIT_EXT,
		memory_plane_1 = VK_IMAGE_ASPECT_MEMORY_PLANE_1_BIT_EXT,
		memory_plane_2 = VK_IMAGE_ASPECT_MEMORY_PLANE_2_BIT_EXT,
		memory_plane_3 = VK_IMAGE_ASPECT_MEMORY_PLANE_3_BIT_EXT,
	};

	using image_aspects = flag_enum<vk::image_aspect>;

}