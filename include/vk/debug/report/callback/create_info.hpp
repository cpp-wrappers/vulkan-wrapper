#pragma once

#include <core/flag_enum.hpp>
#include <core/c_string.hpp>

#include "vk/headers.hpp"

#include "vk/debug/report/flag.hpp"
#include "vk/debug/report/object_type.hpp"

namespace vk {

	typedef uint32 (*PFN_vk_debugReport_callback)(
		flag_enum<vk::debug_report_flag> flags,
		vk::debug_report_object_type objectType,
		uint64 object,
		nuint location,
		int32 message_code,
		c_string layer_prefix,
		c_string message,
		void* user_data
	);

	using debug_report_callback_type = uint32 (*)(
		flag_enum<vk::debug_report_flag> flags,
		vk::debug_report_object_type objectType,
		uint64 object,
		nuint location,
		int32 message_code,
		c_string layer_prefix,
		c_string message,
		void* user_data
	);

	struct debug_report_callback_create_info {
		const uint32 type = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT;
		const void* const next;
		flag_enum<vk::debug_report_flag> flags;
		debug_report_callback_type callback;
		void* user_data;
	};

} // vk

static_assert(sizeof(vk::debug_report_callback_create_info) == sizeof(VkDebugReportCallbackCreateInfoEXT) );