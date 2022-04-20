#pragma once

#include "view_physical_devices.hpp"

namespace vk {

	template<typename F>
	vk::count
	for_each_physical_device(
		handle<vk::instance> instance, vk::count count, F&& f
	) {
		return vk::view_physical_devices(
			instance,
			count,
			[&](auto view) {
				for(handle<vk::physical_device> device : view) f(device);
			}
		);
	}

	template<typename F>
	vk::count
	for_each_physical_device(
		handle<vk::instance> instance, F&& f
	) {
		return vk::for_each_physical_device(
			instance,
			vk::get_physical_device_count(instance),
			forward<F>(f)
		);
	}

} // vk

template<typename F>
vk::count
handle<vk::instance>::for_each_physical_device(
	vk::count count, F&& f
) const {
	return vk::for_each_physical_device(*this, count, forward<F>(f));
}

template<typename F>
vk::count
handle<vk::instance>::for_each_physical_device(F&& f) const {
	return vk::for_each_physical_device(*this, forward<F>(f));
}