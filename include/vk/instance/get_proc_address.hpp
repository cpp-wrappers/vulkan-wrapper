#pragma once

#include "handle.hpp"
#include "../function.hpp"

extern "C" VK_ATTR PFN_vkVoidFunction VK_CALL
vkGetInstanceProcAddr(
	handle<vk::instance> instance,
	const char* name
);

namespace vk {

	PFN_vkVoidFunction
	get_instance_proc_address(handle<vk::instance> instance, const char* name) {
		return vkGetInstanceProcAddr(
			instance,
			name
		);
	}

}