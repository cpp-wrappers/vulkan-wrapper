#pragma once

#include "get_count.hpp"

#include <core/range/view_on_stack.hpp>

namespace vk {

	template<typename Handler>
	void view_instance_layer_properties(vk::count count, Handler&& handler) {
		range::view_on_stack<vk::layer_properties>{ count }(
			[&](span<vk::layer_properties> raw) {
				count = vk::enumerate_instance_layer_properties(raw);
				handler(raw.cut(count));
			}
		);
	}

	template<typename Handler>
	void view_instance_layer_properties(Handler&& handler) {
		vk::view_instance_layer_properties(
			vk::get_instance_layer_properties_count(),
			forward<Handler>(handler)
		);
	}

} // vk