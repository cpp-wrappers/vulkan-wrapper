#pragma once

#include "view.hpp"

namespace vk {

	template<typename F>
	void for_each_physical_device_queue_family_properties(
		handle<vk::physical_device> physical_device, F&& f
	) {
		return vk::view_physical_device_queue_family_properties(
			physical_device,
			[&](auto props) {
				for(auto p : props){ f(p); }
			}
		);
	}

} // vk

template<typename F>
void
handle<vk::physical_device>::for_each_queue_family_properties(F&& f) const {
	return vk::for_each_physical_device_queue_family_properties(
		*this, forward<F>(f)
	);
}