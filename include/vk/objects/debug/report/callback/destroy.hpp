#pragma once

#include "../../../../object/destroy_or_free.hpp"
#include "../../../instance/handle.hpp"
#include "handle.hpp"

namespace vk {

	template<>
	struct vk::destroy_t<vk::debug_report_callback> {

		void operator () (vk::handle<vk::instance> instance, vk::handle<vk::debug_report_callback> debug_report_callback) const {
			auto fn = (PFN_vkDestroyDebugReportCallbackEXT) vkGetInstanceProcAddr(
				(VkInstance) instance.value,
				"vkDestroyDebugReportCallbackEXT"
			);
			
			fn(
				(VkInstance) instance.value,
				(VkDebugReportCallbackEXT) debug_report_callback.value,
				nullptr
			);
		}

	};

}