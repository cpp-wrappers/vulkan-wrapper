#pragma once

#include "../features.hpp"

namespace vk {

	struct physical_device_buffer_device_address_features :
		vk::physical_device_features_mark
	{
		uint32 struct_type = 1000244000;
		const void* next;
		uint32 buffer_device_address;
		uint32 buffer_device_address_capture_replay;
		uint32 buffer_device_address_multi_device;
	};

} // vk