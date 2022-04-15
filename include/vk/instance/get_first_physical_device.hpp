#pragma once

#include "enumerate_physical_devices.hpp"

namespace vk {

	vk::expected<handle<vk::physical_device>> inline
	get_first_physical_device(handle<vk::instance> instance) {
		handle<vk::physical_device> physical_device;

		auto count {
			instance.enumerate_physical_devices(span{ &physical_device, 1 })
		};

		if((uint32)count == 0) {
			vk::unexpected_handler();
		}

		return physical_device;
	}

} // vk

handle<vk::physical_device> inline
handle<vk::instance>::get_first_physical_device() const {
	return vk::get_first_physical_device(*this);
}