#pragma once

#include "shader_group_type.hpp"

#include "vk/headers.hpp"

namespace vk {

	struct ray_tracing_shader_group_create_info {
		uint32 structure_type = VK_STRUCTURE_TYPE_RAY_TRACING_SHADER_GROUP_CREATE_INFO_KHR;
		const void* next;
		vk::ray_tracing_shader_group_type type;
		uint32 general_shader;
		uint32 closest_hot_shader;
		uint32 any_hit_shader;
		uint32 intersection_shader;
		const void* shader_group_capture_replay_handle_ptr;
	};

} // vk

static_assert(sizeof(vk::ray_tracing_shader_group_create_info) == sizeof(VkRayTracingShaderGroupCreateInfoKHR));