#pragma once

#include <core/flag_enum.hpp>
#include "../../shared/headers.hpp"

namespace vk {
	enum class debug_report_flag {
		information = VK_DEBUG_REPORT_INFORMATION_BIT_EXT,
		warning = VK_DEBUG_REPORT_WARNING_BIT_EXT,
		performance_warning = VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT,
		error = VK_DEBUG_REPORT_ERROR_BIT_EXT,
		debug = VK_DEBUG_REPORT_DEBUG_BIT_EXT,
	};

	using debug_report = debug_report_flag;

	using debug_report_flags = flag_enum<vk::debug_report_flag>;
}