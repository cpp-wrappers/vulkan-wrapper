#pragma once

#include "headers.hpp"
#include "device_size.hpp"

namespace vk {
	
	struct memory_size : vk::device_size {};

	constexpr inline vk::memory_size whole_size{ VK_WHOLE_SIZE };

} // vk