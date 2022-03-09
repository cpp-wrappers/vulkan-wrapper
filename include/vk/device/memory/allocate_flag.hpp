#pragma once

#include <core/flag_enum.hpp>

#include "vk/headers.hpp"

namespace vk {

	enum class memory_allocate_flag {
		mask = VK_MEMORY_ALLOCATE_DEVICE_MASK_BIT,
		address = VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_BIT,
		address_capture_replay = VK_MEMORY_ALLOCATE_DEVICE_ADDRESS_CAPTURE_REPLAY_BIT
	};

	using memory_allocate_flags = flag_enum<vk::memory_allocate_flag>;

} // vk