#pragma once

#include <enum_flags.hpp>

namespace vk {

	enum class geometry_flag {
		opaque                          = 0x00000001,
		no_duplicate_any_hit_invocation = 0x00000002
	};

	using geometry_flags = enum_flags<vk::geometry_flag>;

} // vk