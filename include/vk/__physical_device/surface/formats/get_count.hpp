#pragma once

#include "./get.hpp"

namespace vk {

	[[ nodiscard ]] inline
	vk::count get_physical_device_surface_format_count(
		handle<vk::instance> instance,
		handle<vk::physical_device> physical_device,
		handle<vk::surface> surface
	) {
		return vk::get_physical_device_surface_formats(
			instance,
			physical_device,
			surface,
			span<vk::surface_format>{ nullptr, 0 }
		);
	}

} // vk