#pragma once

#include <core/wrapper/of.hpp>

namespace vk {

	enum class filter {
		nearest = 0,
		linear  = 1,
		cubic   = 2
	};

	struct mag_filter : wrapper::of<filter, struct mag_filter_t> {};
	struct min_filter : wrapper::of<filter, struct min_filter_t> {};

} // vk