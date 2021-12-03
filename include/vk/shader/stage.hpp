#pragma once

#include "../shared/headers.hpp"

namespace vk {

	enum class shader_stage {
		vertex = VK_SHADER_STAGE_VERTEX_BIT,
		tessellation_control = VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT,
		tessellation_evaluation = VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT,
		geometry = VK_SHADER_STAGE_GEOMETRY_BIT,
		fragment = VK_SHADER_STAGE_FRAGMENT_BIT,
		compute = VK_SHADER_STAGE_COMPUTE_BIT,
		all_graphics = VK_SHADER_STAGE_ALL_GRAPHICS,
		all = VK_SHADER_STAGE_ALL,
		raygen = VK_SHADER_STAGE_RAYGEN_BIT_KHR,
		any_hit = VK_SHADER_STAGE_ANY_HIT_BIT_KHR,
		closest_hit = VK_SHADER_STAGE_CLOSEST_HIT_BIT_KHR,
		miss = VK_SHADER_STAGE_MISS_BIT_KHR,
		intersection = VK_SHADER_STAGE_INTERSECTION_BIT_KHR,
		callable = VK_SHADER_STAGE_CALLABLE_BIT_KHR,
		task = VK_SHADER_STAGE_TASK_BIT_NV,
		mesh = VK_SHADER_STAGE_MESH_BIT_NV,
		subpass_shading = VK_SHADER_STAGE_SUBPASS_SHADING_BIT_HUAWEI
	};

} // vk