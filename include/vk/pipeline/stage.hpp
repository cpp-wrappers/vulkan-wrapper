#pragma once

#include <core/flag_enum.hpp>

namespace vk {

	enum class pipeline_stage {
		top_of_pipe                      = 0x00000001,
		draw_indirect                    = 0x00000002,
		vertex_input                     = 0x00000004,
		vertex_shader                    = 0x00000008,
		tessellation_control_shader      = 0x00000010,
		tessellation_evaluation_shader   = 0x00000020,
		geometry_shader                  = 0x00000040,
		fragment_shader                  = 0x00000080,
		early_fragment_tests             = 0x00000100,
		late_fragment_tests              = 0x00000200,
		color_attachment_output          = 0x00000400,
		compute_shader                   = 0x00000800,
		transfer                         = 0x00001000,
		bottom_of_pipe                   = 0x00002000,
		host                             = 0x00004000,
		all_graphics                     = 0x00008000,
		all_commands                     = 0x00010000,
		none                             = 0,
		transform_feedback               = 0x01000000,
		conditional_rendering            = 0x00040000,
		acceleration_structure_build     = 0x02000000,
		ray_tracing_shader               = 0x00200000,
		task_shader                      = 0x00080000,
		mesh_shader                      = 0x00100000,
		fragment_density_process         = 0x00800000,
		fragment_shading_rate_attachment = 0x00400000,
		command_preprocess               = 0x00020000
	};

	using pipeline_stages = flag_enum<pipeline_stage>;

	struct src_stages : pipeline_stages {};
	struct dst_stages : pipeline_stages {};

} // vk