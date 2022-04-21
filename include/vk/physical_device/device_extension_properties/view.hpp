#pragma once

#include "get_count.hpp"

#include <core/range/view_on_stack.hpp>

namespace vk {

	template<typename Handler>
	void view_device_extension_properties(
		handle<vk::physical_device> physical_device,
		vk::count count,
		Handler&& handler,
		vk::layer_name layer_name = {}
	) {
		range::view_on_stack<vk::extension_properties>{ count } (
			[&](span<vk::extension_properties> raw) {
				count = vk::enumerate_device_extension_properties(
					physical_device, raw, layer_name
				);

				handler(raw.cut(count));
			}
		);
	}

	template<typename Handler>
	void view_device_extension_properties(
		handle<vk::physical_device> physical_device,
		Handler&& handler,
		vk::layer_name layer_name = {}
	) {
		vk::view_device_extension_properties(
			physical_device,
			vk::get_device_extension_properties_count(
				physical_device, layer_name
			),
			forward<Handler>(handler),
			layer_name
		);
	}

} // vk

template<typename Handler>
void
handle<vk::physical_device>::view_device_extension_properties(
	vk::count count, Handler&& handler, vk::layer_name layer_name
) const {
	vk::view_device_extension_properties(
		*this, count, forward<Handler>(handler), layer_name
	);
}

template<typename Handler>
void
handle<vk::physical_device>::view_device_extension_properties(
	Handler&& handler, vk::layer_name layer_name
) const {
	vk::view_device_extension_properties(
		*this, forward<Handler>(handler), layer_name
	);
}