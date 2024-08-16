#pragma once

#include "../__internal/function.hpp"
#include "../__internal/result.hpp"
#include "../__internal/unexpected_handler.hpp"
#include "../__device/handle.hpp"
#include "../__instance/handle.hpp"

namespace vk {

	struct device_wait_idle_function : vk::function<int32(*)(
		handle<vk::device>::underlying_type device
	)> {
		static constexpr auto name = "vkDeviceWaitIdle";
	};

	vk::result inline try_device_wait_idle(
		handle<vk::instance> instance,
		handle<vk::device> device
	) {
		return {
			vk::get_device_function<device_wait_idle_function>(
				instance, device
			)(
				device.underlying()
			)
		};
	}

	void inline device_wait_idle(
		handle<vk::instance> instance,
		handle<vk::device> device
	) {
		auto result = vk::try_device_wait_idle(instance, device);
		if (result.error()) vk::unexpected_handler(result);
	}

} // vk