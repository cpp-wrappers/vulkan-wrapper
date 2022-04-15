#pragma once

#include "get_queue_family_properties.hpp"

namespace vk {

	[[ nodiscard ]] inline
	vk::count
	get_physical_device_queue_family_properties_count(
		handle<vk::physical_device> physical_device
	) {
		return vk::get_physical_device_queue_family_properties(
			physical_device,
			span<vk::queue_family_properties>{ nullptr, 0 }
		);
	}

} // vk

vk::count inline
handle<vk::physical_device>::get_queue_family_properties_count() const {
	return vk::get_physical_device_queue_family_properties_count(
		*this
	);
}