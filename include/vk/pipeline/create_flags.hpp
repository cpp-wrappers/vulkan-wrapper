#pragma once

#include <core/flag_enum.hpp>

#include "vk/headers.hpp"

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

} // vk