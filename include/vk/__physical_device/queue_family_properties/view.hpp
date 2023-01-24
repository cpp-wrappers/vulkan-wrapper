#pragma once

#include "./get_count.hpp"

namespace vk {

	template<typename Handler>
	void view_physical_device_queue_family_properties(
		handle<vk::instance> instance,
		handle<vk::physical_device> physical_device,
		vk::count count,
		Handler&& handler
	) {
		uint32 count0 = count;

		view_on_stack<vk::queue_family_properties>{ count0 }(
			[&](span<vk::queue_family_properties> raw) {
				count0 = vk::get_physical_device_queue_family_properties(
					instance,
					physical_device,
					raw
				);

				handler(raw.shrink_view(count0));
			}
		);
	}

	template<typename Handler>
	void view_physical_device_queue_family_properties(
		handle<vk::instance> instance,
		handle<vk::physical_device> physical_device,
		Handler&& handler
	) {
		vk::view_physical_device_queue_family_properties(
			instance,
			physical_device,
			vk::get_physical_device_queue_family_properties_count(
				instance, physical_device
			),
			forward<Handler>(handler)
		);
	}

} // vk