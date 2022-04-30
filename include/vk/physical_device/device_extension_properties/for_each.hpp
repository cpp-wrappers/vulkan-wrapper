#pragma once

#include "view.hpp"

namespace vk {

	template<typename Handler>
	void for_each_device_extension_properties(
		handle<vk::physical_device> physical_device,
		Handler&& handler,
		vk::layer layer_name = {}
	) {
		vk::view_device_extension_properties(
			physical_device,
			[&](auto view) {
				for(auto props : view) handler(props);
			},
			layer_name
		);
	}

} // vk

template<typename Handler>
void handle<vk::physical_device>::for_each_device_extension_properties(
	Handler&& handler, vk::layer layer_name
) const {
	vk::for_each_device_extension_properties(
		*this, forward<Handler>(handler), layer_name
	);
}