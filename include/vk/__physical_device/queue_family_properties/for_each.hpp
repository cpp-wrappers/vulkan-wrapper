#pragma once

#include "./view.hpp"

namespace vk {

	template<typename Handler>
	void for_each_physical_device_queue_family_properties(
		handle<vk::instance> instance,
		handle<vk::physical_device> physical_device,
		Handler&& handler
	) {
		return vk::view_physical_device_queue_family_properties(
			instance,
			physical_device,
			[&](auto props) {
				for (auto p : props){ handler(p); }
			}
		);
	}

} // vk