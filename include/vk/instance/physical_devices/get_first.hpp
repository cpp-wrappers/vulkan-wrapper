#pragma once

#include "enumerate.hpp"

#include <core/single.hpp>

namespace vk {

	[[ nodiscard ]]
	vk::expected<handle<vk::physical_device>> inline
	get_first_physical_device(handle<vk::instance> instance) {
		handle<vk::physical_device> physical_device;

		auto count {
			instance.enumerate_physical_devices(single_view{ physical_device })
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