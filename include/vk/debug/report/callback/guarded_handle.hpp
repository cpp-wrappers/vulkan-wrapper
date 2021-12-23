#pragma once

#include "handle.hpp"
#include "../../../instance/handle.hpp"
#include "../../../shared/guarded_instance_child_handle.hpp"

namespace vk {

	template<>
	struct vk::guarded_handle<vk::debug_report_callback> : vk::guarded_instance_child_handle_base<vk::debug_report_callback> {
		using base_type = vk::guarded_instance_child_handle_base<vk::debug_report_callback>;

		using base_type::base_type;

		~guarded_handle() {
			if(handle().value) {
				auto fn = (PFN_vkDestroyDebugReportCallbackEXT) vkGetInstanceProcAddr(
					(VkInstance) instance().value,
					"vkDestroyDebugReportCallbackEXT"
				);

				fn(
					(VkInstance) instance().value,
					(VkDebugReportCallbackEXT) exchange(handle().value, 0),
					(VkAllocationCallbacks*) nullptr
				);
			}
		}
	};
}