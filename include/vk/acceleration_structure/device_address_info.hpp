#pragma once

#include "vk/acceleration_structure/handle.hpp"

#include "vk/headers.hpp"

namespace vk {

	struct acceleration_structure_device_address_info {
		uint32 structure_type = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_DEVICE_ADDRESS_INFO_KHR;
		const void* next;
		handle<vk::acceleration_structure> acceleration_structure;
	};

	namespace as {
		using device_address_info = vk::acceleration_structure_device_address_info;
	}

} // vk

static_assert(sizeof(vk::acceleration_structure_device_address_info) == sizeof(VkAccelerationStructureDeviceAddressInfoKHR));