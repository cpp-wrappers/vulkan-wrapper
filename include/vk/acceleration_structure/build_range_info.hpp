#pragma once

#include "vk/headers.hpp"

namespace vk {

	struct acceleration_structure_build_range_info {
		uint32 primitive_count;
		uint32 primitive_offset;
		uint32 first_vertex;
		uint32 transform_offset;
	};

} // vk

static_assert(sizeof(vk::acceleration_structure_build_range_info) == sizeof(VkAccelerationStructureBuildRangeInfoKHR));