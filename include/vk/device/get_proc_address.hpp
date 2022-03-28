#pragma once

#include "handle.hpp"
#include "../function.hpp"

extern "C" VK_ATTR PFN_vkVoidFunction VK_CALL
vkGetDeviceProcAddr(
	handle<vk::device> device,
	const char* name
);

namespace vk {

	template<possibly_guarded_handle_of<vk::device> Device>
	PFN_vkVoidFunction
	get_device_proc_address(Device&& device, const char* name) {
		return vkGetDeviceProcAddr(
			vk::get_handle(device),
			name
		);
	}

}