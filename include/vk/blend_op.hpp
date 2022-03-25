#pragma once

#include <core/wrapper/of.hpp>

namespace vk {

	enum class blend_op {
		add                = 0,
		subtract           = 1,
		reverse_subtract   = 2,
		min                = 3,
		max                = 4,
		zero               = 1000148000,
		src                = 1000148001,
		dst                = 1000148002,
		src_over           = 1000148003,
		dst_over           = 1000148004,
		src_in             = 1000148005,
		dst_in             = 1000148006,
		src_out            = 1000148007,
		dst_out            = 1000148008,
		src_atop           = 1000148009,
		dst_atop           = 1000148010,
		_xor               = 1000148011,
		multiply           = 1000148012,
		screen             = 1000148013,
		overlay            = 1000148014,
		darken             = 1000148015,
		lighten            = 1000148016,
		colordodge         = 1000148017,
		colorburn          = 1000148018,
		hardlight          = 1000148019,
		softlight          = 1000148020,
		difference         = 1000148021,
		exclusion          = 1000148022,
		invert             = 1000148023,
		invert_rgb         = 1000148024,
		lineardodge        = 1000148025,
		linearburn         = 1000148026,
		vividlight         = 1000148027,
		linearlight        = 1000148028,
		pinlight           = 1000148029,
		hardmix            = 1000148030,
		hsl_hue            = 1000148031,
		hsl_saturation     = 1000148032,
		hsl_color          = 1000148033,
		hsl_luminosity     = 1000148034,
		plus               = 1000148035,
		plus_clamped       = 1000148036,
		plus_clamped_alpha = 1000148037,
		plus_darker        = 1000148038,
		minus              = 1000148039,
		minus_clamped      = 1000148040,
		contrast           = 1000148041,
		invert_ovg         = 1000148042,
		red                = 1000148043,
		green              = 1000148044,
		blue               = 1000148045,
	};

	struct color_blend_op : wrapper::of<vk::blend_op, struct color_blend_op>{};
	struct alpha_blend_op : wrapper::of<vk::blend_op, struct alpha_blend_op>{};

} // vk