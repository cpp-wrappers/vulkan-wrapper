#pragma once

#include <core/wrapper/of.hpp>

#include "../../shared/headers.hpp"

namespace vk {

	enum class sampler_address_mode {
		repeat = VK_SAMPLER_ADDRESS_MODE_REPEAT,
		mirrored_repeat = VK_SAMPLER_ADDRESS_MODE_MIRRORED_REPEAT,
		clamp_to_edge = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE,
		clamp_to_border = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_BORDER,
		mirror_clamp_to_edge = VK_SAMPLER_ADDRESS_MODE_MIRROR_CLAMP_TO_EDGE,
		mirror_clamp_to_edge_khr = VK_SAMPLER_ADDRESS_MODE_MIRROR_CLAMP_TO_EDGE_KHR,
	};

	using address_mode = vk::sampler_address_mode;

	struct address_mode_u : wrapper::of<vk::address_mode, struct address_mode_u_t> {};
	struct address_mode_v : wrapper::of<vk::address_mode, struct address_mode_v_t> {};
	struct address_mode_w : wrapper::of<vk::address_mode, struct address_mode_w_t> {};

} // vk