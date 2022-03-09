#pragma once

#include <core/flag_enum.hpp>

#include "vk/headers.hpp"

namespace vk {

	enum class geometry_flag {
		opaque = VK_GEOMETRY_OPAQUE_BIT_KHR,
		no_duplicate_any_hit_invocation = VK_GEOMETRY_NO_DUPLICATE_ANY_HIT_INVOCATION_BIT_KHR
	};

	using geometry_flags = flag_enum<vk::geometry_flag>;

} // vk