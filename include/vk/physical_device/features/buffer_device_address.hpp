#pragma once

#include "vk/headers.hpp"
#include "vk/physical_device/features.hpp"

namespace vk {

	struct physical_device_buffer_device_address_features : vk::physical_device_features_marker {
		const uint32 __type = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_BUFFER_ADDRESS_FEATURES_EXT;
		void* next;
		uint32 buffer_device_address;
		uint32 buffer_device_address_capture_replay;
		uint32 buffer_device_address_multi_device;
	};

} // vk