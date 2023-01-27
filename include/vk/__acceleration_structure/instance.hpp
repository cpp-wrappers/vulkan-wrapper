#pragma once

#include "handle.hpp"
#include "transform_matrix.hpp"
#include "geometry_instance_flags.hpp"

#include "../__internal/device_address.hpp"

namespace vk {

	struct acceleration_structure_instance {
		vk::transform_matrix transform;
		uint32 instance_custom_index : 24;
		uint32 mask : 8;
		uint32 instance_shader_binding_table_record_offset : 24;
		uint32 flags : 8;
		union {
			vk::device_address address;
			handle<vk::acceleration_structure> handle;
		} acceleration_structure_reference;
	};

	namespace as {
		using instance = vk::acceleration_structure_instance;
	}

} // vk