#pragma once

#include <enum_flags.hpp>

namespace vk {

	enum class query_control_flag {
		precise = 1 << 0
	};

	using query_control_flags = enum_flags<vk::query_control_flag>;

} // vk