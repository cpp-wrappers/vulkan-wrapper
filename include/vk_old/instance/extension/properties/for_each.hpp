#pragma once

#include "view.hpp"

namespace vk {

	template<typename Handler>
	void for_each_instance_extension_properties(
		vk::count count, Handler&& handler
	) {
		return vk::view_instance_extension_properties(
			count,
			[&](span<vk::extension_properties> view) {
				for(vk::extension_properties props : view) handler(props);
			}
		);
	}

	template<typename Handler>
	void for_each_instance_extension_properties(Handler&& handler) {
		vk::for_each_instance_extension_properties(
			vk::get_instance_extension_properties_count(),
			forward<Handler>(handler)
		);
	}

} // vk