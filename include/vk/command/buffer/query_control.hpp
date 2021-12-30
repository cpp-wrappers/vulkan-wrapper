#pragma once

#include <core/flag_enum.hpp>

namespace vk {
	enum class query_control_flag {
		precise = 1<<0
	};

	using query_control_flags = flag_enum<vk::query_control_flag>;
}