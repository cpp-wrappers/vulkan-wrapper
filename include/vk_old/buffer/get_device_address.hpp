#pragma once

#include "handle.hpp"
#include "device_address_info.hpp"

#include "../function.hpp"
#include "../device/handle.hpp"
#include "../device_address.hpp"

extern "C" VK_ATTR vk::device_address VK_CALL vkGetBufferDeviceAddress(
	handle<vk::device>                    device,
	const vk::buffer_device_address_info* info
);

namespace vk {

	vk::device_address inline
	get_device_address(
		handle<vk::device> device,
		handle<vk::buffer> buffer
	) {
		vk::buffer_device_address_info i{
			.buffer = buffer
		};

		return vk::device_address {
			vkGetBufferDeviceAddress(
				device,
				&i
			)
		};
	}

} // vk