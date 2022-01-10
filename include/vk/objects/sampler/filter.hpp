#pragma once

#include <core/wrapper/of.hpp>

#include "../../shared/headers.hpp"

namespace vk {

	enum class filter {
		nearest = VK_FILTER_NEAREST,
		linear = VK_FILTER_LINEAR,
		cubic_img = VK_FILTER_CUBIC_IMG,
		cubic_ext = VK_FILTER_CUBIC_EXT,
	};

	struct mag_filter : wrapper::of<filter, struct mag_filter_t> {};
	struct min_filter : wrapper::of<filter, struct min_filter_t> {};

} // vk