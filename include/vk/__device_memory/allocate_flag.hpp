#pragma once

#include <enum_flags.hpp>

namespace vk {

	enum class memory_allocate_flag {
		mask                   = 0x00000001,
		address                = 0x00000002,
		address_capture_replay = 0x00000004
	};

	using memory_allocate_flags = enum_flags<vk::memory_allocate_flag>;

} // vk