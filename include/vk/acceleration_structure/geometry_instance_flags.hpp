#pragma once

#include <core/flag_enum.hpp>

#include "vk/headers.hpp"

namespace vk {

	enum geometry_instance_flag {
		triangle_facing_cull_disable = VK_GEOMETRY_INSTANCE_TRIANGLE_FACING_CULL_DISABLE_BIT_KHR,
		triangle_flip_facing = VK_GEOMETRY_INSTANCE_TRIANGLE_FLIP_FACING_BIT_KHR,
		force_opaque = VK_GEOMETRY_INSTANCE_FORCE_OPAQUE_BIT_KHR,
		force_no_opaque = VK_GEOMETRY_INSTANCE_FORCE_NO_OPAQUE_BIT_KHR
	};

	using geometry_instance_flags = flag_enum<geometry_instance_flag>;

} // vk