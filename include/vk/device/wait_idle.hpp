#pragma once

#include "handle.hpp"

#include "../function.hpp"

extern "C" VK_ATTR int32 VK_CALL vkDeviceWaitIdle(
	handle<vk::device> device
);

namespace vk {

	vk::result inline
	try_device_wait_idle(handle<vk::device> device) {
		return { vkDeviceWaitIdle(device) };
	}

	void inline
	device_wait_idle(handle<vk::device> device) {
		auto result = vk::try_device_wait_idle(device);
		if(result.error()) vk::unexpected_handler(result);
	}

} // vk

vk::result inline
handle<vk::device>::try_wait_idle() const {
	return vk::try_device_wait_idle(*this);
}

void inline
handle<vk::device>::wait_idle() const {
	vk::device_wait_idle(*this);
}