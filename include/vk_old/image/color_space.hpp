#pragma once

namespace vk {

	enum class color_space {
		srgb_nonlinear          = 0,
		display_p3_nonlinear    = 1000104001,
		extended_srgb_linear    = 1000104002,
		display_p3_linear       = 1000104003,
		dci_p3_nonlinear        = 1000104004,
		bt709_linear            = 1000104005,
		bt709_nonlinear         = 1000104006,
		bt2020_linear           = 1000104007,
		hdr10_st2084            = 1000104008,
		dolbyvision             = 1000104009,
		hdr10_hlg               = 1000104010,
		adobergb_linear         = 1000104011,
		adobergb_nonlinear      = 1000104012,
		pass_through            = 1000104013,
		extended_srgb_nonlinear = 1000104014,
		display_native          = 1000213000
	}; // color_space

} // vk