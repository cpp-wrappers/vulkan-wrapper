#pragma once

#include "view_device_extension_properties.hpp"

namespace vk {

	template<typename F>
	vk::count
	for_each_device_extension_properties(
		handle<vk::physical_device> physical_device,
		F&& f,
		vk::layer_name layer_name = {}
	) {
		return vk::view_device_extension_properties(
			physical_device,
			[&](auto view) {
				for(auto props : view) f(props);
			},
			layer_name
		);
	}

} // vk

template<typename F>
vk::count
handle<vk::physical_device>::for_each_device_extension_properties(
	F&& f, vk::layer_name layer_name
) const {
	return vk::for_each_device_extension_properties(
		*this, forward<F>(f), layer_name
	);
}