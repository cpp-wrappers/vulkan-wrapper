#pragma once

#include "vk/headers.hpp"
#include "vk/device_size.hpp"

namespace vk {

	struct acceleration_structure_build_sizes_info {
		uint32 __type = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_SIZES_INFO_KHR;
		const void* next = nullptr;
		vk::device_size acceleration_structure_size;
		vk::device_size update_scratch_size;
		vk::device_size build_scratch_size;
	};

} // vk

static_assert(sizeof(vk::acceleration_structure_build_sizes_info) == sizeof(VkAccelerationStructureBuildSizesInfoKHR));