#pragma once

#include "get_surface_formats.hpp"

namespace vk {

	[[ nodiscard ]] inline
	vk::count get_physical_device_surface_format_count(
		handle<vk::physical_device> physical_device,
		handle<vk::surface> surface
	) {
		return vk::get_physical_device_surface_formats(
			physical_device,
			surface,
			span<vk::surface_format>{ nullptr, 0 }
		);
	}

} // vk

vk::count inline
handle<vk::physical_device>::get_surface_format_count(
	handle<vk::surface> surface
) const {
	return vk::get_physical_device_surface_format_count(*this, surface);
}