#pragma once

#include "get.hpp"

#include <core/range/view_on_stack.hpp>

namespace vk {

	template<typename Handler>
	void view_physical_device_surface_formats(
		handle<vk::physical_device> physical_device,
		handle<vk::surface> surface,
		vk::count count,
		Handler&& handler
	) {
		range::view_on_stack<vk::surface_format>{ count }(
			[&](span<vk::surface_format> raw) {
				count = vk::get_physical_device_surface_formats(
					physical_device, surface, raw
				);

				handler(raw.cut(count));
			}
		);
	}

	template<typename Handler>
	void view_physical_device_surface_formats(
		handle<vk::physical_device> physical_device,
		handle<vk::surface> surface,
		Handler&& handler
	) {
		vk::view_physical_device_surface_formats(
			physical_device,
			surface,
			vk::get_physical_device_surface_format_count(
				physical_device,
				surface
			),
			forward<Handler>(handler)
		);
	}

} // vk

template<typename Handler>
void handle<vk::physical_device>::view_surface_formats(
	handle<vk::surface> surface, vk::count count, Handler&& handler
) const {
	vk::view_physical_device_surface_formats(
		*this, surface, count, forward<Handler>(handler)
	);
}

template<typename Handler>
void handle<vk::physical_device>::view_surface_formats(
	handle<vk::surface> surface, Handler&& handler
) const {
	vk::view_physical_device_surface_formats(
		*this, surface, forward<Handler>(handler)
	);
}