#pragma once

#include <core/flag_enum.hpp>

namespace vk {

	enum geometry_instance_flag {
		triangle_facing_cull_disable = 0x00000001,
		triangle_flip_facing         = 0x00000002,
		force_opaque                 = 0x00000004,
		force_no_opaque              = 0x00000008
	};

	using geometry_instance_flags = flag_enum<geometry_instance_flag>;

} // vk