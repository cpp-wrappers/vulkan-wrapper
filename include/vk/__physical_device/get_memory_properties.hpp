#pragma once

#include "handle.hpp"
#include "../function.hpp"

extern "C" VK_ATTR void VK_CALL vkGetPhysicalDeviceMemoryProperties(
	handle<vk::physical_device>            physical_device,
	vk::physical_device_memory_properties* memory_properties
);

namespace vk {

	[[ nodiscard ]]
	vk::physical_device_memory_properties inline
	get_physical_device_memory_properties(
		handle<vk::physical_device> physical_device
	) {
		vk::physical_device_memory_properties props;
		vkGetPhysicalDeviceMemoryProperties(physical_device, &props);
		return props;
	}

} // vk

vk::physical_device_memory_properties inline
handle<vk::physical_device>::get_memory_properties() const {
	return vk::get_physical_device_memory_properties(*this);
}