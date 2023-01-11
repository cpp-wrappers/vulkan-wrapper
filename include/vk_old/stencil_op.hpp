#pragma once

namespace vk {
	
	enum class stencil_op {
		keep                = 0,
		zero                = 1,
		replace             = 2,
		increment_and_clamp = 3,
		decrement_and_clamp = 4,
		invert              = 5,
		increment_and_wrap  = 6,
		decrement_and_wrap  = 7,
	};

} // vk