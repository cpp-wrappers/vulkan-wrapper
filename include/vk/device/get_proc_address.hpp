#pragma once

#include "handle.hpp"
#include "../function.hpp"

extern "C" VK_ATTR PFN_vkVoidFunction VK_CALL
vkGetDeviceProcAddr(
	handle<vk::device> device,
	const char* name
);

namespace vk {

	PFN_vkVoidFunction
	get_device_proc_address(handle<vk::device> device, const char* name) {
		return vkGetDeviceProcAddr(
			device,
			name
		);
	}

}