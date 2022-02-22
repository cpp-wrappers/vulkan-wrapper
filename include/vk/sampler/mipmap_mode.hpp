#pragma once

#include "vk/headers.hpp"

namespace vk {

	enum class sampler_mipmap_mode {
		nearest = VK_SAMPLER_MIPMAP_MODE_NEAREST,
		linear = VK_SAMPLER_MIPMAP_MODE_LINEAR,
	};

	using mipmap_mode = vk::sampler_mipmap_mode;

} // vk