#pragma once

#include "vk/headers.hpp"

namespace vk {

	enum class acceleration_structure_type {
		top_level = VK_ACCELERATION_STRUCTURE_TYPE_TOP_LEVEL_KHR,
		bottom_level = VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_KHR,
		generic = VK_ACCELERATION_STRUCTURE_TYPE_GENERIC_KHR
	};

}