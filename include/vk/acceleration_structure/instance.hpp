#pragma once

#include "transform_matrix.hpp"
#include "geometry_instance_flags.hpp"

#include "vk/headers.hpp"

namespace vk {

	struct acceleration_structure_instance {
		vk::transform_matrix transform;
		uint32 instance_custom_index : 24;
		uint32 mask : 8;
		uint32 instance_shader_binding_table_record_offset : 24;
		uint32 flags : 8;
		uint64 acceleration_structure_reference;
	};

} // vk

static_assert(sizeof(vk::acceleration_structure_instance) == sizeof(VkAccelerationStructureInstanceKHR));