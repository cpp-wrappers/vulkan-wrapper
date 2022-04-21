#pragma once

#include "view.hpp"

namespace vk {

	template<typename F>
	void for_each_device_extension_properties(
		handle<vk::physical_device> physical_device,
		F&& f,
		vk::layer_name layer_name = {}
	) {
		vk::view_device_extension_properties(
			physical_device,
			[&](auto view) {
				for(auto props : view) f(props);
			},
			layer_name
		);
	}

} // vk

template<typename F>
void handle<vk::physical_device>::for_each_device_extension_properties(
	F&& f, vk::layer_name layer_name
) const {
	vk::for_each_device_extension_properties(
		*this, forward<F>(f), layer_name
	);
}