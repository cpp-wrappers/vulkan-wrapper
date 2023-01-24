#pragma once

#include "./get.hpp"

namespace vk {

	[[ nodiscard ]] inline
	uint32
	get_physical_device_queue_family_properties_count(
		handle<vk::instance> instance,
		handle<vk::physical_device> physical_device
	) {
		return vk::get_physical_device_queue_family_properties(
			instance,
			physical_device,
			span<vk::queue_family_properties>{ nullptr, 0 }
		);
	}

} // vk