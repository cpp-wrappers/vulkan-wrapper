#pragma once

namespace vk {

	enum class filter {
		nearest = 0,
		linear  = 1,
		cubic   = 2
	};

	struct mag_filter { vk::filter _; };
	struct min_filter { vk::filter _; };

} // vk