#pragma once

#include "headers.hpp"

namespace vk {

enum class color_space {
	srgb_nonlinear = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR,
	display_p3_nonlinear_ext = VK_COLOR_SPACE_DISPLAY_P3_NONLINEAR_EXT,
	extended_srgb_linear_ext  = VK_COLOR_SPACE_EXTENDED_SRGB_LINEAR_EXT,
	display_p3_linear_ext  = VK_COLOR_SPACE_DISPLAY_P3_LINEAR_EXT,
	dci_p3_nonlinear_ext  = VK_COLOR_SPACE_DCI_P3_NONLINEAR_EXT,
	bt709_linear_ext  = VK_COLOR_SPACE_BT709_LINEAR_EXT,
	bt709_nonlinear_ext  = VK_COLOR_SPACE_BT709_NONLINEAR_EXT,
	bt2020_linear_ext  = VK_COLOR_SPACE_BT2020_LINEAR_EXT,
	hdr10_st2084_ext  = VK_COLOR_SPACE_HDR10_ST2084_EXT,
	dolbyvision_ext  = VK_COLOR_SPACE_DOLBYVISION_EXT,
	hdr10_hlg_ext  = VK_COLOR_SPACE_HDR10_HLG_EXT,
	adobergb_linear_ext  = VK_COLOR_SPACE_ADOBERGB_LINEAR_EXT,
	adobergb_nonlinear_ext  = VK_COLOR_SPACE_ADOBERGB_NONLINEAR_EXT,
	pass_through_ext  = VK_COLOR_SPACE_PASS_THROUGH_EXT,
	extended_srgb_nonlinear_ext  = VK_COLOR_SPACE_EXTENDED_SRGB_NONLINEAR_EXT,
	display_native_amd  = VK_COLOR_SPACE_DISPLAY_NATIVE_AMD,
	srgb_nonlinear_khr = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR,
	dci_p3_linear_ext = VK_COLOR_SPACE_DISPLAY_P3_LINEAR_EXT,
}; // color_space

} // vk