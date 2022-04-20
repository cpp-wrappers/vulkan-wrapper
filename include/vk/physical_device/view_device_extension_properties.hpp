#pragma once

#include "get_device_extension_properties_count.hpp"

#include <core/range/view_on_stack.hpp>

namespace vk {

	template<typename F>
	[[ nodiscard ]]
	vk::count view_device_extension_properties(
		handle<vk::physical_device> physical_device,
		vk::count count,
		F&& f,
		vk::layer_name layer_name = {}
	) {
		range::view_on_stack<vk::extension_properties>((uint32) count)(
			[&](auto extensions) {
				count = vk::enumerate_device_extension_properties(
					physical_device, extensions, layer_name
				);

				f(span{ extensions.data(), (uint32) count });
			}
		);

		return count;
	}

	template<typename F>
	[[ nodiscard ]]
	vk::count view_device_extension_properties(
		handle<vk::physical_device> physical_device,
		F&& f,
		vk::layer_name layer_name = {}
	) {
		return vk::view_device_extension_properties(
			physical_device,
			vk::get_device_extension_properties_count(
				physical_device, layer_name
			),
			forward<F>(f),
			layer_name
		);
	}

} // vk

template<typename F>
vk::count
handle<vk::physical_device>::view_device_extension_properties(
	vk::count count, F&& f, vk::layer_name layer_name
) const {
	return vk::view_device_extension_properties(
		*this, count, forward<F>(f), layer_name
	);
}

template<typename F>
vk::count
handle<vk::physical_device>::view_device_extension_properties(
	F&& f, vk::layer_name layer_name
) const {
	return vk::view_device_extension_properties(
		*this, forward<F>(f), layer_name
	);
}