#pragma once

#include "shader_group_create_info.hpp"
#include "pipeline_interface_create_info.hpp"

#include "vk/headers.hpp"
#include "vk/pipeline/create_info.hpp"
#include "vk/pipeline/handle.hpp"
#include "vk/pipeline/shader_stage_create_info.hpp"
#include "vk/pipeline/library_create_info.hpp"
#include "vk/pipeline/dynamic_state_create_info.hpp"
#include "vk/pipeline/layout/handle.hpp"

namespace vk {

	struct ray_tracing_pipeline_create_info {
		uint32 structure_type = VK_STRUCTURE_TYPE_RAY_TRACING_PIPELINE_CREATE_INFO_KHR;
		const void* next;
		vk::pipeline_create_flags flags;
		uint32 stage_count;
		const vk::pipeline_shader_stage_create_info* stages;
		uint32 group_count;
		const vk::ray_tracing_shader_group_create_info group;
		uint32 max_pipeline_ray_recursion_depth;
		const vk::pipeline_library_create_info* library_info;
		const vk::ray_tracing_pipeline_interface_create_info* library_interface;
		const vk::pipeline_dynamic_state_create_info dynamic_state;
		handle<vk::pipeline_layout> layout;
		handle<vk::pipeline> base_pipeline;
		uint32 base_pipeline_index;
	};

} // vk

static_assert(sizeof(vk::ray_tracing_pipeline_interface_create_info) == sizeof(VkRayTracingPipelineInterfaceCreateInfoKHR));