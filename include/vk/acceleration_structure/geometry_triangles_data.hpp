#pragma once

#include "vk/headers.hpp"
#include "vk/format.hpp"
#include "vk/device_or_host_address.hpp"
#include "vk/device_size.hpp"
#include "vk/index_type.hpp"

namespace vk {

	struct acceleration_structure_geometry_triangles_data {
		uint32 __type = VK_STRUCTURE_TYPE_ACCELERATION_STRUCTURE_GEOMETRY_TRIANGLES_DATA_KHR;
		const void* next;
		vk::format format;
		vk::device_or_host_address vertex_data;
		vk::device_size vertex_stride;
		uint32 max_vertex;
		vk::index_type index_type;
		vk::device_or_host_address index_data;
		vk::device_or_host_address transform_data;
	};

} // vk

static_assert(sizeof(vk::acceleration_structure_geometry_triangles_data) == sizeof(VkAccelerationStructureGeometryTrianglesDataKHR));