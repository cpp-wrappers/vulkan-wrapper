#pragma once

#include "headers.hpp"

namespace vk {

	enum class dynamic_state {
		viewport = VK_DYNAMIC_STATE_VIEWPORT,
		scissor = VK_DYNAMIC_STATE_SCISSOR,
		line_width = VK_DYNAMIC_STATE_LINE_WIDTH,
		depth_bias = VK_DYNAMIC_STATE_DEPTH_BIAS,
		blend_constants = VK_DYNAMIC_STATE_BLEND_CONSTANTS,
		depth_bounds = VK_DYNAMIC_STATE_DEPTH_BOUNDS,
		stencil_compare_mask = VK_DYNAMIC_STATE_STENCIL_COMPARE_MASK,
		stencil_write_mask = VK_DYNAMIC_STATE_STENCIL_WRITE_MASK,
		stencil_reference = VK_DYNAMIC_STATE_STENCIL_REFERENCE,
		viewport_w_scaling_nv = VK_DYNAMIC_STATE_VIEWPORT_W_SCALING_NV,
		discard_rectangle_ext = VK_DYNAMIC_STATE_DISCARD_RECTANGLE_EXT,
		sample_locations_ext = VK_DYNAMIC_STATE_SAMPLE_LOCATIONS_EXT,
		//ray_tracing_pipeline_stack_size_khr = VK_DYNAMIC_STATE_RAY_TRACING_PIPELINE_STACK_SIZE_KHR,
		viewport_shading_rate_palette_nv = VK_DYNAMIC_STATE_VIEWPORT_SHADING_RATE_PALETTE_NV,
		viewport_coarse_sample_order_nv = VK_DYNAMIC_STATE_VIEWPORT_COARSE_SAMPLE_ORDER_NV,
		exclusive_scissor_nv = VK_DYNAMIC_STATE_EXCLUSIVE_SCISSOR_NV,
		fragment_shading_rate_khr = VK_DYNAMIC_STATE_FRAGMENT_SHADING_RATE_KHR,
		line_stipple_ext = VK_DYNAMIC_STATE_LINE_STIPPLE_EXT,
		cull_mode_ext = VK_DYNAMIC_STATE_CULL_MODE_EXT,
		front_face_ext = VK_DYNAMIC_STATE_FRONT_FACE_EXT,
		primitive_topology_ext = VK_DYNAMIC_STATE_PRIMITIVE_TOPOLOGY_EXT,
		viewport_with_count_ext = VK_DYNAMIC_STATE_VIEWPORT_WITH_COUNT_EXT,
		scissor_with_count_ext = VK_DYNAMIC_STATE_SCISSOR_WITH_COUNT_EXT,
		vertex_input_binding_stride_ext = VK_DYNAMIC_STATE_VERTEX_INPUT_BINDING_STRIDE_EXT,
		depth_test_enable_ext = VK_DYNAMIC_STATE_DEPTH_TEST_ENABLE_EXT,
		//depth_write_enable_ext = VK_DYNAMIC_STATE_DEPTH_WRITE_ENABLE_EXT,
		//depth_compare_op_ext = VK_DYNAMIC_STATE_DEPTH_COMPARE_OP_EXT,
		depth_bounds_test_enable_ext = VK_DYNAMIC_STATE_DEPTH_BOUNDS_TEST_ENABLE_EXT,
		//stencil_test_enable_ext = VK_DYNAMIC_STATE_STENCIL_TEST_ENABLE_EXT,
		//stencil_op_ext = VK_DYNAMIC_STATE_STENCIL_OP_EXT,
		//vertex_input_ext = VK_DYNAMIC_STATE_VERTEX_INPUT_EXT,
		//patch_control_points_ext = VK_DYNAMIC_STATE_PATCH_CONTROL_POINTS_EXT,
		//rasterizer_discard_enable_ext = VK_DYNAMIC_STATE_RASTERIZER_DISCARD_ENABLE_EXT,
		//depth_bias_enable_ext = VK_DYNAMIC_STATE_DEPTH_BIAS_ENABLE_EXT,
		//logic_op_ext = VK_DYNAMIC_STATE_LOGIC_OP_EXT,
		//primitive_restart_enable_ext = VK_DYNAMIC_STATE_PRIMITIVE_RESTART_ENABLE_EXT,
		//color_write_enable_ext = VK_DYNAMIC_STATE_COLOR_WRITE_ENABLE_EXT
	};
}