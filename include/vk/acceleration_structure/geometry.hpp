#pragma once

#include "geometry_type.hpp"

#include "vk/headers.hpp"

namespace vk {

	struct acceleration_structure_geometry {
		const uint32 __type = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_KHR;
		const void* const __next;
		vk::acceleration_structure_geometry_type type;
	};

}