#pragma once

#include "../__internal/function.hpp"
#include "../__internal/device_address.hpp"
#include "../__buffer/device_address_info.hpp"
#include "../__device/handle.hpp"

namespace vk {

	struct get_buffer_device_address_function :
		vk::function<vk::device_address(*)(
			handle<vk::device>::underlying_type device,
			const vk::buffer_device_address_info* info
		)>
	{
		static constexpr auto name = "vkGetBufferDeviceAddress";
	};

	vk::device_address inline get_device_address(
		handle<vk::instance> instance,
		handle<vk::device> device,
		handle<vk::buffer> buffer
	) {
		vk::buffer_device_address_info i{
			.buffer = buffer
		};

		return vk::device_address {
			vk::get_device_function<vk::get_buffer_device_address_function>(
				instance, device
			)(
				device.underlying(),
				&i
			)
		};
	}

} // vk