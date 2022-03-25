#pragma once

#include "properties.hpp"

namespace vk {

	struct physical_device_properties_2 {
		uint32 structure_type = 1000059001;
		const void* next;
		vk::physical_device_properties properties;
	};

} // vk