#pragma once

#include "get.hpp"

namespace vk {

	[[ nodiscard ]]
	vk::count inline
	get_physical_device_surface_present_mode_count(
		handle<vk::physical_device> physical_device,
		handle<vk::surface> surface
	) {
		return vk::get_physical_device_surface_present_modes(
			physical_device, surface, span<vk::present_mode>{ nullptr, 0 }
		);
	}

} // vk

vk::count inline
handle<vk::physical_device>::get_surface_present_mode_count(
	handle<vk::surface> surface
) const {
	return vk::get_physical_device_surface_format_count(*this, surface);
}