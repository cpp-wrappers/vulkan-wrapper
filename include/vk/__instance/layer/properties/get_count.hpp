#pragma once

#include "./enumerate.hpp"

#include <span.hpp>

namespace vk {

	[[ nodiscard ]]
	vk::count inline
	get_instance_layer_properties_count() {
		return vk::enumerate_instance_layer_properties(
			span<vk::layer_properties>{ nullptr, 0 }
		);
	}

} // vk