#pragma once

#include "handle.hpp"
#include "device_address_info.hpp"

#include "vk/device/handle.hpp"
#include "vk/handle/possibly_guarded_handle_of.hpp"
#include "vk/device_address.hpp"

namespace vk {

	template<vk::possibly_guarded_handle_of<vk::device> Device, vk::possibly_guarded_handle_of<vk::acceleration_structure> AS>
	vk::device_address
	get_device_address(Device&& device, AS&& as) {
		vk::acceleration_structure_device_address_info i{
			.acceleration_structure = vk::get_handle(as)
		};

		auto f { (PFN_vkGetAccelerationStructureDeviceAddressKHR)
			vkGetDeviceProcAddr(
				(VkDevice) vk::get_handle_value(device),
				"vkGetAccelerationStructureDeviceAddressKHR"
			)
		};

		return vk::device_address {
			f(
				(VkDevice) vk::get_handle_value(device),
				(const VkAccelerationStructureDeviceAddressInfoKHR*) &i
			)
		};
	}

} // vk