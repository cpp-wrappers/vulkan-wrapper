#pragma once

#include "vk/headers.hpp"

namespace vk {

	struct ray_tracing_pipeline_interface_create_info {
		uint32 structure_type = VK_STRUCTURE_TYPE_RAY_TRACING_PIPELINE_INTERFACE_CREATE_INFO_KHR;
		const void* next;
		uint32 max_pipeline_ray_payload_size;
		uint32 max_pipeline_ray_hit_attribute_size;
	};

} // vk

static_assert(sizeof(vk::ray_tracing_pipeline_interface_create_info) == sizeof(VkRayTracingPipelineInterfaceCreateInfoKHR));