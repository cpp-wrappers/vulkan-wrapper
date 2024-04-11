#pragma once

#include "enumerate.hpp"

#include <span.hpp>

namespace vk {

	vk::count inline
	get_instance_extension_properties_count() {
		return vk::enumerate_instance_extension_properties(
			span<vk::extension_properties>{ nullptr, 0 }
		);
	}

} // vk