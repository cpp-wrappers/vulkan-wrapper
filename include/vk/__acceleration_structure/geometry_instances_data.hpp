#pragma once

#include "../__internal/device_or_host_address.hpp"

namespace vk {

	struct acceleration_structure_instances_data {
		uint32 structure_type = 1000150004;
		const void* next;
		uint32 array_of_pointers;
		vk::device_or_host_address data;
	};

	namespace as {
		using instances_data = vk::acceleration_structure_instances_data;
	}

} // vk