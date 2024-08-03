#pragma once

#include "view.hpp"

#include <range.hpp>

namespace vk {

	template<range_of<is_same_as<vk::surface_format>.decayed> PreferredFormats>
	optional<vk::surface_format>
	try_choose_physical_device_surface_format(
		handle<vk::instance> instance,
		handle<vk::physical_device> physical_device,
		handle<vk::surface> surface,
		PreferredFormats&& preferred_formats
	) {
		return vk::view_physical_device_surface_formats(
			instance,
			physical_device,
			surface,
			[&](span<vk::surface_format> supported_formats)
			-> optional<vk::surface_format> {
				for(vk::surface_format preferred : preferred_formats) {
					for(vk::surface_format supported : supported_formats) {
						if(preferred == supported) {
							return preferred;
						}
					}
				}
				return {};
			}
		);
	}

} // vk