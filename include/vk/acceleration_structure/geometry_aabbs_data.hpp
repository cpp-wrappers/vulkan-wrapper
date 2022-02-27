#pragma once

#include "vk/headers.hpp"
#include "vk/device_or_host_address.hpp"
#include "vk/device_size.hpp"

namespace vk {

	struct acceleration_structure_geometry_aabbs_data {
		const uint32 __type = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_AABBS_DATA_KHR;
		const void* const __next;
		vk::device_or_host_address data;
		vk::device_size stride;
	};

} // vk

static_assert(sizeof(vk::acceleration_structure_geometry_aabbs_data) == sizeof(VkAccelerationStructureGeometryAabbsDataKHR));