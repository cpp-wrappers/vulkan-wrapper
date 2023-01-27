#pragma once

#include "./handle.hpp"
#include "../__internal/function.hpp"
#include "../__instance/handle.hpp"

namespace vk {

	struct destroy_debug_report_callback_function : vk::function<void(*)(
		handle<vk::instance>::underlying_type instance,
		handle<vk::debug_report_callback>::underlying_type callback,
		const void* allocator
	)> {
		static constexpr auto name = "vkDestroyDebugReportCallbackEXT";
	};

	inline void destroy_debug_report_callback(
		handle<vk::instance> instance,
		handle<vk::debug_report_callback> debug_report_callback
	) {
		vk::get_instance_function<vk::destroy_debug_report_callback_function>(
			instance
		)(
			instance.underlying(),
			debug_report_callback.underlying(),
			nullptr
		);
	}

} // vk