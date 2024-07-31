#pragma once

#include "../features.hpp"

namespace vk {

	struct physical_device_ray_tracing_pipeline_features :
		vk::physical_device_features_mark
	{
		uint32 struct_type = 1000347000;
		const void* next;
		uint32 ray_tracing_pipeline;
		uint32 ray_tracing_pipeline_shader_group_handle_capture_replay;
		uint32 ray_tracing_pipeline_shader_group_handle_capture_replay_mixed;
		uint32 ray_tracing_pipeline_trace_rays_indirect;
		uint32 ray_traversal_primitive_culling;
	};

} // vk