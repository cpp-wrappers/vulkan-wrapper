#pragma once

#include "vk/headers.hpp"

namespace vk {

	enum class ray_tracing_shader_group_type {
		general = VK_RAY_TRACING_SHADER_GROUP_TYPE_GENERAL_KHR,
		triangles_hit_group = VK_RAY_TRACING_SHADER_GROUP_TYPE_TRIANGLES_HIT_GROUP_KHR,
		procedural_hit_group = VK_RAY_TRACING_SHADER_GROUP_TYPE_PROCEDURAL_HIT_GROUP_KHR,
	};

} // vk