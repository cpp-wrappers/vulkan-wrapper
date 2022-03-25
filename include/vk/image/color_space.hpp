#pragma once

namespace vk {

	enum class color_space {
		srgb_nonlinear,
		display_p3_nonlinear_ext = 1000104001,
		extended_srgb_linear_ext,
		display_p3_linear_ext,
		dci_p3_nonlinear_ext,
		bt709_linear_ext,
		bt709_nonlinear_ext,
		bt2020_linear_ext,
		hdr10_st2084_ext,
		dolbyvision_ext,
		hdr10_hlg_ext,
		adobergb_linear_ext,
		adobergb_nonlinear_ext,
		pass_through_ext
	}; // color_space

} // vk