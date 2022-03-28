#pragma once

#include <core/integer.hpp>

namespace vk {

	struct ray_tracing_pipeline_interface_create_info {
		uint32 structure_type = 1000150018;
		const void* next = nullptr;
		uint32 max_pipeline_ray_payload_size;
		uint32 max_pipeline_ray_hit_attribute_size;
	};

} // vk