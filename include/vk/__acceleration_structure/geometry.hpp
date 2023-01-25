#pragma once

#include "geometry_type.hpp"
#include "geometry_data.hpp"
#include "geometry_flags.hpp"

namespace vk {

	struct acceleration_structure_geometry {
		uint32 structure_type = 1000150006;
		const void* next = nullptr;
		vk::geometry_type type;
		vk::acceleration_structure_geometry_data geometry;
		vk::geometry_flags flags;
	};

	namespace as {
		using geometry = vk::acceleration_structure_geometry;
	}

} // vk