#pragma once

#include "get_count.hpp"

#include <core/view_on_stack.hpp>

namespace vk {

	template<typename Handler>
	void view_physical_device_surface_present_modes(
		handle<vk::physical_device> physical_device,
		handle<vk::surface> surface,
		vk::count count,
		Handler&& handler
	) {
		view_on_stack<vk::present_mode>((uint32) count)(
			[&](auto raw) {
				count = vk::get_physical_device_surface_present_modes(
					physical_device,
					surface,
					count
				);

				handler(raw.cut(count));
			}
		);
	}

	template<typename Handler>
	void view_physical_device_surface_present_modes(
		handle<vk::physical_device> physical_device,
		handle<vk::surface> surface,
		Handler&& handler
	) {
		vk::view_physical_device_surface_formats(
			surface,
			vk::get_physical_device_surface_present_mode_count(
				physical_device, surface
			),
			forward<Handler>(handler)
		);
	}

} // vk

template<typename Handler>
void handle<vk::physical_device>::view_surface_present_modes(
	handle<vk::surface> surface, vk::count count, Handler&& handler
) const {
	vk::view_physical_device_surface_present_modes(
		*this, surface, count, forward<Handler>(handler)
	);
}

template<typename Handler>
void handle<vk::physical_device>::view_surface_present_modes(
	handle<vk::surface> surface, Handler&& handler
) const {
	vk::view_physical_device_surface_present_modes(
		surface,
		get_surface_present_mode_count(surface),
		forward<Handler>(handler)
	);
}