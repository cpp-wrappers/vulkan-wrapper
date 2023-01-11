#pragma once

#include "handle.hpp"

namespace vk {

	struct acceleration_structure_device_address_info {
		uint32 structure_type = 1000150002;
		const void* next;
		handle<vk::acceleration_structure> acceleration_structure;
	};

	namespace as {
		using device_address_info =
			vk::acceleration_structure_device_address_info;
	}

} // vk