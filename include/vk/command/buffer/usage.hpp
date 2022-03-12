#pragma once

#include <core/flag_enum.hpp>

namespace vk {

	enum class command_buffer_usage {
		one_time_submit      = 1 << 0,
		render_pass_continue = 1 << 1,
		simultaneius_use     = 1 << 2
	};

	using command_buffer_usages = flag_enum<vk::command_buffer_usage>;

} // vk