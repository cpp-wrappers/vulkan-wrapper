#pragma once

#include "enumerate.hpp"

namespace vk {

	[[ nodiscard ]] inline
	vk::count get_device_extension_properties_count(
		handle<vk::physical_device> physical_device, vk::layer layer_name
	) {
		return vk::enumerate_device_extension_properties(
			physical_device, layer_name,
			span<vk::extension_properties>{ nullptr, 0 }
		);
	}

} // vk

[[ nodiscard ]]
vk::count inline
handle<vk::physical_device>::get_device_extension_properties_count(
	vk::layer layer_name
) const {
	return vk::get_device_extension_properties_count(*this, layer_name);
}