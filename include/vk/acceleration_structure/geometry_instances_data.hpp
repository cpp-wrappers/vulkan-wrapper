#pragma once

#include "vk/headers.hpp"
#include "vk/device_or_host_address.hpp"

namespace vk {

	struct acceleration_structure_instances_data {
		uint32 structure_type = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_INSTANCES_DATA_KHR;
		const void* next;
		uint32 array_of_pointers;
		vk::device_or_host_address data;
	};

	namespace as {
		using instances_data = vk::acceleration_structure_instances_data;
	}

} // vk

static_assert(sizeof(vk::acceleration_structure_instances_data) == sizeof(VkAccelerationStructureGeometryInstancesDataKHR));