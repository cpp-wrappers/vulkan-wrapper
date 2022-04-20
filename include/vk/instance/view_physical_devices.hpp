#pragma once

#include "get_physical_device_count.hpp"

#include <core/span.hpp>
#include <core/range/view_copy_on_stack.hpp>

namespace vk {

	vk::count
	view_physical_devices(
		handle<vk::instance> instance, vk::count count, auto&& f
	) {
		range::view_on_stack<handle<vk::physical_device>>((uint32) count)(
			[&](auto physical_devices) {
				count = instance.enumerate_physical_devices(physical_devices);
				f(physical_devices.cut(count));
			}
		);

		return count;
	}

} // vk

template<typename F>
vk::count
handle<vk::instance>::view_physical_devices(vk::count count, F&& f) const {
	return vk::view_physical_devices(*this, count, forward<F>(f));
}