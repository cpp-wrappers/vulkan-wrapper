#pragma once

#include "get_count.hpp"

#include <core/view_on_stack.hpp>

namespace vk {

	template<typename Handler>
	void view_physical_device_queue_family_properties(
		handle<vk::physical_device> physical_device,
		vk::count count,
		Handler&& handler
	) {
		view_on_stack<vk::queue_family_properties>{ count }(
			[&](span<vk::queue_family_properties> raw) {
				count = vk::get_physical_device_queue_family_properties(
					physical_device, raw
				);

				handler(raw.cut(count));
			}
		);
	}

	template<typename Handler>
	void view_physical_device_queue_family_properties(
		handle<vk::physical_device> physical_device, Handler&& handler
	) {
		vk::view_physical_device_queue_family_properties(
			physical_device,
			vk::get_physical_device_queue_family_properties_count(
				physical_device
			),
			forward<Handler>(handler)
		);
	}

} // vk

template<typename Handler>
void handle<vk::physical_device>::view_queue_family_properties(
	vk::count count, Handler&& handler
) const {
	vk::view_physical_device_queue_family_properties(
		*this, count, forward<Handler>(handler)
	);
}

template<typename Handler>
void handle<vk::physical_device>::view_queue_family_properties(
	Handler&& handler
) const {
	vk::view_physical_device_queue_family_properties(
		*this, forward<Handler>(handler)
	);
}