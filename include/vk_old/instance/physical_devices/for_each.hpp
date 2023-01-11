#pragma once

#include "view.hpp"

namespace vk {

	template<typename Handler>
	void for_each_physical_device(
		handle<vk::instance> instance, vk::count count, Handler&& handler
	) {
		vk::view_physical_devices(
			instance, count,
			[&](auto view) {
				for(handle<vk::physical_device> device : view)
					handler(device);
			}
		);
	}

	template<typename Handler>
	void for_each_physical_device(
		handle<vk::instance> instance, Handler&& handler
	) {
		vk::for_each_physical_device(
			instance,
			vk::get_physical_device_count(instance),
			forward<Handler>(handler)
		);
	}

} // vk

template<typename Handler>
void handle<vk::instance>::for_each_physical_device(
	vk::count count, Handler&& handler
) const {
	vk::for_each_physical_device(*this, count, forward<Handler>(handler));
}

template<typename Handler>
void handle<vk::instance>::for_each_physical_device(
	Handler&& handler
) const {
	vk::for_each_physical_device(*this, forward<Handler>(handler));
}