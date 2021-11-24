#pragma once

namespace vk {
	enum class query_pipeline_statistics {
		input_assembly_vertices                    = 1<<0,
		input_assembly_primitives                  = 1<<1,
		vertex_shader_invocations                  = 1<<2,
		geometry_shader_invocations                = 1<<3,
		geometry_shader_primitives                 = 1<<4,
		clipping_invocations                       = 1<<5,
		clipping_primitives                        = 1<<6,
		fragment_shader_invocations                = 1<<7,
		tessellation_control_shader_patches        = 1<<8,
		tessellation_evaluation_shader_invocations = 1<<9,
		compute_shader_invocations                 = 1<<10,
	};
}