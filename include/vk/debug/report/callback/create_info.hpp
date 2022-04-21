#pragma once

#include "../flag.hpp"
#include "../object_type.hpp"

#include <core/flag_enum.hpp>
#include <core/c_string.hpp>

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
		uint32 structure_type = 1000011000;
		const void* next;
		flag_enum<vk::debug_report_flag> flags;
		debug_report_callback_type callback;
		void* user_data;
	};

} // vk