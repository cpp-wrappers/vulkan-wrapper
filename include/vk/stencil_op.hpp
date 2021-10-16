#pragma once

#include "headers.hpp"

namespace vk {
	
	enum class stencil_op {
		keep = VK_STENCIL_OP_KEEP,
		zero = VK_STENCIL_OP_ZERO,
		replace = VK_STENCIL_OP_REPLACE,
		increment_and_clamp = VK_STENCIL_OP_INCREMENT_AND_CLAMP,
		decrement_and_clamp = VK_STENCIL_OP_DECREMENT_AND_CLAMP,
		invert = VK_STENCIL_OP_INVERT,
		increment_and_wrap = VK_STENCIL_OP_INCREMENT_AND_WRAP,
		decrement_and_wrap = VK_STENCIL_OP_DECREMENT_AND_WRAP,
	};
}