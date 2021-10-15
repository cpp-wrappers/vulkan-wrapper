#pragma once

#include "../headers.hpp"

namespace vk {

enum class composite_alpha {
	opaque = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR,
	pre_multiplied = VK_COMPOSITE_ALPHA_PRE_MULTIPLIED_BIT_KHR,
	post_multiplied = VK_COMPOSITE_ALPHA_POST_MULTIPLIED_BIT_KHR,
	inherit = VK_COMPOSITE_ALPHA_INHERIT_BIT_KHR,
};

}