#pragma once

#include "view_properties.hpp"

namespace vk {

	template<typename Handler>
	void for_each_instance_layer_properties(
		vk::count count, Handler&& handler
	) {
		return vk::view_instance_layer_properties(
			count,
			[&](span<vk::layer_properties> view) {
				for(vk::layer_properties props : view) handler(props);
			}
		);
	}

	template<typename Handler>
	void for_each_instance_layer_properties(Handler&& handler) {
		vk::for_each_instance_layer_properties(
			vk::get_instance_layer_properties_count(),
			forward<Handler>(handler)
		);
	}

} // vk