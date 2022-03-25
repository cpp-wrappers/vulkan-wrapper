#pragma once

#include <core/wrapper/of.hpp>

namespace vk {

	enum class blend_factor {
		zero                     = 0,
		one                      = 1,
		src_color                = 2,
		one_minus_src_color      = 3,
		dst_color                = 4,
		one_minus_dst_color      = 5,
		src_alpha                = 6,
		one_minus_src_alpha      = 7,
		dst_alpha                = 8,
		one_minus_dst_alpha      = 9,
		constant_color           = 10,
		one_minus_constant_color = 11,
		constant_alpha           = 12,
		one_minus_constant_alpha = 13,
		src_alpha_saturate       = 14,
		src1_color               = 15,
		one_minus_src1_color     = 16,
		src1_alpha               = 17,
		one_minus_src1_alpha     = 18,
	};

	struct src_color_blend_factor : wrapper::of<vk::blend_factor, struct src_color_blend_factor_t>{};
	struct dst_color_blend_factor : wrapper::of<vk::blend_factor, struct dst_color_blend_factor_t>{};

	struct src_alpha_blend_factor : wrapper::of<vk::blend_factor, struct src_alpha_blend_factor_t>{};
	struct dst_alpha_blend_factor : wrapper::of<vk::blend_factor, struct dst_alpha_blend_factor_t>{};

} // vk