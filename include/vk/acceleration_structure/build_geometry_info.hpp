#pragma once

#include "handle.hpp"
#include "geometry.hpp"
#include "type.hpp"
#include "build_mode.hpp"

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

	struct acceleration_structure_build_geometry_info {
		uint32 structure_type = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_BUILD_GEOMETRY_INFO_KHR;
		const void* next = nullptr;
		vk::acceleration_structure_type type;
		vk::acceleration_structure_build_flags flags;
		vk::acceleration_structure_build_mode mode;
		vk::handle<vk::acceleration_structure> src;
		vk::handle<vk::acceleration_structure> dst;
		uint32 geometry_count;
		const vk::acceleration_structure_geometry* geometries;
		const vk::acceleration_structure_geometry* const* geometries_pointers;
		vk::device_or_host_address scratch_data;
	};

	namespace as {
		using build_flag = vk::acceleration_structure_build_flag;
		using build_flags = vk::acceleration_structure_build_flags;
		using build_geometry_info = vk::acceleration_structure_build_geometry_info;
	}

} // vk

static_assert(sizeof(vk::acceleration_structure_build_geometry_info) == sizeof(VkAccelerationStructureBuildGeometryInfoKHR));