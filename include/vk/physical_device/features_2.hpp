#pragma once

#include "vk/headers.hpp"
#include "features.hpp"

namespace vk {

	struct physical_device_features_2 {
		const uint32 __type = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2;
		const void* next;
		vk::physical_device_features features;
	};

} // vk

static_assert(sizeof(vk::physical_device_features_2) == sizeof(VkPhysicalDeviceFeatures2));