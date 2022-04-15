#pragma once

#include "get_surface_formats.hpp"

#include <core/box.hpp>

namespace vk {

	template<typename F>
	[[ nodiscard ]]
	vk::count
	view_physical_device_surface_formats(
		handle<vk::physical_device> physical_device,
		handle<vk::surface> surface,
		vk::count count,
		F&& f
	) {
		view_box_of_capacity<vk::surface_format>(
			count,
			[&](auto& surface_formats) {
				count = vk::get_physical_device_surface_formats(
					physical_device, surface, surface_formats
				);

				f(span{ surface_formats.data(), (uint32) count });
			}
		);
	}

	template<typename F>
	[[ nodiscard ]]
	vk::count
	view_physical_device_surface_formats(
		handle<vk::physical_device> physical_device,
		handle<vk::surface> surface,
		F&& f
	) {
		return vk::view_physical_device_surface_formats(
			physical_device,
			surface,
			vk::get_physical_device_surface_format_count(
				physical_device,
				surface
			),
			forward<F>(f)
		);
	}

} // vk

template<typename F>
vk::count
handle<vk::physical_device>::view_surface_formats(
	handle<vk::surface> surface, vk::count count, F&& f
) const {
	return vk::view_physical_device_surface_formats(
		*this, surface, count, forward<F>(f)
	);
}

template<typename F>
vk::count
handle<vk::physical_device>::view_surface_formats(
	handle<vk::surface> surface, F&& f
) const {
	return vk::view_physical_device_surface_formats(
		*this, surface, forward<F>(f)
	);
}