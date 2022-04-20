#pragma once

#include "device_size.hpp"

namespace vk {
	
	struct memory_size { vk::device_size _; };

	constexpr inline vk::memory_size whole_size{ ~0ULL };

} // vk