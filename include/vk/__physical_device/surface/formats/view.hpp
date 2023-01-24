#pragma once

#include "./get.hpp"

namespace vk {

	template<typename Handler>
	void view_physical_device_surface_formats(
		handle<vk::instance> instance,
		handle<vk::physical_device> physical_device,
		handle<vk::surface> surface,
		vk::count count,
		Handler&& handler
	) {
		view_on_stack<vk::surface_format>{ count }(
			[&](span<vk::surface_format> raw) {
				count = vk::get_physical_device_surface_formats(
					instance, physical_device, surface, raw
				);

				handler(raw.shrink(count));
			}
		);
	}

	template<typename Handler>
	void view_physical_device_surface_formats(
		handle<vk::instance> instance,
		handle<vk::physical_device> physical_device,
		handle<vk::surface> surface,
		Handler&& handler
	) {
		vk::count count = vk::get_physical_device_surface_formats(
			instance, physical_device, surface, span<vk::surface_format>{}
		);

		vk::view_physical_device_surface_formats(
			physical_device,
			surface,
			count,
			forward<Handler>(handler)
		);
	}

} // vk