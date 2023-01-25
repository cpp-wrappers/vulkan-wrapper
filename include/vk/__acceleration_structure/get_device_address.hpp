#pragma once

#include "handle.hpp"
#include "device_address_info.hpp"
#include "../device/handle.hpp"
#include "../device_address.hpp"
#include "../device/get_proc_address.hpp"

typedef vk::device_address
	(VK_PTR * PFN_vkGetAccelerationStructureDeviceAddressKHR)(
		handle<vk::device> device,
		const vk::acceleration_structure_device_address_info* pInfo
	);

namespace vk {

	vk::device_address inline
	get_device_address(
		handle<vk::device> device,
		handle<vk::acceleration_structure> as
	) {
		vk::acceleration_structure_device_address_info i{
			.acceleration_structure = as
		};

		auto f { (PFN_vkGetAccelerationStructureDeviceAddressKHR)
			vk::get_device_proc_address(
				device, "vkGetAccelerationStructureDeviceAddressKHR"
			)
		};

		return f(device, &i);
	}

} // vk