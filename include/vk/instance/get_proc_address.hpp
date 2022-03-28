#pragma once

#include "handle.hpp"
#include "../function.hpp"

extern "C" VK_ATTR PFN_vkVoidFunction VK_CALL
vkGetInstanceProcAddr(
	handle<vk::instance> instance,
	const char* name
);

namespace vk {

	template<possibly_guarded_handle_of<vk::instance> Instance>
	PFN_vkVoidFunction
	get_instance_proc_address(Instance&& instance, const char* name) {
		return vkGetInstanceProcAddr(
			vk::get_handle(instance),
			name
		);
	}

}