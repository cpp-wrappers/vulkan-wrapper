#pragma once

#include "vk/headers.hpp"

namespace vk {
	
	enum class border_color {
		float_transparent_black = VK_BORDER_COLOR_FLOAT_TRANSPARENT_BLACK,
		int_transparent_black = VK_BORDER_COLOR_INT_TRANSPARENT_BLACK,
		float_opaque_black = VK_BORDER_COLOR_FLOAT_OPAQUE_BLACK,
		int_opaque_black = VK_BORDER_COLOR_INT_OPAQUE_BLACK,
		float_opaque_white = VK_BORDER_COLOR_FLOAT_OPAQUE_WHITE,
		int_opaque_white = VK_BORDER_COLOR_INT_OPAQUE_WHITE,
		float_custom_ext = VK_BORDER_COLOR_FLOAT_CUSTOM_EXT,
		int_custom_ext = VK_BORDER_COLOR_INT_CUSTOM_EXT,
	};

} // vk