#pragma once

namespace vk {

	enum class pipeline_bind_point {
		graphics        = 0,
		compute         = 1,
		ray_tracing_khr = 1000165000,
		subpass_shading = 1000369003
	};

} // vk