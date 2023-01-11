#pragma once

#include "../device_or_host_address.hpp"
#include "../device_size.hpp"

namespace vk {

	struct acceleration_structure_geometry_aabbs_data {
		uint32 structure_type = 1000150003;
		const void* next;
		vk::device_or_host_address data;
		vk::device_size stride;
	};

	namespace as {
		using geometry_aabbs_data =
			vk::acceleration_structure_geometry_aabbs_data;
	}

} // vk