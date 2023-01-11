#pragma once

#include "geometry_triangles_data.hpp"
#include "geometry_aabbs_data.hpp"
#include "geometry_instances_data.hpp"

namespace vk {

	union acceleration_structure_geometry_data {
		vk::acceleration_structure_geometry_triangles_data triangles;
		vk::acceleration_structure_geometry_aabbs_data aabbs;
		vk::acceleration_structure_instances_data instances;
	};

	namespace as {
		using geometry_data = vk::acceleration_structure_geometry_data;
	}

} // vk