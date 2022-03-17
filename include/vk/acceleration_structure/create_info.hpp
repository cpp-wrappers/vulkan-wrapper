#pragma once

#include "type.hpp"

#include <core/flag_enum.hpp>

#include "vk/headers.hpp"
#include "vk/buffer/handle.hpp"
#include "vk/memory_size.hpp"
#include "vk/memory_offset.hpp"
#include "vk/device_address.hpp"

namespace vk {

	enum class acceleration_structure_create_flag {
		device_address_capture_replay = VK_ACCELERATION_STRUCTURE_CREATE_DEVICE_ADDRESS_CAPTURE_REPLAY_BIT_KHR
	};

	using acceleration_structure_create_flags = flag_enum<acceleration_structure_create_flag>;

	struct acceleration_structure_create_info {
		const uint32 __type = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_CREATE_INFO_KHR;
		const void* const __next;
		vk::acceleration_structure_create_flags flags;
		vk::handle<vk::buffer> buffer;
		vk::memory_offset offset;
		vk::memory_size size;
		vk::acceleration_structure_type type;
		vk::device_address device_address;
	};

	namespace as {
		using create_flag = vk::acceleration_structure_create_flag;
		using create_flags = vk::acceleration_structure_create_flags;
		using create_info = vk::acceleration_structure_create_info;
	}

} // vk

static_assert(sizeof(vk::acceleration_structure_create_info) == sizeof(VkAccelerationStructureCreateInfoKHR));