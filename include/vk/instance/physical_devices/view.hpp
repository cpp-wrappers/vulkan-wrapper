#pragma once

#include "get_count.hpp"

#include <core/span.hpp>
#include <core/view_copy_on_stack.hpp>

namespace vk {

	void view_physical_devices(
		handle<vk::instance> instance, vk::count count, auto&& f
	) {
		view_on_stack<handle<vk::physical_device>>{ count }(
			[&](auto physical_devices) {
				count = instance.enumerate_physical_devices(physical_devices);
				f(physical_devices.cut(count));
			}
		);
	}

} // vk

template<typename F>
void handle<vk::instance>::view_physical_devices(vk::count count, F&& f) const {
	vk::view_physical_devices(*this, count, forward<F>(f));
}