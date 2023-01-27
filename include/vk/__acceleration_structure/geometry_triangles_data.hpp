#pragma once

#include "../__internal/format.hpp"
#include "../__internal/device_or_host_address.hpp"
#include "../__internal/device_size.hpp"
#include "../__internal/index_type.hpp"

namespace vk {

	struct acceleration_structure_geometry_triangles_data {
		uint32 structure_type = 1000150005;
		const void* next;
		vk::format format;
		vk::device_or_host_address vertex_data;
		vk::device_size vertex_stride;
		uint32 max_vertex;
		vk::index_type index_type;
		vk::device_or_host_address index_data;
		vk::device_or_host_address transform_data;
	};

	namespace as {
		using geometry_triangles_data =
			vk::acceleration_structure_geometry_triangles_data;
	}

} // vk