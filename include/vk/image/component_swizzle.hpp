#pragma once

#include "vk/headers.hpp"

namespace vk {

	enum class component_swizzle {
		identity = VK_COMPONENT_SWIZZLE_IDENTITY,
		zero = VK_COMPONENT_SWIZZLE_ZERO,
		one = VK_COMPONENT_SWIZZLE_ONE,
		r = VK_COMPONENT_SWIZZLE_R,
		g = VK_COMPONENT_SWIZZLE_G,
		b = VK_COMPONENT_SWIZZLE_B,
		a = VK_COMPONENT_SWIZZLE_A
	};

} // vk