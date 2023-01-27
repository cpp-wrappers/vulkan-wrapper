#pragma once

#include <integer.hpp>

namespace vk {

	struct acceleration_structure_build_range_info {
		uint32 primitive_count;
		uint32 primitive_offset;
		uint32 first_vertex;
		uint32 transform_offset;
	};

	namespace as {
		using build_range_info = vk::acceleration_structure_build_range_info;
	}

} // vk