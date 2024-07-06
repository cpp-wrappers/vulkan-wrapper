#pragma once

#include "../__instance/handle.hpp"
#include "../__internal/function.hpp"
#include "../__internal/unexpected_handler.hpp"
#include "../__device/handle.hpp"

#include <c_string.hpp>

namespace vk {

	struct get_device_proc_address_function : vk::function<void*(*)(
		handle<vk::device>::underlying_type device,
		const char* name
	)> {
		static constexpr auto name = "vkGetDeviceProcAddr";
	};

	inline void* try_get_device_proc_address(
		handle<vk::instance> instance,
		handle<vk::device> device,
		c_string<char> name
	) {
		return vk::get_instance_function<
			vk::get_device_proc_address_function
		>(instance)(
			device.underlying(), name.iterator()
		);
	}

	inline void* get_device_proc_address(
		handle<vk::instance> instance,
		handle<vk::device> device,
		c_string<char> name
	) {
		void* result = vk::try_get_device_proc_address(
			instance, device, name
		);
		if (result == nullptr) {
			vk::unexpected_handler();
		}
		return result;
	}

}