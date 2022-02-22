#pragma once

#include <core/wrapper/of.hpp>

#include "headers.hpp"

namespace vk {

	enum class blend_op {
		add = VK_BLEND_OP_ADD,
		subtract = VK_BLEND_OP_SUBTRACT,
		reverse_subtract = VK_BLEND_OP_REVERSE_SUBTRACT,
		min = VK_BLEND_OP_MIN,
		max = VK_BLEND_OP_MAX,
		zero_ext = VK_BLEND_OP_ZERO_EXT,
		src_ext = VK_BLEND_OP_SRC_EXT,
		dst_ext = VK_BLEND_OP_DST_EXT,
		src_over_ext = VK_BLEND_OP_SRC_OVER_EXT,
		dst_over_ext = VK_BLEND_OP_DST_OVER_EXT,
		src_in_ext = VK_BLEND_OP_SRC_IN_EXT,
		dst_in_ext = VK_BLEND_OP_DST_IN_EXT,
		src_out_ext = VK_BLEND_OP_SRC_OUT_EXT,
		dst_out_ext = VK_BLEND_OP_DST_OUT_EXT,
		src_atop_ext = VK_BLEND_OP_SRC_ATOP_EXT,
		dst_atop_ext = VK_BLEND_OP_DST_ATOP_EXT,
		xor_ext = VK_BLEND_OP_XOR_EXT,
		multiply_ext = VK_BLEND_OP_MULTIPLY_EXT,
		screen_ext = VK_BLEND_OP_SCREEN_EXT,
		overlay_ext = VK_BLEND_OP_OVERLAY_EXT,
		darken_ext = VK_BLEND_OP_DARKEN_EXT,
		lighten_ext = VK_BLEND_OP_LIGHTEN_EXT,
		colordodge_ext = VK_BLEND_OP_COLORDODGE_EXT,
		colorburn_ext = VK_BLEND_OP_COLORBURN_EXT,
		hardlight_ext = VK_BLEND_OP_HARDLIGHT_EXT,
		softlight_ext = VK_BLEND_OP_SOFTLIGHT_EXT,
		difference_ext = VK_BLEND_OP_DIFFERENCE_EXT,
		exclusion_ext = VK_BLEND_OP_EXCLUSION_EXT,
		invert_ext = VK_BLEND_OP_INVERT_EXT,
		invert_rgb_ext = VK_BLEND_OP_INVERT_RGB_EXT,
		lineardodge_ext = VK_BLEND_OP_LINEARDODGE_EXT,
		linearburn_ext = VK_BLEND_OP_LINEARBURN_EXT,
		vividlight_ext = VK_BLEND_OP_VIVIDLIGHT_EXT,
		linearlight_ext = VK_BLEND_OP_LINEARLIGHT_EXT,
		pinlight_ext = VK_BLEND_OP_PINLIGHT_EXT,
		hardmix_ext = VK_BLEND_OP_HARDMIX_EXT,
		hsl_hue_ext = VK_BLEND_OP_HSL_HUE_EXT,
		hsl_saturation_ext = VK_BLEND_OP_HSL_SATURATION_EXT,
		hsl_color_ext = VK_BLEND_OP_HSL_COLOR_EXT,
		hsl_luminosity_ext = VK_BLEND_OP_HSL_LUMINOSITY_EXT,
		plus_ext = VK_BLEND_OP_PLUS_EXT,
		plus_clamped_ext = VK_BLEND_OP_PLUS_CLAMPED_EXT,
		plus_clamped_alpha_ext = VK_BLEND_OP_PLUS_CLAMPED_ALPHA_EXT,
		plus_darker_ext = VK_BLEND_OP_PLUS_DARKER_EXT,
		minus_ext = VK_BLEND_OP_MINUS_EXT,
		minus_clamped_ext = VK_BLEND_OP_MINUS_CLAMPED_EXT,
		contrast_ext = VK_BLEND_OP_CONTRAST_EXT,
		invert_ovg_ext = VK_BLEND_OP_INVERT_OVG_EXT,
		red_ext = VK_BLEND_OP_RED_EXT,
		green_ext = VK_BLEND_OP_GREEN_EXT,
		blue_ext = VK_BLEND_OP_BLUE_EXT,
	};

	struct color_blend_op : wrapper::of<vk::blend_op, struct color_blend_op>{};
	struct alpha_blend_op : wrapper::of<vk::blend_op, struct alpha_blend_op>{};

} // vk