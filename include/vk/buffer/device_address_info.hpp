#pragma once

#include "handle.hpp"
#include "../headers.hpp"

namespace vk {

	struct buffer_device_address_info {
		uint32 structure_type = VK_STRUCTURE_TYPE_BUFFER_DEVICE_ADDRESS_INFO;
		const void* next;
		vk::handle<vk::buffer> buffer;
	};

} // vk

static_assert(sizeof(vk::buffer_device_address_info) == sizeof(VkBufferDeviceAddressInfo));