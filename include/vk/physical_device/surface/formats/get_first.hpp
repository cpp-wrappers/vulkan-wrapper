#pragma once

#include "get.hpp"

#include <core/span.hpp>
#include <core/single.hpp>

namespace vk {

	template<typename... Args>
	requires types::are_exclusively_satisfying_predicates<
		types::are_contain_one_decayed<handle<vk::physical_device>>,
		types::are_contain_one_decayed<handle<vk::surface>>
	>::for_types<Args...>
	vk::surface_format
	get_first_physical_device_surface_format(Args&&... args) {
		auto physical_device {
			elements::decayed<handle<vk::physical_device>>(args...)
		};

		auto surface {
			elements::decayed<handle<vk::surface>>(args...)
		};

		vk::surface_format surface_format;

		vk::count count {
			vk::get_physical_device_surface_formats(
				physical_device, surface, single_view{ surface_format }
			)
		};

		if(count == 0) {
			vk::unexpected_handler();
		}

		return surface_format;
	}

} // vk

vk::surface_format inline
handle<vk::physical_device>::get_first_surface_format(
	handle<vk::surface> surface
) const {
	return vk::get_first_physical_device_surface_format(*this, surface);
}