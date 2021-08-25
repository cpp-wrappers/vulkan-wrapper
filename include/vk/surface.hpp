#pragma once

#include "headers.hpp"

namespace vk {

enum class surface_transform_flag {
	identity = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR,
	rotate_90 = VK_SURFACE_TRANSFORM_ROTATE_90_BIT_KHR,
	rotate_180 = VK_SURFACE_TRANSFORM_ROTATE_180_BIT_KHR,
	rotate_270 = VK_SURFACE_TRANSFORM_ROTATE_270_BIT_KHR,
	horizontal_mirror = VK_SURFACE_TRANSFORM_HORIZONTAL_MIRROR_BIT_KHR,
	horizontal_mirror_rotate_90 = VK_SURFACE_TRANSFORM_HORIZONTAL_MIRROR_ROTATE_90_BIT_KHR,
	horizontal_mirror_rotate_180 = VK_SURFACE_TRANSFORM_HORIZONTAL_MIRROR_ROTATE_180_BIT_KHR,
	horizontal_mirror_rotate_270 = VK_SURFACE_TRANSFORM_HORIZONTAL_MIRROR_ROTATE_270_BIT_KHR,
	inherit = VK_SURFACE_TRANSFORM_INHERIT_BIT_KHR,
};

enum class composite_alpha_flag {
	opaque = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR,
	pre_multiplied = VK_COMPOSITE_ALPHA_PRE_MULTIPLIED_BIT_KHR,
	post_multiplied = VK_COMPOSITE_ALPHA_POST_MULTIPLIED_BIT_KHR,
	inherit = VK_COMPOSITE_ALPHA_INHERIT_BIT_KHR,
};

struct surface {
	VkSurfaceKHR m_surface;
}; // surface

} // vk