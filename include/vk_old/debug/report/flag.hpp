#pragma once

#include <core/flag_enum.hpp>

namespace vk {

	enum class debug_report_flag {
		information         = 0x00000001,
		warning             = 0x00000002,
		performance_warning = 0x00000004,
		error               = 0x00000008,
		debug               = 0x00000010,
	};

	using debug_report = debug_report_flag;
	using debug_report_flags = flag_enum<vk::debug_report_flag>;

} // vk