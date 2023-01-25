#pragma once

namespace vk {

	enum class ray_tracing_shader_group_type {
		general              = 0,
		triangles_hit_group  = 1,
		procedural_hit_group = 2,
	};

} // vk