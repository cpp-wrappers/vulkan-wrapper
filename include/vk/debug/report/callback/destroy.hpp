#pragma once

#include "handle.hpp"

#include "vk/destroy_or_free.hpp"
#include "vk/instance/handle.hpp"

namespace vk {

	template<>
	struct vk::destroy_t<vk::debug_report_callback> {

		template<typename... Args>
		requires types::are_exclusively_satsify_predicates<
		
		>::for_types<Args...>
		void operator () (vk::handle<vk::instance> instance, vk::handle<vk::debug_report_callback> debug_report_callback) const {
			auto fn = (PFN_vkDestroyDebugReportCallbackEXT) vkGetInstanceProcAddr(
				(VkInstance) instance.value,
				"vkDestroyDebugReportCallbackEXT"
			);
			
			fn(
				(VkInstance) instance.value,
				(VkDebugReportCallbackEXT) debug_report_callback.value,
				(VkAllocationCallbacks*) nullptr
			);
		}

	};

} // vk