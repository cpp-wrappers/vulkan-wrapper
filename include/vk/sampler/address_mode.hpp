#pragma once

namespace vk {

	enum class sampler_address_mode {
		repeat               = 0,
		mirrored_repeat      = 1,
		clamp_to_edge        = 2,
		clamp_to_border      = 3,
		mirror_clamp_to_edge = 4
	};

	using address_mode = vk::sampler_address_mode;

	struct address_mode_u { vk::address_mode _; };
	struct address_mode_v { vk::address_mode _; };
	struct address_mode_w { vk::address_mode _; };

} // vk