#pragma once

#include "properties.hpp"

namespace vk {

	struct physical_device_properties_2 {
		const uint32 __type = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROPERTIES_2;
		void* next;
		vk::physical_device_properties properties;
	};

} // vk

static_assert(sizeof(vk::physical_device_properties_2) == sizeof(VkPhysicalDeviceProperties2));