#pragma once

#include "enumerate_physical_devices.hpp"

namespace vk {

	vk::count inline
	get_physical_device_count(handle<vk::instance> instance) {
		return vk::enumerate_physical_devices(
			instance,
			span<handle<vk::physical_device>>{ nullptr, 0 }
		);
	}

} // vk

vk::count inline handle<vk::instance>::get_physical_device_count() const {
	return vk::get_physical_device_count(*this);
}