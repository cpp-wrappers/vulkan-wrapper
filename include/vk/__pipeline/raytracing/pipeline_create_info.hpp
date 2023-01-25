#pragma once

#include "./shader_group_create_info.hpp"
#include "./pipeline_interface_create_info.hpp"

#include "../create_flags.hpp"
#include "../shader_stage_create_info.hpp"
#include "../library_create_info.hpp"
#include "../dynamic_state_create_info.hpp"
#include "../../__pipeline_layout/handle.hpp"

namespace vk {

	struct ray_tracing_pipeline_create_info {
		uint32                      structure_type = 1000150015;
		const void*                 next = nullptr;
		vk::pipeline_create_flags   flags;
		uint32                      stage_count;
		const vk::pipeline_shader_stage_create_info*
		                            stages;
		uint32                      group_count;
		const vk::ray_tracing_shader_group_create_info group;
		uint32                      max_pipeline_ray_recursion_depth;
		const vk::pipeline_library_create_info*
		                            library_info;
		const vk::ray_tracing_pipeline_interface_create_info*
		                            library_interface;
		const vk::pipeline_dynamic_state_create_info
		                            dynamic_state;
		handle<vk::pipeline_layout>::underlying_type
		                            layout;
		handle<vk::pipeline>::underlying_type
		                            base_pipeline;
		uint32                      base_pipeline_index;
	};

} // vk