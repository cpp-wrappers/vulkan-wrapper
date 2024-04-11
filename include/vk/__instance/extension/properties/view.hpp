#pragma once

#include "get_count.hpp"

#include <view_on_stack.hpp>

namespace vk {

	template<typename Handler>
	void view_instance_extension_properties(
		vk::count count, Handler&& handler
	) {
		view_on_stack<vk::extension_properties>{ count }(
			[&](span<vk::extension_properties> raw) {
				count = vk::enumerate_instance_extension_properties(raw);
				handler(raw.shrink(count));
			}
		);
	}

	template<typename Handler>
	void view_instance_extension_properties(Handler&& handler) {
		vk::view_instance_extension_properties(
			vk::get_instance_extension_properties_count(),
			forward<Handler>(handler)
		);
	}

} // vk