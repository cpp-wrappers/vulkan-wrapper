#pragma once

#include "headers.hpp"

namespace vk {

	enum class cull_mode {
		none = VK_CULL_MODE_NONE,
		front = VK_CULL_MODE_FRONT_BIT,
		back = VK_CULL_MODE_BACK_BIT,
		front_and_back = VK_CULL_MODE_FRONT_AND_BACK
	};

}