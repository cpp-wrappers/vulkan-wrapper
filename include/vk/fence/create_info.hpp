#pragma once

#include <core/integer.hpp>
#include <core/flag_enum.hpp>

#include "../shared/headers.hpp"

namespace vk {

	enum class fence_create_flag {
		signaled = VK_FENCE_CREATE_SIGNALED_BIT
	};

	using fence_create_flags = flag_enum<vk::fence_create_flag>;

	struct fence_create_info {
		const uint32 type = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
		const void* next;
		vk::fence_create_flags flags;
	};

} // vk

static_assert(sizeof(vk::fence_create_info) == sizeof(VkFenceCreateInfo));