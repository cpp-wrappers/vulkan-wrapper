#pragma once

#include "../extension_properties.hpp"
#include "vk/headers.hpp"

namespace vk {

	struct physical_device_acceleration_structure_properties : vk::extension_properties_marker {
		const uint32 __type = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ACCELERATION_STRUCTURE_PROPERTIES_KHR;
		const void* __next;
		uint64 max_geometry_count;
		uint64 max_instance_count;
		uint64 max_primitive_count;
		uint32 max_per_stage_descriptor_acceleration_structures;
		uint32 max_per_stage_descriptor_update_after_bind_acceleration_structures;
		uint32 max_descriptor_set_acceleration_structures;
		uint32 max_descriptor_set_update_after_bind_acceleration_structures;
		uint32 min_acceleration_structure_scratch_offset_alignment;
	};

} // vk

static_assert(sizeof(vk::physical_device_acceleration_structure_properties) == sizeof(VkPhysicalDeviceAccelerationStructurePropertiesKHR));