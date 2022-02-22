#pragma once

#include "vk/headers.hpp"

namespace vk {

	enum class attachment_load_op {
		load = VK_ATTACHMENT_LOAD_OP_LOAD,
		clear = VK_ATTACHMENT_LOAD_OP_CLEAR,
		dont_care = VK_ATTACHMENT_LOAD_OP_DONT_CARE
	};

} // vk