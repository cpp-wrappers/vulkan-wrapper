#pragma once

#include "handle.hpp"
#include "geometry_data.hpp"

#include "type.hpp"
#include "build_flags.hpp"
#include "build_mode.hpp"

#include "vk/headers.hpp"

namespace vk {

	struct acceleration_structure_build_geometry_info {
		const uint32 __type = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_GEOMETRY_INFO_KHR;
		const void* const __next;
		vk::acceleration_structure_type type;
		vk::acceleration_structure_build_flags flags;
		vk::acceleration_structure_build_mode mode;
		vk::handle<vk::acceleration_structure> src;
		vk::handle<vk::acceleration_structure> dst;
		uint32 geometry_count;
		const vk::acceleration_structure_geometry_data* geometries;
		const vk::acceleration_structure_geometry_data* const* geometries_pointers;
		vk::device_or_host_address scratch_data;
	};

} // vk

static_assert(sizeof(vk::acceleration_structure_build_geometry_info) == sizeof(VkAccelerationStructureBuildGeometryInfoKHR));