#pragma once

#include "enumerate_device_extension_properties.hpp"

namespace vk {

	[[ nodiscard ]] inline
	vk::count
	get_device_extension_properties_count(
		handle<vk::physical_device> physical_device, vk::layer_name name
	) {
		return vk::enumerate_device_extension_properties(
			physical_device, name,
			span<vk::extension_properties>{ nullptr, 0 }
		);
	}

} // vk

[[ nodiscard ]]
vk::count inline
handle<vk::physical_device>::get_device_extension_properties_count(
	vk::layer_name name
) const {
	return vk::get_device_extension_properties_count(*this, name);
}