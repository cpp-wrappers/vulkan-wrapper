#pragma once

#include <core/integer.hpp>
#include <core/flag_enum.hpp>

#include "../render_pass/handle.hpp"
#include "../../shared/headers.hpp"
#include "../../shared/subpass.hpp"
#include "shader_stage_create_info.hpp"
#include "vertex_input_state/create_info.hpp"
#include "input_assembly_state_create_info.hpp"
#include "tesselation_state_create_info.hpp"
#include "viewport_state_create_info.hpp"
#include "rasterization_state_create_info.hpp"
#include "multisample_state_create_info.hpp"
#include "depth_stencil_state_create_info.hpp"
#include "color_blend_state_create_info.hpp"
#include "dynamic_state_create_info.hpp"
#include "layout/handle.hpp"
#include "handle.hpp"

namespace vk {

	enum class pipeline_create_flag {
		disable_optimization = VK_PIPELINE_CREATE_DISABLE_OPTIMIZATION_BIT,
		allow_derivatives = VK_PIPELINE_CREATE_ALLOW_DERIVATIVES_BIT,
		derivative = VK_PIPELINE_CREATE_DERIVATIVE_BIT,
		view_index_from_device_index = VK_PIPELINE_CREATE_VIEW_INDEX_FROM_DEVICE_INDEX_BIT,
		dispatch_base = VK_PIPELINE_CREATE_DISPATCH_BASE_BIT,
		ray_tracing_no_null_any_hit_shaders = VK_PIPELINE_CREATE_RAY_TRACING_NO_NULL_ANY_HIT_SHADERS_BIT_KHR,
		ray_tracing_no_null_closest_hit_shaders = VK_PIPELINE_CREATE_RAY_TRACING_NO_NULL_CLOSEST_HIT_SHADERS_BIT_KHR,
		ray_tracing_no_null_miss_shaders = VK_PIPELINE_CREATE_RAY_TRACING_NO_NULL_MISS_SHADERS_BIT_KHR,
		ray_tracing_no_null_intersection_shaders = VK_PIPELINE_CREATE_RAY_TRACING_NO_NULL_INTERSECTION_SHADERS_BIT_KHR,
		ray_tracing_skip_triangles = VK_PIPELINE_CREATE_RAY_TRACING_SKIP_TRIANGLES_BIT_KHR,
		ray_tracing_skip_aabbs = VK_PIPELINE_CREATE_RAY_TRACING_SKIP_AABBS_BIT_KHR,
		//ray_tracing_shader_group_handle_capture_replay = VK_PIPELINE_CREATE_RAY_TRACING_SHADER_GROUP_HANDLE_CAPTURE_REPLAY_BIT_KHR,
		defer_compile = VK_PIPELINE_CREATE_DEFER_COMPILE_BIT_NV,
		capture_statistics = VK_PIPELINE_CREATE_CAPTURE_STATISTICS_BIT_KHR,
		capture_internal_representations = VK_PIPELINE_CREATE_CAPTURE_INTERNAL_REPRESENTATIONS_BIT_KHR,
		indirect_bindable = VK_PIPELINE_CREATE_INDIRECT_BINDABLE_BIT_NV,
		library = VK_PIPELINE_CREATE_LIBRARY_BIT_KHR,
		fail_on_pipeline_compile_required = VK_PIPELINE_CREATE_FAIL_ON_PIPELINE_COMPILE_REQUIRED_BIT_EXT,
		early_return_on_failure = VK_PIPELINE_CREATE_EARLY_RETURN_ON_FAILURE_BIT_EXT,
		//ray_tracing_allow_motion = VK_PIPELINE_CREATE_RAY_TRACING_ALLOW_MOTION_BIT_NV
	};

	using pipeline_create_flags = flag_enum<vk::pipeline_create_flag>;

	struct graphics_pipeline_create_info {
		const uint32 type = (uint32) VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
		const void* next;
		vk::pipeline_create_flags flags;
		uint32 stage_count;
		const vk::pipeline_shader_stage_create_info* stages;
		const vk::pipeline_vertex_input_state_create_info* vertex_input_state;
		const vk::pipeline_input_assembly_state_create_info* input_assembly_state;
		const vk::pipeline_tesselation_state_create_info* tesselation_state;
		const vk::pipeline_viewport_state_create_info* viewport_state;
		const vk::pipeline_rasterization_state_create_info* rasterization_state;
		const vk::pipeline_multisample_state_create_info* multisample_state;
		const vk::pipeline_depth_stencil_state_create_info* depth_stencil_state;
		const vk::pipeline_color_blend_state_create_info* color_blend_state;
		const vk::pipeline_dynamic_state_create_info* dynamic_state;
		vk::handle<vk::pipeline_layout> layout;
		vk::handle<vk::render_pass> render_pass;
		vk::subpass subpass;
		vk::handle<vk::pipeline> base_pipeline;
		int32 base_pipeline_index;
	};
}

static_assert(sizeof(vk::graphics_pipeline_create_info) == sizeof(VkGraphicsPipelineCreateInfo));