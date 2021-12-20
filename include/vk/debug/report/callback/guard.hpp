#pragma once

#include "handle.hpp"
#include "../../../instance/handle.hpp"

namespace vk {

	class debug_report_callback_guard {
		vk::debug_report_callback debug_report_callback;
		vk::instance instance;
	public:

		debug_report_callback_guard(vk::debug_report_callback debug_report_callback, vk::instance instance)
			: debug_report_callback{ debug_report_callback }, instance{ instance }
		{}

		debug_report_callback_guard(debug_report_callback_guard&& other)
			: debug_report_callback{ exchange(other.debug_report_callback.handle, 0) }, instance{ other.instance }
		{}

		~debug_report_callback_guard() {
			if(debug_report_callback.handle) {
				auto fn = (PFN_vkDestroyDebugReportCallbackEXT) vkGetInstanceProcAddr(
					(VkInstance) instance.handle,
					"vkDestroyDebugReportCallbackEXT"
				);

				fn(
					(VkInstance) instance.handle,
					(VkDebugReportCallbackEXT) exchange(debug_report_callback.handle, 0),
					(VkAllocationCallbacks*) nullptr
				);
			}
		}
	};
}