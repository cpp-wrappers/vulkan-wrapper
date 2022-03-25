#pragma once

#include <core/wrapper/of.hpp>

namespace vk {

	enum class sampler_address_mode {
		repeat               = 0,
		mirrored_repeat      = 1,
		clamp_to_edge        = 2,
		clamp_to_border      = 3,
		mirror_clamp_to_edge = 4
	};

	using address_mode = vk::sampler_address_mode;

	struct address_mode_u :
		wrapper::of<vk::address_mode, struct address_mode_u_t>
	{};

	struct address_mode_v :
		wrapper::of<vk::address_mode, struct address_mode_v_t>
	{};

	struct address_mode_w :
		wrapper::of<vk::address_mode, struct address_mode_w_t>
	{};

} // vk