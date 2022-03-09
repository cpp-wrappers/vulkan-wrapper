#pragma once

#include "vk/headers.hpp"
#include "vk/physical_device/features.hpp"

namespace vk {

	struct physical_device_ray_tracing_pipeline_features : vk::physical_device_features_marker {
		uint32 __type = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_RAY_TRACING_PIPELINE_FEATURES_KHR;
		const void* next;
		uint32 ray_tracing_pipeline;
		uint32 ray_tracing_pipeline_shader_group_handle_capture_replay;
		uint32 ray_tracing_pipeline_shader_group_handle_capture_replay_mixed;
		uint32 ray_tracing_pipeline_trace_rays_indirect;
		uint32 ray_traversal_primitive_culling;
	};

} // vk

static_assert(sizeof(vk::physical_device_ray_tracing_pipeline_features) == sizeof(VkPhysicalDeviceRayTracingPipelineFeaturesKHR));