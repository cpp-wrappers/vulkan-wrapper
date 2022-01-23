#pragma once

#include <core/flag_enum.hpp>
#include "../headers.hpp"

namespace vk {

	enum class pipeline_stage {
		top_of_pipe = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT,
		draw_indirect = VK_PIPELINE_STAGE_DRAW_INDIRECT_BIT,
		vertex_input = VK_PIPELINE_STAGE_VERTEX_INPUT_BIT,
		vertex_shader = VK_PIPELINE_STAGE_VERTEX_SHADER_BIT,
		tessellation_control_shader = VK_PIPELINE_STAGE_TESSELLATION_CONTROL_SHADER_BIT,
		tessellation_evaluation_shader = VK_PIPELINE_STAGE_TESSELLATION_EVALUATION_SHADER_BIT,
		geometry_shader = VK_PIPELINE_STAGE_GEOMETRY_SHADER_BIT,
		fragment_shader = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT,
		early_fragment_tests = VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT,
		late_fragment_tests = VK_PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT,
		color_attachment_output = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
		compute_shader = VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT,
		transfer = VK_PIPELINE_STAGE_TRANSFER_BIT,
		bottom_of_pipe = VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT,
		host = VK_PIPELINE_STAGE_HOST_BIT,
		all_graphics = VK_PIPELINE_STAGE_ALL_GRAPHICS_BIT,
		all_commands = VK_PIPELINE_STAGE_ALL_COMMANDS_BIT,
		transform_feedback = VK_PIPELINE_STAGE_TRANSFORM_FEEDBACK_BIT_EXT,
		conditional_rendering = VK_PIPELINE_STAGE_CONDITIONAL_RENDERING_BIT_EXT,
		acceleration_structure_build = VK_PIPELINE_STAGE_ACCELERATION_STRUCTURE_BUILD_BIT_KHR,
		ray_tracing_shader = VK_PIPELINE_STAGE_RAY_TRACING_SHADER_BIT_KHR,
		task_shader = VK_PIPELINE_STAGE_TASK_SHADER_BIT_NV,
		mesh_shader = VK_PIPELINE_STAGE_MESH_SHADER_BIT_NV,
		fragment_density_process = VK_PIPELINE_STAGE_FRAGMENT_DENSITY_PROCESS_BIT_EXT,
		fragment_shading_rate_attachment = VK_PIPELINE_STAGE_FRAGMENT_SHADING_RATE_ATTACHMENT_BIT_KHR,
		command_preprocess = VK_PIPELINE_STAGE_COMMAND_PREPROCESS_BIT_NV,
		//none = VK_PIPELINE_STAGE_NONE_KHR,
		//shading_rate_image = VK_PIPELINE_STAGE_SHADING_RATE_IMAGE_BIT_NV
	};


	using pipeline_stages = flag_enum<pipeline_stage>;

	struct src_stages : pipeline_stages {};
	struct dst_stages : pipeline_stages {};

} // vk