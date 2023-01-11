#pragma once

#include "handle.hpp"
#include "geometry.hpp"
#include "type.hpp"
#include "build_mode.hpp"

#include <core/flag_enum.hpp>

namespace vk {

	enum class acceleration_structure_build_flag {
		allow_update      = 0x00000001,
		allow_compaction  = 0x00000002,
		prefer_fast_trace = 0x00000004,
		prefer_fast_build = 0x00000008,
		low_memory        = 0x00000010
	};

	using acceleration_structure_build_flags = flag_enum<vk::acceleration_structure_build_flag>;

	struct acceleration_structure_build_geometry_info {
		uint32 structure_type = 1000150000;
		const void* next = nullptr;
		vk::acceleration_structure_type type;
		vk::acceleration_structure_build_flags flags;
		vk::acceleration_structure_build_mode mode;
		handle<vk::acceleration_structure> src;
		handle<vk::acceleration_structure> dst;
		uint32 geometry_count;
		const vk::acceleration_structure_geometry* geometries;
		const vk::acceleration_structure_geometry* const* geometries_pointers;
		vk::device_or_host_address scratch_data;
	};

	namespace as {
		using build_flag = vk::acceleration_structure_build_flag;
		using build_flags = vk::acceleration_structure_build_flags;
		using build_geometry_info =
			vk::acceleration_structure_build_geometry_info;
	}

} // vk