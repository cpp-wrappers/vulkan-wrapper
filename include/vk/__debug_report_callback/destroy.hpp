#pragma once

#include "handle.hpp"

#include "../../../handle/get_value.hpp"
#include "../../../destroy_or_free.hpp"
#include "../../../instance/handle.hpp"
#include "../../../instance/get_proc_address.hpp"

typedef void (VK_PTR* PFN_vkDestroyDebugReportCallbackEXT)(
	handle<vk::instance> instance,
	handle<vk::debug_report_callback> callback,
	const void* allocator
);

namespace vk {

	template<>
	struct vk::destroy_t<vk::debug_report_callback> {

		void operator () (
			handle<vk::instance> instance,
			handle<vk::debug_report_callback> debug_report_callback
		) const {
			auto fn = (PFN_vkDestroyDebugReportCallbackEXT)
				vk::get_instance_proc_address(
					instance,
					"vkDestroyDebugReportCallbackEXT"
				);
			
			fn(
				vk::get_handle(instance),
				vk::get_handle(debug_report_callback),
				nullptr
			);
		}

	};

} // vk