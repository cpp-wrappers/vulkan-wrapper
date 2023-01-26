#pragma once

#include "./handle.hpp"
#include "./create_flags.hpp"
#include "./shader_stage_create_info.hpp"
#include "./vertex_input_state/create_info.hpp"
#include "./input_assembly_state_create_info.hpp"
#include "./tesselation_state_create_info.hpp"
#include "./viewport_state_create_info.hpp"
#include "./rasterization_state_create_info.hpp"
#include "./multisample_state_create_info.hpp"
#include "./depth_stencil_state_create_info.hpp"
#include "./color_blend_state_create_info.hpp"
#include "./dynamic_state_create_info.hpp"
#include "./../__pipeline_layout/handle.hpp"
#include "../__render_pass/handle.hpp"
#include "../__internal/subpass.hpp"

namespace vk {

	struct graphics_pipeline_create_info {
		uint32 structure_type = 28;
		const void* next;
		vk::pipeline_create_flags flags;
		uint32 stage_count;
		const vk::pipeline_shader_stage_create_info* stages;
		const vk::pipeline_vertex_input_state_create_info* vertex_input_state;
		const vk::pipeline_input_assembly_state_create_info*
			input_assembly_state;
		const vk::pipeline_tesselation_state_create_info* tesselation_state;
		const vk::pipeline_viewport_state_create_info* viewport_state;
		const vk::pipeline_rasterization_state_create_info* rasterization_state;
		const vk::pipeline_multisample_state_create_info* multisample_state;
		const vk::pipeline_depth_stencil_state_create_info* depth_stencil_state;
		const vk::pipeline_color_blend_state_create_info* color_blend_state;
		const vk::pipeline_dynamic_state_create_info* dynamic_state;
		handle<vk::pipeline_layout>::underlying_type layout;
		handle<vk::render_pass>::underlying_type render_pass;
		vk::subpass subpass;
		handle<vk::pipeline>::underlying_type base_pipeline;
		int32 base_pipeline_index;
	};

} // vk