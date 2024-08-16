#pragma once

#include "./get.hpp"

namespace vk {

	inline
	vk::surface_format
	get_first_physical_device_surface_format(
		handle<vk::instance> instance,
		handle<vk::physical_device> physical_device,
		handle<vk::surface> surface
	) {

		vk::surface_format surface_format;

		vk::count count {
			vk::get_physical_device_surface_formats(
				instance, physical_device, surface, span{ &surface_format }
			)
		};

		if (count == 0) {
			vk::unexpected_handler();
		}

		return surface_format;
	}

} // vk