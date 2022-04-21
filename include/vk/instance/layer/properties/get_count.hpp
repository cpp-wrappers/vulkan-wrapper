#pragma once

#include "enumerate.hpp"

#include <core/span.hpp>

namespace vk {

	[[ nodiscard ]]
	vk::expected<vk::count> inline
	get_instance_layer_properties_count() {
		return enumerate_instance_layer_properties(
			span<vk::layer_properties>{ nullptr, 0 }
		);
	}

} // vk