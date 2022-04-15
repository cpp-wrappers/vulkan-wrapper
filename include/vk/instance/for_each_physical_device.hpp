#pragma once

#include "view_physical_devices.hpp"

namespace vk {

	template<typename F>
	vk::count
	for_each_physical_device(
		handle<vk::instance> instance, vk::count count, F&& f
	) {
		return instance.view_physical_devices(
			count,
			[&](auto view) {
				for(handle<vk::physical_device> device : view) f(device);
			}
		);
	}

} // vk

template<typename F>
vk::count
handle<vk::instance>::for_each_physical_device(
	vk::count count, F&& f
) const {
	vk::for_each_physical_device(*this, count, forward<F>(f));
}