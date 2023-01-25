#pragma once

namespace vk {

	enum class sampler_mipmap_mode {
		nearest = 0,
		linear  = 1,
	};

	using mipmap_mode = vk::sampler_mipmap_mode;

} // vk