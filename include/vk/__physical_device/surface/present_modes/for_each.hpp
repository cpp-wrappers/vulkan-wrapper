#pragma once

#include "view.hpp"

namespace vk {

	template<typename Handler>
	void for_each_physical_device_surface_presesnt_mode(
		handle<vk::physical_device> physical_device,
		handle<vk::surface> surface,
		Handler&& handler
	) {
		vk::view_physical_device_surface_present_modes(
			physical_device,
			surface,
			[&](auto view) {
				for (auto present_mode : view) {
					handler(present_mode);
				}
			}
		);
	}

} //vk

template<typename Handler>
void handle<vk::physical_device>::for_each_surface_presesnt_mode(
	handle<vk::surface> surface, Handler&& handler
) const {
	vk::view_physical_device_surface_present_modes(
		*this, surface, forward<Handler>(handler)
	);
}