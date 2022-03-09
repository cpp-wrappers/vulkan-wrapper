#pragma once

#include "handle.hpp"
#include "device_address_info.hpp"

#include "vk/device/handle.hpp"
#include "vk/handle/possibly_guarded_handle_of.hpp"
#include "vk/device_address.hpp"

namespace vk {

	template<vk::possibly_guarded_handle_of<vk::device> Device, vk::possibly_guarded_handle_of<vk::buffer> Buffer>
	vk::device_address
	get_device_address(Device&& device, Buffer&& buffer) {
		vk::buffer_device_address_info i{
			.buffer = vk::get_handle(buffer)
		};

		return vk::device_address {
			vkGetBufferDeviceAddress(
				(VkDevice) vk::get_handle_value(device),
				(const VkBufferDeviceAddressInfo*) &i
			)
		};
	}

} // vk