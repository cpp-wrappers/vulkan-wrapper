#pragma once

#include <core/flag_enum.hpp>

#include "vk/headers.hpp"

namespace vk {

	enum class acceleration_structure_build_flag {
		allow_update = VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_UPDATE_BIT_KHR,
		allow_compaction = VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_COMPACTION_BIT_KHR,
		prefer_fast_trace = VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_TRACE_BIT_KHR,
		prefer_fast_build = VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_BUILD_BIT_KHR,
		low_memory = VK_BUILD_ACCELERATION_STRUCTURE_LOW_MEMORY_BIT_KHR
	};

	using acceleration_structure_build_flags = flag_enum<vk::acceleration_structure_build_flag>;

}