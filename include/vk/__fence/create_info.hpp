#pragma once

#include <core/integer.hpp>
#include <core/flag_enum.hpp>

namespace vk {

	enum class fence_create_flag {
		signaled = 0x00000001
	};

	using fence_create_flags = flag_enum<vk::fence_create_flag>;

	struct fence_create_info {
		uint32                 structure_type = 8;
		const void*            next;
		vk::fence_create_flags flags;
	};

} // vk