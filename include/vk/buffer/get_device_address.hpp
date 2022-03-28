#pragma once

#include "handle.hpp"
#include "device_address_info.hpp"

#include "../function.hpp"
#include "../device/handle.hpp"
#include "../device_address.hpp"

#include <core/handle/possibly_guarded_of.hpp>

extern "C" VK_ATTR vk::device_address VK_CALL vkGetBufferDeviceAddress(
	handle<vk::device> device,
	const vk::buffer_device_address_info* nfo
);

namespace vk {

	template<
		possibly_guarded_handle_of<vk::device> Device,
		possibly_guarded_handle_of<vk::buffer> Buffer
	>
	vk::device_address
	get_device_address(Device&& device, Buffer&& buffer) {
		vk::buffer_device_address_info i{
			.buffer = vk::get_handle(buffer)
		};

		return vk::device_address {
			vkGetBufferDeviceAddress(
				vk::get_handle(device),
				&i
			)
		};
	}

} // vk