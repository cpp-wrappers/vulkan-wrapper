#pragma once

namespace vk {

	enum class dynamic_state {
		viewport                        = 0,
		scissor                         = 1,
		line_width                      = 2,
		depth_bias                      = 3,
		blend_constants                 = 4,
		depth_bounds                    = 5,
		stencil_compare_mask            = 6,
		stencil_write_mask              = 7,
		stencil_reference               = 8,
		cull_mode                       = 1000267000,
		front_face                      = 1000267001,
		primitive_topology              = 1000267002,
		viewport_with_count             = 1000267003,
		scissor_with_count              = 1000267004,
		vertex_input_binding_stride     = 1000267005,
		depth_test_enable               = 1000267006,
		depth_write_enable              = 1000267007,
		depth_compare_op                = 1000267008,
		depth_bounds_test_enable        = 1000267009,
		stencil_test_enable             = 1000267010,
		stencil_op                      = 1000267011,
		rasterizer_discard_enable       = 1000377001,
		depth_bias_enable               = 1000377002,
		primitive_restart_enable        = 1000377004,
		viewport_w_scaling              = 1000087000,
		discard_rectangle               = 1000099000,
		sample_locations                = 1000143000,
		ray_tracing_pipeline_stack_size = 1000347000,
		viewport_shading_rate_palette   = 1000164004,
		viewport_coarse_sample_order    = 1000164006,
		exclusive_scissor               = 1000205001,
		fragment_shading_rate           = 1000226000,
		line_stipple                    = 1000259000,
		vertex_input                    = 1000352000,
		patch_control_points            = 1000377000,
		logic_op                        = 1000377003,
		color_write_enable              = 1000381000
	}; // dynamic_state

} // vk