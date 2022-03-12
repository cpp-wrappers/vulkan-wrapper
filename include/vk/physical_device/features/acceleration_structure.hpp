#pragma once

#include "vk/physical_device/features.hpp"
#include "vk/headers.hpp"

namespace vk {

	struct physical_device_acceleration_structure_features : vk::physical_device_features_marker {
		uint32 structure_type = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_ACCELERATION_STRUCTURE_FEATURES_KHR;
		const void* next;
		uint32 acceleration_structure;
		uint32 acceleration_structure_capture_replay;
		uint32 acceleration_structure_indirect_build;
		uint32 acceleration_structure_host_commands;
		uint32 descriptor_binding_acceleration_structure_update_after_bind;
	};

} // vk

static_assert(sizeof(vk::physical_device_acceleration_structure_features) == sizeof(VkPhysicalDeviceAccelerationStructureFeaturesKHR));