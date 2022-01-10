#pragma once

#include "../shared/headers.hpp"

namespace vk {

	enum class compare_op {
		never = VK_COMPARE_OP_NEVER,
		less = VK_COMPARE_OP_LESS,
		equal = VK_COMPARE_OP_EQUAL,
		less_or_equal = VK_COMPARE_OP_LESS_OR_EQUAL,
		greater = VK_COMPARE_OP_GREATER,
		not_equal = VK_COMPARE_OP_NOT_EQUAL,
		greater_or_equal = VK_COMPARE_OP_GREATER_OR_EQUAL,
		always = VK_COMPARE_OP_ALWAYS
	};

}