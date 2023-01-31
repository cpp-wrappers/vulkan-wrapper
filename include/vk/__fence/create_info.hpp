#pragma once

#include <integer.hpp>
#include <enum_flags.hpp>

namespace vk {

	enum class fence_create_flag {
		signaled = 0x00000001
	};

	using fence_create_flags = enum_flags<vk::fence_create_flag>;

	struct fence_create_info {
		uint32                 structure_type = 8;
		const void*            next;
		vk::fence_create_flags flags;
	};

} // vk