#pragma once

#include "get_device_extension_properties_count.hpp"

#include <core/box.hpp>

namespace vk {

	template<typename F>
	[[ nodiscard ]]
	vk::count view_device_extension_properties(
		handle<vk::physical_device> physical_device,
		vk::count count,
		F&& f,
		vk::layer_name layer_name = {}
	) {
		view_box_of_capacity<vk::extension_properties>(
			count,
			[&](auto& extensions) {
				count = vk::enumerate_device_extension_properties(
					physical_device, count, extensions, layer_name
				);

				f(span{ extensions.data(), (uint32) count });
			}
		);

		return count;
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