#pragma once

#include "handle.hpp"

#include "../../../handle/get_value.hpp"
#include "../../../destroy_or_free.hpp"
#include "../../../instance/handle.hpp"

namespace vk {

	template<>
	struct vk::destroy_t<vk::debug_report_callback> {

		void operator () (
			handle<vk::instance> instance,
			handle<vk::debug_report_callback> debug_report_callback
		) const {
			auto fn = (PFN_vkDestroyDebugReportCallbackEXT)
				vkGetInstanceProcAddr(
					(VkInstance) vk::get_handle_value(instance),
					"vkDestroyDebugReportCallbackEXT"
				);
			
			fn(
				(VkInstance) vk::get_handle_value(instance),
				(VkDebugReportCallbackEXT)
					vk::get_handle_value(debug_report_callback),
				(VkAllocationCallbacks*) nullptr
			);
		}

	};

} // vk