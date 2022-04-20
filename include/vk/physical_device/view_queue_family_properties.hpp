#pragma once

#include "get_queue_family_properties.hpp"
#include "get_queue_family_properties_count.hpp"

#include <core/range/view_on_stack.hpp>

namespace vk {

	template<typename F>
	[[ nodiscard ]]
	vk::count view_physical_device_queue_family_properties(
		handle<vk::physical_device> physical_device,
		vk::count count,
		F&& f
	) {
		range::view_on_stack<vk::queue_family_properties>((uint32) count)(
			[&](auto families) {
				count = vk::get_physical_device_queue_family_properties(
					physical_device, families
				);

				f(span{ families.data(), (uint32) count });
			}
		);

		return count;
	}

	template<typename F>
	[[ nodiscard ]]
	vk::count view_physical_device_queue_family_properties(
		handle<vk::physical_device> physical_device, F&& f
	) {
		return vk::view_physical_device_queue_family_properties(
			physical_device,
			vk::get_physical_device_queue_family_properties_count(
				physical_device
			),
			forward<F>(f)
		);
	}

} // vk

template<typename F>
vk::count
handle<vk::physical_device>::view_queue_family_properties(
	vk::count count, F&& f
) const {
	return vk::view_physical_device_queue_family_properties(
		*this, count, forward<F>(f)
	);
}

template<typename F>
vk::count
handle<vk::physical_device>::view_queue_family_properties(F&& f) const {
	return vk::view_physical_device_queue_family_properties(
		*this, forward<F>(f)
	);
}