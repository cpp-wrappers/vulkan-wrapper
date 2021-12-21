#pragma once

#include "handle.hpp"
#include "../../../instance/handle.hpp"
#include "../../../shared/guarded.hpp"

namespace vk {

	template<>
	class guarded<debug_report_callback> {
		vk::debug_report_callback debug_report_callback;
		vk::instance instance;
	public:

		guarded(vk::debug_report_callback debug_report_callback, vk::instance instance)
			: debug_report_callback{ debug_report_callback }, instance{ instance }
		{}

		guarded(guarded&& other)
			: debug_report_callback{ exchange(other.debug_report_callback.handle, 0) }, instance{ other.instance }
		{}

		~guarded() {
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