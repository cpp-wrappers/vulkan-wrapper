#pragma once

namespace vk {
	
	enum class border_color {
		float_transparent_black = 0,
		int_transparent_black   = 1,
		float_opaque_black      = 2,
		int_opaque_black        = 3,
		float_opaque_white      = 4,
		int_opaque_white        = 5,
		float_custom            = 1000287003,
		int_custom              = 1000287004,
	};

} // vk