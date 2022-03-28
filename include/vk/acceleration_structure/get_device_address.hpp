#pragma once

#include "handle.hpp"
#include "device_address_info.hpp"
#include "../device/handle.hpp"
#include "../device_address.hpp"
#include "../device/get_proc_address.hpp"

#include <core/handle/possibly_guarded_of.hpp>

typedef vk::device_address
	(VK_PTR * PFN_vkGetAccelerationStructureDeviceAddressKHR)(
		handle<vk::device> device,
		const vk::acceleration_structure_device_address_info* pInfo
	);

namespace vk {

	template<
		possibly_guarded_handle_of<vk::device> Device,
		possibly_guarded_handle_of<vk::acceleration_structure> AS
	>
	vk::device_address
	get_device_address(Device&& device, AS&& as) {
		vk::acceleration_structure_device_address_info i{
			.acceleration_structure = vk::get_handle(as)
		};

		auto f { (PFN_vkGetAccelerationStructureDeviceAddressKHR)
			vk::get_device_proc_address(
				device,
				"vkGetAccelerationStructureDeviceAddressKHR"
			)
		};

		return f(vk::get_handle(device), &i);
	}

} // vk